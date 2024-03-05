/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * Estop.c
 *
 *  Created on: June 4, 2021
 *      Author: Akhutale
 *
 *      Estop State implementation
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
void EStopEntry()
{
#if PRNT_DBG
	printf("\r\n In ESTOP Entry state");
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
void EStopStateLoop()
{
#if PRNT_DBG
	printf("\r\n In ESTOP Loop state");
#endif
	if(!(ESTOP1 && ESTOP2))
	{
		ChangeState (AC_READY);
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
void EStopExit()
{
#if PRNT_DBG
	printf("\r\n In ESTOP Exit state");
#endif
}
