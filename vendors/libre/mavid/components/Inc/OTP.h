/**

******************************************************************************
*/

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

typedef enum{
  LIBREMAC,
  CUSTMAC
}MACTYPE;

HAL_StatusTypeDef  FLASH_MAC_OTP_Write(MACTYPE type, uint64_t value);
int FLASH_MAC_OTP_Read( MACTYPE type,uint8_t * Macid);


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
