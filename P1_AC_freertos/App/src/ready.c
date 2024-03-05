/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * Ready.c
 *
 *  Created on: June 4, 2021
 *      Author: Akhutale
 *
 *      Ready State implementation
*/

#include "global.h"
#include "statemachine.h"
#include "Main.h"


/**************************************************************************//**
* \brief  - State entry code
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ReadyEntry()
{
#if PRNT_DBG
	printf("\r\n In Ready Entry state");
#endif
 	if ((ULS == OFF) || (TRS == ON))
		ChangeState(AC_ALARM);
}


/**************************************************************************//**
* \brief  - State loop code
* \brief  - Wait for supervisor to say do something
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ReadyStateLoop()
{
#if PRNT_DBG
	printf("\r\n In Ready Loop state");
#endif
	if (ESTOP1 || ESTOP2)
	{
		ChangeState(AC_ESTOP);
	}
	else if ((ULS == ON) && (TRS == ON))
	{
		ChangeState (AC_ALARM);
	}	
	else
	{
		switch(rxpdoac.SCState)
		{
			case WAIT_FOR_TRIGGER:
				ChangeState(DOWN_STROKE);
				break;

			default:
				break;
		}
	}
}


/**************************************************************************//**
* \brief  - State exit code
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ReadyExit()
{
#if PRNT_DBG
	printf("\r\n In Ready Exit state");
#endif
}
