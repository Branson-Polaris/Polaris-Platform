/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	  It contains the Emergency Stop state related implementation
***************************************************************************/

#include "PCEstopAcePro.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCEstopAcePro::PCEstopAcePro() 
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
PCEstopAcePro::~PCEstopAcePro() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to Estop state.
*            it will turn off the sonics.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstopAcePro::Enter()
{
	//Call the base class Enter() to call common code part
	PCEstop::Enter();		
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCEstop state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstopAcePro::Loop()
{	
	//Call the base class Loop() to call common code part
	PCEstop::Loop();			
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from Estop state.
*            
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCEstopAcePro::Exit()
{
	//Call the base class Exit() to call common code part
	PCEstop::Exit();
}

