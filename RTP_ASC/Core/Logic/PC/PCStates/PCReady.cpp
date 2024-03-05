/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
   It contains functions that gets executed when PC state machine goes to  ready state.
***************************************************************************/

#include "PCReady.h"
#include "PCStateMachine.h"
#include "commons.h"
#include "SCStateMachine.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCReady::PCReady() 
{
	stateType = PC_READY;
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
PCReady::~PCReady() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Ready state.
*            it will turn off the sonics.
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReady::Enter()
{
	ptrPSTask->TurnOffSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in Ready state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReady::Loop()
{
	// run loop code here...
	// TO_BE_DONE : GetSCMasterEvent needs to be implemented	
	if (PowerSupplyTask::GetCoreState() != NO_ERROR)
	{
	    // Change State to PC_ALARM here..
	    ChangeState(PC_ALARM);
	}
	else if (SCStateMachine::GetSCState() == WELD_SONIC_ON)
	{
		ChangeState(PC_WELD_RUN);
	}
	else if (SCStateMachine::GetSCState() == SEEK_SONIC_ON)
	{
		// change state to SEEK_RUN here...
		ChangeState(PC_SEEK_RUN);
	}
	else
	{
		//TODO
	}
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Ready state.
* 
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReady::Exit()
{
	ptrPSTask->SetRxStartFrequency(PcWeldRecipe::GetInstance().GetDigitalTuneWithOffsets()/10);
}

