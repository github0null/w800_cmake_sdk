#ifndef __WM_BLE_WIFI_INCLUDE_H__
#define __WM_BLE_WIFI_INCLUDE_H__

#include "wm_bt.h"
#include "host/ble_hs.h"
#include "host/ble_gap.h"

#define TLS_BLE_GAP_NAME_MAX_LEN MYNEWT_VAL(BLE_SVC_GAP_DEVICE_NAME_MAX_LENGTH)

typedef int (app_gap_evt_cback_t)(struct ble_gap_event *event, void *arg);

extern int tls_ble_gap_init(void);
extern int tls_ble_gap_deinit(void);
extern int tls_nimble_gap_adv(wm_ble_adv_type_t type , int duration);
extern int tls_ble_gap_set_adv_param(uint8_t adv_type, uint32_t min, uint32_t max, uint8_t chn_map, uint8_t filter_policy,uint8_t *dir_mac, uint8_t dir_mac_type);
extern int tls_ble_gap_set_scan_param(uint32_t window, uint32_t intv, uint8_t filter_policy, bool limited, bool passive, bool filter_duplicate);
extern int tls_ble_gap_set_name(char *dev_name, uint8_t update_flash);
extern int tls_ble_gap_get_name(char *dev_name);
extern int tls_ble_gap_set_data(wm_ble_gap_data_t type, uint8_t *data, int data_len);
extern int tls_ble_gap_scan(wm_ble_scan_type_t type, bool filter_duplicate);
extern int tls_ble_register_gap_evt(uint32_t evt_type, app_gap_evt_cback_t *evt_cback);
extern int tls_ble_deregister_gap_evt(uint32_t evt_type, app_gap_evt_cback_t *evt_cback);



#endif
