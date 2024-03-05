/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	 It contains the SC State Machine related implementation
***************************************************************************/

#include "SCStateMachine.h"
#include "SCStateMachineFromGPIO.h"
#include "SCStateMachineAcePro.h"
#include "PreReady.h"
#include "Ready.h"
#include "StartSwitch.h"
#include "SeekSonicOn.h"
#include "WeldSonicOn.h"
#include "WaitForTrigger.h"
#include "WaitForReadyPosition.h"
#include "Hold.h"
#include "PCStateMachine.h"
#include "Logger_old.h"
#include "ControlTask.h"
extern "C"
{
	#include "customSystemCall.h"	
}
/* StateMachine is implemented for the operation that is only focus on the preset level not relevent to sequence or teachmode */
SCState* SCStateMachine::m_objState = nullptr;
SEM_ID SCStateMachine::m_semaphoreMutex = SEM_ID_NULL;
/**************************************************************************//**
* \brief   - Constructor - Create and Initialize Semaphore, Vector and Map
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
SCStateMachine::SCStateMachine() 
{
	ptrPSTask = PowerSupplyTask::GetInstance();
	_objStateList = new vector<SCState*>();	
	m_StateIndex = 0;
	m_IsRunning = false;
	m_IsLoading = false;
	//create and initialize a mutual-exclusion semaphore
	m_semaphoreMutex = semMCreate(SEM_Q_FIFO);				//Returns Semaphore ID or NULL		
	//Create SC Action Map
	_objActionMap = new map<SCSTATES, SCState*>();

}

/**************************************************************************//**
*
* \brief   - Destructor-Delete all statelist from vector,maps and semaphores
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SCStateMachine::~SCStateMachine() {
	//Delete all objects in SC state List
	deleteAll();
	_objActionMap->clear();
	delete _objActionMap;
	if(m_semaphoreMutex != SEM_ID_NULL)
	{
		semDelete(m_semaphoreMutex);
		m_semaphoreMutex = SEM_ID_NULL;
	}
}

/**************************************************************************//**
*
* \brief   - Delete all objects in SC state List
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachine::deleteAll()
{
	auto iter = _objStateList->begin();
	while (iter != _objStateList->end())
	{
		SCState* _objState = *iter;
		delete _objState;
		iter++;
	}
	_objStateList->clear();
	_objActionMap->clear();
}

/**************************************************************************//**
*
* \brief   - Run SC State Machine.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachine::RunStateMachine()
{
	//Set stateIndex to 0 when there is no state in the vector
	if (_objStateList->size() == 0)								
	{
		m_IsRunning = false;									
		m_StateIndex = 0;										
		return;
	}
	
	if (m_IsLoading == true)									
	{
		m_IsRunning = false;
		m_StateIndex = 0;
		return;
	}	
	
	//Set masterstate to NO_STATE when the stateindex exceeds the list size
	if(m_StateIndex >= _objStateList->size())					
	{
		m_objState->m_State = NO_STATE;
		m_StateIndex = 0;										
		m_IsRunning = false;									
		m_IsLoading = true;										
		// Clear all the state list and action map
		deleteAll();											
		return;
	}
	m_IsRunning = true;
	
	m_objState = _objStateList->at(m_StateIndex);
	
	switch (m_objState->m_Actions)
	{
	case SCState::INIT:
		// Only Enter INIT State Once
		m_objState->Enter();
		m_objState->m_Actions = SCState::LOOP;    				
		break;
	case SCState::LOOP:
		m_objState->Loop();
		break;
	case SCState::FAIL:
		m_objState->Fail();
		break;
	case SCState::JUMP:
		// Exit current state
		m_objState->Exit();										
		m_objState->m_Actions = SCState::INIT;
		//Jump Next State
		m_StateIndex++;											
		break;
	case SCState::ALJUMPNORM:
		m_objState->Exit();
		m_objState->m_Actions = SCState::INIT;
		//Alarm Jump Loop
		m_StateIndex++;											
		break;
	case SCState::ABORT:
		m_objState->Exit();
		m_objState->m_Actions = SCState::INIT;
		m_StateIndex = 0;
		deleteAll();
		break;
	case SCState::PUSH:
		m_objState->Exit();;
		m_objState->m_Actions = SCState::INIT;
		LOG("Push\n");
		break;
	default:
		m_StateIndex = 0;
		m_IsRunning = false;									
		m_IsLoading = true;	
		deleteAll();
		LOGERR((char *) "SCStateMachine : Invalid Action\n",0,0,0);
		break;
	}
}

/**************************************************************************//**
*
* \brief   - Get SC State Machine status.
*
* \param   - None.
*
* \return  - Bool running or not.
*
******************************************************************************/
bool SCStateMachine::GetStateMachineStatus() const
{
	return m_IsRunning;
}

/**************************************************************************//**
*
* \brief   - Get SC Current State.
*
* \param   - None.
*
* \return  - State enum.
*
******************************************************************************/
SCSTATES SCStateMachine::GetSCState()
{
	if(m_objState != nullptr)
	{
		return m_objState->m_State;
	}	
	else
	{
		return NO_STATE;
	}
}

/**************************************************************************//**
*
* \brief   - Load state objects in State List based on operation type
*
* \param   - SC Operation.
*
* \return  - If the Load States to list is successful, it returns OK,
* 			otherwise it will return ERROR; .
******************************************************************************/
int SCStateMachine::LoadStatesHandler(OPERATION operation)
{
	m_IsLoading = TRUE;
	int iResult = ERROR;	
	
	switch(operation)
	{
		case WELD:
			// Execute WELD operation Sequence
			SelectWeldSequence();		
			break;
			
		case SEEK:
			// Execute SEEK operation Sequence
			 SelectSeekSequence();		
			 break;
		
		default:
			iResult = ERROR;
			break;
	}
	iResult = OK;		
	m_IsLoading = FALSE;
	return iResult;
	
}


/**************************************************************************//**
* \brief  - Returns total weld cycle time.
*
* \param  - None
*
* \return - UINT32 - Cycle time counter
*
******************************************************************************/
UINT32 SCStateMachine::CycleTime()
{
	UINT32 cycleTimeCounter = 0;	
	//TODO : later implementation
	return cycleTimeCounter;
}
