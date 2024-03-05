/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 		It handles process/system data from/to the SM and incoming messages.
***************************************************************************/

#include "PowerSupplyTask.h"
#include "PCStateMachine.h"
#include "DSPTask.h"
#include "PCState.h"
#include "Utils.h"
#include "SystemType.h"

/* Static member variables are initialized */
unsigned int PowerSupplyTask::CoreState = 0;
/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PowerSupplyTask::PowerSupplyTask() 
{
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
PowerSupplyTask::~PowerSupplyTask() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* \brief   - Return the instance of class.
*
* \param   - None.
*
* \return  - instance
*
******************************************************************************/
PowerSupplyTask* PowerSupplyTask::GetInstance()
{
	switch(g_enSystemType)
	{
		case SYSTEM_ACE_PRO:
		case SYSTEM_ACE_PRO_POWER_SUPPLY_ONLY_MODE:	
		{
			static DSPTask instance; 
			return &instance;
		}
		break;
		
		case SYSTEM_L20:
		{
			//static L20 instance; 
			//return &instance;
		}
		break;
		
		default:
		{
			LOGERR((char *)"PowerSupplyTask - SYSTEM TYPE: %d UNKNOWN",g_enSystemType,0,0);
		}
		break;
	}
		
	return nullptr;					  
}

/*************************************************************************//**
 * \brief   - Process the received message from UI_MSG_Q.
 *
 * \param   - struct Message&.
 *
 * \return  - None.
 *
 ******************************************************************************/
void PowerSupplyTask::ProcessTaskMessage(Message& message)
{
	char tmpMsgBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0};
	Message	tmpMsg;
	memset(tmpMsg.Buffer, 0, sizeof(tmpMsg.Buffer));
	// Receive request to process data 
	while(mq_timedreceive(CP->GetMsgQId(CommonProperty::cTaskName[POWER_SUPPLY_T]),tmpMsgBuffer,MAX_SIZE_OF_MSG_LENGTH, 0,&NO_TIMEOUT) != ERROR)
	{
		Decode(tmpMsgBuffer, tmpMsg);
		switch(tmpMsg.msgID)
		{
		default:
			LOGERR((char *)"Power Supply_T : --------Unknown Message ID----------- : ", tmpMsg.msgID, 0, 0);
			break;
		}
	}
}

/**************************************************************************//**
* \brief  	- Specific power supply core status
*			  A value of 0 from DSP side means NO_ERROR.
*			  A value of 1 from the DSP side means SONICS_ON, it is not a failure condition.
*
* \param	- None
*
* \return 	- uint32_t
*
******************************************************************************/
const unsigned int PowerSupplyTask::GetCoreState()
{
	//It returns NO_ERROR when getting dsp status 0 or 1 (SONICS_ON).
	return (CoreState > SONICS_ON) ? CoreState : NO_ERROR;
}

/**************************************************************************//**
* \brief  	- Set specific power supply core status
*
* \param	- uint32_t
*
* \return 	- None
*
******************************************************************************/
void PowerSupplyTask::SetCoreState(unsigned int coreState)
{
	CoreState = coreState;
}

/**************************************************************************//**
* \brief  - Power task entry point and constructor. Handles the
* 			process/system data from/to the SM and incoming messages.
* 			The code will instantiate the related child power task following system type,
* 			such  DSP.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void * PowerSupplyTask::PowerSupply_Task(void *)
{
	Message		ProcessBuffer;	
	UINT32		events;
	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[POWER_SUPPLY_T], taskIdSelf());
	
	PowerSupplyTask *PSTask = PowerSupplyTask::GetInstance();
	PCStateMachine *StateMachinePtr = PCStateMachine::GetInstance();
	
	if(nullptr != PSTask)
	{	
		while(PSTask->bIsTaskRunStatus())
		{
			// wait for any one event
			if(eventReceive(PS_TASK_1MS_EVENT | PS_TASK_QEVENT, EVENTS_WAIT_ANY, WAIT_FOREVER, &events) != ERROR)
			{
				if(events & PS_TASK_1MS_EVENT)
				{
					// process outgoing power supply data to SM here...
					PSTask->PDOUploadRequest();
					// process incoming power supply data from SM here...
					PSTask->PDODownloadRequest();
						
					StateMachinePtr->RunStateMachine();
				}
				if(events & PS_TASK_QEVENT)
				{
					// process incoming messages
					PSTask->ProcessTaskMessage(ProcessBuffer);
				}
			}
		}
		
	}
	else
	{
		LOGERR((char *)"POWERSUPPLY_T : ----------------Memory allocation failed----------------", 0, 0, 0);
	}
	PSTask = NULL;
	taskSuspend(taskIdSelf());
	return nullptr;
}
