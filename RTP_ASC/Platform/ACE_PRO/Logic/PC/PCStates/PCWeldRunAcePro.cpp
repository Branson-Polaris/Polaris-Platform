/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	It contains functions that gets executed when PC state machine goes to WeldRun state.
***************************************************************************/

#include "PCWeldRunAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCWeldRunAcePro::PCWeldRunAcePro() 
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
PCWeldRunAcePro::~PCWeldRunAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Ready state.
*            it will turn on the sonics and also set parameters based on PC weld recipe like amplitude,frequency etc. 
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRunAcePro::Enter()
{
	PCWeldRun::Enter();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCWeldRun state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRunAcePro::Loop()
{
	PCWeldRun::Loop();
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when ASC state machine exit from PcWeld state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCWeldRunAcePro::Exit()
{
	PCWeldRun::Exit();
}



