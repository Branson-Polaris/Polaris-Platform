/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#include "HoldAcePro.h"

/**************************************************************************//**
* \brief    - Hold Class constructor
*
* \param    - None
*
* \return  - None
*
******************************************************************************/
HoldAcePro::HoldAcePro()
{

}

/**************************************************************************//**
* \brief    - Hold Class destructor
*
* \param    - None
*
* \return   - None
*
******************************************************************************/
HoldAcePro::~HoldAcePro()
{

}

/**************************************************************************//**
* \brief   - This method will be executed when entering the Hold state
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void HoldAcePro::Enter()
{
	 Hold::Enter();		//Call the base class enter to call common code part
}

/**************************************************************************//**
* \brief   - This method will be executed every 250us while waiting for 
*            the hold time to expire
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void HoldAcePro::Loop()
{
	Hold::Loop();   //Call the base class Loop to call common code part
}

/**************************************************************************//**
* \brief   - This method will be executed when exiting the hold state 
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void HoldAcePro::Exit()
{
	Hold::Exit();	//Call the base class Exit to call common code part
}

/**************************************************************************//**
* 
* \brief   - Hold Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void HoldAcePro::Fail()
{
	Hold::Fail();	//Call the base class Fail to call common code part
}

