/**
 * @file    wm_ram_config.h
 *
 * @brief   WM ram model configure
 *
 * @author  winnermicro
 *
 * Copyright (c) 2015 Winner Microelectronics Co., Ltd.
 */
#ifndef __WM_RAM_CONFIG_H__
#define __WM_RAM_CONFIG_H__

#include "wm_config.h"

extern unsigned int __heap_start;
extern unsigned int __heap_end;
extern unsigned int __hspi_buf_start;
extern unsigned int __wifi_buf_start;

#define SLAVE_HSPI_SDIO_ADDR ((unsigned int)(&__hspi_buf_start)) // 8KB
#define WIFI_MEM_START_ADDR  ((unsigned int)(&__wifi_buf_start)) // 50KB

#endif /*__WM_RAM_CONFIG_H__*/
