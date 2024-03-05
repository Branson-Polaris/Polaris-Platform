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

/**************************************************************************//**
* \brief  - May acquires queue handles for proper intertask communications
* 			and initialize various elements.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
ActuatorTaskProcess::ActuatorTaskProcess() 
{
	bACTTxPdo = false;
	ind_ACTTxPdo = 0;
}

/**************************************************************************//**
* \brief  - ActuatorTask destructor
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
ActuatorTaskProcess::~ActuatorTaskProcess()
{
}

/**************************************************************************//**
* \brief  - Process commands received by its message queue from the ACT 
*			socket task but not limited to.
* 			It is one of the entry point for communications with the this task
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void ActuatorTaskProcess::ProcessTaskMessage ()
{
	memset(recvMsgBuffer,0x00,sizeof(recvMsgBuffer));
	memset(message.Buffer,0x00,sizeof(message.Buffer));
	/*
	 * this while will guarantee rapid events ACT_TASK_TX_EVENT
	 * on the part of the external actuator but may delay ACT_TASK_RX_EVENT
	 * from the control task. As of now incoming actuator data is more important
	 * to make timely relevant outgoing actuator data.
	 */
	while (msgQNumMsgs (CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[ACTUATOR_PROCESS_T])) > 0)
	{
		//Receive a request to process actuator data
		if(mq_timedreceive(CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T]),recvMsgBuffer,MAX_SIZE_OF_MSG_LENGTH, 0,&NO_TIMEOUT) != ERROR)
		{
			memcpy (&message, recvMsgBuffer, sizeof (message));
			
			switch(message.msgID)
			{
			case TO_ACT_PROCESS_TASK_TX_DATA:
				
				// process incoming actuator data
				ACTPdoDownloadRequest ();
				break;
												
			default:
				LOGWARN((char *)"\nACTUATOR_PROCESS_T : Unknown message received",0,0,0);
				break;
			}
		}
	}
}

/**************************************************************************//**
* \brief  - Process RX PDO event received from other tasks and reads data
* 			from shared memory and sends it to the actuator directly.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void ActuatorTaskProcess::ACTPdoUploadRequest()
{
	memset(message.Buffer,0x00,sizeof(message.Buffer));
	message.msgID = TO_ACT_PROCESS_TASK_RX_DATA;
	
#if ACT_DBG
	static int factorRx = 0;
    if (!CP->bConsoleScrollLock) 
		if (++factorRx % ((1000000) / (CTRL_CYCLE_TIME_IN_US * ACT_RX_EVENT_INTERVAL)) == 0)
		{
			printf("%s", KCYN);
			printf("\nACT_PROCESS_T	: RX_DATA:\n");
			printf("SCState         : 0x%X\n", ((RxPDO_AC *) message.Buffer)->SCState);
			printf("ACControlEvent  : 0x%X\n", ((RxPDO_AC *) message.Buffer)->ACControlEvent);
			printf("ACOutputs       : 0x%X\n", ((RxPDO_AC *) message.Buffer)->ACOutputs);
			printf("%s", KNRM);
		}
#endif

	// Send message to actuator here...
	if (SendMessageToClient (message,ACT_REQUEST_MSG_PAYLOAD_SIZE) == ERROR)
		LOGERR((char *)"ActuatorTaskProcess: ACTPdoUploadRequest: failed",0,0,0);
}


/**************************************************************************//**
* \brief  - Process TX PDO event received from the socket task and writes
* 			data to shared memory.
* 			
*		  	UINT16  ActualForce
*			UINT32 	ActualDistance;
*			UINT8   ACStatusEvent;
*			UINT8   ACState;
*			UINT8   ACInputs;
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void ActuatorTaskProcess::ACTPdoDownloadRequest()
{	
#if ACT_DBG
	static int factorTx = 0;
    if (!CP->bConsoleScrollLock) 
		if (++factorTx % ((1000000) / (CTRL_CYCLE_TIME_IN_US * ACT_RX_EVENT_INTERVAL)) == 0)
		{
			printf("%s", KNRM);
			printf("\nACT_PROCESS_T : TX_DATA:\n");
			printf("ACState         : 0x%X\n", ((TxPDO_AC *) message.Buffer)->ACState);
			printf("ACInputs        : 0x%X\n", ((TxPDO_AC *) message.Buffer)->ACInputs);
	//		printf("ACStatusEvent	: 0x%X\n", ((TxPDO_AC *) message.Buffer)->ACStatusEvent);
	//		printf("ActualDistance	: 0x%X\n", ((TxPDO_AC *) message.Buffer)->ActualDistance);
	//		printf("ActualForce		: 0x%X\n", ((TxPDO_AC *) message.Buffer)->ActualForce);
			printf("%s", KNRM);
	}
#endif
	
	// when actuator data received and stored report it as HB
	message.msgID = TO_CTRL_TASK_ACT_PDO_IND;
	SendToMsgQ (message, CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[CTRL_T]));
}

/**************************************************************************//**
* \brief   - checks the expected frequency of the actuator heartbeat with
* 			the incoming indications.   
*
* \param   - None
* 
* \return  - None
*
******************************************************************************/
void ActuatorTaskProcess::CheckActTxPdo()
{
	if (bACTTxPdo)
	{
		if (ind_ACTTxPdo > ACT_TX_PDO_TICK * 2)
			ind_ACTTxPdo = ACT_TX_PDO_TICK * 2;

		ind_ACTTxPdo--; 
		
		if (ind_ACTTxPdo < 0)
		{
			LOG("\n%sALARM_SC: ALARM_INTERNAL_COMM_ENET %s\n", KRED, KNRM);

			bACTTxPdo = false;
		}
	}
	else
	{
		if (ind_ACTTxPdo > ACT_TX_PDO_TICK * 2)
		{
			bACTTxPdo = true;
		}
	}
}


/**************************************************************************//**
* \brief  - Process actuator task entry point and constructor. Handles the
* 			process data aspect of the weld i.e. force and distance control,
* 			actuator and supervisory states etc. 
 
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void* ActuatorTaskProcess::Actuator_Process_Task (void *)
{	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T], taskIdSelf());

	ActuatorTaskProcess * pActuatorTask = new (nothrow) ActuatorTaskProcess();
	UINT32 			events;

	if(NULL != pActuatorTask)
	{
		/* Actuator Task loop if the main's bIsTaskRun flag is enabled */
		while (pActuatorTask->bIsTaskRunStatus())
		{
			// wait for any one event or both
			if(eventReceive(ACT_TASK_TX_EVENT | ACT_TASK_RX_EVENT, EVENTS_WAIT_ANY, WAIT_FOREVER, &events) != ERROR)
			{
				if(events & ACT_TASK_TX_EVENT)
				{
					// process incoming actuator data or messages
					pActuatorTask->ProcessTaskMessage();
				}
				
				if(events & ACT_TASK_RX_EVENT)
				{
					// process outgoing actuator data from SD here
					pActuatorTask->ACTPdoUploadRequest ();
					// heart-beat frequency check
					pActuatorTask->CheckActTxPdo ();
				}
			}
		}

		delete pActuatorTask;
	}
	else
	{
		LOGERR((char *)"ACTUATOR_PROCESS_T : ------------- Allocation failed",0,0,0);
	}

	LOGINFO((char *)"ACTUATOR_PROCESS_T : ------------- Task Terminated",0,0,0);

	taskDelete(taskIdSelf());
	return nullptr;
}

