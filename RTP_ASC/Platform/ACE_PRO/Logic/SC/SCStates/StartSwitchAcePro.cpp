/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC Start Switch State
***************************************************************************/

#include "StartSwitchAcePro.h"

/**************************************************************************//**
*
* \brief   - Constructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
StartSwitchAcePro::StartSwitchAcePro() 
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
StartSwitchAcePro::~StartSwitchAcePro() 
{	
}

/**************************************************************************//**
*
* \brief   - StartSwitch Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void StartSwitchAcePro::Enter()
{
	StartSwitch::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
*
* \brief   - StartSwitch Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void StartSwitchAcePro::Loop()
{
	StartSwitch::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
*
* \brief   - StartSwitch Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void StartSwitchAcePro::Exit()
{
	StartSwitch::Exit();	//Call the base class Exit() to call common code part
}

/**************************************************************************//**
*
* \brief   - StartSwitch Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void StartSwitchAcePro::Fail()
{
	StartSwitch::Fail();	//Call the base class Fail() to call common code part
}
