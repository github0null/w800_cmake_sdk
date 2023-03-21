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

extern volatile tls_bt_state_t bt_adapter_state;

int tls_ble_enable(int uart_no, tls_bt_log_level_t log_level);

int tls_ble_destroy(void);

#endif
