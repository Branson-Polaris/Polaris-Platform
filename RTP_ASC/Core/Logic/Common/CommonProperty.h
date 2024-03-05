/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef COMMONPROPERTY_H_
#define COMMONPROPERTY_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <mqueue.h>
#include "Common.h"
#include "WeldRecipeSC.h"
#include "Com_Cfg.h"
#include "SeekRecipe.h"

using namespace std;

// enum for Task Indices of Task names
enum taskIndex
{
	CTRL_T = 0,
	ACTUATOR_PROCESS_T,
	POWER_SUPPLY_T,
	ACTUATOR_SYSTEM_T,
	UI_T,
	DGTIN_T,
	HMI_SOCKET_T,
	ACT_SOCKET_T,
	CONSOLE_T,
	DIG_SOCKET_T,
	DATA_READ_T,
	DATA_WRITE_T,
	//Add New Tasks Before MAIN_T
	MAIN_T,	
	TOTAL_NUM_OF_TASK
};

//set timeout wait for (non-blocking(NO_WAIT) message queue)
static constexpr struct timespec NO_TIMEOUT = {0};

class CommonProperty
{
public:						
	// Public member functions
	static CommonProperty*	getInstance		();
	TASK_ID					GetTaskId		(string TaskName);
	mqd_t					GetMsgQId		(string TaskName);
	bool					IsFileExist		(string fileName);
	void					SetTaskId		(string TaskName, TASK_ID tid);
	void					SetMsgQId		(string TaskName, mqd_t mid);	
	
	//Constant array for task names
    static const std::string		cTaskName[TOTAL_NUM_OF_TASK];
	bool					bTaskRun;
	vector<DspRealTimeDataDetailed> m_vLastWeldDSPData;
	
	//Members defined for Shutdown feature	
	bool					bActSrNoVerNoReceived;
	bool					bDspSrNoVerNoReceived;
	bool					bHMILogged;
	bool					bWebServicesLogged;
	bool					bUIConnected;
	bool					bActConnected;
	bool					bConsoleScrollLock;
	bool					bConsoleRestReq;
	
private:					
	// Private member functions	
	CommonProperty				();
	CommonProperty				(const CommonProperty& );
	CommonProperty& operator=	(const CommonProperty& );
	~CommonProperty				();
		
	// Private member data
	map<string,MSG_Q_ID>	MsgQMap;
	map<string,TASK_ID>		TaskIdMap;	
	//Member defined for Timed seek event log 
	bool 					bTimedSeekEnabledForEvent;
};

#endif /* COMMONPROPERTY_H_ */
