/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#include "platform_peripheral.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/**
 * WLAN control pins
 */
typedef enum
{
    MHD_PIN_POWER,
    MHD_PIN_RESET,
    MHD_PIN_32K_CLK,
    MHD_PIN_BOOTSTRAP_0,
    MHD_PIN_BOOTSTRAP_1,
    MHD_PIN_CONTROL_MAX,
} mhd_control_pin_t;

/**
 * WLAN SDIO pins
 */
typedef enum
{
    MHD_PIN_SDIO_OOB_IRQ,
    MHD_PIN_SDIO_CLK,
    MHD_PIN_SDIO_CMD,
    MHD_PIN_SDIO_D0,
    MHD_PIN_SDIO_D1,
    MHD_PIN_SDIO_D2,
    MHD_PIN_SDIO_D3,
    MHD_PIN_SDIO_MAX,
} mhd_sdio_pin_t;

/**
 * WLAN SPI pins
 */
typedef enum
{
    MHD_PIN_SPI_IRQ,
    MHD_PIN_SPI_CS,
    MHD_PIN_SPI_CLK,
    MHD_PIN_SPI_MOSI,
    MHD_PIN_SPI_MISO,
    MHD_PIN_SPI_MAX,
} mhd_spi_pin_t;

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/* Externed from <HOST-SDK>/platforms/<Platform>/platform.c */
#if 0
extern const platform_gpio_t wifi_control_pins[];
extern const platform_gpio_t wifi_sdio_pins   [];
extern const platform_gpio_t wifi_spi_pins    [];
#else
extern  platform_gpio_t wifi_control_pins[];
extern  platform_gpio_t wifi_sdio_pins   [];
extern  platform_gpio_t wifi_spi_pins    [];
#endif

/******************************************************
 *               Function Declarations
 ******************************************************/

#ifdef __cplusplus
} /*extern "C" */
#endif
