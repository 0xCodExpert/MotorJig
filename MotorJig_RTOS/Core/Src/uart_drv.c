/***********************************************************************************************//**
* \file	  uart_drv.c
* \brief  UART 드라이버
* \author Gone
* <pre>
* Ver   Date       Changes
* ----- ---------- -----------------------------------------------
* 00.01 2020/11/17 file generated
* </pre>
*
***************************************************************************************************/

/***************************************************************************************************
*	Include Files
***************************************************************************************************/
#include "uart_drv.h"

/***************************************************************************************************
*	Constant Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Type Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Macros (Inline Functions) Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/
static uint8_t UartBuf[UART_BUF_SIZE];
static uint8_t UartBufInIx;
static uint8_t UartBufOutIx;
static uint8_t UartNRead;

/***********************************************************************************************//**
* \brief
* \param
* \param
* \return
* \note
***************************************************************************************************/
void Uart_SendByte(char data)
{
	taskENTER_CRITICAL();
	while((USART1->ISR & UART_FLAG_TXE) == 0); //Wait for empty transmit buffer?
	USART1->TDR = data;
	taskEXIT_CRITICAL();
}

/***********************************************************************************************//**
* \brief
* \param
* \param
* \return
* \note
***************************************************************************************************/
void Uart_RecvByte(char data)
{
	while((USART1->ISR & UART_FLAG_TXE) == 0); //Wait for empty transmit buffer?
	USART1->TDR = data;
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_SendString(char* string)
{
	//while(*string != '\0')
	while (*string)
	{
		Uart_SendByte(*string);
		string++;
	};
}

/***********************************************************************************************//**
* \brief	printf대신 사용하는 함수
* \param
* \return
* \note
***************************************************************************************************/
void Uart_Printf(const char *fmt, ...)
{
	va_list ap;
	char string[64];

	va_start(ap, fmt);
	taskENTER_CRITICAL();
	vsprintf(string, fmt, ap);
	taskEXIT_CRITICAL();
	/*
	* do not use HAL_UART_Transmit in FreeRTOS testing
	* data can not be transmitted in this function in case of HAL_UART_STATE_BUSY_TX
	* HAL_UART_STATE_READY must be set before transmitting new string.
	* HAL_UART_STATE_READY will be set after transmitting the string completely.
	*/
	//HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), (uint32_t)-1);

	for (int k=0; k<strlen(string); k++)
	{
		Uart_SendByte(string[k]);
	}

	va_end(ap);
}

/***********************************************************************************************//**
* \brief	printf 사용하기 위한 함수
* \param
* \return
* \note
***************************************************************************************************/
#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_VarInit(void)
{
	UartBufInIx = 0;
	UartBufOutIx = 0;
	UartNRead = 0;
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
bool Uart_Hit(void)
{
	bool hit;
	hit = (bool)(UartNRead > 0)? TRUE : FALSE;
	return hit;
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_BufIn(uint8_t data)
{
	if(UartNRead < UART_BUF_SIZE){
		UartNRead++;
		UartBuf[UartBufInIx] = data;
		UartBufInIx++;
		if(UartBufInIx >= UART_BUF_SIZE){
			UartBufInIx = 0;
		}
	}
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
uint8_t Uart_BufOut(void)
{
	uint8_t data;
	if(UartNRead > 0){
		UartNRead--;
		data = UartBuf[UartBufOutIx];
		UartBufOutIx++;
		if(UartBufOutIx >= UART_BUF_SIZE){
			UartBufOutIx = 0;
		}
		return data;
	}
	else{
		return 0xFF;
	}
}
