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
 *  Cryptographic function header
 *
 *  Provides prototypes of cryptographic functions for use in applications
 */

#ifndef INCLUDED_MHD_CRYPTO_H
#define INCLUDED_MHD_CRYPTO_H

#include <stdint.h>
#include "host_utilities.h"
#include "mhd_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup wifi HOST Wi-Fi
 *  @{
 */

/******************************************************
 *             Function declarations
 ******************************************************/

/**
 * Gets a 16 bit random number from the Wi-Fi device
 *
 * Allows user applications to retrieve 16 bit random numbers.
 * Random numbers are generated on the Broadcom Wi-Fi chip using a
 * 47-bit PRBS generator in the hardware MAC.
 *
 * @param val : pointer to a variable which will receive the
 *              generated random number
 *
 * @return MHD_SUCCESS or Error code
 */

extern mhd_result_t mhd_wifi_get_random( void* buffer, uint16_t buffer_length );

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ifndef INCLUDED_MHD_CRYPTO_H */
