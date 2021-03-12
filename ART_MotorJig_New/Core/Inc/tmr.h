#ifndef _TMR_H_
#define _TMR_H_

#include <stdbool.h>

#define TMR_MAX_TMR				20

typedef struct {
	bool TmrEn;
	uint16_t TmrCtr;
	uint16_t TmrInit;
	void (*TmrFnct)(void*);
	void* TmrFnctArg;
} TMR;

extern TMR TmrTbl[TMR_MAX_TMR];

void TmrInit(TMR* pTmr);
void TmrSetT(TMR* pTmr, uint8_t n, uint16_t tenths);
void TmrSetFnct(TMR* pTmr, uint8_t n, void (*pFnct)(void*), void* pArg);
void TmrStart(TMR* pTmr, uint8_t n);
void TmrStop(TMR* pTmr, uint8_t n);
void TmrTask(TMR* pTmr);

#endif
