/***********************************************************************************************//**
* \file	  define.h
* \brief  UART 드라이버
* \author Gone
* <pre>
* Ver   Date       Changes
* ----- ---------- -----------------------------------------------
* 00.01 2020/11/17 file generated
* </pre>
*
***************************************************************************************************/

#ifndef __DEFINE_H__
#define __DEFINE_H__

/***************************************************************************************************
*	Include Files
***************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>

/* System Include */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "cmsis_os.h"
#include "portmacro.h"

#include "timers.h"
#include "usart.h"
#include "tim.h"

/* User Include */
#include "main.h"
#include "uart_drv.h"
/***************************************************************************************************
*	Constant Definitions
***************************************************************************************************/
#define TRUE			1
#define FALSE 			0
#define CFG_BIN_PACKET_MAX_SIZE		512
#define CFG_UART_BUF_SIZE			(CFG_BIN_PACKET_MAX_SIZE + 32)	/* 명령 버퍼 크기 : BIN 명령 최대 패킷크기(512) + margin */
#define htons(x)					((INT16U)(x))
#define htonl(x)					((INT32U)(x))
#define htonll(x)					((INT64U)(x))
#define ntohs(x)					((INT16U)(x))
#define ntohl(x)					((INT32U)(x))
#define ntohll(x)					((INT64U)(x))

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

typedef union {
	U8 flag;
	struct {
		unsigned bit0:1;
		unsigned bit1:1;
		unsigned bit2:1;
		unsigned bit3:1;
		unsigned bit4:1;
		unsigned bit5:1;
		unsigned bit6:1;
		unsigned bit7:1;
	}bitf;
} bitDef;

bitDef sts1,sts2;

#define	 	RXTest			sts1.bitf.bit0
/***************************************************************************************************
*	Macros (Inline Functions) Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Variable Definitions
***************************************************************************************************/


/***************************************************************************************************
*	Function Prototypes
***************************************************************************************************/




#endif	/* #ifndef __DEFINE_H__ */
