/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
      It contains power-up state AcePro platform related implementation 
***************************************************************************/

#include "PowerupAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PowerupAcePro::PowerupAcePro() 
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
PowerupAcePro::~PowerupAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to PowerupAcePro state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PowerupAcePro::Enter()
{
	//Call base class Enter() to call common code part
	Powerup::Enter();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PowerupAcePro state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PowerupAcePro::Loop()
{
	//Call base class Loop() to call common code part
	Powerup::Loop();
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from PowerupAcePro state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PowerupAcePro::Exit()
{
	//Call base class Exit() to call common code part
	Powerup::Exit();
}

