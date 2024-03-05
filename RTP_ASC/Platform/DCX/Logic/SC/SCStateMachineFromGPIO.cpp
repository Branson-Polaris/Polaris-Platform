/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the GPIO related SC State Machine implementation
***************************************************************************/

#include "SCStateMachineFromGPIO.h"
#include "PreReadyFromGPIO.h"
#include "ReadyFromGPIO.h"
#include "SeekSonicOnFromGPIO.h"
#include "WeldSonicOnFromGPIO.h"

/**************************************************************************//**
* \brief   - Constructor -
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
SCStateMachineFromGPIO::SCStateMachineFromGPIO() 
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
SCStateMachineFromGPIO::~SCStateMachineFromGPIO() 
{	
}

/**************************************************************************//**
*
* \brief   - State Machine Loop for WELD operation Sequence.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachineFromGPIO::SelectWeldSequence()
{

	m_objState = NULL;
	m_objState = new PreReadyFromGPIO();
	_objStateList->push_back(m_objState);
			
	m_objState = new ReadyFromGPIO();
	_objStateList->push_back(m_objState);
			
	m_objState = new WeldSonicOnFromGPIO();
	_objStateList->push_back(m_objState);
}		


/**************************************************************************//**
*
* \brief   - State Machine Loop for SEEK operation Sequence.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SCStateMachineFromGPIO::SelectSeekSequence()
{
	//Sequence for SEEK operation using gpio
	m_objState = NULL;
	m_objState = new PreReadyFromGPIO();
	_objStateList->push_back(m_objState);
					
	m_objState = new ReadyFromGPIO();
	_objStateList->push_back(m_objState);
			
	m_objState = new SeekSonicOnFromGPIO();
	_objStateList->push_back(m_objState);	
}


