/***********************************************************************************************//**
* \file	  uart_drv.h
* \brief  UART 드라이버
* \author Gone
* <pre>
* Ver   Date       Changes
* ----- ---------- -----------------------------------------------
* 00.01 2020/11/17 file generated
* </pre>
*
***************************************************************************************************/

#ifndef __UART_DRV_H__
#define __UART_DRV_H__

/***************************************************************************************************
*	Include Files
***************************************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

/***************************************************************************************************
*	Constant Definitions
***************************************************************************************************/
#define UART_BUF_SIZE					256

/***************************************************************************************************
*	Type Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Macros (Inline Functions) Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Function Prototypes
***************************************************************************************************/
void Uart_SendByte(char data);
void Uart_RecvByte(char data);
void Uart_SendString(char* string);
void Uart_Printf(const char *fmt, ...);

#ifdef __GNUC__
int __io_putchar(int ch);
#else
int fputc(int ch, FILE *f);
#endif /* __GNUC__ */

#endif	/* #ifndef __UART_DRV_H__ */