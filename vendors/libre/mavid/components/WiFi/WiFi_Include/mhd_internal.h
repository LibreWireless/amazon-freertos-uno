/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#ifndef INCLUDED_MHD_INTERNAL_H
#define INCLUDED_MHD_INTERNAL_H

#include <stdint.h>
#include "mhd_constants.h" /* for mhd_result_t */

//HT**
//#include "network/mhd_network_interface.h"
#include "mhd_network_interface.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *             Constants
 ******************************************************/

typedef enum
{
    /* Note : If changing this, core_base_address must be changed also */
    WLAN_ARM_CORE    = 0,
    SOCRAM_CORE = 1,
    SDIOD_CORE  = 2
} device_core_t;

typedef enum
{
    WLAN_DOWN,
    WLAN_UP
} wlan_state_t;

typedef enum
{
    WLAN_CORE_FLAG_NONE,
    WLAN_CORE_FLAG_CPU_HALT,
} wlan_core_flag_t;

/******************************************************
 *             Structures
 ******************************************************/

typedef struct
{
    wlan_state_t         state;
    host_country_code_t country_code;
    uint32_t             keep_wlan_awake;
} mhd_wlan_status_t;

#define MHD_WLAN_KEEP_AWAKE( )  do { mhd_wlan_status.keep_wlan_awake++; } while (0)
#define MHD_WLAN_LET_SLEEP( )   do { mhd_wlan_status.keep_wlan_awake--; } while (0)
#define MHD_WLAN_MAY_SLEEP()     ( ( mhd_wlan_status.keep_wlan_awake == 0 ) && ( mhd_wlan_status.state == WLAN_UP ) )

/******************************************************
 *             Function declarations
 ******************************************************/

extern host_bool_t mhd_wifi_ap_is_up;
extern uint8_t      mhd_tos_map[8];


/* Device core control functions */
extern mhd_result_t mhd_disable_device_core    ( device_core_t core_id, wlan_core_flag_t core_flag );
extern mhd_result_t mhd_reset_device_core      ( device_core_t core_id, wlan_core_flag_t core_flag );
extern mhd_result_t mhd_device_core_is_up      ( device_core_t core_id );
extern mhd_result_t mhd_wifi_set_down          ( void );
extern mhd_result_t mhd_wifi_set_up            ( void );
extern void         mhd_set_country            ( host_country_code_t code );

/* Chip specific functions */
extern mhd_result_t mhd_allow_wlan_bus_to_sleep( void );
extern mhd_result_t mhd_ensure_wlan_bus_is_up  ( void );

extern mhd_result_t mhd_chip_specific_init     ( void );
#ifdef MHD_FAST_BOOT_SUPPORT
extern mhd_result_t mhd_chip_specific_resume   ( void );
#endif
#if ( BRCM_CHIP_FAMILY == 4343 ) // Only needed by bcm4343x
extern mhd_result_t mhd_disable_sram3_remap    ( void );
#endif

/******************************************************
 *             Global variables
 ******************************************************/

extern mhd_wlan_status_t mhd_wlan_status;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_INTERNAL_H */
