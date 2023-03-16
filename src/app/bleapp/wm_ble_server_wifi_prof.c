#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "wm_bt_config.h"

#if (WM_NIMBLE_INCLUDED == CFG_ON)


#include "wm_bt_util.h"
#include "host/ble_hs.h"
#include "wm_ble_gap.h"
#include "wm_ble_server_wifi_app.h"
#include "wm_ble_server_wifi_prof.h"


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

static wm_ble_wifi_prof_callbacks_t  *ps_wifi_prof_callback = NULL;
static uint8_t wm_ble_wifi_prof_connected = 0;

/* ble wifi attr write/notify handle */
uint16_t g_blewifi_attr_write_and_notify_handle;
uint16_t g_blewifi_conn_handle;
uint8_t g_blewifi_prof_disconect_reason;



#define WM_BLE_WIFI_SERVICE_UUID        0x1824
#define WM_BLE_WIFI_WRITE_INDICATE_UUID 0x2ABC


static int
gatt_svr_chr_access_wifi_write_and_notify(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg);


/*
 * LOCAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */

static int
gatt_svr_chr_access_wifi_write(uint16_t conn_handle, uint16_t attr_handle,
                              struct ble_gatt_access_ctxt *ctxt, void *arg);


static const struct ble_gatt_svc_def gatt_wifi_svr_svcs[] = {
    {
        /* Service: uart */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(WM_BLE_WIFI_SERVICE_UUID),
        .characteristics = (struct ble_gatt_chr_def[]) { {
            .uuid = BLE_UUID16_DECLARE(WM_BLE_WIFI_WRITE_INDICATE_UUID),
            .val_handle = &g_blewifi_attr_write_and_notify_handle,
            .access_cb = gatt_svr_chr_access_wifi_write_and_notify,
            .flags = BLE_GATT_CHR_F_INDICATE|BLE_GATT_CHR_F_WRITE,
        },{
            0, /* No more characteristics in this service */
        } },
    },

    {
        0, /* No more services */
    },
};

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static int
gatt_svr_chr_access_wifi_write_and_notify(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    struct os_mbuf *om = ctxt->om;
    switch (ctxt->op) {
        case BLE_GATT_ACCESS_OP_WRITE_CHR:
              while(om) {
                  TLS_HAL_CBACK(ps_wifi_prof_callback, write_cb, 0, (uint8_t *)om->om_data, om->om_len, 0);
                  om = SLIST_NEXT(om, om_next);
              }
              return 0;
        default:
            assert(0);
            return BLE_ATT_ERR_UNLIKELY;
    }
}

int
blewifi_gatt_svr_init(void)
{
    int rc;

    rc = ble_gatts_count_cfg(gatt_wifi_svr_svcs);
    if (rc != 0) {
        goto err;
    }

    rc = ble_gatts_add_svcs(gatt_wifi_svr_svcs);
    if (rc != 0) {
        return rc;
    }

err:
    return rc;
}
static void update_data_length(void *arg)
{
    ble_gap_set_data_length(g_blewifi_conn_handle, BLE_HCI_SET_DATALEN_TX_OCTETS_MAX, 0x200);
}
static int ble_gap_evt_cb(struct ble_gap_event *event, void *arg)
{
    switch(event->type)
    {
        case BLE_GAP_EVENT_CONNECT:
            wm_ble_wifi_prof_connected = 1;
            g_blewifi_prof_disconect_reason = 0;
            g_blewifi_conn_handle = event->connect.conn_handle;
            TLS_BT_APPL_TRACE_DEBUG("connected handle=%d,g_blewifi_attr_write_and_notify_handle=%d\r\n",g_blewifi_conn_handle, g_blewifi_attr_write_and_notify_handle );
            TLS_HAL_CBACK(ps_wifi_prof_callback, connected_cb, 0);
            //tls_bt_async_proc_func(update_data_length,NULL, 10);
            break;
        case BLE_GAP_EVENT_DISCONNECT:
            wm_ble_wifi_prof_connected = 0;
            TLS_BT_APPL_TRACE_DEBUG("disconnect reason=0x%02x(%d)\r\n", (event->disconnect.reason-0x200),event->disconnect.reason);
            TLS_HAL_CBACK(ps_wifi_prof_callback, disconnected_cb, event->disconnect.reason);
            if(g_blewifi_prof_disconect_reason)
            {
                //hci error code:  0x16 + 0x200 = 534; //local host terminate the connection;
                tls_ble_deregister_gap_evt(WM_BLE_GAP_EVENT_CONNECT|WM_BLE_GAP_EVENT_DISCONNECT|WM_BLE_GAP_EVENT_NOTIFY_TX|WM_BLE_GAP_EVENT_MTU, ble_gap_evt_cb);
                ps_wifi_prof_callback = NULL;
                g_blewifi_prof_disconect_reason = 0;
            }
            break;
        case BLE_GAP_EVENT_NOTIFY_TX:
            if(event->notify_tx.status == BLE_HS_EDONE)
            {
                TLS_HAL_CBACK(ps_wifi_prof_callback, indication_cb, 0);
            }else
            {
                /*Application will handle other cases*/
            }
            break;
       case BLE_GAP_EVENT_MTU:
            TLS_BT_APPL_TRACE_DEBUG("wm ble dm mtu changed to(%d)\r\n", event->mtu.value);
            TLS_HAL_CBACK(ps_wifi_prof_callback, mtu_changed_cb, event->mtu.value);
            break;
        default:
            break;
    }

    return 0;
}

/*
 * EXPORTED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

int tls_ble_wifi_adv(bool enable)
{
    int rc;
    
    if(enable)
    {
        struct ble_hs_adv_fields fields;
        uint8_t adv_ff_data[] = {0x0C, 0x07, 0x00, 0x10};
        /**
         *  Set the advertisement data included in our advertisements:
         *     o Flags (indicates advertisement type and other general info).
         *     o Device name.
         *     o user specific field (winner micro).
         */
        
        memset(&fields, 0, sizeof fields);
        
        /* Advertise two flags:
         *     o Discoverability in forthcoming advertisement (general)
         *     o BLE-only (BR/EDR unsupported).
         */
        fields.flags = BLE_HS_ADV_F_DISC_GEN |
                       BLE_HS_ADV_F_BREDR_UNSUP;
        
        const char *name = ble_svc_gap_device_name();
        fields.name = (uint8_t *)name;
        fields.name_len = strlen(name);
        fields.name_is_complete = 1;
        
        fields.mfg_data = adv_ff_data;
        fields.mfg_data_len = 4;
        
        rc = ble_gap_adv_set_fields(&fields);
        if (rc != 0) {
            TLS_BT_APPL_TRACE_ERROR("error setting advertisement data; rc=%d\r\n", rc);
            return rc;
        }


        
        /* As own address type we use hard-coded value, because we generate
              NRPA and by definition it's random */
        rc = tls_nimble_gap_adv(WM_BLE_ADV_IND, 0);

    }else
    {
        rc = ble_gap_adv_stop();

    }
    return rc;
}

int tls_ble_wifi_prof_init(wm_ble_wifi_prof_callbacks_t *callback)
{
	int rc = 0;
    
    if(ps_wifi_prof_callback == NULL)
    {
        wm_ble_wifi_prof_connected = 0;
    	ps_wifi_prof_callback = callback;
        
        rc = blewifi_gatt_svr_init();

		if(rc == 0)
		{	
		    tls_ble_register_gap_evt(WM_BLE_GAP_EVENT_CONNECT|WM_BLE_GAP_EVENT_DISCONNECT|WM_BLE_GAP_EVENT_NOTIFY_TX|WM_BLE_GAP_EVENT_MTU, ble_gap_evt_cb);
			TLS_BT_APPL_TRACE_DEBUG("### wm_wifi_prof_init success\r\n");
            TLS_HAL_CBACK(ps_wifi_prof_callback, enabled_cb, rc);
		}else
		{
			ps_wifi_prof_callback = NULL;
			TLS_BT_APPL_TRACE_ERROR("### wm_ble_server_register_server failed\r\n");
		}
    }
    else
    {
    	TLS_BT_APPL_TRACE_WARNING("wm_ble_server_register_server registered\r\n");
        rc = BLE_HS_EALREADY;
    }
	
	return rc;
}
int tls_ble_wifi_prof_deinit(int reason)
{
	int rc = 0;
    
    if(ps_wifi_prof_callback)
    {
        TLS_HAL_CBACK(ps_wifi_prof_callback, enabled_cb, reason);
        if(wm_ble_wifi_prof_connected == 0)
        {
            tls_ble_deregister_gap_evt(WM_BLE_GAP_EVENT_CONNECT|WM_BLE_GAP_EVENT_DISCONNECT|WM_BLE_GAP_EVENT_NOTIFY_TX|WM_BLE_GAP_EVENT_MTU, ble_gap_evt_cb);
            ps_wifi_prof_callback = NULL;   //this ptr will be cleared, when got deregister event
        }else
        {
            //this ptr will be freed when disconected with remote device;
        }
    }else
    {
    	TLS_BT_APPL_TRACE_WARNING("wm_wifi_prof_deinit deinited already\r\n");
		rc = BLE_HS_EALREADY;
    }

    return rc;
}

int tls_ble_wifi_prof_disconnect(int status)
{
    g_blewifi_prof_disconect_reason = status;
    return ble_gap_terminate(g_blewifi_conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

int tls_ble_wifi_prof_send_msg(uint8_t *data, int data_len)
{
    int rc;
    struct os_mbuf *om;

    if(data_len<=0 || data == NULL)
    {
        return BLE_HS_EINVAL;
    }
    
    om = ble_hs_mbuf_from_flat(data, data_len);
    if (!om) {
        return BLE_HS_ENOMEM;
    }
    
    rc = ble_gattc_indicate_custom(g_blewifi_conn_handle,
                            g_blewifi_attr_write_and_notify_handle, om);    
    return rc;
}

#endif



