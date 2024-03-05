/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * timer.c
 *
 *  Created on: June 11, 2021
 *      Author: Pdevsarkar
 *
 *      Timer implementation
*/

#include "global.h"
#include "timer.h"

#define TOTAL_TIMER_NO   				4


TimerFunc callback_struct[TOTAL_TIMER_NO];


static uint32_t Timer0CurrentValue = 0;





/**************************************************************************//**
* \brief  - Timer Init function
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TimerInit(LPC_TIMER_T *pTMR)
{
	Chip_TIMER_Init(pTMR);
	Chip_TIMER_Reset(pTMR);
}

/**************************************************************************//**
* \brief  - Timer Setup function
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TimerSet(LPC_TIMER_T *pTMR,uint32_t timeMs,uint8_t matchRegNo)
{
	uint32_t timeInSec = MS_TO_SEC(timeMs);
	uint32_t pclk = Chip_Clock_GetPeripheralClockRate();

	Chip_TIMER_MatchEnableInt(pTMR, matchRegNo);
	Chip_TIMER_SetMatch(pTMR, matchRegNo,(pclk * timeInSec));
	Chip_TIMER_ResetOnMatchEnable(pTMR, matchRegNo);
	Chip_TIMER_Enable(pTMR);
	NVIC_ClearPendingIRQ(matchRegNo);
	NVIC_EnableIRQ(matchRegNo);
}

/**************************************************************************//**
* \brief  - Timer Stop function
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TimerStop(LPC_TIMER_T *pTMR,uint8_t matchRegNo)
{
	Chip_TIMER_MatchDisableInt(pTMR, matchRegNo);
	Chip_TIMER_Disable(pTMR);
}

/**************************************************************************//**
* \brief  - Timer Callback function
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TimerCallback(TimerFunc function, uint8_t matchRegNo)
{
	callback_struct[matchRegNo] = function;
}


/**************************************************************************//**
* \brief  - Timer0  ISR
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, TIMER0_MATCH_REG_NO))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER0, TIMER0_MATCH_REG_NO);
		callback_struct[TIMER0_MATCH_REG_NO]();
	}
}

/**************************************************************************//**
* \brief  - Timer1  ISR
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void TIMER1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER1, TIMER1_MATCH_REG_NO))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER1, TIMER1_MATCH_REG_NO);
		callback_struct[TIMER1_MATCH_REG_NO]();
	}
}

/**************************************************************************//**
* \brief  - Timer 0 Callback function
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void Timer0Callback(void)
{
	 Timer0CurrentValue++;
}

/**************************************************************************//**
* \brief  - Timer 0  function to return the current value of Timer.
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
uint32_t GetTimer0CurrentValue(void)
{
	return  Timer0CurrentValue;
}
