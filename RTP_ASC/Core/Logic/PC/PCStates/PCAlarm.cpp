/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
      It contains the PC Alarm State related implementation 
***************************************************************************/

#include "PCAlarm.h"
#include "PCStateMachine.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCAlarm::PCAlarm() 
{
	stateType = PC_ALARM;
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
PCAlarm::~PCAlarm() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Alarm state.
*            it will turn off the sonics.
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarm::Enter()
{
	ptrPSTask->TurnOffSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCAlarm state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarm::Loop()
{
	if (PowerSupplyTask::GetCoreState() != NO_ERROR)
	{
		ptrPSTask->UpdateRxMasterEvent(CTRL_PC_CLEAR_ALARMS);
	}
	else
	{
		ChangeState(PC_READY);
	}
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarm::Exit()
{
	// take actions here...
}

