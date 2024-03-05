/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	  It contains the Emergency Stop state related implementation
***************************************************************************/

#include "PCEstop.h"
#include "PCStateMachine.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCEstop::PCEstop() {
	stateType = PC_ESTOP;
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
PCEstop::~PCEstop() {
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Estop state.
*            it will turn off the sonics.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstop::Enter()
{
	ptrPSTask->TurnOffSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCEstop state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstop::Loop()
{	
	
// TO_BE_DONE : GetSCMasterEvent needs to be implemented
//	if((GetSCMasterEvent() & BIT_MASK(CTRL_ESTOP)) != BIT_MASK(CTRL_ESTOP))
//	{
		// take actions here...
//		ChangeState(PC_READY);
//	}
//	else
//	{
		// do nothing while in E-stop
//	}
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Estop state.
*            
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstop::Exit()
{
	// take actions here...
}

