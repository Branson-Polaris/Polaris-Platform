/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * ControlTask.c
 *
 *  Created on: Apr 26, 2021
 *      Author: Kkadu
 *
 *
*/


#include "ControlTask.h"
#include "SocketReceiver.h"
#include "Main.h"
#include "Inputs.h"
#include "statemachine.h"

#include "lwip/opt.h"
#include "string.h"
#include "arch\lpc_arch.h"
#include "arch\sys_arch.h"


extern uint32_t ADC_Done;
/**************************************************************************//**
* \brief  - ControlTask(void *arg)
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ControlTask(void *arg)
{

	while(1)
	{
		if(ADC_Done)
		{
			GetInputs();
			StateMachine();
		}
		msDelay(1);
	}

}

/**************************************************************************//**
* \brief  - getpdo()
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void getpdo()
{
	GetInputs();
	StateMachine();
}

