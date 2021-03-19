#include "main.h"
#include "common.h"
#include "tmr.h"

TMR TmrTbl[TMR_MAX_TMR];

void TmrInit(TMR* pTmr)
{
	uint8_t i;

	for(i = 0; i < TMR_MAX_TMR; i++){
		pTmr[i].TmrEn = FALSE;
		pTmr[i].TmrCtr = 0;
		pTmr[i].TmrInit = 0;
		pTmr[i].TmrFnct = NULL;
	}
}

void TmrSetT(TMR* pTmr, uint8_t n, uint16_t tenths)
{
	if( n < TMR_MAX_TMR ){
		pTmr[n].TmrInit = tenths;
		pTmr[n].TmrCtr = tenths;
	}
}

void TmrSetFnct(TMR* pTmr, uint8_t n, void (*pFnct)(void*), void* pArg)
{
	if( n < TMR_MAX_TMR ){
		pTmr[n].TmrFnct = pFnct;
		pTmr[n].TmrFnctArg = pArg;
	}
}

void TmrStart(TMR* pTmr, uint8_t n)
{
	if( n < TMR_MAX_TMR ){
		pTmr[n].TmrEn = TRUE;
	}
}

void TmrStop(TMR* pTmr, uint8_t n)
{
	if( n < TMR_MAX_TMR ){
		pTmr[n].TmrEn = FALSE;
	}
}

void TmrTask(TMR* pTmr)
{
	uint8_t i;

	void (*pFnct)(void*);
	void* pArg;

	pFnct = (void (*)(void*))0;
	pArg = (void*)0;

	for(i = 0; i < TMR_MAX_TMR; i++){
		if( pTmr[i].TmrEn == TRUE ){
			if( pTmr[i].TmrCtr > 0 ){
				pTmr[i].TmrCtr--;
				if( pTmr[i].TmrCtr == 0 ){
					//pTmr[i].TmrEn = FALSE;
					pFnct = pTmr[i].TmrFnct;
					pArg = pTmr[i].TmrFnctArg;
				}
			}
		}
		if( pFnct != (void (*)(void*))0 ){
			(*pFnct)(pArg);
			pFnct = (void (*)(void*))0;
			TmrSetT(pTmr, i, 1000);
		}
	}
}
