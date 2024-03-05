/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------
This module has the implementation of the Timer
 Module name: Timer
 File name: timer.h
 -------------------------- TECHNICAL NOTES --------------------------------
 *  timer.h
 *
 *  Created on: Jun 11, 2021
 *      Author: E1363163
*/

#ifndef SRC_AC_TIMER_H_
#define SRC_AC_TIMER_H_

#include "../../board_Eval/inc/board.h"




#define TIMER0_MATCH_REG_NO  			1
#define TIMER1_MATCH_REG_NO  			2

#define MS_TO_SEC(X)   (X/1000)

typedef void (*TimerFunc)(void);


void TimerInit(LPC_TIMER_T *pTMR);
void TimerSet(LPC_TIMER_T *pTMR, uint32_t time_ms, uint8_t matchRegNo);
void TimerStop(LPC_TIMER_T *pTMR, uint8_t matchRegNo);
void TimerCallback(TimerFunc func, uint8_t matchRegNo);
uint32_t GetTimer0CurrentValue(void);
void Timer0Callback(void);


#endif /* SRC_AC_TIMER_H_ */
