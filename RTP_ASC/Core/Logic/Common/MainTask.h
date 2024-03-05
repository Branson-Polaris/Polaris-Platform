/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 	This file contains the main loop that sets the system type and system freq
	Create a task and msgQ and set the required gpio.
***************************************************************************/

#ifndef MAINTASK_H_
#define MAINTASK_H_

#include <map>  
#include <sdLib.h>
#include "memory"
#include "Common.h"
#include "CommonProperty.h"
#include "commons.h"
#include "ActuatorTask.h"
#include "versions.h"
#include "GPIO.h"
#include "ScDgtInput.h"
#include "SystemType.h"
#include "ControlTask.h"
#include "UserInterface.h"
#include <mqueue.h>

extern "C"
{
	#include "Com.h"
}

static constexpr unsigned int MAX_BUFSIZE = 32;

// FUNCPTR for available business logic tasks 
typedef void* FUNC(void *);

#define streamtest9

class MainTask : public SCTask
{
public:
	MainTask();
	~MainTask();
	
	// Creates the message queue for all the task spawned
	bool CreateMsgQ();
	// Creates required tasks
	bool CreateTasks();

	// Destroy created MsgQ
	bool DestroyAllMsgQ();
	
	// Exit from created tasks
	void TerminateTasks();

	// Delete all tasks
	void DeleteTasks();
	
	// Initialise Auxclk timer
	bool InitauxClk();
 	
private:
	//Create POSIX Thread
	pthread_t CreateThread(const std::string TaskName, const int PriorityValue, const size_t StackSize, void * functionName(void *));
	
	//Map containing Task Index, Task Priority, Task Stack Size, Task Entry Function Pointer.
	static const std::map<taskIndex, std::tuple<int, size_t, FUNC*>> mapOfTaskIndexAndParameters;

	// Message queue OFFSETS
	static constexpr unsigned int MAX_MSG 			= 1000;
	static constexpr unsigned int MAX_MSG_LEN 		= 1024;	
};

#endif /* MAINTASK_H_ */
