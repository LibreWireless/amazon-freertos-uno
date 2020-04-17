/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 *  Provides prototypes for initialization and other management functions for Host system
 *
 */

#ifndef INCLUDED_MHD_MANAGEMENT_H
#define INCLUDED_MHD_MANAGEMENT_H

#include "mhd_constants.h"  /* for mhd_result_t and country codes */
#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup mgmt HOST Management
 *  User functions for initialization and other management functions for the HOST system
 *  @{
 */

/******************************************************
 *             Function declarations
 ******************************************************/
/*@-exportlocal@*/

/**
 * HOST Initialisation Function
 *
 * - Initialises parts of the hardware platform used for Wi-Fi control
 *   including pins for : SDIO/SPI, interrupt, reset, power etc.
 * - Initialises the HOST thread (which arbitrates access to the SDIO/SPI bus)
 * - Sets the country code to set which radio channels are allowed
 * - Clear the events mask
 * - Bring the Wireless interface to the 'Up' state
 * - Turn off minimum power consumption feature to avoid SDIO timeouts
 *
 * @param country : enumerated country identifier, which sets the allowed
 *                  radio channels according to country regulations
 * @param buffer_interface_arg : abstract parameter which is passed
 *                        to the buffer interface during init.
 *                        Look in @ref host_buffer_init for details
 *                        of the argument required for your particular buffering system
 *
 * @return MHD_SUCCESS if initialization is successful, Error code otherwise
 */

mhd_result_t mhd_management_init( host_country_code_t country, /*@null@*/ void* buffer_interface_arg );

mhd_result_t mhd_management_deinit( void );

/**
 * Turn on the Wi-Fi device
 *
 * - Initialises the required parts of the hardware platform
 *   i.e. pins for SDIO/SPI, interrupt, reset, power etc.
 *
 * - Bring the Wireless interface "Up"
 * - Initialises the Host thread which arbitrates access
 *   to the SDIO/SPI bus
 *
 * @return MHD_SUCCESS if initialization is successful, Error code otherwise
 */
mhd_result_t mhd_management_wifi_on( void );
mhd_result_t mhd_management_wifi_On_Cont( void );

/**
 * Turn off the Wi-Fi device
 *
 * - De-Initialises the required parts of the hardware platform
 *   i.e. pins for SDIO/SPI, interrupt, reset, power etc.
 *
 * - Bring the Wireless interface "Down"
 * - De-Initialises the Host thread which arbitrates access
 *   to the SDIO/SPI bus
 *
 * @return MHD_SUCCESS if deinitialization is successful, Error code otherwise
 */
mhd_result_t mhd_management_wifi_off( void );

mhd_result_t mhd_management_wifi_is_on(void);

/*@+exportlocal@*/

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ifndef INCLUDED_MHD_MANAGEMENT_H */
