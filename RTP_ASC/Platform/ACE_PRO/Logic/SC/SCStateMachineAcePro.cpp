/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	It contains the SC State Machine related implementation
***************************************************************************/

#include "SCStateMachineAcePro.h"
#include "PreReadyAcePro.h"
#include "ReadyAcePro.h"
#include "StartSwitchAcePro.h"
#include "SeekSonicOnAcePro.h"
#include "WeldSonicOnAcePro.h"
#include "WaitForTriggerAcePro.h"
#include "WaitForReadyPositionAcePro.h"
#include "HoldAcePro.h"

/**************************************************************************//**
* \brief   - Constructor -
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
SCStateMachineAcePro::SCStateMachineAcePro() 
{	
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
SCStateMachineAcePro::~SCStateMachineAcePro() 
{
}

/**************************************************************************//**
*
* \brief   - State Machine Loop for Weld Sequence.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachineAcePro::SelectWeldSequence()
{
	//for testing only, this will be removed while implementing the ACEPRO related shate machine
	m_objState = NULL;

	m_objState = new PreReadyAcePro();
	_objStateList->push_back(m_objState);

	m_objState = new ReadyAcePro();
	_objStateList->push_back(m_objState);
	
	m_objState = new StartSwitchAcePro();
	_objStateList->push_back(m_objState);
		
	m_objState = new WaitForTriggerAcePro();
	_objStateList->push_back(m_objState);
	
	m_objState = new WeldSonicOnAcePro();
	_objStateList->push_back(m_objState);
	
	m_objState = new HoldAcePro();
	_objStateList->push_back(m_objState);

	m_objState = new WaitForReadyPositionAcePro();
	_objStateList->push_back(m_objState);
	
}


/**************************************************************************//**
*
* \brief   - State Machine Loop for Weld Sequence.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachineAcePro::SelectSeekSequence()
{
	//for testing only, this will be removed while implementing the ACEPRO related shate machine
	m_objState = NULL;

	m_objState = new PreReadyAcePro();
	_objStateList->push_back(m_objState);

	m_objState = new ReadyAcePro();
	_objStateList->push_back(m_objState);
}

