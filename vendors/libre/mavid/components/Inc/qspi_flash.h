/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QSPI_FLASH_H
#define __QSPI_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Definition for QSPI clock resources */
#define QSPI_CLK_ENABLE()          __HAL_RCC_QSPI_CLK_ENABLE()
#define QSPI_CLK_DISABLE()         __HAL_RCC_QSPI_CLK_DISABLE()
#define QSPI_CS_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_CLK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_D0_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()
#define QSPI_D1_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()


#define QSPI_FORCE_RESET()         __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()       __HAL_RCC_QSPI_RELEASE_RESET()

/* Definition for QSPI Pins */
#define QSPI_CS_PIN                GPIO_PIN_6
#define QSPI_CS_GPIO_PORT          GPIOB
#define QSPI_CLK_PIN               GPIO_PIN_2
#define QSPI_CLK_GPIO_PORT         GPIOB
#define QSPI_D0_PIN                GPIO_PIN_11
#define QSPI_D0_GPIO_PORT          GPIOD
#define QSPI_D1_PIN                GPIO_PIN_12
#define QSPI_D1_GPIO_PORT          GPIOD

/* W25Q32FW Winbond memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE                      64
#define QSPI_PAGE_SIZE                       256
#define QSPI_BLOCK_SIZE                      64*1024

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99


/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B

#define FAST_READ_DUAL_OUT_CMD               0x3B

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG1_CMD                 0x05
#define WRITE_STATUS_REG1_CMD                0x01

/* Program Operations */
#define PAGE_PROG_CMD                        0x02

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20

#define BLOCK_ERASE_CMD                      0x62
#define BLOCK_ERASE_64_CMD                   0xD8

#define CHIP_ERASE_CMD                       0xC7

/* Default dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ              8

/* End address of the QSPI memory */
#define QSPI_END_ADDR                        0x3FFFFF


typedef enum  {
  QSPI_COMMAND,
  QSPI_COMMAND_RESPONSE,
  QSPI_ADDRESS,
  QSPI_READ,
  QSPI_WRITE
} qspi_mode;


int qSPI_open();
int qSPI_process(qspi_mode mode,uint32_t command, uint32_t address, uint32_t size, uint8_t* buffer);
void qSPI_waitFor_deviceReady();
void qSPI_write_pages(uint32_t offset, uint8_t* buf, uint32_t size);

#define EXTERNAL_NUM_IMAGES 3

#define EXTERNAL_LOAD_D2 1
#define EXTERNAL_LOAD_D4 1
#define EXTERNAL_LOAD_AMODEL 1

#define D4_MAX_SIZE 0x40000 //256KB
#define D2_MAX_SIZE 0x40000 //256KB
#define AMODEL_MAX_SIZE 0x80000 //512KB

#define D4_IMAGE_OFFSET         0x00100 
#define D2_IMAGE_OFFSET         0x40100 
#define AMODEL_IMAGE_OFFSET     0x80100 

/* image_id : 1 - d4 image , 2 - D2 image, 3 - Amodel*/
#define D4_IMAGE_ID     0
#define D2_IMAGE_ID     1
#define AMODEL_IMAGE_ID 2

#define EXTENAL_FLASH_PAGESIZE 256


typedef struct
{
  int image_id;
  int image_offset;
  int image_size;
  int reserved;
}dspg_img_header;

typedef struct
{
   int madic_id;
   int num_images;
   dspg_img_header dspg_header[EXTERNAL_NUM_IMAGES];
}ext_img_header;

#endif