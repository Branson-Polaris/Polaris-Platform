/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
    It contains functions that gets executed when PC state machine goes to  ready state.
***************************************************************************/

#include "PCReadyAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCReadyAcePro::PCReadyAcePro() 
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
PCReadyAcePro::~PCReadyAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Ready state.
*            it will turn off the sonics.
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReadyAcePro::Enter()
{
	PCReady::Enter();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in Ready state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReadyAcePro::Loop()
{
	PCReady::Loop();
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Ready state.
* 
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCReadyAcePro::Exit()
{
	 PCReady::Exit();
}

