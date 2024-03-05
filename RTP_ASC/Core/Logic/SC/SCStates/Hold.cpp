/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
SC Hold State
***************************************************************************/

#include "Hold.h"

/***************************************************************************
* \brief    - Hold Class constructor
*
* \param    - None
*
* \return  - None
*
******************************************************************************/
Hold::Hold()
{	
}

/**************************************************************************
* \brief    - Hold Class destructor
*
* \param    - None
*
* \return   - None
*
******************************************************************************/
Hold::~Hold()
{	
}

/****************************************************************************
* \brief   - This method will be executed when entering the Hold state
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void Hold::Enter()
{
}

/****************************************************************************
* \brief   - This method will be executed every 250us while waiting for 
*            the hold time to expire
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void Hold::Loop()
{
}

/*****************************************************************************
* \brief   - This method will be executed when exiting the hold state 
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void Hold::Exit()
{
}

/*****************************************************************************
* 
* \brief   - Hold Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Hold::Fail()
{	
}

