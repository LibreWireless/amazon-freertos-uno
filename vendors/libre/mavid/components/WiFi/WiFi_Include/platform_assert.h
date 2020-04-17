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
 * Defines macros for defining asserts for ARM-Cortex-M3 CPU
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Micky add ++
#include "my_print.h"

//#define HOST_TRIGGER_BREAKPOINT() __asm("bkpt 0")
#define HOST_TRIGGER_BREAKPOINT() PRINTF("\nassert bkpt 0 %s, %d\r\n", __FILE__, __LINE__)
#define HOST_ASSERTION_FAIL_ACTION() HOST_TRIGGER_BREAKPOINT()
// Micky add --

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/


#if defined ( __GNUC__ )

#if defined ( __clang__ )

static inline /*@noreturn@*/void HOST_TRIGGER_BREAKPOINT( void ) __attribute__((analyzer_noreturn))
{
    __asm__("bkpt");
}

#else

#if defined ( LINT ) /* Lint requires a prototype */

extern /*@noreturn@*/ void HOST_TRIGGER_BREAKPOINT( void );

#else /* #if defined ( LINT ) */

//#define HOST_TRIGGER_BREAKPOINT( ) __asm__("bkpt")

#endif /* #if defined ( LINT ) */

#endif /* #if defined ( __clang__ ) */


#define HOST_ASSERTION_FAIL_ACTION() HOST_TRIGGER_BREAKPOINT()

#define HOST_DISABLE_INTERRUPTS() { __asm__("CPSID i"); }

#define HOST_ENABLE_INTERRUPTS() { __asm__("CPSIE i"); }

#elif defined ( __IAR_SYSTEMS_ICC__ )

// Micky
//#include <cmsis_iar.h>

//#define HOST_TRIGGER_BREAKPOINT() __asm("bkpt 0")

#define HOST_ASSERTION_FAIL_ACTION() HOST_TRIGGER_BREAKPOINT()

#define HOST_DISABLE_INTERRUPTS() { __asm("CPSID i"); }

#define HOST_ENABLE_INTERRUPTS() { __asm("CPSIE i"); }

#endif

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

#ifdef __cplusplus
} /*extern "C" */
#endif
