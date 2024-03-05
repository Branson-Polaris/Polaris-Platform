/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     DataWriteTask for DB related write  operations  
 
**********************************************************************************************************/

#include "CommonProperty.h"
#include "Common.h"
#include "DataWriteTask.h"
#include <string.h>
#include <stdio.h>
size_t DataWriteInterface::static_log_id=0;
extern "C"
{
	#include "customSystemCall.h"	
}

/**************************************************************************//**
* 
* \brief   - Constructor - initialize the data members of DataWritetask.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
DataWriteInterface::DataWriteInterface()
{
	static_log_id = logger::enroll(this);
}

/**************************************************************************//**
* 
* \brief   - Destructor of DataWritetask..
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
DataWriteInterface::~DataWriteInterface()
{
	
}

/**************************************************************************//**
* 
* \brief  - Decodes the received buffer from the message queue into a
* 			structured message.
*
* \param   - char *pRecvBuffer:received buffer from the message queue.
* 			 DataReadWrite_Message&ReqMessage:the structured message in which the
* 			 decoded data like msgid,taskmsgQID ,data Buffer is stored.
*
* \return  - None
*
******************************************************************************/
inline void DataWriteInterface::DecodeDataWriteMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage)
{
	memcpy(&ReqMessage.msgID, pRecvBuffer, sizeof(ReqMessage.msgID));
	memcpy(&ReqMessage.task_msgQID, pRecvBuffer + sizeof(ReqMessage.msgID), sizeof(ReqMessage.task_msgQID));
	memcpy(ReqMessage.Buffer, pRecvBuffer + sizeof(ReqMessage.msgID) + sizeof(ReqMessage.task_msgQID), MAX_SIZE_OF_MSG_LENGTH - sizeof(ReqMessage.msgID)-sizeof(ReqMessage.task_msgQID));
}

/**************************************************************************//**
* \brief   - Process Write commands received from MsgQ.
*
* \param-	DataReadWrite_Message&ReqMessage:the structured message in which the
* 			 decoded data like msgid,taskmsgQID ,data Buffer is stored.
* 
* \return  - None.
*
******************************************************************************/
void DataWriteInterface::ProcessTaskMessage(DataReadWrite_Message & datarequestBuffer)
{  
	Message	ResponseBuffer;

    switch(datarequestBuffer.msgID)
    {
    
	case LAST_WELD_RESULT_DATA_WRITE:
		ResponseBuffer.msgID=LAST_WELD_RESULT_DATA_WRITE;
		SendToMsgQ(ResponseBuffer, datarequestBuffer.task_msgQID);
		break;
		
	case LAST_WELD_SIGNATURE_DATA_WRITE:
		
		break;
	default:
		char  msg[buff_size_config];
		snprintf(msg,buff_size_config,"Unknown MsgID=%d\n",datarequestBuffer.msgID);
		int return_val = logger::add_entry(static_log_id ,SEVERITY::LOG_GENERAL_INFO, (uint8_t*)msg, sizeof(msg));
		break;     
   
    }    
    
}

/**************************************************************************//**
* 
* \brief   - Processing the User data write  request that will be related any database operation.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void *DataWriteInterface ::Data_Write_Task(void* )
{   
	char msgBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0x00};
	CommonProperty *CP = CommonProperty::getInstance();
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[DATA_WRITE_T], taskIdSelf());
	DataWriteInterface *DataWriteInterfaceInit = new(nothrow) DataWriteInterface();
	DataReadWrite_Message ReqMessage;
	
	if(NULL != DataWriteInterfaceInit)
	{
		while(DataWriteInterfaceInit->CP->bTaskRun)
		{
			if(mq_receive(CP->GetMsgQId(CommonProperty::cTaskName[DATA_WRITE_T]), msgBuffer, MAX_SIZE_OF_MSG_LENGTH,NULL ) != ERROR)
			{
				DataWriteInterfaceInit->DecodeDataWriteMessage(msgBuffer, ReqMessage);
				DataWriteInterfaceInit->ProcessTaskMessage(ReqMessage);			
			}
			else
			{
				char  msg[buff_size_config];
				snprintf(msg,buff_size_config,"msgQRecv fail\n");
				int return_val = logger::add_entry(static_log_id,SEVERITY::LOG_GENERAL_INFO, (uint8_t*)msg, sizeof(msg));
				
			}
		}	
		delete DataWriteInterfaceInit;
	}
	else
	{
		char  msg[buff_size_config];
		snprintf(msg,buff_size_config,"Mem alloc fail\n");
		int return_val = logger::add_entry(static_log_id,SEVERITY::LOG_ALARM , (uint8_t*)msg, sizeof(msg));
	}
	DataWriteInterfaceInit = NULL;	
	taskSuspend(taskIdSelf());
	return nullptr;	
}

    
