/**
  ******************************************************************************
  * @file    hardware_rng.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    30-December-2016
  * @brief   Entropy data generation function using the STM32 RNG.
  *   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#if !defined( MBEDTLS_CONFIG_FILE )
    #include "mbedtls/config.h"
#else
    #include MBEDTLS_CONFIG_FILE
#endif

#ifdef MBEDTLS_ENTROPY_HARDWARE_ALT

//#include "main.h"

#include "stm32f7xx_hal_conf.h"
#include "stm32f7xx_hal_sdram.h"
#include "stm32f7xx_hal_dma2d.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rng.h"
#include "stm32f769i_eval.h"
//#include "stm32f769i_eval_lcd.h"
#include "stm32f769i_eval_io.h"


#include <string.h>

#include "mbedtls/entropy_poll.h"

#include "lib.h"

extern RNG_HandleTypeDef RngHandle;

int mbedtls_hardware_poll( void *Data, unsigned char *Output, size_t Len, size_t *oLen )
{
  uint32_t index;
  uint32_t randomValue;
		
  for (index = 0; index < Len/4; index++)
  {
    if (HAL_RNG_GenerateRandomNumber(&RngHandle, &randomValue) == HAL_OK)
    {
      *oLen += 4;
      memset(&(Output[index * 4]), (int)randomValue, 4);
    }
    else
    {
      fatal("HAL_RNG_GenerateRandomNumber failed..");
      //Error_Handler();
    }
  }
  
  return 0;
}


int mbedtls_randomnumber_generate( void *Data, unsigned char *Output, size_t Len, size_t *oLen )
{
  uint32_t index,i=0,j=0;;
  uint32_t randomValue;
  uint8_t  *p = (uint8_t  *)&randomValue;                   
  for (index = 0; index < Len/8; index++)
  {
    if (HAL_RNG_GenerateRandomNumber(&RngHandle, &randomValue) == HAL_OK)
    {
      *oLen += 8;
      j=0;
      for(i =0;i < 8;i= i+2)
      {
        sprintf(&Output[(index * 8) + i],"%d%d",(p[j] & 0x0f ),((p[j] >> 4) & 0x0f ));
        j++;
      }
    }
    else
    {
      fatal("HAL_RNG_GenerateRandomNumber failed..");
      //Error_Handler();
    }
  }
  
  return 0;
}

#endif /*MBEDTLS_ENTROPY_HARDWARE_ALT*/
