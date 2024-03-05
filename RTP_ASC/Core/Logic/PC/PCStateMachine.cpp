/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	It contains the PC State Machine related implementation
***************************************************************************/

#include "PCStateMachine.h"
#include "Utils.h"

PCState* PCStateMachine::CurrentStateObj = nullptr;
PCStateMachine* PCStateMachine::StateMachineObj = nullptr;
PowerSupplyTask* PCStateMachine :: ptrPSTask = nullptr;
/**************************************************************************//**
* \brief   - Constructor - 
* 			 PC state machine will be instantiated the PoweupObj, ReadyObj, WeldRunObj, EstopObj,
* 			 AlarmObj and SeekRunObj following the system type, such as L20 refresh and P1.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCStateMachine::PCStateMachine() 
{
	ptrPSTask = PowerSupplyTask::GetInstance();	
	m_PowerupObj	= new Powerup();
	m_ReadyObj 		= new PCReady();
	m_WeldRunObj 	= new PCWeldRun();
	m_EstopObj 		= new PCEstop();
	m_AlarmObj 		= new PCAlarm();
	m_SeekRunObj 	= new PCSeekRun();
	
	// Powerup state will be the default state in PC State Machine
	CurrentStateObj = m_PowerupObj;
	CurrentStateObj->stateType = PCState::PC_POWERUP;
	CurrentStateObj->Enter();
}

/**************************************************************************//**
* 
* \brief   - Destructor. Release ReadyObj, WeldRunObj, EstopObj, AlarmObj and SeekRunObj
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
PCStateMachine::~PCStateMachine() 
{
	if(m_PowerupObj != nullptr)
	{
		delete m_PowerupObj;
		m_PowerupObj = nullptr;
	}
	if(m_ReadyObj != nullptr)
	{
		delete m_ReadyObj;
		m_ReadyObj = nullptr;
	}
	if(m_WeldRunObj != nullptr)
	{
		delete m_WeldRunObj;
		m_WeldRunObj = nullptr;
	}
	if(m_EstopObj != nullptr)
	{
		delete m_EstopObj;
		m_EstopObj = nullptr;
	}
	if(m_AlarmObj != nullptr)
	{   
		delete m_AlarmObj;
		m_AlarmObj = nullptr;
	}
	if(m_SeekRunObj != nullptr)
	{
		delete m_SeekRunObj;
		m_SeekRunObj = nullptr;
	}
}

/**************************************************************************//**
* 
* \brief   - Run PC State Machine.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCStateMachine::RunStateMachine()
{
// TO_BE_DONE : GetSCMasterEvent needs to be implemented
//	if(((GetSCMasterEvent() & BIT_MASK(PCState::CTRL_ESTOP)) == BIT_MASK(PCState::CTRL_ESTOP)) && (CurrentStateObj->stateType != PCState::PC_ESTOP))
//	{		
		// take actions for Power supply module here...
//		ChangeState(PCState::PC_ESTOP);
//	}
	CurrentStateObj->Loop();
}

/**************************************************************************//**
* 
* \brief   - Get PC Current State.
*
* \param   - None.
*
* \return  - State enum.
*
******************************************************************************/
PCState::PCSTATES PCStateMachine::GetPCState()
{
	return CurrentStateObj->stateType;
}

/**************************************************************************//**
* 
* \brief   - Change Current State.
*
* \param   - State enum.
*
* \return  - None.
*
******************************************************************************/
void PCStateMachine::ChangeState(PCState::PCSTATES nextState)
{
	bool bValidState = true;
	PCState* previousStateObj = CurrentStateObj; 
	PCStateMachine* _obj = GetInstance();
	switch(nextState)
	{
	case PCState::PC_POWERUP:
		LOG("\n%sPS_T: _PC_POWERUP%s\n", KGRN, KNRM);
		CurrentStateObj = _obj->m_PowerupObj;
		break;
	case PCState::PC_READY:
		LOG("\n%sPS_T: _PC_READY%s\n", KGRN, KNRM);
		CurrentStateObj = _obj->m_ReadyObj;
		break;
	case PCState::PC_WELD_RUN:
		LOG("\n%sPS_T: _PC_WELD_RUN%s\n", KGRN, KNRM);
		CurrentStateObj = _obj->m_WeldRunObj;
		break;
	case PCState::PC_ESTOP:
		LOG("\n%sPS_T: _PC_ESTOP%s\n", KRED, KNRM);
		CurrentStateObj = _obj->m_EstopObj;
		break;
	case PCState::PC_ALARM:
		LOG("\n%sPS_T: _PC_ALARM%s\n", KRED, KNRM);
		CurrentStateObj = _obj->m_AlarmObj;
		break;
	case PCState::PC_SEEK_RUN:
		LOG("\n%sPS_T: _PC_SEEK_RUN%s\n", KGRN, KNRM);
		CurrentStateObj = _obj->m_SeekRunObj;
		break;
	default:
		bValidState = false;
		break;
	}
	
	if(bValidState)
	{
		previousStateObj->Exit();
		CurrentStateObj->Enter();
		CurrentStateObj->stateType = nextState;
	}
}

/**************************************************************************//**
* 
* \brief   - get instance of PCStateMachine.
*
* \param   - None.
*
* \return  - PCStateMachine instance.
*
******************************************************************************/
PCStateMachine*	PCStateMachine::GetInstance()
{
	static PCStateMachine instance; 
						   
	return &instance;
}
