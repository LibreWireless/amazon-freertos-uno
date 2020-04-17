/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_SDIO_MHD_BUS_PROTOCOL_H
#define INCLUDED_SDIO_MHD_BUS_PROTOCOL_H

#include "mhd_buffer.h"

//HT**
//#include "platform/mhd_sdio_interface.h"
#include "mhd_sdio_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *             Constants
 ******************************************************/

/******************************************************
 *             Structures
 ******************************************************/

#undef MHD_BUS_HAS_HEADER

#define MHD_BUS_HEADER_SIZE               ( 0 )

/* Reserved length for SDPCM header, generally the larger of the TX and RX headers */
#define MHD_SDPCM_HEADER_RESERVED_LENGTH  ( 18 )

/* SDPCM transmit header length */
#define MHD_SDPCM_HEADER_TX_LENGTH        ( MHD_SDPCM_HEADER_RESERVED_LENGTH )

/* SDPCM receive header length */
#define MHD_SDPCM_HEADER_RX_LENGTH        ( MHD_SDPCM_HEADER_RESERVED_LENGTH )

/******************************************************
 *             Function declarations
 ******************************************************/


/******************************************************
 *             Global variables
 ******************************************************/

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_SDIO_MHD_BUS_PROTOCOL_H */
