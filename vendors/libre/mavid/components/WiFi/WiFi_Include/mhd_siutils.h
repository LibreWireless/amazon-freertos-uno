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
 */

#ifndef INCLUDED_MHD_SI_UTILS_H_
#define INCLUDED_MHD_SI_UTILS_H_

#include <stdint.h>
#include "mhd_constants.h"
#include "chip_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WLAN_ARMCM3_BASE_ADDRESS

/* Register offsets */
#define	SR_COREINFO		0x00
#define	SR_BANKINDEX		0x10
#define	SR_BANKINFO		0x40

/*
 * In corerev 1 the bank size is 2 ^ the bank size field plus 14,
 * the memory size is number of banks times bank size.
 * The same applies to rom size.
 */
#define	SRCI_SRNB_MASK		0xf0
#define	SRCI_SRNB_SHIFT		4

/* bankinfo rev >= 10 */
#define SOCRAM_BANKINFO_RETNTRAM_MASK		0x00010000

#define SOCRAM_BANKIDX_MEMTYPE_SHIFT	8
/* socram bankinfo memtype */
#define SOCRAM_MEMTYPE_RAM		0

/* bank info to calculate bank size */
#define   SOCRAM_BANKINFO_SZBASE          8192

/* bankidx and bankinfo reg defines corerev >= 8 */
#define SOCRAM_BANKINFO_SZMASK		0x7f

uint32_t si_socram_srmem_size( void );

#endif

#ifdef WLAN_ARMCR4_BASE_ADDRESS
mhd_result_t si_set_reset_instruction( const uint8_t *fw_image );
#endif

uint32_t si_chip_ram_size( void );
mhd_result_t si_chip_info( uint32_t *chip_id, uint32_t *chip_rev );
mhd_result_t si_bus_info( uint32_t *bus_rev );

mhd_result_t dump_cccr_reg_info(void);
mhd_result_t dump_sdio_stats(void);


#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_SI_UTILS_H_ */
