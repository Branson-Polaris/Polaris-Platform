/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC Wait For Trigger State
***************************************************************************/

#include "WaitForTriggerAcePro.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
WaitForTriggerAcePro::WaitForTriggerAcePro() 
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
WaitForTriggerAcePro::~WaitForTriggerAcePro() 
{	
}

/**************************************************************************//**
*
* \brief   - Wait For Trigger Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForTriggerAcePro::Enter()
{
	 WaitForTrigger::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Trigger Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForTriggerAcePro::Loop()
{
	 WaitForTrigger::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Trigger Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForTriggerAcePro::Exit()
{
	 WaitForTrigger::Exit();	//Call the base class Exit() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Trigger Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForTriggerAcePro::Fail()
{
	 WaitForTrigger::Fail();	//Call the base class Fail() to call common code part
}

