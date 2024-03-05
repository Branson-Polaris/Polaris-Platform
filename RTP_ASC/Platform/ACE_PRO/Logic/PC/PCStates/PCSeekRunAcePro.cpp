/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	It contains functions that gets executed when PC state machine goes to SeekRun state.
***************************************************************************/

#include "PCSeekRunAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCSeekRunAcePro::PCSeekRunAcePro() 
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
PCSeekRunAcePro::~PCSeekRunAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to SeekRun state.
*            it will turn on the sonics and also set parameters based on seek recipe like amplitude,frequency etc. 
*            
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRunAcePro::Enter()
{	
	PCSeekRun::Enter();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCSeekRun state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRunAcePro::Loop()
{
	PCSeekRun::Loop();
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from SeekRun state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRunAcePro::Exit()
{
	PCSeekRun::Exit();
}

