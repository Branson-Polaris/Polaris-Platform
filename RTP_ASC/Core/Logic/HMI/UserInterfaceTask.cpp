/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
#include "UserInterface.h"
#include "versions.h"
#include <string.h>
#include <usrFsLib.h>
#include "MainTask.h"
#include "version_common.h"
#include "WeldRecipeSC.h"
#include "WeldRecipe.h"
#include "SystemInformation.h"
#include "CommunicationInterface_HMI.h"
#include "SocketReceiver.h"

extern "C"
{
	#include "customSystemCall.h"	
}

/**************************************************************************//**
* 
* \brief   - Constructor - initialize the data members of UserInterface.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
UserInterface::UserInterface() 
{		
	socketInterface = HMI_CommunicationInterface::getInstance();
}

/*************************************************************************//**
* \brief   -  Sends CMD(weld, seek, Setup and Scan) to Control task.
*
* \param   - Message& message.
*
* \return  - None.
*
******************************************************************************/
 void UserInterface::SendMessageToControlTask(Message& message)
{	
	 bool bIsIdValid = true;

	 switch(message.msgID)
	 {
		 case TO_UI_TASK_WELD_CMD:
			 message.msgID = TO_CTRL_TASK_WELD_CMD;
			 break;
	
		 case TO_UI_TASK_SETUP_CMD:
			 message.msgID = TO_CTRL_TASK_SETUP_CMD;
			 break;

		 case TO_UI_TASK_SET_NEXT_OPERATION_REQ:
			 message.msgID = TO_CTRL_TASK_SET_NEXT_OPERATION_REQ;
			 break;

		 case TO_UI_TASK_HORN_SCAN_CMD:
			 message.msgID = TO_CTRL_TASK_HORN_SCAN_CMD;
			 break;
	
		 case TO_UI_TASK_HORN_SCAN_ABORT_CMD:
			 message.msgID = TO_CTRL_TASK_HORN_SCAN_ABORT_CMD;
			 break;
	
		 case TO_UI_TASK_RESET_ALARM_CMD:
			 message.msgID = TO_CTRL_TASK_RESET_ALARM_CMD;
			 break;
	
		 case TO_UI_TASK_SC_STATE_REQ:
			 message.msgID = TO_CTRL_TASK_SC_STATE_REQ;
			 break;
	
		 case TO_UI_TASK_WELD_RECIPE_CONFIGURED:
			 message.msgID = TO_CTRL_TASK_WELD_RECIPE_CONFIGURED;
			 break;
	
		 case TO_UI_TASK_SEEK_RECIPE_CONFIGURED:
			 message.msgID = TO_CTRL_TASK_SEEK_RECIPE_CONFIGURED;
			 break;
	
		 case TO_UI_TASK_TEST_CMD_REQ:
			 message.msgID = TO_CTRL_TASK_TEST_CMD_REQ;
			 break;
	
		 case TO_UI_TASK_TEST_ABORT_CMD_REQ:
			 message.msgID = TO_CTRL_TASK_TEST_ABORT_CMD_REQ;
			 break;
	
		 case TO_UI_TASK_CALIBRATION_CMD_REQ:
			 message.msgID = TO_CTRL_TASK_CALIBRATION_CMD_REQ;
			 break;
	
		 case TO_UI_TASK_BATCH_COUNT_RESET_REQ:
			 message.msgID = TO_CTRL_TASK_BATCH_COUNT_RESET_CMD_REQ;
			 break;
	
		 case TO_UI_TASK_BATCH_COUNT_EXCEED_CMD:
			 message.msgID = TO_CTRL_TASK_BATCH_COUNT_EXCEED_CMD;
			 break;
			 
		 case TO_UI_TASK_EMMC_WEAR_LEVEL_REQ:
			 LOGINFO((char *)"\nUI_T : TO_UI_TASK_EMMC_WEAR_LEVEL_REQ\n",0,0,0);
			 message.msgID = TO_CTRL_TASK_EMMC_WEAR_LEVEL_REQ;
			 break;

		 case TO_UI_TASK_OPTIMIZE_DATABASE_REQ:
			 message.msgID = TO_CTRL_TASK_OPTIMIZE_DATABASE_REQ;
			 break;
		 default:
			 bIsIdValid = false;
			 LOGINFO((char *)"UI_T : trying to send Invalid Msg id to Control Task : %d",message.msgID,0,0); 
			 break;
	 }

	 if(bIsIdValid)
	 {
		 SendToMsgQ (message, CP->GetMsgQId(CommonProperty::cTaskName[CTRL_T]));
	 }
 }
 
 /**************************************************************************//**
 * 
 * \brief   - Prepare message and sends to ACT or DSP Tasks message queue.
 *
 * \param   - Message& message
 *
 * \return  - None.
 *
 ******************************************************************************/
 void UserInterface::SendMessageToACTDSPTask(Message& message)
 {
	 switch(message.msgID)
	 {
		 case TO_UI_TASK_WELD_RECIPE:
			 message.msgID = TO_ACT_SYSTEM_TASK_WELD_RECIPE;
			 SendToMsgQ (message, CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_SYSTEM_T]));
			 break;
			 
		 case TO_UI_TASK_SYS_INFO_WRITE_REQ:
			 message.msgID = TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_REQ;
			 SendToMsgQ (message, CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_SYSTEM_T]));
			 break;

		default:
			LOGWARN((char *)"UI_T : Invalid msgId to send to ACT/DSP msgQ : %d",message.msgID,0,0);
			break;
	 }
	 
 }

/*************************************************************************//**
 * \brief   - Process the received message from UI_MSG_Q.
 *
 * \param   - struct Message&.
 *
 * \return  - None.
 *
 ******************************************************************************/
void UserInterface::ProcessTaskMessage(Message& message)
{
	UINT32 msgLen = 0;
	UINT8 status;
	INT32 socketStatus = 0;
	string details;
	char signal;
	
	switch(message.msgID)
	{	
		case TO_UI_TASK_WELD_RECIPE:
			SendMessageToACTDSPTask(message);
			break;

		case TO_UI_TASK_VERSION_SERIAL_REQUEST_RESP_AC:
		{
			// storing AC version info locally, it can be retrieved by the UI
			FWVersion::Set(FW_VERSION_AC, VERSION_MAJOR, message.Buffer[0]);
			FWVersion::Set(FW_VERSION_AC, VERSION_MINOR, message.Buffer[1]);
			FWVersion::Set(FW_VERSION_AC, VERSION_BUILD, message.Buffer[2]);
			FWSerial::Set(FW_VERSION_AC, &message.Buffer[SER_VER_NO_HDR_SIZE]);
			FWVersion::PrintVersion(FW_VERSION_AC);

			FWCrc::Set(FW_CRC_AC, 0);
			FWInfo::Set(FW_INFO_AC, 0);
		}
		break;

		case TO_UI_TASK_SYSINFO_READ_REQ:
			message.msgID = UIC_SYSINFO_READ_RES;
			memset(message.Buffer, 0x00, sizeof(message.Buffer));
			msgLen = SystemInformation::AccessSystemInformation(message.Buffer);
			NotifyResponseToClient(message, msgLen);
			break;
			
		case TO_UI_TASK_SYS_INFO_WRITE_REQ:
			SendMessageToACTDSPTask(message);
			break;
			
		default:
			LOGERR((char *)"UI_T : --------Unknown Message ID----------- : ",message.msgID,0,0);
			break;
	}
}

/*************************************************************************//**
* \brief   -  On power up, request for FW version data of slaves. 
*
* \param   -  UINT8 typeOfReq
*
* \return  -  None
*
******************************************************************************/
void UserInterface::PowerOnRequest (UINT8 typeOfReq)
{
	Message powerOnReq;
	powerOnReq.msgID = 0;
	memset(powerOnReq.Buffer, 0x00, sizeof(powerOnReq.Buffer));
}

/**************************************************************************//**
* 
* \brief   - Decodes the received message from UI_MSG_Q . 
*
* \param   - char *pRecvBuffer, Message& destBuffer.
*
* \return  - struct Message.
*
******************************************************************************/
void UserInterface::DeCoder(char *pRecvBuffer, Message& ReqMessage) 
{
	memcpy(&ReqMessage.msgID, pRecvBuffer, sizeof(ReqMessage.msgID));
	memcpy(ReqMessage.Buffer, pRecvBuffer + sizeof(ReqMessage.msgID), MAX_SIZE_OF_MSG_LENGTH - sizeof(ReqMessage.msgID));
}

/**************************************************************************//**
* 
* \brief   - Get the response status of message sent to client over socket.
*
* \param   - Message& message, UINT16 buffLen.
*
* \return  - boolean (fail -1 or success >=0)
*
******************************************************************************/
bool UserInterface::NotifyResponseToClient(Message& message, UINT32 buffLen)
{
	Client_Message sendBuffer;
	bool bSocketSendResponse = false;
	char outBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0};
	memset(sendBuffer.Buffer, 0x00, sizeof(sendBuffer.Buffer));
	
	sendBuffer.msgID 	= message.msgID;
	sendBuffer.msgLen 	= buffLen;
	sendBuffer.rspCode	= 0;
	
	if(sendBuffer.msgLen > MAX_SIZE_OF_MSG_BUFF)
	{
		LOGERR((char *)"UI_T : Invalid message limit : %d, msg_ID : %d",sendBuffer.msgLen, sendBuffer.msgID, 0);
	}
	else
	{
		memcpy(sendBuffer.Buffer, message.Buffer, sendBuffer.msgLen);
		bSocketSendResponse = HMI_SocketReceiver::SendMessageToClient(&sendBuffer, sendBuffer.msgLen);	
	}

	return bSocketSendResponse;
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
UserInterface::~UserInterface()
{
	CP = NULL;
}

/**************************************************************************//**
* 
* \brief   - Processing the User data.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void* UserInterface::UserInterface_Task( void *)
{
	Message		ProcessBuffer;
	char		MsgQBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0x00};	
	CommonProperty *CP = CommonProperty::getInstance();
	CP->SetTaskId(CommonProperty::cTaskName[UI_T], taskIdSelf());
	
	UserInterface	*UI	= new(nothrow) UserInterface();
	
	if(NULL != UI)
	{
		/* UserInterface Task loop and the bIsTaskRun flag enabled when task created */
		while(UI->bIsTaskRunStatus())
		{
			//UI task stays in wait forever timeout till Receive request to Process the User data.
			if(mq_receive(CP->GetMsgQId(CommonProperty::cTaskName[UI_T]),MsgQBuffer,sizeof(MsgQBuffer), NULL) != ERROR)
			{
				UI->DeCoder(MsgQBuffer,ProcessBuffer);
				UI->ProcessTaskMessage(ProcessBuffer);
			}
		}
		
		delete UI;
	}
	else
	{
		LOGERR((char *)"UI_T : ----------------Memory allocation failed----------------",0,0,0);
	}
	
	UI = NULL;	
	taskSuspend(taskIdSelf());
	return nullptr;
}
