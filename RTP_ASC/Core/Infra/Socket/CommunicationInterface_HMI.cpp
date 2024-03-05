/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * CommunicationInterface_HMI.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: DShilonie
 */

#include "CommunicationInterface_HMI.h"
#include "Common.h"

HMI_CommunicationInterface* HMI_CommunicationInterface::obj = NULL;
int HMI_CommunicationInterface::count;

HMI_CommunicationInterface::HMI_CommunicationInterface()
	: m_CommunicationStatus(SOCKET_LINK)
	, m_SocketConnectedDescriptor(-1)
{

}


HMI_CommunicationInterface::~HMI_CommunicationInterface()
{
	count = 0;
	if (obj)
		delete obj;
}

/**************************************************************************//**
* \brief  - Creates the new instance of the HMI communications object if not
* 			present else returns the object if already present.
* 
* \param  - None
*
* \return - HMI_CommunicationInterface* Object
* 
******************************************************************************/
HMI_CommunicationInterface* HMI_CommunicationInterface::getInstance()
{
	if(obj != NULL)
	{
		return obj;
	}
	else
	{
		obj = new HMI_CommunicationInterface();
		count += 1;
	}
	return obj;
}
