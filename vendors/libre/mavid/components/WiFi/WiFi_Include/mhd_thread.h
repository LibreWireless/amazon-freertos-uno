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
 *  The Host Thread allows thread safe access to the Host hardware bus
 *  This is an Host internal file and should not be used by functions outside Host.
 *
 *  This file provides prototypes for functions which allow multiple threads to use the Host hardware bus (SDIO or SPI)
 *  This is achieved by having a single thread (the "Host Thread") which queues messages to be sent, sending
 *  them sequentially, as well as receiving messages as they arrive.
 *
 *  Messages to be sent come from the @ref mhd_sdpcm_send_common function in mhd_sdpcm.c .  The messages already
 *  contain SDPCM headers, but not any bus headers (GSPI), and are passed via a queue
 *  This function can be called from any thread.
 *
 *  Messages are received by way of a callback supplied by in mhd_sdpcm.c - mhd_sdpcm_process_rx_packet
 *  Received messages are delivered in the context of the Host Thread, so the callback function needs to avoid blocking.
 *
 */

#ifndef INCLUDED_MHD_THREAD_H_
#define INCLUDED_MHD_THREAD_H_

#include "mhd_buffer.h"
#include "mhd_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Micky modify for LiteOS
#if defined(__LITEOS_VER__)
#define MHD_THREAD_PRIORITY   RTOS_DEFAULT_THREAD_PRIORITY
#else
#define MHD_THREAD_PRIORITY   RTOS_HIGHEST_PRIORITY
#endif

/** Initialises the Host Thread
 *
 * Initialises the Host thread, and its flags/semaphores,
 * then starts it running
 *
 * @return    host result code
 */
extern mhd_result_t mhd_thread_init( void )  /*@modifies internalState@*/;


/** Terminates the Host Thread
 *
 * Sets a flag then wakes the Host Thread to force it to terminate.
 *
 */
extern void mhd_thread_quit( void );


extern void mhd_thread_notify( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_THREAD_H_ */
