/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
/*
 * CommunicationInterface_ACT.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: DShilonie
 */


#include "CommunicationInterface.h"
#include "CommunicationInterface_ACT.h"

ACT_CommunicationInterface* ACT_CommunicationInterface::obj = NULL;
int ACT_CommunicationInterface::count;

ACT_CommunicationInterface::~ACT_CommunicationInterface()
{
	count = 0;
	if (obj)
		delete obj;
}

/**************************************************************************//**
* \brief  - Creates the new instance of the ACT communications object if not
* 			present else returns the object if already present.
* 
* \param  - None
*
* \return - ACT_CommunicationInterface* Object
* 
******************************************************************************/
ACT_CommunicationInterface* ACT_CommunicationInterface::getinstance()
{
	if(obj != NULL)
	{
		return obj;
	}
	else
	{
		obj = new ACT_CommunicationInterface;
		count += 1;
	}
	return obj;
}

