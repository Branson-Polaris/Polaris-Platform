/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC PreReadyAcePro state
***************************************************************************/

#include "PreReadyAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PreReadyAcePro::PreReadyAcePro() 
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
PreReadyAcePro::~PreReadyAcePro() 
{	
}

/**************************************************************************//**
* 
* \brief   - PreReady Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PreReadyAcePro::Enter()
{
	PreReady::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
* 
* \brief   - PreReady Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PreReadyAcePro::Loop()
{
	 PreReady::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
* 
* \brief   - PreReady Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PreReadyAcePro::Exit()
{
	PreReady::Exit();	//Call the base class Exit() to call common code part
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
void PreReadyAcePro::Fail()
{
	PreReady::Fail();	//Call the base class Fail() to call common code part
}
