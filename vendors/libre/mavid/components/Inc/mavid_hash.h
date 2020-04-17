#ifndef __MAVID_HASH_H
#define __MAVID_HASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_conf.h"
#include "stm32f7xx_hal_hash.h"

void init_Hash(void);
int get_SHA256(uint8_t* pInBuf, uint8_t* pOutBuff, uint32_t size);
void unitTest(void);
void HASH_DMA_IRQHandler(void);

#endif //MAVID_HASH