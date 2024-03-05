/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     DataReadTask for DB related read  operations  
 
**********************************************************************************************************/

#include "CommonProperty.h"
#include "Common.h"
#include "DataReadTask.h"
#include <string.h>
#include <stdio.h>
size_t DataReadInterface::static_log_id=0;
extern "C"
{
	#include "customSystemCall.h"	
}

/**************************************************************************//**
* 
* \brief   - Constructor - initialize the data members of DataReadtask.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
DataReadInterface::DataReadInterface()
{
	this->log_id = logger::enroll(this);	
	static_log_id = logger::enroll(this);
}

/**************************************************************************//**
* 
* \brief   - Destructor of DataReadtask..
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
DataReadInterface::~DataReadInterface()
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
inline void DataReadInterface::DecodeDataReadMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage)
{
	memcpy(&ReqMessage.msgID, pRecvBuffer, sizeof(ReqMessage.msgID));
	memcpy(&ReqMessage.task_msgQID, pRecvBuffer + sizeof(ReqMessage.msgID), sizeof(ReqMessage.task_msgQID));
	memcpy(ReqMessage.Buffer, pRecvBuffer + sizeof(ReqMessage.msgID) + sizeof(ReqMessage.task_msgQID), MAX_SIZE_OF_MSG_LENGTH - sizeof(ReqMessage.msgID)-sizeof(ReqMessage.task_msgQID));
}

/**************************************************************************//**
* \brief   - Process Read commands received from MsgQ.
*
* param-	DataReadWrite_Message&ReqMessage:the structured message in which the
* 			 decoded data like msgid,taskmsgQID ,data Buffer is stored.
* 
* \return  - None.
*
******************************************************************************/
void DataReadInterface::ProcessTaskMessage(DataReadWrite_Message & datarequestBuffer)
{  
	Message	ResponseBuffer;

    switch(datarequestBuffer.msgID)
    {
    
	case LAST_WELD_RESULT_DATA_READ:
		ResponseBuffer.msgID=LAST_WELD_RESULT_DATA_READ;
		SendToMsgQ(ResponseBuffer, datarequestBuffer.task_msgQID);
		break;
		
	case LAST_WELD_SIGNATURE_DATA_READ :
		
		break;
	default:
		char  msg[buff_size_config];
		sprintf(msg,"Unknown MsgID=%d\n",datarequestBuffer.msgID);
		int return_val = logger::add_entry(this->log_id,SEVERITY::LOG_GENERAL_INFO, (uint8_t*)msg, sizeof(msg));
		break;     
   
    }    
    
}

/**************************************************************************//**
* 
* \brief   - Processing the User data read  request that will be related any database operation.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void *DataReadInterface ::Data_Read_Task(void* )
{   
	char msgBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0x00};
	CommonProperty *CP = CommonProperty::getInstance();
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[DATA_READ_T], taskIdSelf());
	DataReadInterface *DataReadInterfaceInit = new(nothrow) DataReadInterface();
	DataReadWrite_Message ReqMessage;
	
	if(NULL != DataReadInterfaceInit)
	{
		while(DataReadInterfaceInit->CP->bTaskRun)
		{
			if(mq_receive(CP->GetMsgQId(CommonProperty::cTaskName[DATA_READ_T]), msgBuffer, MAX_SIZE_OF_MSG_LENGTH,NULL ) != ERROR)
			{
				DataReadInterfaceInit->DecodeDataReadMessage(msgBuffer, ReqMessage);
				DataReadInterfaceInit->ProcessTaskMessage(ReqMessage);			
			}
			else
			{
				char  msg[buff_size_config];
				sprintf(msg,"msgQRecv fail\n");
				int return_val = logger::add_entry(static_log_id,SEVERITY::LOG_GENERAL_INFO, (uint8_t*)msg, sizeof(msg));
				
			}
		}	
		delete DataReadInterfaceInit;
	}
	else
	{
		char  msg[buff_size_config];
		sprintf(msg,"Mem alloc fail\n");
		int return_val = logger::add_entry(static_log_id,SEVERITY::LOG_ALARM , (uint8_t*)msg, sizeof(msg));
	}
	DataReadInterfaceInit = NULL;	
	taskSuspend(taskIdSelf());
	return nullptr;	
}

    
