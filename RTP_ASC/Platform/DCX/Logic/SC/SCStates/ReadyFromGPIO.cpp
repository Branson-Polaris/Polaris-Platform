/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
     It contains the Ready State from GPIO related implementation 
***************************************************************************/

#include "ReadyFromGPIO.h"
#include "AlarmFunctions.h"
#include "PCStateMachine.h"

/**************************************************************************//**
* \brief   - ReadyFromGPIO Class constructor - Initialize action and particular state
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

ReadyFromGPIO::ReadyFromGPIO()
{		
	m_Actions = SCState::INIT;
	m_State = SC_READY;
}

/**************************************************************************//**
* \brief   - ReadyFromGPIO Class destructor
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

ReadyFromGPIO::~ReadyFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = NO_STATE;
}

/**************************************************************************//**
* \brief   - This method will be executed when entering the ReadyFromGPIO state
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void ReadyFromGPIO::Enter()
{	
	LOG("\n%sCTRL_T: _READY_FROM_GPIO%s\n", KGRN, KNRM);
}

/**************************************************************************//**
* \brief   - This method will be executed every 250us while waiting for the
*            PC in the ready state.
*              
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void ReadyFromGPIO::Loop()
{
	if(PCStateMachine::GetPCState() == PCState::PC_ALARM)	
	{
		m_Actions = SCState::FAIL;
	}
	 
	else
	{
		//jump to next state according to mode of operation(WELD or SEEK)
		m_Actions = SCState::JUMP;
	}
}

/**************************************************************************//**
* \brief   - This method will be executed when exiting the Exit state
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void ReadyFromGPIO::Exit()
{
	 Ready::Exit(); 				//Call the base class Exit() to call common code part
}


/**************************************************************************//**
* 
* \brief   - Ready Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ReadyFromGPIO::Fail()
{
	Ready::Fail();					//Call the base class Fail() to call common code part
	m_Actions = SCState::ABORT;
}

