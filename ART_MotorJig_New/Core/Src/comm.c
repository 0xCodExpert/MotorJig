#include "main.h"
#include "common.h"
#include "comm.h"

COMM_RING_BUF RingBuf_Modbus;
COMM_RING_BUF RingBuf_EziStep;

void CommInit(COMM_RING_BUF *pbuf)
{
	pbuf->RingBufRxCtr = 0;
	pbuf->RingBufRxInPtr = &pbuf->RingBufRx[0];
	pbuf->RingBufRxOutPtr = &pbuf->RingBufRx[0];
}

void CommPutRxChar(COMM_RING_BUF *pbuf, uint8_t data)
{
	pbuf->RingBufRxCtr++;
	*(pbuf->RingBufRxInPtr) = data;
	pbuf->RingBufRxInPtr++;
	if( pbuf->RingBufRxInPtr == &pbuf->RingBufRx[COMM_RX_BUF_SIZE] ){
		pbuf->RingBufRxInPtr = &pbuf->RingBufRx[0];
	}
}

uint8_t CommGetRxChar(COMM_RING_BUF *pbuf)
{
	uint8_t data;

	pbuf->RingBufRxCtr--;
	data = *(pbuf->RingBufRxOutPtr);
	pbuf->RingBufRxOutPtr++;
	if( pbuf->RingBufRxOutPtr == &pbuf->RingBufRx[COMM_RX_BUF_SIZE] ){
		pbuf->RingBufRxOutPtr = &pbuf->RingBufRx[0];
	}

	return data;
}

bool CommIsEmpty(COMM_RING_BUF *pbuf)
{
	bool empty;

	if( pbuf->RingBufRxCtr > 0 ){
		empty = FALSE;
	}
	else{
		empty = TRUE;
	}

	return empty;
}
