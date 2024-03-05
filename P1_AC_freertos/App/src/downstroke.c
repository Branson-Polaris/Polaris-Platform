/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * downstroke.c
 *
 *  Created on: June 4, 2021
 *      Author: Akhutale
 *
 *      DownStroke State implementation
*/


#include "statemachine.h"
#include "main.h"
#include "SetOutputs.h"
#include "timer.h"
#include "global.h"


static uint32_t DownStrokeEntryCounter = 0;

/**************************************************************************//**
* \brief  - State entry code
* \brief  - Start to move down request sv1 energized
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void DownStrokeEntry()
{
#if PRNT_DBG
	printf("\r\n In DownStroke Entry state");
#endif
	// Enable Solenoid valves
	SetSVRequests();

	//Get the Timer 0 Current value
    DownStrokeEntryCounter = GetTimer0CurrentValue();
}



/**************************************************************************//**
* \brief  - State loop code
* \brief  - Wait for trigger
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void DownStrokeStateLoop()
{
	if (ESTOP1 || ESTOP2)
	{
		ChangeState(AC_ESTOP);
	}
	else if ((rxpdoac.SCState == SC_ALARM))
	{
		ChangeState (AC_READY);
	}
	//Check if 1 Sec or more has passed after entering the downstroke
	else if (((GetTimer0CurrentValue() - DownStrokeEntryCounter) >=1) && (ULS == ON))
	{
		ChangeState (AC_ALARM);
	}
	else
	{
		switch(rxpdoac.SCState)
		{
			case WELD_SONIC_ON: //intentional fall-through
				ChangeState(WELD_HOLD);
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
void DownStrokeExit()
{
#if PRNT_DBG
	printf("\r\n In DownStroke Exit state");
#endif
}


