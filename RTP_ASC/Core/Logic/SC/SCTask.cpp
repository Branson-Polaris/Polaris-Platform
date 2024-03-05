/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Task functions for ASC

**********************************************************************************************************/
#include "SCTask.h"
#include "MainTask.h"
/**************************************************************************//**
* 
* \brief  - Decodes the received buffer from the message queue into a
* 			structured message.
*
* \param   - char *pRecvBuffer, MESSAGE& ReqMessage.
*
* \return  - None
*
******************************************************************************/
void SCTask::Decode(const char *pRecvBuffer, Message& ReqMessage)
{
	memcpy(&ReqMessage.msgID, pRecvBuffer, sizeof(ReqMessage.msgID));
	memcpy(ReqMessage.Buffer, pRecvBuffer + sizeof(ReqMessage.msgID), MAX_SIZE_OF_MSG_LENGTH - sizeof(ReqMessage.msgID));
}

/**************************************************************************//**
* \brief  - Posts the encoded message to the destination message queue of
* 			a given task  
*
* \param  - Message& msgBuffer
* \param  - MSG_Q_ID &msgQID
* \param  - _Vx_ticks_t waitType	
*
* \return  - STATUS status
*
******************************************************************************/
STATUS SCTask::SendToMsgQ (Message& msgBuffer, const MSG_Q_ID& msgQID, _Vx_ticks_t waitType)
{
	CommonProperty 	*CP = CommonProperty::getInstance();
	STATUS status = ERROR;
	
	//Send request to specific task according to msgQID
	if(mq_timedsend(msgQID, reinterpret_cast<char*>(&msgBuffer), sizeof (msgBuffer), 0, &NO_TIMEOUT) != ERROR)
	{
		if (msgQID == CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T]))
		{
			// enter event for incoming process data
			if(eventSend (CP->GetTaskId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T]), ACT_TASK_TX_EVENT) == OK)
				status = OK;
			else
				LOGERR((char *) "ACTUATOR_PROCESS_T: eventSend: Error\n",0,0,0);
		}
		else if (msgQID == CP->GetMsgQId(CommonProperty::cTaskName[POWER_SUPPLY_T]))
		{		
			// enter event for queue data
			if(eventSend (CP->GetTaskId(CommonProperty::cTaskName[POWER_SUPPLY_T]), PS_TASK_QEVENT) == OK)
				status = OK;
			else
				LOGERR((char *) "POWER_SUPPLY_T: eventSend: Error\n",0,0,0);
		}
		else
			status = OK;
	}
	else
		LOGERR((char *) "SCTask: SendToMsgQ: msgQSend Error\n",0,0,0);

	return status;
}
