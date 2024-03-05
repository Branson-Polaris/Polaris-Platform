/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC ReadyAcePro state
***************************************************************************/

#include "ReadyAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
ReadyAcePro::ReadyAcePro() 
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
ReadyAcePro::~ReadyAcePro() 
{	
}

/**************************************************************************//**
* 
* \brief   - Ready Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ReadyAcePro::Enter()
{
	 Ready::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
* 
* \brief   - Ready Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ReadyAcePro::Loop()
{
	 Ready::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
* 
* \brief   - Ready Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ReadyAcePro::Exit()
{
	 Ready::Exit(); //Call the base class Exit() to call common code part

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
void ReadyAcePro::Fail()
{
	 Ready::Fail();	//Call the base class Fail() to call common code part
}
