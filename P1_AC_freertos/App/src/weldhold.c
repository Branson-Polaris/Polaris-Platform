/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * Weldhold.c
 *
 *  Created on: June 4, 2021
 *      Author: Akhutale
 *
 *      Weld Hold State implementation
*/


#include "statemachine.h"
#include "main.h"


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
void WeldHoldEntry()
{
#if PRNT_DBG
	printf("\r\n In WeldHold Entry state");
#endif
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
void WeldHoldStateLoop()
{
#if PRNT_DBG
	printf("\r\n In WeldHold Loop state");
#endif
	if (ESTOP1 || ESTOP2)
	{
		ChangeState(AC_ESTOP);
	}
	else if ((rxpdoac.SCState == SC_ALARM))
	{
		ChangeState (AC_READY);
	}
	else
	{
		switch(rxpdoac.SCState)
		{
			case WAIT_FOR_READY_POSITION: //intentional fall-through
				ChangeState(RETURN_STROKE);
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
void WeldHoldExit()
{
#if PRNT_DBG
	printf("\r\n In WeldHold Exit state");
#endif
}
