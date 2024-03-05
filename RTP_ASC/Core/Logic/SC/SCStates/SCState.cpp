/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	 This file processes the messages based on MsgQ-ID
***************************************************************************/

#include "SCState.h"

/**************************************************************************//**
* \brief   - Constructor-Task's message queue ID
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
SCState::SCState() 
{
	CP = CommonProperty::getInstance();		
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
SCState::~SCState() 
{
}

