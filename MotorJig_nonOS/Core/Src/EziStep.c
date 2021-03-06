#include "main.h"
#include "common.h"
#include "EziStep.h"
#include <string.h>

EZISTEP EziStep;

void EziStepInit(EZISTEP *pEziStep, uint8_t slaveID)
{
	pEziStep->state = EZISTEP_STATE_HEADER_HIGH;
	pEziStep->header = 0xaacc;
	pEziStep->slaveID = slaveID;
	pEziStep->tail = 0xaaee;
	pEziStep->done = FALSE;
}

const uint16_t TABLE_EZISTEP_CRC16[] =
{
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

const EZISTEP_FRAME TABLE_EZISTEP_FRAMETYPE[] =
{
	{0x11,	{1,5}},			//FAS_GetRomParameter
	{0x12,	{5,1}},			//FAS_SetParameter
	{0x13,	{1,5}},			//FAS_GetParameter
	{0x2A,	{1,1}},			//FAS_StepEnable
	{0x2C,	{1,1}},			//FAS_StepAlarmRest
	{0x2E,  {0,2}},			//FAS_GetAlarmType
	{0x31,	{0,1}},			//FAS_MoveStop
	{0x34,	{8,1}},			//FAS_MoveSingleAxisAbsPos
	{0x35,	{8,1}},			//FAS_MoveSingleAxisIncPos
	{0x36,	{5,1}},			//FAS_MoveToLimit
	{0x37,	{5,1}},			//FAS_MoveVelocity
	{0x38,	{4,1}},			//FAS_PositionAbsOverride
	{0x39,	{4,1}},			//FAS_PositionOverride
	{0x3A,	{4,1}},			//FAS_VelocityOverride
	{0x3D,	{0,0}},			//FAS_AllMoveOriginSingleAxis
	{0x3E,	{0,0}},			//FAS_AllSingleAxisAbsPos
	{0x3F,	{8,0}},			//FAS_AllSingleAxisIncPos
	{0x40,	{0,5}},			//FAS_GetAxisStatus
	{0x42,	{0,21}},		//FAS_GetMotionStatus
	{0x43,	{0,33}},		//FAS_GetAllStatus
	{0x50,	{4,1}},			//FAS_SetCommandPos
	{0x51,	{0,5}},			//FAS_GetCommandPos
	{0x53,	{0,5}},			//FAS_GetActualPos
	{0x56,	{0,1}},			//FAS_ClearPosition
	{0x58,  {1,1}},			//FAS_MovePause
	{0x80,	{40,1}},		//FAS_MoveSingleAxisAbsPosEx
	{0x81,	{40,1}},		//FAS_MoveSingleAxisIncPosEx
	{0x82,	{37,1}},		//FAS_MoveVelocityEx

	{0x99,  {0,0}},			//Error 
};

uint16_t EziStepCalCRC16(uint8_t* pDataBuffer, uint32_t usDataLen)
{
	uint8_t nTemp;
	uint16_t wCRCWord = 0xFFFF;

	while (usDataLen--)
	{
		nTemp = wCRCWord ^ *(pDataBuffer++);
		wCRCWord >>= 8;
		wCRCWord ^= TABLE_EZISTEP_CRC16[nTemp];
	}

	return wCRCWord;
}

void EziStepProcessData(EZISTEP *pEziStep, uint8_t data)
{
	uint16_t crc16;
	static uint8_t dataCnt;
	const EZISTEP_FRAME *pFrame;
	static bool num;

	switch( pEziStep->state)
	{
	case EZISTEP_STATE_HEADER_HIGH:
		if( ((pEziStep->header >> 8) & 0xFF) == data )
		{
			pEziStep->state = EZISTEP_STATE_HEADER_LOW;
		}
		break;
	case EZISTEP_STATE_HEADER_LOW:
		if( (pEziStep->header & 0xFF) == data )
		{
			pEziStep->data.index = 0;
			pEziStep->state = EZISTEP_STATE_SLAVEID;
		}
		break;
	case EZISTEP_STATE_SLAVEID:
		if( pEziStep->slaveID == data )
		{
			pEziStep->data.buf[pEziStep->data.index++] = data;
			pEziStep->state = EZISTEP_STATE_FRAMETYPE;
		}
		break;
	case EZISTEP_STATE_FRAMETYPE:
		pEziStep->frameType.cmd = data;
		for(pFrame = TABLE_EZISTEP_FRAMETYPE; pFrame->cmd != 0x99 ; pFrame++)
		{
			if(pEziStep->frameType.cmd == pFrame->cmd)
			{
				if( pEziStep->slaveID == 1 ) num = SEND; 
				if( pEziStep->slaveID == 2 ) num = RECV; 

				pEziStep->frameType.cnt[num] = pFrame->cnt[num];
				dataCnt = pEziStep->frameType.cnt[num];

				pEziStep->data.buf[pEziStep->data.index++] = data;

				if( pEziStep->frameType.cnt[num] == 0 )
				{
					pEziStep->state = EZISTEP_STATE_CRC16_LOW;
				}
				else
				{
					pEziStep->state = EZISTEP_STATE_DATA;
				}
				break;
			}
		}

		if ( pFrame->cmd == 0x99 ) //error
		{
			pEziStep->state = EZISTEP_STATE_HEADER_HIGH;
		}
		break;
	case EZISTEP_STATE_DATA:
		pEziStep->data.buf[pEziStep->data.index++] = data;
		dataCnt--;
		if(dataCnt == 0)
		{
			pEziStep->state = EZISTEP_STATE_CRC16_LOW;
		}
		break;
	case EZISTEP_STATE_CRC16_LOW:
		pEziStep->crc16 = (uint16_t)data & 0x00FF;
		pEziStep->state = EZISTEP_STATE_CRC16_HIGH;
		break;
	case EZISTEP_STATE_CRC16_HIGH:
		pEziStep->crc16 |= ((uint16_t)data << 8) & 0xFF00;

		crc16 = EziStepCalCRC16(pEziStep->data.buf, pEziStep->data.index);
		if( crc16 == pEziStep->crc16 )
		{
				pEziStep->state = EZISTEP_STATE_TAIL_HIGH;
				//print
		}
		else
		{
				//ERROR
		}
		break;
	case EZISTEP_STATE_TAIL_HIGH:
		if( ((pEziStep->tail >> 8) & 0xFF) == data )
		{
			pEziStep->state = EZISTEP_STATE_TAIL_LOW;
		}
		break;
	case EZISTEP_STATE_TAIL_LOW:
		if( (pEziStep->tail & 0xFF) == data )
		{
			pEziStep->state = EZISTEP_STATE_HEADER_HIGH;
			pEziStep->done = TRUE;

			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		break;
	}
}

void EziStepSendData(EZISTEP *pEziStep)
{
	uint8_t sendBuf[EZISTEP_DATA_BUF_SIZE] = {0,};
	uint8_t index = 0;	
	uint16_t crc16 = 0;

	sendBuf[index++] = (uint8_t)(pEziStep->header >> 8) & 0xFF;
	sendBuf[index++] = (uint8_t) pEziStep->header & 0xFF;
	sendBuf[index++] = pEziStep->slaveID;

	//data.index 는 실제 slaveID 바이트도 포함하므로 -1 해줌
	memcpy(&sendBuf[index], &(pEziStep->data.buf[1]), (pEziStep->data.index)-1);
	index = index + (pEziStep->data.index-1);

	crc16 = EziStepCalCRC16(&sendBuf[2], pEziStep->data.index);

	sendBuf[index++] = (uint8_t) crc16 & 0xFF;
	sendBuf[index++] = (uint8_t) (crc16 >> 8) & 0xFF;

	sendBuf[index++] = (uint8_t) (pEziStep-> tail >> 8) & 0xFF;
	sendBuf[index++] = (uint8_t) pEziStep->tail & 0xFF;

	if(pEziStep->slaveID == 1){
		HAL_UART_Transmit(&huart4, sendBuf, index, 0xffffffff);
	}
	else if(pEziStep->slaveID == 2){
		HAL_UART_Transmit(&huart5, sendBuf, index, 0xffffffff);
	}
}
