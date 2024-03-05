/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
/*
 * CommunicationInterface_ACT.h
 *
 *  Created on: Mar 25, 2021
 *      Author: DShilonie
 */

#ifndef COMMUNICATIONINTERFACE_ACT_H_
#define COMMUNICATIONINTERFACE_ACT_H_


#include "EmrsnSocket.h"
#include "CommunicationInterface.h"

class ACT_CommunicationInterface:public CommunicationInterface
{
public:
	
	~ACT_CommunicationInterface ();
	
	static ACT_CommunicationInterface*  getinstance();

private:
	static ACT_CommunicationInterface *obj;
	static int 						count;

};

#endif /* COMMUNICATIONINTERFACE_ACT_H_ */
