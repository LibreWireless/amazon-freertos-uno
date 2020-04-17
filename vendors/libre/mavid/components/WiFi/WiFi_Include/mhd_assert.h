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
 *  Defines macro for assertions
 *
 */
#pragma once

#include "mhd_debug.h"
#include "platform_assert.h"




#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 * @cond       Macros
 ******************************************************/

#ifdef MHD_DEBUG
    #ifdef WPRINT_ENABLE_ERROR
        #define WPRINT_ERROR(args)                      do { WPRINT_MACRO(args); HOST_ASSERTION_FAIL_ACTION(); } while(0)
        #define host_assert( error_string, assertion ) do { if (!(assertion)) { HOST_ASSERTION_FAIL_ACTION(); } } while(0)
    #else
        #define WPRINT_ERROR(args)                      do { HOST_ASSERTION_FAIL_ACTION();} while(0)
        #define host_assert( error_string, assertion ) do { if (!(assertion)) { HOST_ASSERTION_FAIL_ACTION();} } while(0)
    #endif
#else
    #define host_assert( error_string, assertion ) do { if (!(assertion)) { PRINTF("\tW_Assert: ");PRINTF(error_string);PRINTF("\n");} } while(0)
#endif

#define host_minor_assert( error_string, assertion )

/** @endcond */

#ifdef __cplusplus
} /* extern "C" */
#endif
