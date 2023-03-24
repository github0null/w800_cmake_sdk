/**
 * @file    wm_include.h
 *
 * @brief   the configuration file of sdk
 *
 * @author  winnermicro
 *
 * Copyright (c) 2014 Winner Microelectronics Co., Ltd.
 */
#ifndef __WM_INCLUDE_H__
#define __WM_INCLUDE_H__

/**
 * @mainpage WinnerMicro SDK
 *
 * Quick Start of WinnerMicro SDK.
 *
 *
 * HOW TO CODE ?
 *
 * Function UserMain(void) is the entrance function of the application:
 * @code
 * void UserMain(void)
 * {
 *     printf("\n user task\n");
 *
 * #if DEMO_CONSOLE
 *	   CreateDemoTask();
 * #endif
 *
 *     //user's task
 * }
 * @endcode
 *
 *
 * \n
 * HOW TO COMPILE ?
 *
 * To build with the SDK you can use the CDS or Make.
 * Please refer to the CDS and script compilation documentation for details.
 *
 *
 * \n
 * HOW TO DOWNLOAD THE FIRMWARE ?
 *
 * Download the "w800.fls" image
 *
 * This will download image which includes secboot & user application image into flash by ROM using xmodem-protocol for factory burning.
 * @code
 * Pulling down the bootmode pin(PA0) and reset the device. Then UART0 will output: 
 * CCC...
 * For details,please refer to the sdk manual.
 * @endcode
 *
 * Download the "w800.img" image
 *
 * This will download image which only includes user application using xmodem-protocol.
 * @code
 * Press "ESC" and then reset the device. Then UART0 will output:
 * CCC...
 * For details,please refer to the sdk manual.
 * @endcode
 *
 * \n
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "wm_type_def.h"
#include "wm_debug.h"
#include "wm_regs.h"

#include "wm_config.h"
#include "wm_ram_config.h"
#include "wm_wifi_config.h"
#include "wm_bt_config.h"

#include "list.h"
#include "random.h"

#include "arch/xt804/csi_config.h"
#include "arch/xt804/csi_core/core_804.h"
#include "arch/xt804/csi_core/csi_core.h"
#include "arch/xt804/csi_core/csi_gcc.h"
#include "arch/xt804/csi_dsp/csky_common_tables.h"
#include "arch/xt804/csi_dsp/csky_const_structs.h"
#include "arch/xt804/csi_dsp/csky_math.h"
#include "arch/xt804/csi_dsp/csky_vdsp2_const_structs.h"
#include "arch/xt804/csi_dsp/csky_vdsp2_math.h"

#include "driver/wm_7816.h"
#include "driver/wm_adc.h"
#include "driver/wm_cpu.h"
#include "driver/wm_dma.h"
#include "driver/wm_efuse.h"
#include "driver/wm_flash.h"
#include "driver/wm_flash_map.h"
#include "driver/wm_fls_gd25qxx.h"
#include "driver/wm_gpio.h"
#include "driver/wm_gpio_afsel.h"
#include "driver/wm_hostspi.h"
#include "driver/wm_hspi.h"
#include "driver/wm_i2c.h"
#include "driver/wm_i2s.h"
#include "driver/wm_internal_flash.h"
#include "driver/wm_io.h"
#include "driver/wm_irq.h"
#include "driver/wm_lcd.h"
#include "driver/wm_pmu.h"
#include "driver/wm_psram.h"
#include "driver/wm_pwm.h"
#include "driver/wm_rtc.h"
#include "driver/wm_sasc.h"
#include "driver/wm_sdio_host.h"
#include "driver/wm_timer.h"
#include "driver/wm_tipc.h"
#include "driver/wm_touchsensor.h"
#include "driver/wm_uart.h"
#include "driver/wm_watchdog.h"

#include "platform/aes.h"
#include "platform/wm_crypto_hard.h"
#include "platform/wm_crypto_hard_mbed.h"
#include "platform/wm_fwup.h"
#include "platform/wm_mem.h"
#include "platform/wm_params.h"
#include "platform/wm_wl_mbox.h"
#include "platform/wm_wl_task.h"
#include "platform/wm_wl_timers.h"

#include "os/wm_osal.h"
#include "os/wm_os_config.h"

#include "bt/wm_ble.h"
#include "bt/wm_ble_gatt.h"
#include "bt/wm_bt.h"
#include "bt/wm_bt_av.h"
#include "bt/wm_bt_def.h"
#include "bt/wm_bt_hf_client.h"
#include "bt/wm_bt_spp.h"

#include "wifi/wm_wifi.h"

#include "net/wm_socket.h"
#include "net/wm_sockets.h"

// --- export types

struct w800_img_signature_info_t {
    uint32_t sign_addr;      // 固件的签名数据地址
    uint8_t  sign_data[128]; // 固件的原始签名数据
    uint8_t  image_sha1[20]; // 固件的 sha1（从 sign_data 生成）
};

// --- export funcs

int         w800sdk_get_version_main(void);
int         w800sdk_get_version_sub(void);
int         w800sdk_get_version_revision(void);
const char *w800sdk_get_version_string(void);

int w800sdk_get_img_info(struct IMAGE_HEADER_PARAM *info);
int w800sdk_get_img_signature(struct w800_img_signature_info_t *info);

#endif
