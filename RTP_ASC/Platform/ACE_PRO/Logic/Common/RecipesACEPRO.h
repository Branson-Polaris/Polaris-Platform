/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef RECIPESACEPRO_H_
#define RECIPESACEPRO_H_

typedef enum WELD_MODE
{
   TIME,
   ENERGY,
   PEAK_POWER,
   GROUND_DETECT,
}WELD_MODE;

typedef enum STEP_TYPE 
{
   TIME,
   ENERGY,
   POWER,
   EXTERNAL,
}STEP_TYPE ;

typedef struct WeldRecipeSCACEPRO
{
	INT32  			RecipeNumber; 			// the number of recipe
	WELD_MODE  		WeldMode;     			// the weld mode type ie time,energy etc.
	INT32 			ModeValueTime;
	INT32 			ModeValueEnergy;
	INT32 			ModeValuePeakPower;
	INT32 			ModeValueGroundDetect;
	INT32  			HoldTime;
	INT32 			MaxWeldTimeout; 		// the weld operation time out period
	UINT32  		NumAmplitudeSteps;		//The number of amplitude changes or steps that need to occur during the weld.
	STEP_TYPE   	AmplitudeStepAt;        //This holds the attribute of the amplitude step value. This can be time, energy, etc.
											//and this determines the data type that is present in AmplitudeStepValue. 
											//For example, if this variable is set to TIME, then the contents of AmplitudeStepValue is a 
											//time based value
	UINT32 			AmplitudeStepAtValue;   //Holds the value that is monitored during the weld to tell the power supply when to perform the step.
											//For example, if step at is set to TIME, and this value is 500, then after 500 milliseconds, 
											//the power supply will step to the next amplitude setting.
	UINT32          AmplitudeStepTarget;    //The target amplitude that gets sent to the power supply after meeting the criteria defined 
											//in StepAt and StepValue
	
	UINT32 			AmplitudeStepRamp;  	//This defines the rate at which the power supply changes the amplitude from 
											//the current setting to the new step value.
	bool   			bIsCoolingValveEnabled; //When true, the actuator board will turn on a valve that allows extra 
											//air to be applied to the converter to prevent overheating.
	CutOffLimitsACEPRO   CutoffLimit;
	TRIGGER_TYPE    TriggerType;
	PreTriggerACEPRO PreTrigger;
	AfterBurstACEPRO AfterBurst;
	EnergyBrakeACEPRO EnergyBrake;
	RejectACEPRO 	RejectLimit;
	UINT32			TimedSeekPeriod;  		//This is a time value in seconds that determines the period of how often the 
									  	  	//power supply will automatically initiate a Seek function. (only if system is idle)
	bool			bIsTimedSeekEnabled;  	//When true, enables the Timed Seek function
	bool			bIsPreWeldSeekEnabled;  //When true, during the downstroke of the actuator for a weld, the power supply 
											//will perform a seek function
	bool			bIsPostWeldSeekEnabled; //When true, at the completion of hold time, the power supply will perform a
											//Seek function
	UINT32			ScrubAmplitude;   		//This value is only applicable when the system is in ground detect mode. 
											//After the system has detected ground, the power supply will change its amplitude 
											//to this value
}__attribute__((packed))  WeldRecipeSCACEPRO;

/*following structure will be used fro AC  PRIME
typedef struct WeldRecipeSCACEPRIME
{
	INT32  			RecipeNumber;
	INT32  			WeldMode;
	INT32  			ModeValue;
	INT32  			HoldTime;
	INT32  			TriggerForce;
	INT32  			TriggerDistance;
	INT32 			MaxWeldTimeout;
	UINT8  			NumForceSteps;
	UINT8  			ForceStepAt;
	UINT32  		ForceStepAtValue[];
	UINT8  			NumAmplitudeSteps;
	UINT8  			AmplitudeStepAt;
	UINT32 			AmplitudeStepValue;
	UINT16 			AmplitudeStep;
	bool   			bIsCoolingValveEnabled;
	bool   			bIsRejectLimitEnabled;
	bool			bIsCutoffLimitEnabled;
	CutOffLimits    CutoffLimit;
	Trigger 		PreTrigger;
	Burst			AfterBurst;
	Brake			EnergyBrake;
	SuspectReject 	RejectLimit;
	UINT32			TimedSeekPeriod;
	bool			bIsTimedSeekEnabled;
	bool			bIsPreWeldSeekEnabled;
	bool			bIsPostWeldSeekEnabled;
	UINT32			ScrubAmplitude; 
	
	bool   bIsSuspectLimitEnabled;  //may be need in ACE ELITE
	SuspectReject 	SuspectLimit;   //may be need in ACE ELITE
}WeldRecipeSCACEPRIME;
*/

typedef struct StackRecipeSCACEPRO
{
public:
	//INT32	PhaseLoopCF;      			//reserved for future use
	INT32	FrequencyLow;     			//This is the lower frequency limit for the Weld function. If the read frequency
										//from the DSP drops below this value, it will generate an alarm
	INT32	FrequencyHigh;   			//This is the upper frequency limit for the Weld function.If the read frequency 
										//from the DSP exceeds this value, it will generate an alarm  
	INT32	PhaseLimitTime;  			//System will generate an alarm if the Phase value reported from the power supply
										//exceeds PhaseLimit for a certain time period. This is the time period.
	INT32	PhaseLimit;     			//This is a threshold that will generate an alarm in conjunction with the 
										//PhaseLimitTime if the Phase value read from the Power supply exceeds it.
	INT32	ControlMode;   				//reserved for future use 
	INT32	Blindtimeweld;   			//Time in milliseconds that tells the power supply to run open loop at the start
										//of the weld prior to enabling the control loops.
	INT32	AmpProportionalGain;
	INT32	AmpIntegralGain;
	INT32	AmpDerivativeGain;
	INT32	PhaseDerivativeGain;
	INT32 	PhaseIntegralGain;
	INT32	PhaseProportionalGain;
	INT32	WeldRampTime;
	INT32   StartFrequency;   			//A value in tenths of hertz that tells the power supply what frequency to start 
										//running at. Weld Start Frequency = Digital Tune + Frequency Offset + Memory Offset
	INT32   MemoryOffset;     			//Value in tenths of hertz that is applied to the Ditigital Tune value. This value 
										//is automatically calculated and updated in software at the end of the weld depending
										//on the value of bEndOfWeldStore. If the flag is true, this value is updated with the
										//difference of the frequency read at the end of the weld minus the start frequency. 
										//It effectively acts as a tracking mechanism as the stack frequency shifts during 
										//production.
	INT32   DigitalTune;      			//This is the frequency at which the stack "wants" to run at. It is typically found 
										//during a horn scan, but can also be manually overriden on the HMI. 
	INT32   FrequencyOffset;  			//A value in tenths of hertz that can be applied to the Start Frequency. This is 
										//manually entered from the HMI for special conditions where Digital Tune and Memory Offset
										//are not enough. This value can also come from other interfaces like analog input or fieldbus.
	                          	  	  	//The value is applied to the Start Frequency when bInternalOffset is true or when false,
										//it will use the externally provided value
	bool 	bEndOfWeldStore;  			//When true, the MemoryOffset value will be updated at the end of the weld (if no alarm is present) as follows:
							  	  	  	//MemoryOffset = End Frequency - DigitalTune.
							  	  	  	//FrequencyOffset has no effect on this value.
							  	  	  	//End Frequency is defined as the frequency value read at the time the sonics are turned off.
							 			//When false, MemoryOffset will not be modified (previous value will be maintained)
	bool  	InternalOffsetFlag; 								
	bool   	bClearMemoryAtPowerUp;		//When true, MemoryOffset will be set to 0 when the system powers up.
										//When false, MemoryOffset will be maintained from the previous power down.
	bool   	bClearMemoryWithReset;		//When true, any time an alarm reset is applied (HMI, Digital Input, fieldbus, etc.)
										//the MemoryOffset will also be set to 0.
	                              	  	//When false, MemoryOffset is maintained.
}__attribute__((packed))  StackRecipeSCACEPRO;

typedef struct SeekRecipeACEPRO
{

	INT32  SeekFreqLimitHigh;    		//This is the upper frequency limit for the Seek function.If the read frequency from the DSP
										//exceeds this value, it will generate an alarm  
	INT32  SeekFreqLimitLow;     		//This is the lower frequency limit for the Seek function. If the read frequency from the DSP
										//drops below this value, it will generate an alarm
	INT32  SeekFreqOffset;       		//This value will be applied to the start frequency value when Seek is initiated.
	                             		//Weld Start Frequency = Digital Tune + Frequency Offset + Memory Offset
	                             		//Seek Start Frequency = System Midband + Frequency Offset + Memory Offset
	bool   SeekMemClearBeforeSeek;  	//This will set MemoryOffset equal to 0 at the start of the Seek
	UINT32 SeekTime;                	//time required for the seek operation
	UINT32 SeekAmplitudeRampTime;   	//Time in milliseconds that it will take for the amplitude to reach 100%
	UINT32 SeekAmplitude;           	//Target amplitude for the DSP during seek function
	INT32  SeekAmpProportionalGain; 	//The following 6 values are the control loop parameters for the ultrasonics.
										//Weld and Seek ideally have different optimal values
	INT32  SeekAmpIntegralGain;
	INT32  SeekAmpDerivativeGain;
	INT32  SeekPhaseProportionalGain;
	INT32  SeekPhaseIntegralGain;
	INT32  SeekPhaseDerivativeGain;
	INT32	BlindtimeSeek; 
/*following parameter's are present in GSX-E2 project only . */	
	INT32  SeekPhaseloopCF;	
}__attribute__((packed))  SeekRecipeACEPRO;

typedef struct ScanRecipeACEPRO	
{
	UINT32 FrequencyStart;
	UINT32 FrequencyStop;
	UINT32 FrequencyStep;
	UINT32 TimeDelay;
	UINT32 MaxAmplitude;
	UINT32 MaxCurrent;
	bool  SetDigTuneWithHornScan;
}__attribute__((packed))  ScanRecipeACEPRO;


typedef struct TestRecipeACEPRO
{
	INT32  TestFreqLimitHigh;
	INT32  TestFreqLimitLow; 
	INT32  TestFreqOffset;
	bool   TestMemClearBeforeSeek;
	UINT32 TestAmplitudeRampTime;
	UINT32 TestAmplitude; 
	INT32  TestAmpProportionalGain;
	INT32  TestAmpIntegralGain;
	INT32  TestAmpDerivativeGain;
	INT32  TestPhaseProportionalGain;
	INT32  TestPhaseIntegralGain;
	INT32  TestPhaseDerivativeGain;
	INT32  TestPhaseloopCF;		
}__attribute__((packed))  TestRecipeACEPRO;

typedef struct AfterBurstACEPRO
{
	bool   bEnabled;       	//When true, enables the afterburst function which will turn on sonics during 
							//the upstroke for a short period of time to shake any stuck plastic off the horn
	INT32  BurstAmplitude; 	//Amplitude setting for the afterburst function
	INT32 BurstDelay;      	//A value in milliseconds that the system will wait after the end of hold time 
							//(during upstroke) before turning on sonics.
	INT32 BurstTime;		//A value in milliseconds that determines the duration that sonics will be on for 
							//the afterburst function
}__attribute__((packed))  AfterBurstACEPRO;

typedef struct EnergyBrakeACEPRO
{
	bool   bEnabled;
	INT32  EnergyBrakeAmplitude;
	INT32 EnergyBrakeTime;	
}__attribute__((packed))  EnergyBrakeACEPRO;

// ACE Pro only has one method of triggering so keeping this enum for future code reuse.
typedef enum TRIGGER_TYPE
{
    EXTERNAL, //sonics turns on based on a digital input
}TRIGGER_TYPE;

// ACE Pro only has one method of Pretriggering so keeping this enum for future code reuse.
typedef enum PRE_TRIGGER_TYPE
{
    AUTO, //sonics turns on when leaving ULS
}PRE_TRIGGER_TYPE;

typedef struct PreTriggerACEPRO
{
	bool   bEnabled;
	PRE_TRIGGER_TYPE Pretriggertype;
	INT32  Amplitude;
}__attribute__((packed))  PreTriggerACEPRO;

typedef struct Limits
{
   bool	bEnabled;
   bool bLowEnabled;
   bool bHighEnabled;
   INT32 LowLimit;
   INT32 HighLimit;
}__attribute__((packed))  Limits;

/* reserved for future use 
typedef struct SuspectACEPRO
{
	bool   bSuspectLimitsEnabled;
	Limits Time;	
	Limits Energy;
	Limits PeakPower;
	Limits Frequency;
}SuspectACEPRO;
*/
typedef struct RejectACEPRO
{
	bool   bRejectLimitsEnabled;
	Limits Time;	
	Limits Energy;
	Limits PeakPower;
	Limits Frequency;
}__attribute__((packed))  RejectACEPRO;

typedef struct CutoffLimitsProp
{
	bool 	bEnabled;
	INT32 	Value;
}__attribute__((packed))  CutOffLimitsProp;

typedef struct CutOffLimitsACEPRO
{
	bool                bCutOffLimitsEnabled;
	CutOffLimitsProp  	PeakPowerCutoff;
    CutOffLimitsProp  	AbsoluteDistanceCutoff;
	CutOffLimitsProp  	CollapseDistanceCutoff;
	CutOffLimitsProp  	TimeCutoff;  
	CutOffLimitsProp    FrequencyLowCutoff;
	CutOffLimitsProp    FrequencyHighCutoff;
	CutOffLimitsProp  	EnergyCutoff;
    bool				bGroundDetectCutoff;
}__attribute__((packed))  CutOffLimitsACEPRO;



#endif /* RECIPESACEPRO_H_*/
