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
 *  Defines the Bus part of the HOST Platform Interface.
 *
 *  Provides prototypes for functions that allow HOST to start and stop
 *  the hardware communications bus for a platform.
 */

//HT**
//#include "network/mhd_buffer_interface.h"
#include "mhd_buffer_interface.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup platif Platform Interface
 *  @{
 */

/** @name Bus Functions
 *  Functions that enable HOST to start and stop
 *  the hardware communications bus for a paritcular platform.
 */
/**@{*/

/******************************************************
 *             Function declarations
 ******************************************************/

/**
 * Initializes the HOST Bus
 *
 * Implemented in the HOST Platform interface which is specific to the
 * platform in use.
 * This function should set the bus GPIO pins to the correct modes,  set up
 * the interrupts for the HOST bus, enable power and clocks to the bus, and
 * set up the bus peripheral.
 *
 * @return MHD_SUCCESS or Error code
 */
extern mhd_result_t host_platform_bus_init( void );

/**
 * De-Initializes the HOST Bus
 *
 * Implemented in the HOST Platform interface which is specific to the
 * platform in use.
 * This function does the reverse of @ref host_platform_bus_init
 *
 * @return MHD_SUCCESS or Error code
 */
extern mhd_result_t host_platform_bus_deinit( void );


/**
 * Informs MHD of an interrupt
 *
 * This function should be called from the SDIO/SPI interrupt function
 * and usually indicates newly received data is available.
 * It wakes the MHD Thread, forcing it to check the send/receive
 *
 */
extern void mhd_thread_notify_irq( void );


/**
 * Enables the bus interrupt
 *
 * This function is called by HOST during init, once
 * the system is ready to receive interrupts
 */
extern mhd_result_t host_platform_bus_enable_interrupt( void );

/**
 * Disables the bus interrupt
 *
 * This function is called by HOST during de-init, to stop
 * the system supplying any more interrupts in preparation
 * for shutdown
 */
extern mhd_result_t host_platform_bus_disable_interrupt( void );


/**
 * Informs the platform bus implementation that a buffer has been freed
 *
 * This function is called by HOST during buffer release to allow
 * the platform to reuse the released buffer - especially where
 * a DMA chain needs to be refilled.
 */
extern void host_platform_bus_buffer_freed( mhd_buffer_dir_t direction );

extern int host_platform_sdio_set_f2_block_size( unsigned int blksz );

/** @} */
/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif
