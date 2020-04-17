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

#include "mhd_constants.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                   Enumerations
 ******************************************************/

typedef enum
{
    MHD_RESOURCE_WLAN_FIRMWARE,
    MHD_RESOURCE_WLAN_NVRAM,
} mhd_resource_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

extern mhd_result_t host_platform_resource_size( mhd_resource_t resource, uint32_t* size_out );

/*
 * This function is used when MHD_DIRECT_RESOURCES is defined
 */
extern mhd_result_t host_platform_resource_read_direct( mhd_resource_t resource, const void** ptr_out );

/*
 * This function is used when MHD_DIRECT_RESOURCES is not defined
 */
extern mhd_result_t host_platform_resource_read_indirect( mhd_resource_t resource, uint32_t offset, void* buffer, uint32_t buffer_size, uint32_t* size_out );
extern uint8_t * host_platform_resource_get_ptr( uint32_t offset );


#ifdef __cplusplus
} /* extern "C" */
#endif
