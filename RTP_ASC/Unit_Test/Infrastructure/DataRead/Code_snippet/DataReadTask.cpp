/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     UI Database Interface task for DB related read or write operations  
 
**********************************************************************************************************/

//#include "DataInterface.h"
#include "CommonProperty.h"
#include "CommunicationInterface_HMI.h"
#include "SocketReceiver.h"
#include "Common.h"
#include "WeldRecipe.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "DataReadTask.h"
extern "C"
{
	#include "customSystemCall.h"	
}
DataReadInterface::DataReadInterface()
{

}

DataReadInterface::~DataReadInterface()
{
	
}

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
void DataReadInterface::DecodeDataReadMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage)
{
	memcpy(&ReqMessage.msgID, pRecvBuffer, sizeof(ReqMessage.msgID));
	memcpy(&ReqMessage.task_msgQID, pRecvBuffer + sizeof(ReqMessage.msgID), sizeof(ReqMessage.task_msgQID));
	memcpy(ReqMessage.Buffer, pRecvBuffer + sizeof(ReqMessage.msgID) + sizeof(ReqMessage.task_msgQID), MAX_SIZE_OF_MSG_LENGTH - sizeof(ReqMessage.msgID)-sizeof(ReqMessage.task_msgQID));
}


void DataReadInterface::ProcessTaskMessage(DataReadWrite_Message & datarequestBuffer)
{  
	Message	ResponseBuffer;
	WeldResult testWelddata;
	testWelddata.CycleCounter=2;
	testWelddata.EndHoldForce=3;
	printf("ProcessTaskMessage1\n");	
    switch(datarequestBuffer.msgID)
    {
    
	case LAST_WELD_RESULT_DATA_READ_REQ:
		ResponseBuffer.msgID=LAST_WELD_RESULT_DATA_READ_RES ;
		memcpy(ResponseBuffer.Buffer, &testWelddata, sizeof(WeldResult));
		SendToMsgQ(ResponseBuffer, datarequestBuffer.task_msgQID);
		printf("LAST_WELD_RESULT_DATA_READ_REQ sent from data read\n");
		break;
		
	case LAST_WELD_SIGNATURE_DATA_READ_REQ :
		
		break;
	default:
		//LOGERR((char* )"DataReadTask: --------Unknown Message ID----------- : %d", message.msgID, 0, 0);
		break;     
   
    }
    
    
    
}




/**************************************************************************//**
* 
* \brief   - Processing the User data that will be related any database operation.
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
			if(msgQReceive(CP->GetMsgQId(CommonProperty::cTaskName[DATA_READ_T]), msgBuffer, MAX_SIZE_OF_MSG_LENGTH, WAIT_FOREVER) != ERROR)
			{
				printf("Data_Read_Task(void* )1\n");
				DataReadInterfaceInit->DecodeDataReadMessage(msgBuffer, ReqMessage);
				DataReadInterfaceInit->ProcessTaskMessage(ReqMessage);			
			}
		}	
		delete DataReadInterfaceInit;
	}
	else
	{
		LOGERR((char *)"DATA_READ_INTERFACE_T : ----------------Memory allocation failed----------------",0,0,0);
	}
	DataReadInterfaceInit = NULL;	
	taskSuspend(taskIdSelf());
	return nullptr;	
}

    
