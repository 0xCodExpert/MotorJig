#ifndef _COMM_H_
#define _COMM_H_

#include <stdbool.h>

#define COMM_RX_BUF_SIZE		256

typedef struct {
	uint16_t RingBufRxCtr;
	uint8_t  *RingBufRxInPtr;
	uint8_t  *RingBufRxOutPtr;
	uint8_t  RingBufRx[COMM_RX_BUF_SIZE];
} COMM_RING_BUF;

extern COMM_RING_BUF RingBuf_Modbus;
extern COMM_RING_BUF RingBuf_EziStep;

void CommInit(COMM_RING_BUF *pbuf);
void CommPutRxChar(COMM_RING_BUF *pbuf, uint8_t data);
uint8_t CommGetRxChar(COMM_RING_BUF *pbuf);
bool CommIsEmpty(COMM_RING_BUF *pbuf);

#endif
