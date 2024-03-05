/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  		This file contains the DSP related information
***************************************************************************/

#ifndef DSPTASK_H_
#define DSPTASK_H_

#include "PowerSupplyTask.h"
#include "MainTask.h"
#include <sdLib.h>
#include "PCState.h"
#include "PCStateMachine.h"
extern "C"
{
	#include "Com.h"
}

class DSPTask: public PowerSupplyTask 
{
public:
	DSPTask				();
	virtual	~DSPTask	();
	
	//Function to Read data from internal shared memory (SD)
	virtual void		PDOUploadRequest		() 			override;	
	//Function to write data to internal shared memory (SD)
	virtual void		PDODownloadRequest		() 			override;			
	virtual void 		TurnOffSonics			() 			override;	
	//Function to update all seek recipe parameter
	virtual void 		UpdateSeekParameters	() 			override;			
	virtual void 		TurnOnSonics			() 			override;	
	//Function to update all Weld recipe parameter
	virtual void 		UpdateWeldParameters	()			override;				
	virtual void 		CaptureDSPData			() 			override;			

	virtual UINT32 		GetTxFrequency			() 			override;				
	virtual void		SetRxStartFrequency   	(UINT32)  	override;					
	virtual void		UpdateRxMasterEvent		(UINT32)	override;

private:
	struct RxPDO_DSP
	{
		UINT32	MasterState;
		UINT32	TargetAmplitude;
		UINT32	MasterEvents;
		UINT32  StartFrequency;
		UINT32  AmplitudeRampTime;
		INT32   AmpProportionalGain;
		INT32   AmpIntegralGain;
		INT32   AmpDerivativeGain;
		INT32   PhaseProportionalGain;
		INT32   PhaseIntegralGain;
		INT32   PhaseDerivativeGain;
		};
			
	struct TxPDO_DSP
	{
		UINT32  Amplitude;
		INT32  	Phase;
		UINT32  Power;
		UINT32  Frequency;
		UINT32  Current;
		UINT32  DSP_StatusEvent;
		UINT32	DSPState;
	};
	
	static TxPDO_DSP DSP_TX;
	static RxPDO_DSP DSP_RX;
	static DspRealTimeData 	dspData;
};

#endif /* DSPTASK_H_ */
