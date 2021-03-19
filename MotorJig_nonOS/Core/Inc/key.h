/*
 * key.h
 *
 *  Created on: 2020. 8. 30.
 *      Author: lilol
 */

#ifndef _KEY_H_
#define _KEY_H_

#include <stdbool.h>

#define KEY_01_GPIO_PORT			GPIOC
#define KEY_01_GPIO_PIN				GPIO_PIN_12

#define KEY_02_GPIO_PORT			GPIOD
#define KEY_02_GPIO_PIN				GPIO_PIN_2

#define KEY_BUF_SIZE				10

#define KEY_MAX_ROWS				2
#define KEY_MAX_COLS				2

#define KEY_MAX_NUM					2

#define KEY_RPT_DLY					2
#define KEY_RPT_START_DLY			10

#define KEY_SHIFT1_MASK				0x80
#define KEY_SHIFT1_OFFSET			4

#define KEY_SHIFT2_MASK				0x40
#define KEY_SHIFT2_OFFSET			8

#define KEY_ALL_ROWS				KEY_MAX_ROWS

typedef struct {
	uint8_t Buf[KEY_BUF_SIZE];
	uint8_t BufInIx;
	uint8_t BufOutIx;
	uint8_t NRead;

	uint8_t RptStartDlyCtr;
	uint8_t RptDlyCtr;

	uint8_t ScanState;
} KEY;

extern KEY Key;

bool KeyHit(KEY *Key);
uint8_t KeyGetKey(KEY *Key);
void KeyInit(KEY *Key);
void KeyScanTask(KEY *Key);

#endif
