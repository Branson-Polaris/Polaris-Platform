/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
    It contains the PreReady State related implementation 
***************************************************************************/

#include "PreReadyFromGPIO.h"
#include "ControlTask.h"
#include "AlarmFunctions.h"
#include "PCStateMachine.h"

/**************************************************************************//**
* \brief   - PreReadyFromGPIO Class constructor
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

PreReadyFromGPIO::PreReadyFromGPIO()
{	
	m_Actions = SCState::INIT;
	m_State = PREREADY;
}

/**************************************************************************//**
* \brief   - PreReadyFromGPIO Class destructor
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

PreReadyFromGPIO::~PreReadyFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = PREREADY;
}

/**************************************************************************//**
* \brief   - This method will be executed when entering the PreReadyFromGPIO state
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void PreReadyFromGPIO::Enter()
{
	LOG("\nCTRL_T: _PREREADY_FROM_GPIO\n");
}

/**************************************************************************//**
* \brief   - This method will be executed every 250us while waiting for the
*          	PC in the ready state. 
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void PreReadyFromGPIO::Loop()
{													
	 if(PCStateMachine::GetPCState() == PCState::PC_ALARM)		
	 {
		 m_Actions = SCState::FAIL;								
	 }
	 if(PCStateMachine::GetPCState() == PCState::PC_READY)		
	 {
		//jump to next state if PC is in Ready state
		m_Actions = SCState::JUMP;									
	 }
}

/**************************************************************************//**
* \brief   - This method will be executed when exiting the PreReadyFromGPIO state 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void PreReadyFromGPIO::Exit()
{	
	PreReady::Exit();												//Call the base class Exit() to call common code part
}

/**************************************************************************//**
* 
* \brief   - PreReady Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PreReadyFromGPIO::Fail()
{	
	PreReady::Fail();											//Call the base class Fail() to call common code part
	//Abort the operation
	m_Actions = SCState::ABORT;									
}

