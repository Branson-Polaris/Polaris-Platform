/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Common property class functions for Real time and Non real time data communication
 
**********************************************************************************************************/


#include "CommonProperty.h"
#include  "versions.h"
#include <fstream>
#include <mqueue.h>

/* static initializations */
//TO_BE_DONE - Try to get rid of it and move it into MainTask::mapOfTaskIndexAndParameters
const std::string CommonProperty::cTaskName[TOTAL_NUM_OF_TASK] = 
{
		"/Ctrl_Task",
		"Actuator_Process_Task",
		"PowerSupply_Task",
		"Actuator_System_Task",
		"UI_Task",
		"ScDgtInput_Task",
		"HMI_Socket_Task",
		"ACT_Socket_Task",
		"ConsoleApp_Task",
		"DIG_Task",
		"DATA_READ_TASK",
		"DATA_WRITE_TASK",
		"RtpMain_Task"
};
/**************************************************************************//**
* \brief   - Constructor - Read default recipe and load into MAP.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
CommonProperty::CommonProperty()
{
	/*Critical Data Status member variable*/		
	bTimedSeekEnabledForEvent 	= false;
	bActConnected				= false;
	bActSrNoVerNoReceived		= false;
	bDspSrNoVerNoReceived		= false;
	bConsoleScrollLock			= false;
	bConsoleRestReq				= false;	
	bHMILogged 					= false;
	bWebServicesLogged 			= false;
	bUIConnected				= false;
}

/**************************************************************************//**
* \brief   - Return the single instance of class.
*
* \param   - None.
*
* \return  -    CommonProperty* Object 
*
******************************************************************************/
CommonProperty* CommonProperty::getInstance()
{
	static CommonProperty instance; 				   
	return &instance;
}

/**************************************************************************//**
* \brief   - Checks for specific file available or not.
*
* \param   - string filename - recipe file name.
*
* \return  - bool - on available return true
*
******************************************************************************/
bool CommonProperty::IsFileExist(string fileName)
{
	ifstream infile(fileName.c_str());
    return infile.good();
}

/**************************************************************************//**
* \brief   - Returns the particular task's message queue ID.
*
* \param   - string TaskName.
*
* \return  - mqd_t.
*
******************************************************************************/
mqd_t CommonProperty::GetMsgQId(string TaskName)
{
	return MsgQMap.find(TaskName)->second;
}

/**************************************************************************//**
* \brief   - Store all the message queues id created for business logic.
*
* \param   - string TaskName, mqd_t.
*
* \return  - void.
*
******************************************************************************/
void CommonProperty::SetMsgQId(string TaskName, mqd_t MID)
{
	MsgQMap.insert ( pair<string,mqd_t>(TaskName,MID));
}

/**************************************************************************//**
* \brief   - Returns the particular task ID.
*
* \param   - string TaskName.
*
* \return  - TASK_ID.
*
******************************************************************************/
TASK_ID CommonProperty::GetTaskId(string TaskName)
{
	return TaskIdMap.find(TaskName)->second;
}

/**************************************************************************//**
* \brief   - Store all the tasks id created for business logic.
*
* \param   - string TaskName, TASK_ID.
*
* \return  - TASK_ID.
*
******************************************************************************/
void CommonProperty::SetTaskId(string TaskName, TASK_ID TID)
{
	TaskIdMap.insert ( pair<string,TASK_ID>(TaskName,TID) );
}

/**************************************************************************//**
* \brief   - Destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
CommonProperty::~CommonProperty()
{
}
