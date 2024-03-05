/************************************************************************** 

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
#include "Alarm.h"

/****************************************************************************
* \brief   - Alarm Class constructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
Alarm::Alarm()
{
}

/*****************************************************************************
* \brief   - Alarm Class destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
Alarm::~Alarm()
{
}

/*****************************************************************************
* \brief   - This method will be executed when entering the Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Alarm::Enter()
{
}

/*****************************************************************************
* \brief   - This method will be executed every 250us while waiting for the.
* 			 reset alarm signal
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Alarm::Loop()
{	
}


/****************************************************************************
* \brief   - This method will be executed when exiting the Alarm state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Alarm::Exit()
{		
}

/******************************************************************************
* 
* \brief   - Alarm Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void Alarm::Fail()
{	
}

