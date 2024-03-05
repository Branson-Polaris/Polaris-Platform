/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	It contains functions that gets executed when PC state machine goes to WeldRun state.
***************************************************************************/

#include "PCWeldRun.h"
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
PCWeldRun::PCWeldRun() 
{
	stateType = PC_WELD_RUN;
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
PCWeldRun::~PCWeldRun() {
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Ready state.
*            it will turn on the sonics and also set parameters based on PC weld recipe like amplitude,frequency etc. 
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRun::Enter()
{
	ptrPSTask->UpdateWeldParameters();
	ptrPSTask->TurnOnSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCWeldRun state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRun::Loop()
{
    if(PowerSupplyTask::GetCoreState() != NO_ERROR)
	{
    	// Change State to PC_ALARM here..
    	ChangeState(PC_ALARM);
	}
    else
    {
    	if ((SCStateMachine::GetSCState() == HOLD)  || (SCStateMachine::GetSCState() == NO_STATE)
    			|| (SCStateMachine::GetSCState() == PREREADY) || (SCStateMachine::GetSCState() == SC_READY) || (SCStateMachine::GetSCState() == SC_ALARM) 
    			|| (SCStateMachine::GetSCState() == WAIT_FOR_READY_POSITION))
		{
			ChangeState(PC_READY);
		}
		else
		{
			// do more while welding here...
		}
    }
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from PcWeld state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRun::Exit()
{
	ptrPSTask->TurnOffSonics();
}



