/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   

***************************************************************************/
#include  "ControlTask.h"
#include  "MainTask.h"
#include "ActuatorTask.h"
#include "WeldRecipe.h"
#include  "versions.h"

/**************************************************************************//**
* \brief  - May acquires queue handles for proper intertask communications
* 			and initialize various elements.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
ActuatorTaskSystem::ActuatorTaskSystem()
{
}

/**************************************************************************//**
* \brief  - Process commands received by the message queue from other tasks
* 			It is the entry point for communications with the this task
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void ActuatorTaskSystem::ProcessTaskMessage ()
{
	memset(recvMsgBuffer,0x00,sizeof(recvMsgBuffer));
	
	//Receive request to process actuator system data
	if(mq_receive(CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_SYSTEM_T]), recvMsgBuffer, MAX_SIZE_OF_MSG_LENGTH, NULL) != ERROR)
	{
		memcpy (&message, recvMsgBuffer, sizeof (message));
		
		switch(message.msgID)
		{
		case TO_ACT_SYSTEM_TASK_WELD_RECIPE:
			
			// Sending WELD RECIPE to ACT
			memcpy(&weldRecipeAC,&message.Buffer[0], sizeof(WeldRecipeAC));
			PrintRecipe(weldRecipeAC);
			
			// Send message to actuator here...
			SendMessageToClient (message, strlen(message.Buffer));
			break;
			
		case TO_ACT_SYSTEM_TASK_WELD_RECIPE_RELOAD:
			
			// Sending WELD RECIPE to ACT
			GetAcWeldRecipe(message.Buffer);

			// Send message to actuator here...
			SendMessageToClient (message, strlen(message.Buffer));
			break;
			
		case TO_ACT_SYSTEM_TASK_WELD_RECIPE_RESP:
			
			message.msgID = TO_UI_TASK_WELD_RECIPE_RESP_AC;
			SendToMsgQ(message,CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[UI_T]));
			break;
			
		case TO_ACT_SYSTEM_TASK_ALARM_DATA_REQ:
		case TO_ACT_SYSTEM_TASK_CAL_DATA_REQ:
		case TO_ACT_SYSTEM_TASK_CAL_READ_REQ:
			
			// Send message to actuator here...
			SendMessageToClient (message, strlen(message.Buffer));
			break;
			
		case TO_ACT_SYSTEM_TASK_ALARM_DATA_RESP:
			break;

		case TO_ACT_SYSTEM_TASK_VERSION_SERIAL_REQ:
			ACTSerVerNoRequest();		
			break;
			
		case TO_ACT_SYSTEM_TASK_VERSION_SERIAL_RESP:
			CP->bActSrNoVerNoReceived = true;	
			message.msgID = TO_UI_TASK_VERSION_SERIAL_REQUEST_RESP_AC;

			SendToMsgQ(message,CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[UI_T]));
			break;
		
		case TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_REQ:
			SendMessageToClient(message, ACT_REQUEST_MSG_PAYLOAD_SIZE);
			break;	
			
		case TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_RESP:
			break;
			
		case TO_ACT_SYSTEM_TASK_CAL_DATA__RESP:
			
			message.msgID = TO_UI_CALIBRATION_DATA_REQUEST_RESP;
			SendToMsgQ(message,CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[UI_T]));
			break;
			
		case TO_ACT_SYSTEM_TASK_CAL_READ_RESP:
			
			message.msgID = TO_UI_TASK_CALIBRATION_READ_RES;
			SendToMsgQ(message,CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[UI_T]));
			break;

		default:
			LOGWARN((char *)"\nACTUATOR_SYSTEM_T : Unknown message received",0,0,0);
			break;
		}
	}
}


/**************************************************************************//**
* \brief  - Recalls the saved weld recipe within the system
* 			
*
* \param  - char* pRecipe
*
* \return  - bool
*
******************************************************************************/
bool ActuatorTaskSystem::GetAcWeldRecipe (char* pRecipe)
{
	bool bStatus = true;
	return bStatus;
}


/**************************************************************************//**
* \brief  - ActuatorTask destructor
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
ActuatorTaskSystem::~ActuatorTaskSystem()
{
}

/**************************************************************************//**
 * \brief  - send serial no and version no request to AC 
 *
 * \param  - None
 *
 * \return  - None
 *
 ******************************************************************************/

void ActuatorTaskSystem::ACTSerVerNoRequest() 
{

	memset(message.Buffer, 0x00, sizeof(message.Buffer));
	message.msgID = TO_ACT_SYSTEM_TASK_VERSION_SERIAL_REQ;

	// Send message to actuator here...
	if (SendMessageToClient(message, ACT_REQUEST_MSG_PAYLOAD_SIZE) == ERROR)
		LOGERR((char* )"ACTUATOR_SYSTEM_T :ACTSerVerNoRequest: failed", 0, 0, 0);

}

/**************************************************************************//**
* \brief  - System actuator task entry point and constructor. Handles the system
* 			data i.e. recipes, alarms, calibration data and other management information 
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void* ActuatorTaskSystem::Actuator_System_Task (void *)
{	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[ACTUATOR_SYSTEM_T], taskIdSelf());

	ActuatorTask * pActuatorTask     = new (nothrow) ActuatorTaskSystem();

	if(NULL != pActuatorTask)
	{
		/* Actuator Task loop if the main's bIsTaskRun flag is enabled */
		while (pActuatorTask->bIsTaskRunStatus())
		{
			pActuatorTask->ProcessTaskMessage();
		}

		delete pActuatorTask;
	}
	else
	{
		LOGERR((char *)"\nACTUATOR_SYSTEM_T : ------------- Allocation failed",0,0,0);
	}

	LOGINFO((char *)"ACTUATOR_SYSTEM_T : ------------- Task Terminated",0,0,0);

	taskDelete(taskIdSelf());
	return nullptr;
}
