/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	It contains functions that gets executed when PC state machine goes to SeekRun state.
***************************************************************************/

#include "PCSeekRun.h"
#include "PCStateMachine.h"
#include "commons.h"
#include "SCStateMachine.h"

/**************************************************************************//**
* \brief   - Constructor - 
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PCSeekRun::PCSeekRun() 
{
	stateType = PC_SEEK_RUN;
	ptrPSTask = PowerSupplyTask::GetInstance();
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
PCSeekRun::~PCSeekRun() {
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine goes to SeekRun state.
*            it will turn on the sonics and also set parameters based on seek recipe like amplitude,frequency etc. 
*            
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRun::Enter()
{	
	ptrPSTask->SetRxStartFrequency(PcWeldRecipe::GetInstance().GetDigitalTuneWithOffsets()/10);	
	ptrPSTask->UpdateSeekParameters();
	ptrPSTask->TurnOnSonics();
}

/**************************************************************************//**
* 
* \brief   - this function gets executed in a loop when PC state machine is in PCSeekRun state
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRun::Loop()
{
	if(PowerSupplyTask::GetCoreState() != NO_ERROR)
	{
		// Change State to PC_ALARM here..
		ChangeState(PC_ALARM);
	}
	else
	{	
		if ((SCStateMachine::GetSCState() != SEEK_SONIC_ON) && (SCStateMachine::GetSCState() != TEST_SONICS_ON))
		{
			ChangeState(PC_READY);
		}
		else
		{
			// do more while seeking here...
		}
	}
}

/**************************************************************************//**
* 
* \brief   - This function gets executed when PC state machine exit from SeekRun state.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void PCSeekRun::Exit()
{
	if(SCStateMachine::GetSCState() != TEST_SONICS_ON)
	{
		//Turn off sonics
		ptrPSTask->TurnOffSonics();	
	}
}

