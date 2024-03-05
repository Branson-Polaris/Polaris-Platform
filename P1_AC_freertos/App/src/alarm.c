/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * alarm.c
 *
 *  Created on: June 8, 2021
 *      Author: Akhutale
 *
 *      Alarm State implementation
*/


#include "statemachine.h"
#include "main.h"

#include "SetOutputs.h"


/**************************************************************************//**
* \brief  - State entry code
* \brief  - Alarm occurred
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void AlarmEntry()
{
#if PRNT_DBG
	printf("\r\n In Alarm Entry state");
#endif
	// Disable Solenoid valves
	ClearSVRequests();

}


/**************************************************************************//**
* \brief  - State loop code
* \brief  - Check for alarm reset
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void AlarmStateLoop()
{
#if PRNT_DBG
	printf("\r\n In Alarm Loop state");
#endif

	if((ULS == ON) && (TRS == OFF))
	{
		ChangeState(AC_READY);
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
void AlarmExit()
{
#if PRNT_DBG
	printf("\r\n In Alarm Exit state");
#endif
}
