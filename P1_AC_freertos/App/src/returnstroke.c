/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * returnstroke.c
 *
 *  Created on: June 4, 2021
 *      Author: Akhutale
 *
 *      Return Stroke State implementation
*/



#include "statemachine.h"
#include "main.h"
#include "SetOutputs.h"

/**************************************************************************//**
* \brief  - State entry code
* \brief  - Start move to ready position
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ReturnStrokeEntry()
{
#if PRNT_DBG
	printf("\r\n In ReturnStroke Entry state");
#endif
	// Disable Solenoid valves
	ClearSVRequests();
}


/**************************************************************************//**
* \brief  - State loop code
* \brief  - Wait for move back to ready position
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ReturnStrokeStateLoop()
{
#if PRNT_DBG
	printf("\r\n In ReturnStroke Loop state");
#endif
	if (ESTOP1 || ESTOP2)
	{
		ChangeState(AC_ESTOP);
	}
	else if (ULS == ON)
	{
		ChangeState (AC_READY);
	}
	else if (ULS == OFF)
	{
		ChangeState (AC_ALARM);
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
void ReturnStrokeExit()
{
#if PRNT_DBG
	printf("\r\n In ReturnStroke Exit state");
#endif
}
