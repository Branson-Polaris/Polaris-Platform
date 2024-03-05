/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
       It contains the PC Alarm State related implementation 
***************************************************************************/

#include "PCAlarmAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCAlarmAcePro::PCAlarmAcePro() 
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
PCAlarmAcePro::~PCAlarmAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Alarm state.
*            it will turn off the sonics.
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarmAcePro::Enter()
{
	//Call the base class Enter() to call common code part
	PCAlarm::Enter();			
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCAlarm state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarmAcePro::Loop()
{
	//Call the base class Loop() to call common code part
	PCAlarm::Loop();			
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCAlarmAcePro::Exit()
{
	//Call the base class Exit() to call common code part
	PCAlarm::Exit();
}

