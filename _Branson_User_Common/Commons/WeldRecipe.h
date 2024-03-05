/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/


#ifndef WELDRECIPE_H_
#define WELDRECIPE_H_

#include "Common.h"
#include "Utils.h"
#include "WeldRecipeAC.h"
#include "WeldRecipePC.h"

#define USER_NAME_SIZE						16
#define RECIPE_NAME_SIZE					16
#define SYSINFO_SIZE						16
#define MAC_ADDR_SIZE      					18

enum 
{
	SUSPECT_LIMIT = 1,
	REJECT_LIMIT
};

typedef 
enum 
{
	TIME_LIMIT_ML = 1,
	TIME_LIMIT_PL,
	ENERGY_LIMIT_ML,
	ENERGY_LIMIT_PL,
	PEAKPOWER_LIMIT_ML,
	PEAKPOWER_LIMIT_PL,
	COLLAPSE_LIMIT_ML,
	COLLAPSE_LIMIT_PL,
	ABSOLUTE_LIMIT_ML,
	ABSOLUTE_LIMIT_PL,
	TRIGGER_LIMIT_ML,
	TRIGGER_LIMIT_PL,
	WELDFORCE_LIMIT_ML,
	WELDFORCE_LIMIT_PL,
	FREQUENCY_LIMIT_ML,
	FREQUENCY_LIMIT_PL,
}LimitType;

typedef 
enum 
{
	PEAK_POWER_CUTOFF,
	COLLAPSE_DISTANCE_CUTOFF,
	ABSOLUTE_DISTANCE_CUTOFF,
	TIME_CUTOFF,
	FREQUENCY_LOW_CUTOFF,
	FREQUENCY_HIGH_CUTOFF,
	ENERGY_CUTOFF,
	GROUND_DETECT_CUTOFF,
}ControlLimitType;

typedef enum {
	STEPBYTIME = 1,
	STEPBYENERGY,
	STEPBYPOWER,
	STEPBYABSOLUTEDISTANCE,
	STEPBYCOLLAPSEDISTANCE
} STEPPINGMODE;

/* PROPORTIONAL GAIN FACTOR - LOW = 1.5, MEDIUM = 3.0 and HIGH = 5.0 */
typedef
	enum {CONTROL_LOW = 1, CONTROL_MEDIUM, CONTROL_HIGH}WELDFORCECONTROL;
	
typedef enum {
	SAVED,
	VALIDATED,
	UNSAVED
}RECIPE_STATUS;
	
typedef struct Limits
{
   bool	bEnabled;
   bool bLowEnabled;
   bool bHighEnabled;
   INT32 LowLimit;
   INT32 HighLimit;
}Limits;

typedef struct SuspectReject
{
	Limits Time;	
	Limits Energy;
	Limits PeakPower;
	Limits CollapseDistance;
	Limits AbsoluteDistance;
	Limits TriggerDistance;
	Limits WeldForce;
	Limits Frequency;
}SuspectReject;

typedef struct CutoffLimitsProp
{
	bool 	bEnabled;
	INT32 	Value;
}CutOffLimitsProp;

typedef struct CutOffLimits
{
	CutOffLimitsProp  	PeakPowerCutoff;
    CutOffLimitsProp  	AbsoluteDistanceCutoff;
	CutOffLimitsProp  	CollapseDistanceCutoff;
	CutOffLimitsProp  	TimeCutoff;  
	CutOffLimitsProp    FrequencyLowCutoff;
	CutOffLimitsProp    FrequencyHighCutoff;
	CutOffLimitsProp  	EnergyCutoff;
    bool				bGroundDetectCutoff;
}CutOffLimits;

typedef struct Burst
{
	bool   bEnabled;
	INT32  BurstAmplitude;
	INT32 BurstDelay;
	INT32 BurstTime;
}Burst;

typedef struct Trigger
{
	bool   bEnabled;
	bool   bAutoEnabled;
	INT32  TriggerAmplitude;
	bool   bDistanceEnabled;
	INT32 PreTriggerDistance;
}Trigger;

typedef struct Brake
{
	bool   bEnabled;
	INT32  EnergyBrakeAmplitude;
	INT32 EnergyBrakeTime;	
}EnergyBrake;


/**************************************************************************//**
* 
* \brief   - Base type definition for the encapsulation of a recipe member
* 			in all of its possible forms all at the same time, an efficient
* 			way that allows it to support an active system configuration for
* 			the ASC, combining basic and advanced P/S together with various
* 			actuator.   
*
******************************************************************************/
typedef struct ParamDescriptor
{
public:
	
	// system enabled flag true for now, normally based on system type
	ParamDescriptor (): bSystemEnabled (true) {}
	~ParamDescriptor () {}
	
	enum {
		VALUE_INVALID = -2147483648	
	};
	
	typedef struct {
		INT32 		value;
		INT32 		mode;
	}MODEVALUE;
	
	// parameter control
	bool				bSystemEnabled;

protected:
	virtual INT32 		ValidateValue	(INT32 value) {return value;}
	
} ParamDescriptor;


/**************************************************************************//**
* 
* \brief   - Derived type definitions for a specific encapsulation of a
* 			recipe member.
* 			
******************************************************************************/
typedef struct ParamDesc_WELDMODE : public ParamDescriptor {

	// parameter copy
	ParamDesc_WELDMODE& operator=(const ParamDesc_WELDMODE& source) {
		bSystemEnabled = source.bSystemEnabled;
		mode = source.mode;
		return *this;
	}

	// parameter assignment 
	void operator=(const INT32& value) {
		if (bSystemEnabled) {
			mode = ValidateValue (value);
		}
		else
			mode = VALUE_INVALID;
	}
	
	INT32 	Get	() const {return mode;}

private:
	INT32 	ValidateValue	(INT32 value);
	INT32	mode; 
	
} ParamDesc_WELDMODE;

typedef struct ParamDesc_MODEVALUE : public ParamDescriptor {

	// parameter copy
	ParamDesc_MODEVALUE& operator=(const ParamDesc_MODEVALUE& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&modeValue, &source.modeValue, sizeof(modeValue));
		return *this;
	}

	// parameter assignment 
	void operator=(const MODEVALUE& value) {
		if (bSystemEnabled) {
			modeValue[value.mode] = ValidateValue (value.value);
		}
		else
			modeValue[value.mode] = VALUE_INVALID;
	}
	
	INT32	Get	(INT32 mode) const {_CHECKRETURN(mode > 0 && mode < MAX_MODES,VALUE_INVALID) return modeValue[mode];}
	
private:
	INT32 	ValidateValue	(INT32 value);
	INT32	modeValue[MAX_MODES];
	
} ParamDesc_MODEVALUE;

typedef struct ParamDesc_INT32 : public ParamDescriptor {

	// parameter copy
	ParamDesc_INT32& operator=(const ParamDesc_INT32& source) {
		bSystemEnabled = source.bSystemEnabled;
		intNumber = source.intNumber;
		return *this;
	}

	// parameter assignment 
	virtual void operator=(const INT32& value) {
		if (bSystemEnabled)
			intNumber = value;
		else
			intNumber = VALUE_INVALID;
	}
	
	INT32 Get () const {return intNumber;}
	
protected:
	INT32	intNumber;
	
} ParamDesc_INT32;

// An ParamDesc_INT32 descriptor with the ability to validate other RT parameters
typedef struct ParamDesc_AMPSTEPS : public ParamDesc_INT32 {
	
	// parameter assignment 
	void operator=(const INT32 value) {
		if (bSystemEnabled)
			intNumber = ValidateValue (value);
		else
			intNumber = VALUE_INVALID;
	}
	
private:
	INT32 	ValidateValue	(INT32 value);

} ParamDesc_AMPSTEPS;

typedef struct ParamDesc_STRING : public ParamDescriptor {

	// parameter copy
	ParamDesc_STRING& operator=(const ParamDesc_STRING& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (str, source.str, sizeof(str));
		return *this;
	}

	// parameter assignment 
	void operator=(const char* value) {
		if (bSystemEnabled) {
			memset(str, 0x00, sizeof(str));
			memcpy (str, value, sizeof(str));
		}
		else
			snprintf (str, sizeof(str), "%s", "N/A");
	}
	
	char* Get () const {return (char*) str;}

private:
	char	str[100];
	
} ParamDesc_STRING;

typedef struct ParamDesc_CUTOFFLIMITS : public ParamDescriptor {

	// parameter copy
	ParamDesc_CUTOFFLIMITS& operator=(const ParamDesc_CUTOFFLIMITS& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&cutoffLimit, &source.cutoffLimit, sizeof(cutoffLimit));
		return *this;
	}

	// parameter assignment 
	void operator=(const CutOffLimits& value) {
		if (bSystemEnabled)
			memcpy (&cutoffLimit, &value, sizeof(cutoffLimit));
		else { 
			cutoffLimit.AbsoluteDistanceCutoff.Value = VALUE_INVALID;
			cutoffLimit.CollapseDistanceCutoff.Value = VALUE_INVALID;
			cutoffLimit.EnergyCutoff.Value = VALUE_INVALID;
			cutoffLimit.FrequencyHighCutoff.Value = VALUE_INVALID;
			cutoffLimit.FrequencyLowCutoff.Value = VALUE_INVALID;
			cutoffLimit.PeakPowerCutoff.Value = VALUE_INVALID;
			cutoffLimit.TimeCutoff.Value = VALUE_INVALID;
		}
	}
			
	CutOffLimits Get () const {return cutoffLimit;}

private:
	CutOffLimits cutoffLimit;
		
} ParamDesc_CUTOFFLIMITS;

typedef struct ParamDesc_TRIGGER : public ParamDescriptor {

	// parameter copy
	ParamDesc_TRIGGER& operator=(const ParamDesc_TRIGGER& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&preTrigger, &source.preTrigger, sizeof(preTrigger));
		return *this;
	}

	// parameter assignment 
	void operator=(const Trigger& value) {
		if (bSystemEnabled)
			memcpy (&preTrigger, &value, sizeof(preTrigger));
		else 
			preTrigger.PreTriggerDistance = VALUE_INVALID;
			preTrigger.TriggerAmplitude = VALUE_INVALID;
	}
	
	Trigger Get () const {return preTrigger;}
	
private:
	Trigger	preTrigger;

} ParamDesc_TRIGGER;

typedef struct ParamDesc_BURST : public ParamDescriptor {

	// parameter copy
	ParamDesc_BURST& operator=(const ParamDesc_BURST& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&afterBurst, &source.afterBurst, sizeof(afterBurst));
		return *this;
	}

	// parameter assignment 
	void operator=(const Burst& value) {
		if (bSystemEnabled)
			memcpy (&afterBurst, &value, sizeof(afterBurst));
		else {
			afterBurst.BurstAmplitude = VALUE_INVALID;
			afterBurst.BurstDelay = VALUE_INVALID;
			afterBurst.BurstTime = VALUE_INVALID;
		}
	}
	
	Burst Get () const {return afterBurst;}

private:
	Burst	afterBurst;
	
} ParamDesc_BURST;

typedef struct ParamDesc_BRAKE : public ParamDescriptor {

	// parameter copy
	ParamDesc_BRAKE& operator=(const ParamDesc_BRAKE& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&energyBrake, &source.energyBrake, sizeof(energyBrake));
		return *this;
	}

	// parameter assignment 
	void operator=(const Brake& value) {
		if (bSystemEnabled)
			memcpy (&energyBrake, &value, sizeof(energyBrake));
		else {
			energyBrake.EnergyBrakeAmplitude = VALUE_INVALID;
			energyBrake.EnergyBrakeTime = VALUE_INVALID;
		}
	}
		
	Brake Get () const {return energyBrake;}

private:
	Brake			energyBrake;

} ParamDesc_BRAKE;

typedef struct ParamDesc_SUSPECT : public ParamDescriptor {

	// parameter copy
	ParamDesc_SUSPECT& operator=(const ParamDesc_SUSPECT& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&suspectLimits, &source.suspectLimits, sizeof(suspectLimits));
		return *this;
	}

	// parameter assignment 
	void operator=(const SuspectReject& value) {
		if (bSystemEnabled)
			memcpy (&suspectLimits, &value, sizeof(suspectLimits));
		else {
			suspectLimits.AbsoluteDistance.HighLimit = VALUE_INVALID;
			suspectLimits.AbsoluteDistance.LowLimit = VALUE_INVALID;
			suspectLimits.CollapseDistance.HighLimit = VALUE_INVALID;
			suspectLimits.CollapseDistance.LowLimit = VALUE_INVALID;
			suspectLimits.Energy.HighLimit = VALUE_INVALID;
			suspectLimits.Energy.LowLimit = VALUE_INVALID;
			suspectLimits.Frequency.HighLimit = VALUE_INVALID;
			suspectLimits.Frequency.LowLimit = VALUE_INVALID;
			suspectLimits.PeakPower.HighLimit = VALUE_INVALID;
			suspectLimits.PeakPower.LowLimit = VALUE_INVALID;
			suspectLimits.Time.HighLimit = VALUE_INVALID;
			suspectLimits.Time.LowLimit = VALUE_INVALID;
			suspectLimits.TriggerDistance.HighLimit = VALUE_INVALID;
			suspectLimits.TriggerDistance.LowLimit = VALUE_INVALID;
			suspectLimits.WeldForce.HighLimit = VALUE_INVALID;
			suspectLimits.WeldForce.LowLimit = VALUE_INVALID;
		}
	}
		
	SuspectReject Get () const {return suspectLimits;}
	
private:
	SuspectReject 	suspectLimits;

} ParamDesc_SUSPECT;

typedef struct ParamDesc_REJECT : public ParamDescriptor {

	// parameter copy
	ParamDesc_REJECT& operator=(const ParamDesc_REJECT& source) {
		bSystemEnabled = source.bSystemEnabled;
		memcpy (&rejectLimits, &source.rejectLimits, sizeof(rejectLimits));
		return *this;
	}

	// parameter assignment 
	void operator=(const SuspectReject& value) {
		if (bSystemEnabled)
			memcpy (&rejectLimits, &value, sizeof(rejectLimits));
		else {
			rejectLimits.AbsoluteDistance.HighLimit = VALUE_INVALID;
			rejectLimits.AbsoluteDistance.LowLimit = VALUE_INVALID;
			rejectLimits.CollapseDistance.HighLimit = VALUE_INVALID;
			rejectLimits.CollapseDistance.LowLimit = VALUE_INVALID;
			rejectLimits.Energy.HighLimit = VALUE_INVALID;
			rejectLimits.Energy.LowLimit = VALUE_INVALID;
			rejectLimits.Frequency.HighLimit = VALUE_INVALID;
			rejectLimits.Frequency.LowLimit = VALUE_INVALID;
			rejectLimits.PeakPower.HighLimit = VALUE_INVALID;
			rejectLimits.PeakPower.LowLimit = VALUE_INVALID;
			rejectLimits.Time.HighLimit = VALUE_INVALID;
			rejectLimits.Time.LowLimit = VALUE_INVALID;
			rejectLimits.TriggerDistance.HighLimit = VALUE_INVALID;
			rejectLimits.TriggerDistance.LowLimit = VALUE_INVALID;
			rejectLimits.WeldForce.HighLimit = VALUE_INVALID;
			rejectLimits.WeldForce.LowLimit = VALUE_INVALID;
		}
	}
		
	SuspectReject Get () const {return rejectLimits;}
	
private:
	SuspectReject 	rejectLimits;

} ParamDesc_REJECT;

/**************************************************************************//**
* 
* \brief   - Recipe type definitions for a specific discipline
* 			 i.e. supervisory, power controller or an actuator.
* 			
******************************************************************************/
typedef struct WeldRecipeSC
{
public:
	WeldRecipeSC ();
	
	ParamDesc_INT32  	RecipeNumber;
	ParamDesc_INT32		RecipeRevNumber;
	ParamDesc_WELDMODE	WeldMode;
	ParamDesc_MODEVALUE	ModeValue;
	ParamDesc_INT32		HoldTime;
	ParamDesc_INT32		TriggerForce;
	ParamDesc_INT32		TriggerDistance;
	ParamDesc_INT32 	MaxWeldTimeout;
	
	ParamDesc_AMPSTEPS  NumAmplitudeSteps;
	INT32  				AmplitudeStepAt; 								// stepping by what i.e. time, energy
	
	INT32				NumForceSteps;
	INT32  				ForceStepAt; 									// stepping by what i.e. time, energy
	
	INT32  				ForceStepAtValue[MAX_NO_OF_FORCE_STEP]; 		// i.e. time, energy values to step
	INT32 				AmplitudeStepValue[MAX_NO_OF_AMPLITUDE_STEP]; 	// i.e. time, energy values to step
	
	INT32 				AmplitudeStep[MAX_NO_OF_AMPLITUDE_STEP];		// i.e. the amplitudes themselves
	
	bool   				bCoolingValveEnabled;
	bool   				bSuspectLimitEnabled;
	bool   				bRejectLimitEnabled;
	bool				bCutoffLimitEnabled;
	CutOffLimits    	CutoffLimit;
	Trigger 			PreTrigger;
	Burst				AfterBurst;
	Brake				EnergyBrake;
	SuspectReject 		SuspectLimit;
	SuspectReject 		RejectLimit;
	INT32				TimedSeekPeriod;
	bool				bTimedSeekEnabled;
	bool				bPreWeldSeekEnabled;
	bool				bPostWeldSeekEnabled;
	bool				bRecipeValidated;
	INT32 				StackSerialNo;
	char   				User[USER_NAME_SIZE];
}WeldRecipeSC;


typedef struct StackRecipeSC
{
	INT32  DigitalTune;		
	INT32  MemOffset;
	INT32  InternalOffset;
	INT32  DigitalTuneMemory;
	bool   bMemoryClear;
	bool   bHornScanPassed;
	INT32  SystemMidBand;	
	INT32  Memory;
	INT32  InternalFreqOffset;
	INT32  InternalOffsetFlag;
	INT32  EndofWeldStore;
	bool   bClearMemoryAtPowerUp;
    bool   bClearMemoryWithReset;
	
}StackRecipeSC;


typedef struct WeldRecipe
{
	WeldRecipeSC	SCData;
	WeldRecipePC	PCData;
	WeldRecipeAC	ACData;
}WeldRecipe;


class WeldRecipeStatus
{
public:
	static RECIPE_STATUS GetRecipeStatus () { return recipeStatus;};
	static void SetRecipeStatus (RECIPE_STATUS status) { recipeStatus = status;};
	
private:
	static RECIPE_STATUS recipeStatus;
};


#endif /* WELDRECIPE_H_ */
