/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the Weld Sonic On State from GPIO related implementation
***************************************************************************/

#include "WeldSonicOnFromGPIO.h"
extern "C"
{
	#include "Com.h"
}
/**************************************************************************//**
* 
* \brief   - WeldSonicOnFromGPIO Class constructor. 
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
WeldSonicOnFromGPIO::WeldSonicOnFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = WELD_SONIC_ON;
	ptrPSTask = PowerSupplyTask::GetInstance();			//instance of powersupply task

}

/**************************************************************************//**
* 
* \brief   - WeldSonicOnFromGPIO Class destructor. 
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
WeldSonicOnFromGPIO::~WeldSonicOnFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = NO_STATE;
}

/**************************************************************************//**
* 
* \brief   - This method will be executed when entering the Sonic on state. 
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnFromGPIO::Enter()
{
	WeldSonicOn::Enter();									//Call the base class Enter() to call common code part
	LOG("\nCTRL_T: _WELD_SONIC_FROM_GPIO\n");	
	sonicsDelayCounter		= 0;
	SonicsOnCounter			= 0;
	auto &refScWeldRecipe = ScWeldRecipe::GetInstance();
	
	//clear last weld dsp data
	CP->m_vLastWeldDSPData.clear();							
	
	modes 				= refScWeldRecipe.GetWeldMode();	
	modeValue 			= refScWeldRecipe.GetModeValue();	

	if(modes == TIMEMODE)
	{
		weldSonicOnTime = (modeValue * (1000/CTRL_CYCLE_TIME_IN_US));
	}
}

/**************************************************************************//**
* 
* 
* \brief   - This method will be executed every 250us while waiting for the. 
* 			 weld time to expire for the Time mode,
* 			 energy reach specified weld energy for the energy mode,
* 			 Weld distance reach specified distance for absolute mode,
* 			 Collapse distance reach specified distance for the collapse mode,
* 			 scrub time to expire for the ground detect mode,
* 			 Power reach specified peak power level for the Peak Power mode.
* 			 both PC and AC in the ready state.
* 			 This function is using multiple returns to resolve digital inputs
* 			 lines status as quick and in line. The purpose is to resolve to a fault
* 			 thus showing the return statements rather than them being hidden
* 			 in a sub-routine call. This gives faster resolution and execution and simplifies
* 			 the flow of the code.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnFromGPIO::Loop()
{															
	bool bWeldDone = false;
	bool bWeldMaxTimeout = false;

	//If there is an alarm from the PC,jump to fail 
	if(PCStateMachine::GetPCState() == PCState::PC_ALARM)					
	{
		m_Actions = SCState::FAIL;
	}  
	//below code will run when PC state machine will be in a WELD RUN state 
	//capture the dsp data once, and jump to next state.
	else if (PCStateMachine::GetPCState() == PCState::PC_WELD_RUN)		
	{ 
		if (SonicsOnCounter % 4 == 0)
		{
			//Captures DSP shared memory data
			ptrPSTask->CaptureDSPData(); 									
		}
		SonicsOnCounter = SonicsOnCounter + 1;
			
		switch(modes)
		{
			case TIMEMODE:
				if(SonicsOnCounter >= weldSonicOnTime) 
				{
					bWeldDone = true;
				}
				break;

			default:
				LOGWARN((char *) "CTRL_T WeldSonicOnFromGPIO: Unknown weld mode",0,0,0);
				bWeldDone = true;
				break;
		}
		
		if(true != bWeldDone) 
		{
			//TODO
		}
		else 
		{	
			//Jump to next state
			m_Actions = SCState::JUMP;
		}
	}
	else
	{
		// no sonics for max delay
		if(++sonicsDelayCounter > MAX_SONIC_DELAY_IN_MS)
		{
			m_Actions = SCState::FAIL;
		}
	}
}

/**************************************************************************//**
* 
* \brief   - This method will be executed when exiting the WeldSonicOnFromGPIO state . 
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnFromGPIO::Exit()
{		
	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();
	
	if(refPcWeldRecipe.GetEndOfWeldStore() == true)
	{		
		//Read frequency value from the DSP will update the MemoryOffset = EndFrequency - DigitalTune.
		INT32 EndFrequency = ptrPSTask->GetTxFrequency();
		INT32 MemoryOffset = EndFrequency - refPcWeldRecipe.GetDigitalTune()/10;
		refPcWeldRecipe.SetMemoryOffset(MemoryOffset);	
	}
	//Print the last weld's last captured DSP data on console.
	int nVectorSize = CP->m_vLastWeldDSPData.size();
	if(nVectorSize > 0)
	{
		std::cout << "DspAmplitude,DspPhase,DspFrequency,DspCurrent,DspStatus" << std::endl;
		std::cout << CP->m_vLastWeldDSPData[nVectorSize - 1].Entry0 << ',';
		std::cout << CP->m_vLastWeldDSPData[nVectorSize - 1].Entry1/1000.0 << ',';
		std::cout << CP->m_vLastWeldDSPData[nVectorSize - 1].Entry2 << ',';
		std::cout << CP->m_vLastWeldDSPData[nVectorSize - 1].Entry3 << ',';
		std::cout << CP->m_vLastWeldDSPData[nVectorSize - 1].Entry4  << '\n';
	}
	else
	{
		std::cout << "WeldSonicOnFromGPIO - No DSP Data available for last weld" << std::endl;
	}	
}

/**************************************************************************//**
*
* \brief   - Weld Sonic On Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnFromGPIO::Fail()
{
	//If there is an alarm from the PC, set MemoryOffset = 0 and Abort the state operation.
	PcWeldRecipe::GetInstance().SetMemoryOffset(0);
	m_Actions = SCState::ABORT;
}

/**************************************************************************//**
* 
* \brief  - This method should be called when we want to send a request to  
* Control_Task to perform the Weld Sonic On operation using GPIO. 
*
* \param  - None.
*
* \return  - true on successfully sending Weld Sonic On from GPIO request to 
* Control_Task else false.
*
******************************************************************************/
bool WeldSonicOnFromGPIO::PerformWeldSonicOnFromGPIO()
{		
	bool bResult = false;
	Message WeldMessage = {0};
	WeldMessage.msgID = TO_CTRL_TASK_WELD_CMD_FROM_GPIO;
	CommonProperty *CP = CommonProperty::getInstance();
	if(CP != NULL)
	{
		//send a request to Control_Task to perform the weld operation using GPIO.  						
		if(mq_timedsend(CP->GetMsgQId(CommonProperty::cTaskName[CTRL_T]), reinterpret_cast<char*>(&WeldMessage), sizeof (WeldMessage), 0, &NO_TIMEOUT) == ERROR)
		{
			LOGERR((char *)"\nPerformWeldSonicOnFromGPIO : msgQSend Error\n",0,0,0);
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		LOGERR((char *)"\nPerformWeldSonicOnFromGPIO : CommonProperty NULL\n",0,0,0);
	}
	
	return bResult;
}
