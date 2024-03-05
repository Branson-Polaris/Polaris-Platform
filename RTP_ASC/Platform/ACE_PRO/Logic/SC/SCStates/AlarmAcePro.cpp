/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#include "AlarmAcePro.h"

/**************************************************************************//**
* \brief   - Alarm Class constructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AlarmAcePro::AlarmAcePro()
{
}

/**************************************************************************//**
* \brief   - Alarm Class destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AlarmAcePro::~AlarmAcePro()
{
}

/**************************************************************************//**
* \brief   - This method will be executed when entering the Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmAcePro::Enter()
{
	Alarm::Enter();		//Call the base class enter to call common code part
}

/**************************************************************************//**
* \brief   - This method will be executed every 250us while waiting for the.
* 			 reset alarm signal
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmAcePro::Loop()
{
	Alarm::Loop();		//Call the base class Loop to call common code part
}


/**************************************************************************//**
* \brief   - This method will be executed when exiting the Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmAcePro::Exit()
{	
	Alarm::Exit();		//Call the base class Exit to call common code part
}

/**************************************************************************//**
* 
* \brief   - Alarm Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmAcePro::Fail()
{
	Alarm::Fail();		//Call the base class Fail to call common code part
}

