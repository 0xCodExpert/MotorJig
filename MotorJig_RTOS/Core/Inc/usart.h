/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
/***************************************************************************************************
*	Include Files
***************************************************************************************************/
#include "uart_drv.h"
#include "define.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
/***************************************************************************************************
*	Constant Definitions
***************************************************************************************************/
#define SOH							0x01
#define STX							0x02	/* Start of message identifier */
#define ETX							0x03	/* End of message ideitifier */
#define SUB							0x1A	/* Indicates substitution for the next character */
#define ACK							0x06	/* Positive acknowledgement */
#define NAK							0x20	/* Negative acknowledgement */
#define DONE						0x08	/* Command is done */
#define NODONE						0x28	/* Command is failed */

#define RX1_MAX 		16
#define RX1_TIMEOUT		1000
#define Debug			Uart_Printf
/***************************************************************************************************
*	Type Definitions
***************************************************************************************************/
typedef unsigned char 				U8;
typedef unsigned int 				U16;
typedef bool						BOOL;
typedef uint8_t						INT8U;
typedef uint16_t					INT16U;
typedef uint32_t					INT32U;
typedef int 						STATUS;

/**
* \enum		CMD_TYPE
* \brief	?λ¦¬μΌ λͺλ Ή? μ’λ₯
*/
typedef enum
{
	CMD_TYPE_UNKNOWN,
	CMD_TYPE_BIN,
	CMD_TYPE_ASC
}CMD_TYPE;

/**
* \struct	BIN_CMD
* \brief	?΄μ§? λͺλ Ή ?¬λ§? κ΅¬μ‘°μ²?
*/
typedef struct
{
	INT8U		MainCmd;		/**< ?? λͺλ Ή?΄ 	*/
	INT8U		SubCmd;			/**< ?? λͺλ Ή?΄ 	*/
	INT16U		Address;		/**< ??κ²? μ£Όμ	*/
	INT16U		Length;			/**< ?°?΄?° κΈΈμ΄ 	*/
	INT8U		*pData;			/**< ?°?΄?° λ²νΌ 	*/
}BIN_CMD;

/**
* \struct	ASCII_CMD
* \brief	??€?€ λͺλ Ή κ΅¬μ‘°μ²?
*/
typedef struct st_ASCII_CMD
{
	INT8U		*pStr;			/**< λͺλ Ή λ¬Έμ?΄ 	*/
}ASCII_CMD;

/**
* \struct	UART_CMD
* \brief	?λ¦¬μΌ λͺλ Ή μ²λ¦¬λ₯? ?? κ΅¬μ‘°μ²?
*/
typedef struct
{
	BOOL		CmdReady;		/**< ?λ‘μ΄ λͺλ Ή?΄ ?μ°©ν?μ§? ?λ¦? */
	CMD_TYPE	CmdType;		/**< λͺλ Ή? μ’λ₯	*/
	union
	{
		BIN_CMD 	CmdBin;		/**< ?΄μ§λͺ? Ή ?¬λ§? */
		ASCII_CMD	CmdAsc;		/**< ??€?€λͺλ Ή ?¬λ§? */
	};
}UART_CMD;
/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/
/* xqueue */
xQueueHandle xQueue_UartRecv;

/* xSemaphore */
//xSemaphoreHandle xCountingSemaphore_UartRecv;
//xSemaphoreHandle xBinarySemaphore_UartRecv;
//xSemaphoreHandle xMutex;

/* xTask */
xTaskHandle xHandle_UartRecv;

/* RX1 Uart */
volatile uint8_t Rx1Data;
char Rx1Buf[RX1_MAX], Rx1Buffer[RX1_MAX];
int Rx1Cnt, Rx1Count;
volatile uint16_t Rx1TermTimer;

extern UART_HandleTypeDef huart1;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
/***************************************************************************************************
*	Function Prototypes
***************************************************************************************************/
void Uart_InitModules(void);
void Uart_InitTasks(void);
void Uart1_Irq(void);
void Uart_RecvTask(void *pvParameters);
void uart1_check(void);
UART_CMD *Uart_Parse(INT8U data);
void Uart_ResetState(void);
INT8U Uart_MakeCheckSum(INT8U *pdata, INT32U length);
void Uart_ACK(void);
void Uart_NAK(void);
void Uart_DONE(void);
void Uart_NODONE(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
