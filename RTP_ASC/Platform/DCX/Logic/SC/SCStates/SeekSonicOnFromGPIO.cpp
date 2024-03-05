/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------
 	  It contains the Seek Sonic On State related implementation       
**********************************************************************************************************/

#include "SeekSonicOnFromGPIO.h"

extern "C"
{
	#include "Com.h"
}

/**************************************************************************//**
* 
* \brief   - SeekSonicOnFromGPIO Class constructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
SeekSonicOnFromGPIO::SeekSonicOnFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = SEEK_SONIC_ON;
	//instance of powersupply task
	ptrPSTask = PowerSupplyTask::GetInstance();		
}

/**************************************************************************//**
* 
* \brief   - SeekSonicOnFromGPIO Class destructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
SeekSonicOnFromGPIO::~SeekSonicOnFromGPIO()
{
	m_Actions = SCState::INIT;
	m_State = NO_STATE;

}

/**************************************************************************//**
* 
* \brief   - This method will be executed when entering the SeekSonicOnFromGPIO state.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void SeekSonicOnFromGPIO::Enter()
{
	LOG("\nCTRL_T: _SEEK_SONIC_ON_FROM_GPIO\n");
	SonicsOnCounter			= 0;															
	CP->m_vLastWeldDSPData.clear();													
	
	auto &refSeekRecipe = SeekRecipe::GetInstance();								

	sonicsDelayCounter		= 0;													
	UINT32 SeekTimeRecipe 	= refSeekRecipe.GetSeekTime();							
	SeekTime 				= (SeekTimeRecipe * (1000/CTRL_CYCLE_TIME_IN_US)); 	
	SeekTimeCounter			= 0;
}

/**************************************************************************//**
* 
* \brief   - This method will be executed every 250us when in Seek Sonic On state from GPIO.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void SeekSonicOnFromGPIO::Loop()
{
	//Jump to fail action whenever PC alarm gets generated
	if(PCStateMachine::GetPCState() == PCState::PC_ALARM)			
	{
		m_Actions = SCState::FAIL;
	}
	else
	{
		//below code will run when PC state machine will be in a PCSeekRun state 
		//capture the dsp data once, and jump to next state when seektime expires
		if(PCStateMachine::GetPCState() == PCState::PC_SEEK_RUN)	
		{	
			if (SonicsOnCounter % 4 == 0)
			{
				//Captures DSP shared memory data
				ptrPSTask->CaptureDSPData();						
			}
			SonicsOnCounter = SonicsOnCounter + 1;
			++SeekTimeCounter;	

			if(SeekTimeCounter >= SeekTime)							
			{
				m_Actions = SCState::JUMP;							
				return;
			}
		}
		else //PC hasn't turned on sonics
		{
			if(++sonicsDelayCounter > MAX_SONIC_DELAY_IN_MS)
			{
				m_Actions = SCState::FAIL;
			}
		}
	}
}

/**************************************************************************//**
* 
* \brief  - This method will be called when exiting the SeekSonicOnFromGPIO state 
*
* \param  - None.
*
* \return  - None
*
******************************************************************************/
void SeekSonicOnFromGPIO::Exit()
{
	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();	
	
	//Read frequency value from the DSP will update the MemoryOffset = EndFrequency - DigitalTune.
	INT32 EndFrequency = ptrPSTask->GetTxFrequency();
	INT32 MemoryOffset = EndFrequency - refPcWeldRecipe.GetDigitalTune()/10;
	refPcWeldRecipe.SetMemoryOffset(MemoryOffset);

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
		std::cout << "SeekSonicOnFromGPIO - No DSP Data available for last SEEK" << std::endl;
	}
	
}

/**************************************************************************//**
*
* \brief   - SeekSonicOn Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSonicOnFromGPIO::Fail()
{
	//If there is an alarm from the PC, set MemoryOffset = 0.
	PcWeldRecipe::GetInstance().SetMemoryOffset(0);
	//Abort the state operation
	m_Actions = SCState::ABORT;
}
