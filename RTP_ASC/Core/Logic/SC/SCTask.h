/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SCTASK_H_
#define SCTASK_H_

#include "Common.h"
#include "CommonProperty.h"

class SCTask
{
public:
	
	typedef enum {
		PRIORITY_CONTROL,
		PRIORITY_DATA,
		PRIORITY_REQUEST
		
	} TASK_MSG_PRIORITY;
 	
	SCTask(){
		CP = CommonProperty::getInstance();
	};
	virtual ~SCTask(){};
	
	virtual void			ProcessTaskMessage		() {CP = CommonProperty::getInstance();}
	virtual void 			ProcessTaskMessage		(Message& message, ResponseMessage& response) {}
	virtual void 			ProcessTaskMessage		(Message& message) {}
	virtual void			ProcessTaskMessage		(char * message, TASK_MSG_PRIORITY) {}
	virtual bool			bIsTaskRunStatus		() {return CP->bTaskRun;}

protected:
	virtual void 			Decode					(const char *pRecvBuffer, Message& ReqMessage);
	STATUS					SendToMsgQ 				(Message& msgBuffer, const MSG_Q_ID& msgQID, _Vx_ticks_t waitType = NO_WAIT);	
	CommonProperty 			*CP;
	
};



#endif /* SCTASK_H_ */
