/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
/***************************************************************************************************
*	Include Files
***************************************************************************************************/
#include "uart_drv.h"

/***************************************************************************************************
*	Type Definitions
***************************************************************************************************/
/**
* \enum	UART_STATE
* \brief	UART Parser ?��?�� 리스?��
*/
typedef enum
{
	UART_STATE_IDLE,	/**< Idle */
	UART_STATE_ASCII,	/**< ASCII 명령 ?��?�� */
	UART_STATE_BIN,		/**< BIN 명령 ?��?�� */
	UART_STATE_BIN_ETX,	/**< BIN 명령 ?��?�� ?���? */
	UART_STATE_BUSY		/**< 명령 처리�? */
}UART_STATE;

/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/
static	INT32U		UartRecvCount;
static	INT8U		*UartRecvBuf;
static	UART_STATE	UartState;
static	UART_CMD	UartCmd;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/***********************************************************************************************//**
* \brief	1Byte Receive ISR
* \param
* \return
* \note
***************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		Uart1_Irq();
	}
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note		?��?��?��?�� callback ?��?�� ?���??��?��?�� task_EXIT_CRITICAL_FROM_ISR ?��?��?��?��?��
***************************************************************************************************/
void Uart1_Irq(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint8_t rx1Data;
	/* 방법0: ?��?�� 버퍼 비슷?���? 만들?��?�� �??��?��?���? 버퍼?�� ???�� */
	rx1Data = USART1->RDR;
	Uart_BufIn(rx1Data);
	//Uart_SendByte(rx1Data);

//	vTaskNotifyGiveFromISR(xHandle_UartRecv, &xHigherPriorityTaskWoken);
	//	Rx1Buf[Rx1Cnt++]=USART1->RDR;
	//	if(Rx1Cnt >= RX1_MAX)	Rx1Cnt = 0;
	//	Rx1TermTimer = 10;

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

	/* uart Interrupt Ready Again */
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&Rx1Data,1);

	/* 방법1: Queue�? ?��?��?��?�� 1byte?�� RecvThread?�� ?��?�� */
//하핳하
//
//	if( xQueueSendToBackFromISR( xQueue_UartRecv, (void*)&Rx1Data, &xHigherPriorityTaskWoken ) != pdPASS)
//	{
//		Debug("xQueueSendToBackFromISR was not executed successfully.\r\n");
//	}
//
//	/* Now the buffer is empty we can switch context if necessary. */
//    if( xHigherPriorityTaskWoken )
//    {
//        /* Actual macro used here is port specific. */
//    	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
//    }
//
//    /* uart Interrupt Ready Again */
//    HAL_UART_Receive_IT(&huart1, (uint8_t*)&Rx1Data, 1);

	/* 방법2:Software Timer Start ?��?�� timeout?�� callback ?��?��?��?��
	   RX1Buf?�� ?��?�� ?��?��?���? ?��?�� ?��?��?�� ?��?��*/
//	Rx1Buf[Rx1Cnt++]=USART1->RDR;
//	if(Rx1Cnt >= RX1_MAX)	Rx1Cnt = 0;

//    if( xTimerStartFromISR( xTimer_Uart, &xHigherPriorityTaskWoken ) != pdPASS )
//    {
//    	Debug("xTimerStartFromISR was not executed successfully.\r\n");
//    }
//
//    /* uart Interrupt Ready Again */
//    HAL_UART_Receive_IT(&huart1, (uint8_t*)&Rx1Data, 1);

	/* 방법3: Semaphore ?��?��?��?�� 법인?�� ?�� 방법보다?��
	vTaskNotifyGiveFromISR(xHandle_UartRecv, NULL); 방식?�� ?�� 빠르�? 좋다*/
//	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

//	xSemaphoreGiveFromISR(xBinarySemaphore_UartRecv, &xHigherPriorityTaskWoken);
//	xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );

//	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);

//	/* uart Interrupt Ready Again */
//	HAL_UART_Receive_IT(&huart1,(uint8_t *)&Rx1Data,1);
}

/***********************************************************************************************//**
* \brief	?�� ?��?��?�� ?��?��?��?�� ?��?��?�� ?��?��림을 ?��?��?��?��, binary 명령, ascii 명령, ?��?�� ?���?
*			벤더?�� 명령?���?�? 구분?��?�� ?��?��?�� ?��?��?���? ?��?�� 버퍼?�� ?���?, 명령?��?��?�� ?��?��?��?�� ?���?
*			?���? ?��?�� 명령?�� ???�� ?��?��그�?? ?��?��?��?�� 명령?�� ?��?��?��?��?�� ?��?��주는 ?��?��?��?��.
* \param	data
* \return
* \note		?��?��?�� ?��버는 기본?��?���? byte ?��?��?��?��.  byte ?��?��?�� ?��?��?�� ???��?�� �?�? ?��?��?���? ?��?��?��
*			경우 data alignment?�� 주의?��?��.
***************************************************************************************************/
UART_CMD *Uart_Parse(INT8U data)
{
	static INT16U	data_len;
	INT8U			checksum;

	switch(UartState)
	{
		case UART_STATE_IDLE:
			switch(data)
			{
				case STX:
					//Tmr_StartTimer(TMR_ID_UART, CFG_UART_TIMEOUT, (void(*)(void *))Uart_TimeOut, NULL);
					UartState = UART_STATE_BIN;
					break;
				case '\b':
				case '\n':
					UartState = UART_STATE_IDLE;
					break;
				case '\r':
					printf("\r\n");
					//printf(CFG_PROMPT);
					UartState = UART_STATE_IDLE;
					break;
#ifdef CONFIG_LINEEDIT
				case ESC:
					UartRecvBuf[UartRecvCount++] = data;
					line_edit((char *)UartRecvBuf);
					historylog((char *)UartRecvBuf);
					UartCmd.CmdReady			= TRUE;
					UartCmd.CmdType				= CMD_TYPE_ASC;
					UartCmd.CmdAsc.pStr	= UartRecvBuf;

					UartState = UART_STATE_BUSY;
					break;
#endif
				default:
					if(isgraph(data) || isspace(data))	/* ?��?���??�� 문자, 공백?�� 경우�? ascii 명령?���? ?��?�� */
					{
						UartRecvCount = 0;
						UartRecvBuf[UartRecvCount++] = data;
						printf("%c", data);
						UartState = UART_STATE_ASCII;
					}
					break;
			}
			break;
		case UART_STATE_ASCII:
			switch(data)
			{
				case '\r':
				case '\n':
					UartRecvBuf[UartRecvCount] = '\0';
					printf("\r\n");
#ifdef CONFIG_LINEEDIT
					historylog((char *)UartRecvBuf);
#endif
					UartCmd.CmdReady		= TRUE;
					UartCmd.CmdType			= CMD_TYPE_ASC;
					UartCmd.CmdAsc.pStr		= UartRecvBuf;

					UartState = UART_STATE_BUSY;
					break;
//				case '\n':
//					UartState = UART_STATE_IDLE;
//					break;
				case '\b' :
					UartRecvBuf[--UartRecvCount] = 0;
					printf("\b \b");
					UartState = UartRecvCount ? UART_STATE_ASCII : UART_STATE_IDLE;
					break;
#ifdef CONFIG_LINEEDIT
				case ESC:
					UartRecvBuf[UartRecvCount++] = data;
					line_edit((char *)UartRecvBuf);
					historylog((char *)UartRecvBuf);
					UartCmd.CmdReady			= TRUE;
					UartCmd.CmdType				= CMD_TYPE_ASC;
					UartCmd.CmdAsc.pStr	= UartRecvBuf;

					UartState = UART_STATE_BUSY;
					break;
#endif
				default :
					if(isgraph(data) || isspace(data))	/* ?��?���??�� 문자, 공백?�� 경우�? ascii 명령?���? ?��?�� */
					{
						UartRecvBuf[UartRecvCount++] = data;
						printf("%c", data);
						if(UartRecvCount >= CFG_UART_BUF_SIZE)	/* 버퍼 ?��?��즈�?? 초과?�� 경우 리셋 */
						{
							Uart_ResetState();
						}
					}
					else
					{
						Uart_ResetState();
					}
					break;
			}
			break;
		case UART_STATE_BIN:
			UartRecvBuf[UartRecvCount++] = data;
			if(UartRecvCount == 6)
			{
				data_len = ntohs(*(INT16U *)(UartRecvBuf + 4));
			}
			/* At the point transmission ends, total length = cmd(2) + addr(2) + length(2) + data_len + checksum(1) */
			else if(UartRecvCount == (INT32U)(data_len + 7))
			{
				UartState = UART_STATE_BIN_ETX;
			}
			else if(UartRecvCount >= CFG_UART_BUF_SIZE)
			{
				//Tmr_StopTimer(TMR_ID_UART);
				Uart_ResetState();
			}
			break;
		case UART_STATE_BIN_ETX:
			//Tmr_StopTimer(TMR_ID_UART);
			checksum = UartRecvBuf[UartRecvCount - 1];
			if((data == ETX) && (Uart_MakeCheckSum(UartRecvBuf, UartRecvCount - 1) == checksum))
			{
				UartCmd.CmdReady 			= TRUE;
				UartCmd.CmdType	 			= CMD_TYPE_BIN;
				UartCmd.CmdBin.MainCmd		= UartRecvBuf[0];
				UartCmd.CmdBin.SubCmd		= UartRecvBuf[1];
				UartCmd.CmdBin.Address		= ntohs(*(INT16U *)(UartRecvBuf + 2));
				UartCmd.CmdBin.Length		= ntohs(*(INT16U *)(UartRecvBuf + 4));
				/* ?��?��?�� 버퍼?�� alignment 문제�? ?��?���? ?��?�� 4byte?��?�� align */
				memmove(UartRecvBuf, UartRecvBuf + 6, UartCmd.CmdBin.Length);
				UartCmd.CmdBin.pData		= UartRecvBuf;

				Uart_ACK();
				UartState = UART_STATE_BUSY;
			}
			else
			{
				Uart_NAK();
				Uart_ResetState();
			}
			break;
		case UART_STATE_BUSY:
			printf("Error: Processing another command.\r\n");
			break;
		default:
			Uart_ResetState();
			break;
	}

	return &UartCmd;
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_InitModules(void)
{
	xQueue_UartRecv = xQueueCreate(64, sizeof(Rx1Data));
	Uart_VarInit();
//	xCountingSemaphore_UartRecv = xSemaphoreCreateCounting(1, 0);
//	vSemaphoreCreateBinary(xBinarySemaphore_UartRecv);
//	xMutex = xSemaphoreCreateMutex();
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_InitTasks(void)
{
	xTaskCreate(Uart_RecvTask,				/* Function that implements the task. */
			    "Receive",					/* Text name for the task. */
				configMINIMAL_STACK_SIZE,	/* Stack size in words, not bytes. */
				NULL,						/* Parameter passed into the task. */
				osPriorityAboveNormal4,		/* Priority at which the task is created. */
				&xHandle_UartRecv);			/* Used to pass out the created task's handle. */
}

/***********************************************************************************************//**
* \brief
* \param
* \return
* \note
***************************************************************************************************/
void Uart_RecvTask(void *pvParameters)
{

//	char rx1Buf[RX1_MAX];
	uint8_t rx1Data;
//	portBASE_TYPE xStatus;
//	portTickType xLastWakeTime;
//	const portTickType xTicksToWait = 10 / portTICK_RATE_MS;

//	xLastWakeTime = xTaskGetTickCount();
	UART_CMD		*pcmd;

	for (;;)
	{
//		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//Flag ???�� ?��?��(OS Control available)
		while( !Uart_Hit() ){
			vTaskDelay(10);
		}
		taskENTER_CRITICAL();
//		if( Uart_Hit() ){
			rx1Data = Uart_BufOut();
//		}
		taskEXIT_CRITICAL();
//		Uart_SendByte(rx1Data);
//		xStatus = xQueueReceive(xQueue_UartRecv, (void*)&rx1Data, portMAX_DELAY);
//		if (xStatus != pdPASS)
//		{
//			Debug("xQueueReceive was not executed successfully.\r\n");
//		}
//		else
//		{
//			Uart_SendByte(rx1Data);
//		}
//		xSemaphoreTake(xBinarySemaphore_UartRecv, portMAX_DELAY);


//        xStatus = xQueueSendToBack(xQueue_UartRecv, &Rx1Buf, xTicksToWait);
//        if (xStatus != pdPASS)
//        {
//            Debug("Could not send to the queue.\r\n");
//        }
//
//		vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_RATE_MS));

		pcmd = Uart_Parse(rx1Data);
		if(pcmd->CmdReady)
		{
			switch(pcmd->CmdType)
			{
				case CMD_TYPE_BIN:
					//BinCmd_Parse(&(pcmd->CmdBin));
					break;
				case CMD_TYPE_ASC:
					//AscCmd_Parse(&(pcmd->CmdAsc));
					//printf(CFG_PROMPT);
					break;
				default:
					Debug("Unknown command type\r\n");
					break;
			}
			Uart_ResetState();
		}

	}
}
/***********************************************************************************************//**
* \brief	명령?�� ?��?��기의 ?��?���? 초기�? ?��?��리는 ?��?��
* \return
* \note		명령?�� 처리�? ?��?�� ?��마다 ?�� ?��?���? ?��출해?�� ?��?��.
***************************************************************************************************/
void Uart_ResetState(void)
{
	UartRecvCount 	= 0;
	UartState		= UART_STATE_IDLE;
	memset(&UartCmd, 0, sizeof(UartCmd));
}

/***********************************************************************************************//**
* \brief	BIN 명령?�� ???�� ACK�? ?��?��?��?�� ?��?��
* \return
* \note
***************************************************************************************************/
void Uart_ACK(void)
{
	INT8U data[3];

	data[0] = STX;
	data[1] = ACK;
	data[2] = ETX;

	Uart_SendString( (char*)data);
}

/***********************************************************************************************//**
* \brief	BIN 명령?�� ???�� NACK�? ?��?��?��?�� ?��?��
* \return
* \note
***************************************************************************************************/
void Uart_NAK(void)
{
	INT8U data[3];

	data[0] = STX;
	data[1] = NAK;
	data[2] = ETX;

	Uart_SendString( (char*)data);
}

/***********************************************************************************************//**
* \brief	BIN 명령?�� ???�� DONE?�� ?��?��?��?�� ?��?��
* \return
* \note
***************************************************************************************************/
void Uart_DONE(void)
{
	INT8U data[3];

	data[0] = STX;
	data[1] = DONE;
	data[2] = ETX;

	Uart_SendString( (char*)data);
}

/***********************************************************************************************//**
* \brief	BIN 명령?�� ???�� NODONE?�� ?��?��?��?�� ?��?��
* \return
* \note
***************************************************************************************************/
void Uart_NODONE(void)
{
	INT8U data[3];

	data[0] = STX;
	data[1] = NODONE;
	data[2] = ETX;

	Uart_SendString( (char*)data);
}

/***********************************************************************************************//**
* \brief	BIN 명령?�� 체크?��?�� 계산?��?��. byte ?��?���? ?��?��?�� 결과값을 리턴?��?��.
* \param	pdata	?��?��?�� 버퍼
* \param	length	?��?��?�� 길이
* \return
* \note
***************************************************************************************************/
INT8U Uart_MakeCheckSum(INT8U *pdata, INT32U length)
{
	INT8U 	checksum;
	INT32U 	i;

	checksum = 0;
	for(i = 0; i < length; i++)
	{
		checksum += pdata[i];
	}

	return checksum;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
