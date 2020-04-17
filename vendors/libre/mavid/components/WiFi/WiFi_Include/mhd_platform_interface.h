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

/** @file
 *  Defines the Non-Bus part of the HOST Platform Interface.
 *
 *  Provides prototypes for functions that allow HOST to use
 *  the hardware platform.
 */

#include "mhd_bus_protocol_interface.h"

#include "mhd_constants.h" /* for mhd_result_t */

//#include "network/mhd_buffer_interface.h" /* for host_buffer_t */
#include "mhd_buffer_interface.h" /* for host_buffer_t */

#include "mhd_wifi.h" /* For host_mac_t */

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *             Constants
 ******************************************************/

#if defined(__LITEOS_VER__) && defined(MHD_RX_BUFFER_ALLOC_ONCE)
#ifndef ETH_PAD_SIZE
#define ETH_PAD_SIZE                    2
#endif
#endif

#define F0_WORKING_TIMEOUT_MS (500)
#define F1_AVAIL_TIMEOUT_MS   (500)
#define F2_AVAIL_TIMEOUT_MS   (500)
#define F2_READY_TIMEOUT_MS   (1000)
#define ALP_AVAIL_TIMEOUT_MS  (100)
#define HT_AVAIL_TIMEOUT_MS   (500)
#define ABORT_TIMEOUT_MS      (100)
/* Taken from FALCON_5_90_195_26 dhd/sys/dhd_sdio.c. */
#define SDIO_F2_WATERMARK     (8)

#define WLAN_BUS_UP_ATTEMPTS  (1000)

#define INITIAL_READ   4

#define BUS_PROTOCOL_LEVEL_MAX_RETRIES  8

#define VERIFY_RESULT( x )  { mhd_result_t verify_result; verify_result = (x); if ( verify_result != MHD_SUCCESS ) { host_assert("command failed",0==1); printf("\tret=%d\n", verify_result); return verify_result; } }

#ifndef MHD_BUS_SDIO_RESET_DELAY
#define MHD_BUS_SDIO_RESET_DELAY    (1)
#endif

#ifndef MHD_BUS_SDIO_AFTER_RESET_DELAY
#define MHD_BUS_SDIO_AFTER_RESET_DELAY    (1)
#endif

#define MHD_OVERFLOW_BLKSZ512_WM		96
#define MHD_OVERFLOW_BLKSZ512_MES		80

/******************************************************
 *             Structures
 ******************************************************/

#pragma pack(1)
typedef struct
{
    unsigned char stuff_bits;
    unsigned int  ocr :24;
} sdio_cmd5_argument_t;

typedef struct
{
    unsigned int  _unique2         : 9; /* 0-8   */
    unsigned int  register_address :17; /* 9-25  */
    unsigned int  _unique          : 2; /* 26-27 */
    unsigned int  function_number  : 3; /* 28-30 */
    unsigned int  rw_flag          : 1; /* 31    */
} sdio_cmd5x_argument_t;

typedef struct //HT**
{
  union 
  {
    uint32_t dWord;
    struct{
    uint32_t  write_data       : 8;        /* 0 - 7 */
    uint32_t  _stuff2          : 1;        /* 8     */
    uint32_t  register_address :17;        /* 9-25  */
    uint32_t  _stuff           : 1;        /* 26    */
    uint32_t  raw_flag         : 1;        /* 27    */
    uint32_t  function_number  : 3;        /* 28-30 */
    uint32_t  rw_flag          : 1;        /* 31    */
    }bits;
  };
} mhd_bus_sdio_cmd52_argument_t;

typedef struct
{
  union 
  {
    uint32_t dWord;
    struct{

    uint32_t  count            : 9; /* 0-8   */
    uint32_t  register_address :17; /* 9-25  */
    uint32_t  op_code          : 1; /* 26    */
    uint32_t  block_mode       : 1; /* 27    */
    uint32_t  function_number  : 3; /* 28-30 */
    uint32_t  rw_flag          : 1; /* 31    */
    }bits;
  };
  
} mhd_bus_sdio_cmd53_argument_t;


typedef struct
{
  union 
  {
    uint32_t dWord;
    struct{  
    uint32_t  readData  :8   ;          //  Read data  :   8; /* 0-7   */
    uint32_t  flags     :8   ;          //  Response flags :8; /* 8-15  */
    uint32_t  stuffs    :16  ;     //  NU :16; /* 16-31  */
    }bits; 
  };  
} mhd_bus_sdio_cmd52_cmd53_response_t;


typedef union
{
    uint32_t              value;
    sdio_cmd5_argument_t  cmd5;
    sdio_cmd5x_argument_t cmd5x;
    mhd_bus_sdio_cmd52_argument_t cmd52;
    mhd_bus_sdio_cmd53_argument_t cmd53;
} sdio_cmd_argument_t;

typedef struct
{
    unsigned int  ocr              :24; /* 0-23  */
    unsigned int  stuff_bits       : 3; /* 24-26 */
    unsigned int  memory_present   : 1; /* 27    */
    unsigned int  function_count   : 3; /* 28-30 */
    unsigned int  c                : 1; /* 31    */
} sdio_response4_t;

typedef struct
{
    uint8_t       data;                /* 0-7   */
    uint8_t       response_flags;       /* 8-15  */
    uint16_t      stuff;               /* 16-31 */
} sdio_response5_t;

typedef struct
{
    uint16_t      card_status;          /* 0-15  */
    uint16_t      rca;                 /* 16-31 */
} sdio_response6_t;

typedef union
{
    uint32_t                    value;
    sdio_response4_t            r4;
    sdio_response5_t            r5;
    sdio_response6_t            r6;
} sdio_response_t;

#pragma pack()
  
    
/** @addtogroup platif Platform Interface
 * Enables HOST to use the hardware platform.
 *  @{
 */

/** @name General Platform Functions
 *  Functions that enable HOST to use the hardware platform.
 */
/**@{*/

/******************************************************
 *             Function declarations
 ******************************************************/


/**
 * Switches the Reset signal to the Broadcom Wi-Fi
 *
 * HOST uses this function to switch the reset
 * signal to the Broadcom Wi-Fi chip. It should
 * toggle the appropriate GPIO pins.
 *
 * @param reset_asserted: HOST_TRUE  = reset asserted
 *                        HOST_FALSE = reset de-asserted
 */
/*@external@*/ extern void host_platform_reset_wifi( host_bool_t reset_asserted );

/**
 * Switches the Power signal to the Broadcom Wi-Fi
 *
 * HOST uses this function to switch the
 * power signal to the Broadcom Wi-Fi chip. It should
 * toggle the appropriate GPIO pins.
 *
 * @param power_enabled : HOST_TRUE  = power up
 *                        HOST_FALSE = power down
 */
/*@external@*/ extern void host_platform_power_wifi( host_bool_t power_enabled );

/**
 * Initialises platform for HOST
 *
 * Sets up parts of the hardware platform which are not
 * directly part of the bus. These may include: Reset Pin
 * and Regulator-On Pin.
 *
 * @return MHD_SUCCESS or Error code
 */
/*@external@*/ extern mhd_result_t host_platform_init( void );

/**
 * De-Initialises platform for HOST
 *
 * Does the opposite to the @ref host_platform_init function,
 * leaving the Broadcom Wi-Fi in a powered down, reset
 * state.
 *
 * @return MHD_SUCCESS or Error code
 */
/*@external@*/ extern mhd_result_t host_platform_deinit( void );


/**
 * Disable power saving modes that would stop clocks
 */
/*@external@*/ extern void host_platform_clocks_needed( void );

/**
 * Enable power saving modes that would stop clocks
 */
/*@external@*/ extern void host_platform_clocks_not_needed( void );

/**
 * The host MCU can provide a MAC address to the Wi-Fi driver (rather than
 * the driver using the MAC in NVRAM or OTP). To use this functionality,
 * add a global define (MAC_ADDRESS_SET_BY_HOST) in the application makefile.
 * Further information is available in the generated_mac_address.txt file
 * that is created during the application build process.
 * @param mac : A host_mac_t pointer to the Wi-Fi MAC address
 */
/*@external@*/ extern mhd_result_t host_platform_get_mac_address( host_mac_t* mac );

/**
 * Returns the current CPU cycle count.
 *
 * This function is used to accurately calculate sub-systick timing.
 */
/*@external@*/ extern uint32_t host_platform_get_cycle_count( void );

/**
 * Returns TRUE if the CPU is currently running in interrupt context
 *
 */
/*@external@*/ extern host_bool_t host_platform_is_in_interrupt_context( void );

extern mhd_result_t host_platform_init_wlan_powersave_clock( void );

extern mhd_result_t host_platform_deinit_wlan_powersave_clock( void );


extern mhd_result_t mhd_bus_sdio_cmd52 ( mhd_bus_transfer_direction_t direction, mhd_bus_function_t function, uint32_t address, /*@in@*/ /*@out@*/ uint8_t * dataPtr, sdio_response_needed_t response_expected, /*@out@*/ uint8_t* response );
extern mhd_result_t mhd_bus_sdio_cmd53 ( mhd_bus_transfer_direction_t direction, mhd_bus_function_t function, sdio_transfer_mode_t mode, uint32_t address, uint16_t data_size, /*@in@*/ /*@out@*/  uint8_t* dataPtr, sdio_response_needed_t response_expected, /*@null@*/ /*@out@*/ uint32_t* response );




/** @} */
/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif
