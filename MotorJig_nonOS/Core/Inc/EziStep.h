#ifndef _EZISTEP_H_
#define _EZISTEP_H_

#include <stdbool.h>

typedef enum {
	EZISTEP_STATE_HEADER_HIGH,
	EZISTEP_STATE_HEADER_LOW,
	EZISTEP_STATE_SLAVEID,
	EZISTEP_STATE_FRAMETYPE,
	EZISTEP_STATE_DATA,
	EZISTEP_STATE_CRC16_LOW,
	EZISTEP_STATE_CRC16_HIGH,
	EZISTEP_STATE_TAIL_HIGH,
	EZISTEP_STATE_TAIL_LOW,
} EZISTEP_STATE;

#define EZISTEP_DATA_BUF_SIZE		256

typedef struct {
	uint8_t buf[EZISTEP_DATA_BUF_SIZE];
	uint32_t index;
} EZISTEP_DATA;

typedef struct {
	uint8_t cmd;
	uint8_t cnt[2];
}EZISTEP_FRAME;

typedef struct {
	EZISTEP_STATE state;
	uint16_t header;
	uint8_t slaveID;
	EZISTEP_FRAME frameType;
	EZISTEP_DATA data;
	uint16_t crc16;
	uint16_t tail;
	bool done;
} EZISTEP;

extern EZISTEP EziStep;

void EziStepInit(EZISTEP *pEziStep, uint8_t slaveID);
unsigned short EziStepCalCRC16(unsigned char* pDataBuffer, unsigned long usDataLen);
void EziStepProcessData(EZISTEP *pEziStep, uint8_t data);
void EziStepSendData(EZISTEP *pEziStep);

#endif
