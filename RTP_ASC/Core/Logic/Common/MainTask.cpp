/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
	This file contains the main loop that sets the system type and system freq.
	Create a task and msgQ, and sets the required gpio.
***************************************************************************/

#include <pthread.h>
#include "MainTask.h"
#include "ConsoleApp.h"
#include "SocketReceiver.h"
#include "DIG_client.h"
#include "DataReadTask.h"
#include "DataWriteTask.h"
//Map containing Task Index, Task Priority, Task Stack Size, Task Entry Function Pointer.
const std::map<taskIndex, std::tuple<int, size_t, FUNC*>> MainTask::mapOfTaskIndexAndParameters = 
{
	//TO_BE_DONE - Set proper priority values.
	//Task Index, Priority, Stack Size, Function Pointer to Task entry function
	{ CTRL_T, { 35, 1024*6, ControlTask::Control_Task } },
	{ ACTUATOR_PROCESS_T, { 34, 1024*6, ActuatorTaskProcess::Actuator_Process_Task } },
	{ POWER_SUPPLY_T, { 33, 1024*6, PowerSupplyTask::PowerSupply_Task } },
	{ ACTUATOR_SYSTEM_T, { 32, 1024*6, ActuatorTaskSystem::Actuator_System_Task } },
	{ UI_T, { 31, 1024*10, UserInterface::UserInterface_Task } },
	{ DGTIN_T, { 29, 1024*4, ScDgtInputTask::ScDgtInput_Task } },
 	{ HMI_SOCKET_T, { 28, 1024*10, HMI_SocketReceiver::Socket_HMI_Task } },
	{ ACT_SOCKET_T, { 27, 1024*8, ACT_SocketReceiver::Socket_ACT_Task } },
	{ CONSOLE_T, { 26, 1024*6, ConsoleApp::ConsoleApp_Task } },
	{ DIG_SOCKET_T, { 25, 1024*8, DIGClient::Socket_DIG_Task } },
	{ DATA_READ_T,  { 24, 1024*8, DataReadInterface ::Data_Read_Task }},
	{ DATA_WRITE_T,  { 30, 1024*8, DataWriteInterface ::Data_Write_Task }}  
};

/**************************************************************************//**
* \brief   - Create the R/W shared memory
*
* \param   - uint32_t addr and uint32_t length
*
* \return  - void*
*
******************************************************************************/
void* MEM_MAP(uint32_t addr, uint32_t length)
{
    void* buff = nullptr;
    char memName[MAX_BUFSIZE];
    SD_ID sd = 0;
    uint32_t err = 0;

    // Write a formatted string to memName buffer.
    snprintf(memName, MAX_BUFSIZE, "/ComData_%x", addr);
 
    // Create the R/W shared buffer
    if ((sd = sdOpen(memName, 0, OM_CREATE, length, addr, SD_ATTR_RW | SD_CACHE_OFF, (void **)&buff)) == SD_ID_NULL)
    {
        err = errno;
		LOGERR((char *) "Main_T : MEM_MAP failed. 0x%x\n!",err,0,0);
    }
    return buff;
}

/**************************************************************************//**
* \brief   - Constructor
* \param   - None
*
* \return  - None
*
******************************************************************************/
MainTask::MainTask()
{	
	// begin Shared data region
	void *Buff = MEM_MAP(0x40400000, 1024);
	ComConfig config;
    config.ShmBaseAddress = (uint32_t)Buff;

    CP = CommonProperty::getInstance();
			
	// Enabling the flag allows business logic tasks to run continuously
	CP->bTaskRun = true;
	int retries = 3;
	
	while((retries--))
	{
		// begin SM, receive DSP f/w version
	    if(Com_start(&config))
	    {
	        DspConfigData* dspConfigData = Com_getDspConfig();
	        DspInfoData* dspInfoData = Com_getDspInfo();

			// storing PC version info locally, it can be retrieved by the UI
	        // note: we need to expand dspInfoData->FwVersion
			FWVersion::Set(FW_VERSION_PC, VERSION_MAJOR, 0);
			FWVersion::Set(FW_VERSION_PC, VERSION_MINOR, 0);
			FWVersion::Set(FW_VERSION_PC, VERSION_BUILD, dspInfoData->FwVersion);
			FWVersion::PrintVersion(FW_VERSION_PC);
	        LOG("\nMAIN_T: DSP Config A: %d\n", dspConfigData->Cfg_A);
	        
	        // reset outgoing SM buffer
	        ArmRealTimeData* rtData = Com_armDataBeginWrite();
	        ArmRealTimeDataDetailed* armDataDetailed = (ArmRealTimeDataDetailed*)&rtData->Entries;
	        armDataDetailed->Entry0 = 0xFFFFFFFF;
	        armDataDetailed->Entry1 = 0xFFFFFFFF;
	        armDataDetailed->Entry2 = 0xFFFFFFFF;
	        armDataDetailed->Entry3 = 0xFFFFFFFF;
	        armDataDetailed->Entry4 = 0xFFFFFFFF;
	        armDataDetailed->Entry5 = 0xFFFFFFFF;
	        armDataDetailed->Entry6 = 0xFFFFFFFF;
	        armDataDetailed->Entry7 = 0xFFFFFFFF;
	        armDataDetailed->Entry8 = 0xFFFFFFFF;
	        armDataDetailed->Entry9 = 0xFFFFFFFF;
	        armDataDetailed->Entry10 = 0xFFFFFFFF;
	        Com_armDataEndWrite();

	        // allows for reader/writer operations
	        CP->bDspSrNoVerNoReceived = true;
	        break;
	    }
	    else
	    {
			//TODO : Generate Alarm for this catastrophic failure
	    	LOG("\n%sMAIN_T: DSP core not started%s\n", KRED, KNRM);
			taskDelay(FORTY_MS_DELAY);	
	    }
	
	}
	
	//retries was decremented after last check
	if(retries < 0) 
	{
		LOG( "\nerror:Too many retries\n");      
	}
}

/**************************************************************************//**
* \brief   - Creates the message queue using posix api for all created task
*
* \param   - None
*
* \return  - true 0 on success else return false
*
******************************************************************************/
bool MainTask::CreateMsgQ()
{
	bool bResult = false;
	bool bErrorOccured = false;
	
	//Initialize message queue descriptor
	mqd_t qID = 0;
		
	//Initialize the queue attributes 
	struct mq_attr  attr;
	
	attr.mq_flags 	= 0;							//Message queue description flags: 0 or O_NONBLOCK
	attr.mq_maxmsg 	= MAX_MSG;						//Maximum number of messages on queue
	attr.mq_msgsize = MAX_SIZE_OF_MSG_LENGTH;		//Maximum message size (in bytes)
	attr.mq_curmsgs = 0;							//Number of messages currently in queue
	
	for(UINT32 t_index=0; t_index < TOTAL_NUM_OF_TASK; t_index++)
	{	
		//Create MsgQ for all tasks
		qID = mq_open(CommonProperty::cTaskName[t_index].c_str(), O_CREAT | O_RDWR, 0, &attr);

		if (qID != ERROR) 
		{
			// register queue ID with its name
			CP->SetMsgQId(CommonProperty::cTaskName[t_index],qID);			
		}
		else		
		{
			LOG((char *) "Main_T : CreateMsgQ Failure for Task: %s",CommonProperty::cTaskName[t_index].c_str(),0,0);
			bErrorOccured = true;
		}
	}
	if(bErrorOccured == false)
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* \brief   - Spawns the required tasks
*
* \param   - None
*
* \return  - true on success else false
*
******************************************************************************/
bool MainTask::CreateTasks()
{
	bool bResult = false;
	bool bErrorOccured = false;
	pthread_t ThreadID = 0;
		
	for(UINT32 t_index = 0; t_index < TOTAL_NUM_OF_TASK; t_index++)
	{
		//Get the tuple from map so that we can get the priority, stack size and function pointer from tuple
		auto tupleElement = MainTask::mapOfTaskIndexAndParameters.find((taskIndex)t_index)->second;
		
		//No need to create a thread separately for Main Task as we are already in main() function.
		if(t_index == MAIN_T)
		{
			continue;
		}
		//Create DIG Client Task thread only if it is enabled.
		else if(t_index == DIG_SOCKET_T)	
		{
				#ifdef	ENABLE_DIG_CLIENT
				//TO_BE_DONE: CPSW1 will be used by DIG Client and WebServer.
				//So, the IP address setting screen for DIG client/WebServer 
				//on HMI should inform user that changing the IP address will 
				//affect both DIG client and WebServer IP address.
				if(DIGClient::SetCPSW1IP() == true)
				{
					ThreadID = CreateThread(CommonProperty::cTaskName[t_index], std::get<0>(tupleElement), std::get<1>(tupleElement), std::get<2>(tupleElement));
					if(ThreadID == 0)
					{
						bErrorOccured = true;
						LOG((char *) "Main_T : CreateThread Failure for Task: %s",CommonProperty::cTaskName[t_index].c_str(),0,0);
					}		
				}
				else
				{
					bErrorOccured = true;
					LOGERR((char *)"SetCPSW1IP: Failure to set CPSW1 IP Address",0,0,0);
				}
				#endif
		}
		else
		{
			ThreadID = CreateThread(CommonProperty::cTaskName[t_index], std::get<0>(tupleElement), std::get<1>(tupleElement), std::get<2>(tupleElement));
			if(ThreadID == 0)
			{
				bErrorOccured = true;
				LOG((char *) "Main_T : CreateThread Failure for Task: %s",CommonProperty::cTaskName[t_index].c_str(),0,0);
				//TODO : Generate Alarm for this catastrophic failure
			}	
		}	
	}
	
	if(bErrorOccured == false)
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* \brief   - Release memory and exits from spawned tasks
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void MainTask::TerminateTasks()
{
	// Disabling the flag allows business logic tasks to exit from continuous loop
	CP->bTaskRun = false;
}

/**************************************************************************//**
* \brief   - Delete the created message queue.
*
* \param   - None
*
* \return  - true on success else false
*
******************************************************************************/
bool MainTask::DestroyAllMsgQ()
{
	bool bResult = false;
	bool bErrorOccured = false;
	for(INT32 t_index = 0; t_index < TOTAL_NUM_OF_TASK; t_index++)
	{
		if(msgQDelete(CP->GetMsgQId(CommonProperty::cTaskName[t_index] )) != OK)
		{
			LOGERR((char *) "MainTask::DestroyAllMsgQ: MessageQ deletion failed",0,0,0);
			bErrorOccured = true;
		}
	}	
	
	if(bErrorOccured == false)
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* \brief   - Deletes all tasks
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
 
void MainTask::DeleteTasks()
{
	for(UINT32 t_index = 0; t_index < TOTAL_NUM_OF_TASK; t_index++)
	{
		//No need to delete a thread for Main Task as we are already in main() function and main thread is not created using posix thread creation API.
		if(t_index == MAIN_T)
		{
			continue;
		}
		//delete DIG Client Task thread only if it is enabled.
		else if(t_index == DIG_SOCKET_T)	
		{
				#ifdef	ENABLE_DIG_CLIENT
				taskDelete(CP->GetTaskId(CommonProperty::cTaskName[t_index]));
				#endif
		}
		else
		{
			taskDelete(CP->GetTaskId(CommonProperty::cTaskName[t_index]));
		}
	}
}

/**************************************************************************//**
* \brief   - De-initialize the allocated stack memory for MainTask Class
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
MainTask::~MainTask()
{
	#ifdef DEBUG
		/*	need to decide on calling DestroyTask function from here.	*/
		cout << "-----------Main task destructor is called------------" << endl;
	#endif
	CP = nullptr;
}

/**************************************************************************//**
* \brief   - main loop that sets the system type and system freq
*				Create a task and msgQ and set the required gpio.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
int main()
{
	INT16 gpioStatus = ERROR;
	UINT32 iEvent = 0;
	bool bSuccess = true;
	TASK_ID MainTaskID	= taskIdSelf();
		
	//Read system type e.g. ACE Pro, ACE Pro in Power Supply Only Mode, GSX_E1, L20 etc at startup.
	//NEVER set/change "g_enSystemType" later from anywhere in code.
	g_enSystemType = GetSystemTypeFromStorage();
	if(g_enSystemType == SYSTEM_UNKNOWN)
	{
		//By default, set the system type to SYSTEM_ACE_PRO for now if it is not set. 
		//In future, we can show some error message to the user on HMI and ask him to set the system type first on first boot or if system type is not set. 
		SetSystemType(SYSTEM_ACE_PRO);
		g_enSystemType = SYSTEM_ACE_PRO;
	}
	
	//Read the System Frequency choice and set the system frequency as per choice.
	//By default, set the system frequency to 20KHZ.
	SystemFrequency objSystemFrequency;
	FREQUENCY enSystemFrequencyChoice = objSystemFrequency.GetSystemFrequencyFromStorage();
	if(enSystemFrequencyChoice != FREQ_UNKNOWN)
	{
		objSystemFrequency.SetSystemFrequency(enSystemFrequencyChoice);
	}
	else
	{
		objSystemFrequency.SetSystemFrequency(FREQ_20KHZ);
	}
		
	// Create object and pass it to a smart pointer
	std::unique_ptr<MainTask> MT(new MainTask());
	
	// Enable powers v5_0EXT and V12_0EXT
	gpioStatus = GpioExtPwrEn();
	if (gpioStatus != GPIO_OK)
	{
		LOGERR((char *)"\nMAIN_T:Failed to Enable Power\n",0,0,0);
	}
	// Initialize GPIO lines
	gpioStatus = GpioInit();
	if (gpioStatus != GPIO_OK)
	{
		LOGERR((char *)"\nMAIN_T:Failed to Initialize GPIO\n",0,0,0);
	}
	
	// Disable /IO_RESET pin, which will be enable the devices connected
	gpioStatus = GpioIOResetDis();
	if (gpioStatus != GPIO_OK)
	{
		LOGERR((char *)"\nMAIN_T:Failed to enable connected devices\n",0,0,0);
	}
	
	if(nullptr != MT)
	{		
		CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[MAIN_T], MainTaskID);

		bSuccess = MT->CreateMsgQ();
		if(bSuccess)
		{
			LOG("\nMAIN_T: Create MsgQ: OK\n");
			
			bSuccess = MT->CreateTasks();		
			if(bSuccess)
			{
				LOG("\nMAIN_T: Create Tasks: OK\n");
			}
			else
			{
				LOGERR((char *)"MAIN_T:Failed to create Tasks:\n",0,0,0);
			}
		}
		else
		{
			LOGERR((char *)"MAIN_T:Failed to create MsgQ:\n",0,0,0);
		}
		
		//Initialise Auxclk timer for 1msec
		bool setAuxRate = MT->InitauxClk();
		if (setAuxRate != OK)
		{
			LOGERR((char *)"MAIN_T:Failed to set AuxClk rate:\n",0,0,0);
		}
		
		
		if(bSuccess)
		{
			while(MT->bIsTaskRunStatus())
			{
				//When SHUTDOWN_EVENT is received all tasks will terminate, all MsgQ will be destroyed and all tasks will be deleted
				if(eventReceive(SHUTDOWN_EVENT,EVENTS_WAIT_ANY,WAIT_FOREVER, &iEvent) != ERROR)
				{
					MT->TerminateTasks();
					//Delay for exit all the business logic tasks
					taskDelay(FORTY_MS_DELAY);	
					MT->DeleteTasks();
					MT->DestroyAllMsgQ();
				}
			}
		}
		else
		{
			LOGERR((char *) "Main_T : Data structure creation failed",0,0,0);
			MT->DestroyAllMsgQ();
			MT->TerminateTasks();
		}
	}
	else
	{
		LOGERR((char *) "Main_T : --------Memory allocation failed------------",0,0,0);
	}
	
	MT = nullptr;
	LOGINFO((char *) "Main_T : EXIT FROM RTP PROCESS",0,0,0);
	return 0;
}

/**************************************************************************//**
 * \brief   - Initialise Auxclk timer for 1ms and connect to control task
 * 			  Partition
 * \param   - None
 *
 * \return  - None
 *
 ******************************************************************************/
bool MainTask::InitauxClk(void)
{

	bool status = 0;
	UINT32 SampleRate;
	INT32 tid = (INT32) CP->GetTaskId(CommonProperty::cTaskName[CTRL_T]);
	
	MsDelay(100);
	
	SampleRate = (1000*1000)/DEFAULT_TIMEINTERVAL_US;
	status = AuxClkRateSet(SampleRate);

	if(status == OK)
		LOG("\nMain_T : AuxClk set at Rate = %d\n",AuxClkRateGet());
	else
		LOGERR((char *) "Main_T : AuxClk set Rate failed status: %d",status,0,0);

#ifdef	PRINT_DBG
	if(status == OK)
		LOG("\nAuxClk set at Rate = %d\n",AuxClkRateGet());
	else
		LOGERR((char *) "Main_T : AuxClk set Rate failed status: %d",status,0,0);
#endif
	
	status = AuxClkConnect(tid);
	
	if(status == OK)
		LOG("\nMain_T : TaskId: %d connected Aux ISR\n",tid);
	else
		LOGERR((char *) "Main_T : Failed to connect Aux ISR!",0,0,0);

#ifdef	PRINT_DBG
	if(status != OK)
	{
		LOGERR((char *) "Main_T : Failed to connect Aux ISR!",0,0,0);
	}
	else
		LOG("\nMain_T : TaskId: %d connected Aux ISR\n",tid);
#endif
	
	AuxClkEnable();
	MsDelay(1000);
	return status;
}


/**************************************************************************//**
 * \brief   - Create POSIX Thread
 * 			  
 * \param   - TaskName - Name of created thread
 *			- PriorityValue - Priority of Thread
 *			- StackSize - Stack Size for created Thread
 *			- functionName - Name of Thread function
 * \return  - On Success returns ThreadID of created thread, on failure returns 0
 *
 ******************************************************************************/
pthread_t MainTask::CreateThread(const std::string TaskName, const int PriorityValue, const size_t StackSize, void * functionName(void *))
{
	pthread_attr_t ThreadAttributes;
	sched_param SchedulingParameters;
	pthread_t ThreadID = 0;
	
	//Initialize with default attributes
	if(pthread_attr_init (&ThreadAttributes) != 0)
	{
		LOG("\npthread_attr_init failure for %s \n",TaskName.c_str());
	}
	else
	{
		//Safe to get existing scheduling parameters
		if(pthread_attr_getschedparam (&ThreadAttributes, &SchedulingParameters) != 0)
		{
			LOG("\npthread_attr_getschedparam failure for %s \n",TaskName.c_str());
		}
		else
		{		
			//Set the priority, others are unchanged 
			SchedulingParameters.sched_priority = PriorityValue;
			
			//Set the thread name and stack size 
			ThreadAttributes.threadAttrName = (char *)TaskName.c_str();
			ThreadAttributes.threadAttrStacksize = StackSize;
				
			//Specify explicit scheduling
			if(pthread_attr_setinheritsched (&ThreadAttributes, PTHREAD_EXPLICIT_SCHED) != 0)
			{
				LOG("\npthread_attr_setinheritsched failure for %s \n",TaskName.c_str());
			}
			else
			{
				//Set Scheduling Policy
				if(pthread_attr_setschedpolicy(&ThreadAttributes, SCHED_FIFO) != 0)
				{
					LOG("\npthread_attr_setschedpolicy failure for %s \n",TaskName.c_str());
				}
				else
				{
					//Set the new scheduling parameters
					if(pthread_attr_setschedparam (&ThreadAttributes, &SchedulingParameters) != 0)
					{
						LOG("\npthread_attr_setschedparam failure for %s \n",TaskName.c_str());
					}
					else
					{										
						//Create thread, the ID of created thread is received in ThreadID
						if(pthread_create(&ThreadID, &ThreadAttributes, functionName, nullptr) != 0)
						{
							LOG("\npthread_create failure for %s \n",TaskName.c_str());
							ThreadID = 0;
						}
					}
				}
			}
		}
	}

	return ThreadID;
}
