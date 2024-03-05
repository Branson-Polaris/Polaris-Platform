/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
     It contains the Alarm State related implementation 
***************************************************************************/

#include "AlarmFromGPIO.h"
#include  "ControlTask.h"
#include "AlarmFunctions.h"
#include "PCStateMachine.h"

/**************************************************************************//**
* \brief   - AlarmFromGPIO Class constructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AlarmFromGPIO::AlarmFromGPIO()
{
}

/**************************************************************************//**
* \brief   - AlarmFromGPIO Class destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AlarmFromGPIO::~AlarmFromGPIO()
{
}

/**************************************************************************//**
* \brief   - This method will be executed when entering the AlarmFromGPIO state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmFromGPIO::Enter()
{
	Alarm::Enter();		//Call the base class enter to call common code part
}

/**************************************************************************//**
* \brief   - This method will be executed every 250us while waiting for the
* 			 reset alarm signal
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmFromGPIO::Loop()
{
	Alarm::Loop();		//Call the base class Loop to call common code part
}


/**************************************************************************//**
* \brief   - This method will be executed when exiting the AlarmFromGPIO state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmFromGPIO::Exit()
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
void AlarmFromGPIO::Fail()
{
	Alarm::Fail();		//Call the base class Fail to call common code part
}


