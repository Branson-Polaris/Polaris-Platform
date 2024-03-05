/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 		This file Controls state machine functionalities
***************************************************************************/

#include "SC.h"
#include "MainTask.h"
#include "ControlTask.h"
#include "Utils.h"
extern "C"
{
	#include <customSystemCall.h>
}

// Static member variables are initialized
//NO_OPERATION; RBF: temporary WELD state 
OPERATION 	ControlTask::OpType				= WELD;		
// Will be assigned with latest counter from DB on power up
UINT32		ControlTask::m_CycleCounter		= 0;		
bool		ControlTask::bAlarmReset 		= false;
bool		ControlTask::bSuspectStatus 	= false;
bool		ControlTask::bRejectStatus 		= false;

/**************************************************************************//**
* 
* \brief   - Constructor - initialize the data members of ControlTask.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ControlTask::ControlTask()
{		
	// initialize SC StateMachine pointer based on platform type
	string Platform_Name = GetSystemTypeName();
	
	if(Platform_Name ==  "ACE Pro Power Supply Only Mode")
	{	
		SC::stateMachine = new SCStateMachineFromGPIO();
	}
	else if (Platform_Name ==  "ACE Pro")
	{
		SC::stateMachine = new SCStateMachineAcePro();
	}
	else
	{
		//TODO : handle error
	}
	
}
/**************************************************************************//**
* \brief   - Process commands(WELD,SEEK received from MsgQ.
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::ProcessTaskMessage(Message& message)
{	
	switch(message.msgID)
	{
		case TO_CTRL_OPERATE_MODE_SET:			
			LOGINFO((char *)"CTRL_T : -------Weld command received-------",0,0,0);
			// To identify what operation (weld) selected chosen in consoleApp or UIC
			OpType 		= WELD;							
			SC::stateMachine->LoadStatesHandler(SCStateMachine::WELD);
			break;
		
		case TO_CTRL_TASK_WELD_CMD_FROM_GPIO:
			LOGINFO((char *)"CTRL_T : -------Weld command received from GPIO-------",0,0,0);
			OpType 		= WELD;
			SC::stateMachine->LoadStatesHandler(SCStateMachine::WELD);
			break;

		case TO_CTRL_TASK_SEEK_CMD:
			LOGINFO((char *)"CTRL_T : -------Seek command received-------",0,0,0);
			// To identify what operation (seek) selected
			OpType 		= SEEK;			
			SC::stateMachine->LoadStatesHandler(SCStateMachine::SEEK);
			break;
			
		default:
			LOGERR((char *)"CTRL : ----------Unknown Message ID------------- : %d",message.msgID,0,0);
			break;
	}
}

/**************************************************************************//**
* \brief   - Process State machine and Message received from MsgQ. 
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::StateMachineHandler()
{	
	switch(OpType)
	{
		case WELD:
			//Run SC State Machine for WELD OP
			SC::stateMachine->RunStateMachine();	
			break;
		
		case SEEK:
			//Run SC State Machine for SEEK OP
			SC::stateMachine->RunStateMachine();	
			break;
			
		default:
			SC::stateMachine->RunStateMachine();	
			break;
	}
	
}


/**************************************************************************//**
* \brief   - Returns the current operation type (Weld or Seek) 
*
* \param   - None
* 
* \return  - OPERATION OpType
*
******************************************************************************/
OPERATION ControlTask::GetOperationType()
{
	return OpType;	
}

/**************************************************************************//**
* \brief   - Sets the selected operation(Weld or Seek) from UIC.  
*
* \param   - OPERATION - typeOfOp - weld, seek. setup, alarm or horn scan. 
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::SetOperationType(OPERATION typeOfOp)
{
	OpType = typeOfOp;
}

/**************************************************************************//**
* \brief   - Triggers the ConsoleApp task for user input 
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::TriggerConsoleTask()
{
#if CONSOLE_DBG
	eventSend(CP->GetTaskId(CommonProperty::cTaskName[CONSOLE_T]),CONSOLE_EVENT);
#endif
}

/**************************************************************************//**
* \brief   - Updates cycle counter when weld cycle met trigger point.
* 
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ControlTask::UpdateCycleCounter()
{
	m_CycleCounter = m_CycleCounter + 1;
}

/**************************************************************************//**
* \brief   - Stub function for the cycle counter getting
* 
* \param   - None.
*
* \return  - m_CycleCounter.
*
******************************************************************************/
unsigned int ControlTask::GetCycleCounter()
{
	return m_CycleCounter;
}

/**************************************************************************//**
* \brief   - Returns status of alarm clearance for purposes of handling it
* 			 in other states 
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
bool ControlTask::IsAlarmReset()
{
	return bAlarmReset;
}

/**************************************************************************//**
* \brief   - Returns status of suspect for purposes of handling it
* 			 in other states 
*
* \param   - None.
* 
* \return  - bool.
*
******************************************************************************/
bool ControlTask::IsSuspectStatus()
{
	return bSuspectStatus;
}

/**************************************************************************//**
* \brief   - Returns status of reject for purposes of handling it
* 			 in other states 
*
* \param   - None.
* 
* \return  - bool.
*
******************************************************************************/
bool ControlTask::IsRejectStatus()
{
	return bRejectStatus;
}

/**************************************************************************//**
* \brief   - Sets status of alarm clearance for purposes of handling it
* 			 in other states 
*
* \param   - bool.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::SetIsAlarmReset(bool set)
{
	bAlarmReset = set;
}

/**************************************************************************//**
* \brief   - Sets status of suspect  for purposes of handling it
* 			 in other states 
*
* \param   - bool.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::SetIsSuspectStatus(bool set)
{
	bSuspectStatus = set;
}

/**************************************************************************//**
* \brief   - Sets status of reject  for purposes of handling it
* 			 in other states 
*
* \param   - bool.
* 
* \return  - None.
*
******************************************************************************/
void ControlTask::SetIsRejectStatus(bool set)
{
	bRejectStatus = set;
}


/**************************************************************************//**
* \brief   - De-Initialize allocated stack memory of ControlTask.  
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
ControlTask::~ControlTask()
{
	CP = NULL;
}

/**************************************************************************//**
* \brief   - Controls state machine functionalities(TASK ROUTINE).  
*
* \param   - None.
* 
* \return  - None.
*
******************************************************************************/
void* ControlTask::Control_Task(void *)
{	
	char RecvMsgBuffer[MAX_SIZE_OF_MSG_LENGTH]= {0x00};
	Message	ProcessBuffer;
	
	CommonProperty* CP = CommonProperty::getInstance();
		
	CP->SetTaskId(CommonProperty::cTaskName[CTRL_T], taskIdSelf());
		
	ControlTask *ScCtrl = new(nothrow) ControlTask();
	UINT32 events;
	UINT32 io_sem_selector = 0;
	UINT32 io_loop_selector = 0;
	UINT32 act_loop_selector = 0;
	UINT32 dsp_loop_selector = 0;

	if(NULL != ScCtrl)
	{
		// Control Task loop and the bIsTaskRun flag enabled when task created		
		while(ScCtrl->bIsTaskRunStatus())
		{
			// receive a request to perform weld or seek operation from console or through GPIO.  						
			if(mq_timedreceive(CP->GetMsgQId(CommonProperty::cTaskName[CTRL_T]),RecvMsgBuffer,MAX_SIZE_OF_MSG_LENGTH, 0,&NO_TIMEOUT) != ERROR)
			{
				
				ScCtrl->Decode(RecvMsgBuffer,ProcessBuffer);
				// Process commands received from MsgQ.
				ScCtrl->ProcessTaskMessage(ProcessBuffer);
			}

			// Event auxiliary clock timer every 250us or a shutdown event
			if(eventReceive(SHUTDOWN_EVENT | CTRL_250US, EVENTS_WAIT_ANY, WAIT_FOREVER, &events) != ERROR)
			{
				if(events & SHUTDOWN_EVENT)
				{
					LOGWARN((char *)"CTRL_T: Shutdown Event: %f\n",TimeStamp(), 0, 0);
				}			
				else if(events & CTRL_250US)
				{
					// Use this event case to do timely operations outside of weld
					io_loop_selector++;
					act_loop_selector++;
					dsp_loop_selector++;
					
					//Trigger Digital Input Task every 1 millisecond.
					if (io_loop_selector % 4 == 0)
					{				 		
						if(eventSend(CP->GetTaskId(CommonProperty::cTaskName[DGTIN_T]),DIGITAL_INPUT_TASK_EVENT) != OK)
						{
							LOGERR((char *)"CTRL_T :Failed to send event to ScDgtInput_Task",0,0,0);
						}		
					}
					
					// actuator loop sync
					if (0 == act_loop_selector % ACT_RX_EVENT_INTERVAL)
					{
						// enter event for outgoing process data
						if(CP->bActConnected)
						{
							if(eventSend (CP->GetTaskId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T]), ACT_TASK_RX_EVENT) != OK)
								LOGERR((char *)"CTRL_T: Failed to send event: Error\n",0,0,0);	
						}
					}
					
					// DSP loop sync
					if (0 == dsp_loop_selector % DSP_1MS_EVENT_INTERVAL)
					{
						// enter optional event for outgoing DSP control data
						// Note: writing control data to the SM for the DSP to read is synchronous
						// to the DSP task's state machine and does not have to be event driven.
						if(CP->bDspSrNoVerNoReceived)
						{
							// send PS_TASK_1MS_EVENT to read from SM here
							if(eventSend (CP->GetTaskId(CommonProperty::cTaskName[POWER_SUPPLY_T]), PS_TASK_1MS_EVENT) != OK)
								LOGERR((char *)"CTRL_T: eventSend: Error\n",0,0,0);
						}
					}
					// handle other state machine transitions and operations
					ScCtrl->StateMachineHandler();
				}
			}
		}
		
		delete ScCtrl;
	}
	else
	{
		LOGERR((char *)"CTRL_T : -------------Memory allocation failed-----------",0,0,0);
	}

	ScCtrl = NULL;
	LOGINFO((char *)"-------------ControlTask Terminated-----------",0,0,0);
	return nullptr;
}

