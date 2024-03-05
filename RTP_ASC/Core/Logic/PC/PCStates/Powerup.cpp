/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
      It contains power-up related implementation 
***************************************************************************/

#include "Powerup.h"
#include "PCStateMachine.h"
#include "PowerSupplyTask.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
Powerup::Powerup() 
{
	stateType = PC_POWERUP;
	ptrPSTask = PowerSupplyTask::GetInstance();
}

/**************************************************************************//**
* 
* \brief   - Destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
Powerup::~Powerup() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Powerup state.
*            it will turn off the sonics.
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Powerup::Enter()
{
	//Turn off sonics
	ptrPSTask->TurnOffSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in Powerup state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Powerup::Loop()
{
	//Powerup to Ready state transition time
	static int transitionDelay = POWERUP_TRANSITION_TIME_IN_MS;
	
	if (PowerSupplyTask::GetCoreState() != NO_ERROR)
	{
		ChangeState(PC_ALARM);
	}
	else
	{
		if (transitionDelay == 0)
		{
			ChangeState(PC_READY);
		}
	}
	transitionDelay--;
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from powerup state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Powerup::Exit()
{
	// take actions here...
}

