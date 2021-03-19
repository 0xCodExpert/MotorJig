/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;

/* USER CODE BEGIN Private defines */
/***************************************************************************************************
*	Constant Definitions
***************************************************************************************************/
#define TMR_ID_SYSTEM 		0
#define TMR_ID_UART			1
#define TMR_ID_HEARTBEAT	2

/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/
/* xTimer */
xTimerHandle xTimer_Uart;

extern __IO uint16_t cap_first;
extern __IO uint32_t cap_freq;
extern __IO uint32_t cap_duty;

extern __IO uint32_t cap_1_2;
extern __IO uint32_t cap_1_3;

extern __IO uint16_t cap_1;
extern __IO uint16_t cap_2;
extern __IO uint16_t cap_3;

volatile uint16_t ledTogTimer;
volatile uint16_t TimSetTimer;
volatile uint16_t TestTimer;
volatile uint16_t TestResult;
bool Rx1PkFlag;

/* USER CODE END Private defines */

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM6_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
/***************************************************************************************************
*	Function Prototypes
***************************************************************************************************/
void Timer_1ms(void);
void Timer_InitTasks(void);
void Timer_TimeOut(TimerHandle_t xTimer);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
