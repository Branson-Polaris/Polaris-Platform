/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC Wait for Ready Position State
***************************************************************************/

#include "WaitForReadyPositionAcePro.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
WaitForReadyPositionAcePro::WaitForReadyPositionAcePro() 
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
WaitForReadyPositionAcePro::~WaitForReadyPositionAcePro() 
{
}

/**************************************************************************//**
*
* \brief   - Wait For Ready Position Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForReadyPositionAcePro::Enter()
{
	 WaitForReadyPosition::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Ready Position Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForReadyPositionAcePro::Loop()
{
	WaitForReadyPosition::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Ready Position Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForReadyPositionAcePro::Exit()
{
	 WaitForReadyPosition::Exit();	//Call the base class Exit() to call common code part
}

/**************************************************************************//**
*
* \brief   - Wait For Ready Position Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WaitForReadyPositionAcePro::Fail()
{
	 WaitForReadyPosition::Fail();	//Call the base class Fail() to call common code part
}
