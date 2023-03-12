#ifndef _WM_BT_APP_H
#define _WM_BT_APP_H

/*****************************************************************************
**
**  Name:           wm_bt_app.h
**
**  Description:    This file contains the sample functions for bluetooth application
**
*****************************************************************************/
#include "wm_bt.h"

int tls_at_bt_enable(int uart_no, tls_bt_log_level_t log_level, tls_bt_host_callback_t at_callback_ptr);
int tls_at_bt_destroy(void);

extern void wm_bt_init_report_list();
extern tls_bt_status_t wm_bt_register_report_evt(tls_bt_host_evt_t rpt_evt,  tls_bt_host_callback_t rpt_callback);
extern tls_bt_status_t wm_bt_deregister_report_evt(tls_bt_host_evt_t rpt_evt,  tls_bt_host_callback_t rpt_callback);

#endif
