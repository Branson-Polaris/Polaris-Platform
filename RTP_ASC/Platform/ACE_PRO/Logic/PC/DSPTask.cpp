/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 		This file contains the DSP related information
***************************************************************************/

#include "DSPTask.h"

DspRealTimeData DSPTask::dspData;
DSPTask::TxPDO_DSP DSPTask::DSP_TX;
DSPTask::RxPDO_DSP DSPTask::DSP_RX;
/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
DSPTask::DSPTask() 
{	
	//Set start frequency and PID parameters at powerup
	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();

	DSP_RX.StartFrequency = (PcWeldRecipe::GetInstance().GetDigitalTuneWithOffsets()/10);	
	DSP_RX.AmpProportionalGain = refPcWeldRecipe.GetAmplitudePGain(); 
	DSP_RX.AmpIntegralGain = refPcWeldRecipe.GetAmplitudeIGain();
	DSP_RX.AmpDerivativeGain = refPcWeldRecipe.GetAmplitudeDGain(); 
	DSP_RX.PhaseProportionalGain = refPcWeldRecipe.GetPhasePGain(); 
	DSP_RX.PhaseIntegralGain = refPcWeldRecipe.GetPhaseIGain(); 
	DSP_RX.PhaseDerivativeGain = refPcWeldRecipe.GetPhaseDGain();
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
DSPTask::~DSPTask() 
{
	// TODO Auto-generated destructor stub
}

/**************************************************************************//**
* \brief  - Process RX PDO event received from the control task to read data
* 			from internal shared memory (SD), run the native state machine
* 			and write relevant data to the SM.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::PDOUploadRequest()
{	
	DSP_RX.MasterState = PCStateMachine::GetPCState();
	// read data from internal shared memory here...
	ArmRealTimeDataDetailed armDataDetailedSource;

	armDataDetailedSource.Entry0 = DSP_RX.MasterState;
	armDataDetailedSource.Entry1 = DSP_RX.TargetAmplitude;
	armDataDetailedSource.Entry2 = DSP_RX.StartFrequency;
	armDataDetailedSource.Entry3 = DSP_RX.MasterEvents; 
	armDataDetailedSource.Entry4 = DSP_RX.AmplitudeRampTime; 
	armDataDetailedSource.Entry5 = DSP_RX.AmpProportionalGain;
	armDataDetailedSource.Entry6 = DSP_RX.AmpIntegralGain;
	armDataDetailedSource.Entry7 = DSP_RX.AmpDerivativeGain;
	armDataDetailedSource.Entry8 = DSP_RX.PhaseProportionalGain;
	armDataDetailedSource.Entry9 = DSP_RX.PhaseIntegralGain;
	armDataDetailedSource.Entry10 = DSP_RX.PhaseDerivativeGain;
	
	// write relevant data to the SM here...
	ArmRealTimeData* rtData = Com_armDataBeginWrite();
	ArmRealTimeDataDetailed* armDataDetailedDestination = (ArmRealTimeDataDetailed*)&rtData->Entries;
	
	armDataDetailedDestination->Entry0 = armDataDetailedSource.Entry0;
	armDataDetailedDestination->Entry1 = armDataDetailedSource.Entry1;
	armDataDetailedDestination->Entry2 = armDataDetailedSource.Entry2;
	armDataDetailedDestination->Entry3 = armDataDetailedSource.Entry3;
	armDataDetailedDestination->Entry4 = armDataDetailedSource.Entry4;
	armDataDetailedDestination->Entry5 = armDataDetailedSource.Entry5;
	armDataDetailedDestination->Entry6 = armDataDetailedSource.Entry6;
	armDataDetailedDestination->Entry7 = armDataDetailedSource.Entry7;
	armDataDetailedDestination->Entry8 = armDataDetailedSource.Entry8;
	armDataDetailedDestination->Entry9 = armDataDetailedSource.Entry9;
	armDataDetailedDestination->Entry10 = armDataDetailedSource.Entry10;

	Com_armDataEndWrite();
	
#if DSP_DBG
	static int factorRx = 0;
	if (!CP->bConsoleScrollLock) 
		if (++factorRx % ((1000000) / (CTRL_CYCLE_TIME_IN_US * DSP_RX_EVENT_INTERVAL)) == 0)
		{
		   LOG("\n%sDSPpdoUploadRequest  : S:%d, A:%d, F:%d, E:0x%X, R:%d, AmpP:%d, AmpI:%d, AmpD:%d, PhaseP:%d, PhaseI:%d, PhaseD:%d%s\n",
				KCYN,
				armDataDetailedDestination->Entry0, 
				armDataDetailedDestination->Entry1, 
				armDataDetailedDestination->Entry2, 
				armDataDetailedDestination->Entry3,
				armDataDetailedDestination->Entry4,
				armDataDetailedDestination->Entry5,
				armDataDetailedDestination->Entry6,
				armDataDetailedDestination->Entry7,
				armDataDetailedDestination->Entry8,
				armDataDetailedDestination->Entry9,
				armDataDetailedDestination->Entry10,
				KNRM);
		}
#endif
}

/**************************************************************************//**
* \brief  - Process TX PDO event received from the control task to write
* 			data to internal shared memory (SD) after relevant data was
* 			read from the SM.
* 			
*			UINT32  Amplitude;
*			INT32  	Phase;
*			UINT32  Power;
*			UINT32  Frequency;
*			UINT32  Current;
*			UINT32  PC_StatusEvent;
*			UINT32	PCState;
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::PDODownloadRequest()
{
	// read data from the SM here...
	if(Com_dspDataRead(&dspData))
	{
		DspRealTimeDataDetailed* dspDataDetailed = (DspRealTimeDataDetailed*)&dspData.Entries;
		
		// write DSP core data to internal shared memory here...
		DSP_TX.Amplitude = dspDataDetailed->Entry0;
		DSP_TX.Phase = dspDataDetailed->Entry1;
		DSP_TX.Frequency = dspDataDetailed->Entry2;
		DSP_TX.Current = dspDataDetailed->Entry3;
		SetCoreState(dspDataDetailed->Entry4);
		
#if DSP_DBG
		static int factorTx = 0;
		if (!CP->bConsoleScrollLock) 
			if (++factorTx % ((1000000) / (CTRL_CYCLE_TIME_IN_US * DSP_TX_EVENT_INTERVAL)) == 0)
			{
				LOG("\nDSPpdoDownloadRequest: A:%d, P:%d, F:%d, C:%d, S:%X\n", 
					dspDataDetailed->Entry0, 
					dspDataDetailed->Entry1, 
					dspDataDetailed->Entry2, 
					dspDataDetailed->Entry3, 
					dspDataDetailed->Entry4);
			}
#endif
	}
	else
		LOGERR((char *)"Invalid DSP data", 0,0,0);
}

/**************************************************************************//**
* \brief  - this function will turn off the sonics.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::TurnOffSonics()
{		
	//Turn Off Sonics	
	DSP_RX.MasterEvents |= BIT_MASK(PCState::CTRL_PC_SONIC_DISABLE);
	DSP_RX.TargetAmplitude = 0;	
}

/**************************************************************************//**
* \brief  - this function will turn on the sonics.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::TurnOnSonics()
{	
	//Turn on sonics	
	DSP_RX.MasterEvents &= ~BIT_MASK(PCState::CTRL_PC_SONIC_DISABLE);
}
/**************************************************************************//**
* \brief  - this function will read seek recipe parameter and assign them to
*  respective DSP state parameters.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::UpdateSeekParameters()
{
	auto &refSeekRecipe = SeekRecipe::GetInstance();
	
	DSP_RX.TargetAmplitude = refSeekRecipe.GetSeekAmplitude();
	DSP_RX.AmplitudeRampTime = refSeekRecipe.GetSeekAmplitudeRampTime();
	DSP_RX.AmpProportionalGain =refSeekRecipe.GetSeekAmpProportionalGain(); 
	DSP_RX.AmpIntegralGain = refSeekRecipe.GetSeekAmpIntegralGain();
	DSP_RX.AmpDerivativeGain = refSeekRecipe.GetSeekAmpDerivativeGain(); 
	DSP_RX.PhaseProportionalGain = refSeekRecipe.GetSeekPhaseProportionalGain(); 
	DSP_RX.PhaseIntegralGain = refSeekRecipe.GetSeekPhaseIntegralGain(); 
	DSP_RX.PhaseDerivativeGain = refSeekRecipe.GetSeekPhaseDerivativeGain(); 
}

/**************************************************************************//**
* \brief  - this function will read weld recipe parameters and assign them to
*  respective DSP state parameters.
*
* \param  - None
*
* \return  - None
*
******************************************************************************/
void DSPTask::UpdateWeldParameters()
{
	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();
	
	DSP_RX.TargetAmplitude = (ScWeldRecipe::GetInstance().InitialAmplitude());
	DSP_RX.StartFrequency = refPcWeldRecipe.GetDigitalTuneWithOffsets()/10;	
	DSP_RX.AmplitudeRampTime = refPcWeldRecipe.GetWeldRampTime();
	DSP_RX.AmpProportionalGain = refPcWeldRecipe.GetAmplitudePGain(); 
	DSP_RX.AmpIntegralGain = refPcWeldRecipe.GetAmplitudeIGain();
	DSP_RX.AmpDerivativeGain = refPcWeldRecipe.GetAmplitudeDGain(); 
	DSP_RX.PhaseProportionalGain = refPcWeldRecipe.GetPhasePGain(); 
	DSP_RX.PhaseIntegralGain = refPcWeldRecipe.GetPhaseIGain(); 
	DSP_RX.PhaseDerivativeGain = refPcWeldRecipe.GetPhaseDGain();
}

/**************************************************************************//**
* \brief   -  	Captures DSP shared memory data at every 1 ms and insert into
* 				std::vector called m_vLastWeldDSPData.
*
* \param   -	None
*
* \return  -    None 
*
******************************************************************************/
void DSPTask::CaptureDSPData()
{
	DspRealTimeData dspData = {0};
	DspRealTimeDataDetailed dspDataDetailed = {0};
	//read data from the Shared Memory here.
	if(Com_dspDataRead(&dspData))
    {
        DspRealTimeDataDetailed* pdspDataDetailed = (DspRealTimeDataDetailed*)&dspData.Entries;
        
        dspDataDetailed.Entry0 = pdspDataDetailed->Entry0;
        dspDataDetailed.Entry1 = pdspDataDetailed->Entry1;
        dspDataDetailed.Entry2 = pdspDataDetailed->Entry2;
        dspDataDetailed.Entry3 = pdspDataDetailed->Entry3;
        dspDataDetailed.Entry4 = pdspDataDetailed->Entry4;
        dspDataDetailed.Entry5 = pdspDataDetailed->Entry5;
        dspDataDetailed.Entry6 = pdspDataDetailed->Entry6;
		
		CP->m_vLastWeldDSPData.push_back(dspDataDetailed);
	}
	else
	{
		LOGERR((char *)"SonicOn - CaptureDSPData: Invalid DSP data", 0,0,0);
	}
}

/**************************************************************************//**
* \brief  -  this function will set the StartFrequency.
*
* \param  - UINT32 - StartFrequency
*
* \return  - None
*
******************************************************************************/
void DSPTask::SetRxStartFrequency(UINT32 startfrequency)
{
	DSP_RX.StartFrequency = startfrequency;
}

/**************************************************************************//**
* \brief  - this function will return the Frequency.
*
* \param  - None
*
* \return - UINT32 - Frequency
*
******************************************************************************/
UINT32 DSPTask::GetTxFrequency()
{
	return DSP_TX.Frequency;
}

/**************************************************************************//**
* \brief  - this function will update the PC Control events.
*
* \param  - UINT32 - PC control event
*
* \return  - None
*
******************************************************************************/
void DSPTask:: UpdateRxMasterEvent (UINT32 masterevent)
{
	DSP_RX.MasterEvents |= BIT_MASK(masterevent);	
}
