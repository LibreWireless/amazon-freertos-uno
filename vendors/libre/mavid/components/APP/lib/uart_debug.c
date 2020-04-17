/**
 Libre Wireless Technologies
 **/

//Dependencies
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f769i_eval.h"
//#include "stm32f769i_eval_lcd.h"
#include "debug.h"

//Variable declaration
static unsigned int  lcdLine = 0;
static unsigned int  lcdColumn = 0;
static UART_HandleTypeDef UART_Handle;

#define MIN(a,b) (((a)<(b))?(a):(b))

/**
 * @brief Set cursor location
 * @param[in] line Line number
 * @param[in] column Column number
 **/

void lcdSetCursor(unsigned int  line, unsigned int  column)
{
    lcdLine = MIN(line, 20);
    lcdColumn = MIN(column, 50);
}


/**
 * @brief Write a character to the LCD display
 * @param[in] c Character to be written
 **/

void lcdPutChar(char c)
{
    if(c == '\r')
    {
        lcdColumn = 0;
    }
    else if(c == '\n')
    {
        lcdColumn = 0;
        lcdLine++;
    }
    else if(lcdLine < 20 && lcdColumn < 50)
    {
        //Display current character
        BSP_LCD_DisplayChar(lcdColumn * 16, lcdLine * 24, c);

        //Advance the cursor position
        if(++lcdColumn >= 50)
        {
            lcdColumn = 0;
            lcdLine++;
        }
    }
}


/**
 * @brief Debug UART initialization
 * @param[in] baudrate UART baudrate
 **/

void debugInit(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    //Enable USART1 clock
    __HAL_RCC_USART1_CLK_ENABLE();

    //Configure USART1_TX (PA9) and USART1_RX (PA10)
    GPIO_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    GPIO_InitStructure.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Configure USART1
    UART_Handle.Instance = USART1;
    UART_Handle.Init.BaudRate = baudrate;
    UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    UART_Handle.Init.StopBits = UART_STOPBITS_1;
    UART_Handle.Init.Parity = UART_PARITY_NONE;
    UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART_Handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART_Handle);
}


/**
 * @brief Display the contents of an array
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @param[in] prepend String to prepend to the left of each line
 * @param[in] data Pointer to the data array
 * @param[in] length Number of bytes to display
 **/

void debugDisplayArray(FILE *stream,
                       const char *prepend, const void *data, size_t length)
{
    unsigned int  i;

    for(i = 0; i < length; i++)
    {
        //Beginning of a new line?
        if((i % 16) == 0)
            fprintf(stream, "%s", prepend);
        //Display current data byte
        fprintf(stream, "%02" "PRIX8" " ", *((uint8_t *) data + i));
        //End of current line?
        if((i % 16) == 15 || i == (length - 1))
            fprintf(stream, "\r\n");
    }
}


/**
 * @brief Write character to stream
 * @param[in] c The character to be written
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @return On success, the character written is returned. If a writing
 *   error occurs, EOF is returned
 **/

int fputc(int c, FILE *stream)
{
#if 0
    //Standard output?
    if(stream == stdout)
    {
        //Display current character
        lcdPutChar(c);

        //On success, the character written is returned
        return c;
    }
    //Standard error output?
    else if(stream == stderr)
#endif
    {
        //Character to be written
        uint8_t ch = c;

        //Transmit data
        HAL_UART_Transmit(&UART_Handle, &ch, 1, HAL_MAX_DELAY);

        //On success, the character written is returned
        return c;
    }
#if 0
    //Unknown output?
    else
    {
        //If a writing error occurs, EOF is returned
        return EOF;
    }
#endif
}
