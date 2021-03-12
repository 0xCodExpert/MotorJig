/*
 * key.c
 *
 *  Created on: 2020. 8. 30.
 *      Author: lilol
 */

#include "main.h"
#include "common.h"
#include "key.h"

#define KEY_STATE_UP					1
#define KEY_STATE_DEBOUNCE				2
#define KEY_STATE_RPT_START_DLY			3
#define KEY_STATE_RPT_DLY				4

KEY Key;

static uint8_t KeyGetCol(void);
static bool KeyIsKeyDown(void);
static uint8_t KeyDecode(void);
static void KeyBufIn(KEY *Key, uint8_t code);

static uint8_t KeyGetCol(void)
{
	uint8_t col = 0x00;

	if( HAL_GPIO_ReadPin(KEY_01_GPIO_PORT, KEY_01_GPIO_PIN) == GPIO_PIN_RESET ){
		col |= 0x01;
	}
	if( HAL_GPIO_ReadPin(KEY_02_GPIO_PORT, KEY_02_GPIO_PIN) == GPIO_PIN_RESET ){
		col |= 0x02;
	}

	return col;
}

static void KeyBufIn(KEY* Key, uint8_t code)
{
	if( Key->NRead < KEY_BUF_SIZE ){
		Key->NRead++;
		Key->Buf[Key->BufInIx++] = code;
		if( Key->BufInIx >= KEY_BUF_SIZE ){
			Key->BufInIx = 0;
		}
	}
}

static bool KeyIsKeyDown(void)
{
	if( KeyGetCol() & ((1 << KEY_MAX_COLS) - 1) ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

static uint8_t KeyDecode(void)
{
	uint8_t col;
	bool done;
	uint8_t col_id;
	uint8_t msk;

	col = KeyGetCol();

	msk = 0x01;
	col_id = 0;
	done = FALSE;
	while( col_id < KEY_MAX_NUM && !done ){
		if( col & msk ){
			done = TRUE;
		}
		else{
			col_id++;
			msk <<= 1;
		}
	}

	return col_id;
}

bool KeyHit(KEY* Key)
{
	bool hit;

	hit = (bool)(Key->NRead > 0) ? TRUE : FALSE;

	return hit;
}

uint8_t KeyGetKey(KEY* Key)
{
	uint8_t code;

	if( Key->NRead > 0 ){
		Key->NRead--;
		code = Key->Buf[Key->BufOutIx];
		Key->BufOutIx++;
		if( Key->BufOutIx >= KEY_BUF_SIZE ){
			Key->BufOutIx = 0;
		}

		return code;
	}
	else{
		return 0xFF;
	}
}

void KeyInit(KEY* Key)
{
	Key->ScanState = KEY_STATE_UP;
	Key->NRead = 0;
	Key->BufInIx = 0;
	Key->BufOutIx = 0;
}

void KeyScanTask(KEY* Key)
{
	uint8_t code;

	switch( Key->ScanState ){
	case KEY_STATE_UP:
		if( KeyIsKeyDown() ){
			Key->ScanState = 	KEY_STATE_DEBOUNCE;
		}
		break;

	case KEY_STATE_DEBOUNCE:
		if( KeyIsKeyDown() ){
			code = KeyDecode();
			KeyBufIn(Key, code);
			Key->RptStartDlyCtr = KEY_RPT_START_DLY;
			Key->ScanState = KEY_STATE_RPT_START_DLY;
		}
		else{
			Key->ScanState = KEY_STATE_UP;
		}
		break;

	case KEY_STATE_RPT_START_DLY:
		if( KeyIsKeyDown() ){
			if( Key->RptStartDlyCtr > 0 ){
				Key->RptStartDlyCtr--;
				if( Key->RptStartDlyCtr == 0 ){
					code = KeyDecode();
					KeyBufIn(Key, code);
					Key->RptDlyCtr = KEY_RPT_DLY;
					Key->ScanState = KEY_STATE_RPT_DLY;
				}
			}
		}
		else{
			Key->ScanState = KEY_STATE_DEBOUNCE;
		}
		break;

	case KEY_STATE_RPT_DLY:
		if( KeyIsKeyDown() ){
			if( Key->RptDlyCtr > 0 ){
				Key->RptDlyCtr--;
				if( Key->RptDlyCtr == 0 ){
					code = KeyDecode();
					KeyBufIn(Key, code);
					Key->RptDlyCtr = KEY_RPT_DLY;
				}
			}
		}
		else{
			Key->ScanState = KEY_STATE_DEBOUNCE;
		}
		break;
	}
}








