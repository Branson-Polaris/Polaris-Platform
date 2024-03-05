/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef WELDRECIPESC_H_
#define WELDRECIPESC_H_

#include "WeldRecipe.h"

/* Default value of weld recipe for the AC */
#define SC_WELDMODE_DEFAULT           		TIMEMODE
#define SC_WELDMODE_VALUE_DEFAULT      		100
#define SC_HOLD_TIME_IN_MS_DEFAULT      	1000

class ScWeldRecipe
{
public:
	ScWeldRecipe(const ScWeldRecipe& srcObj) = delete;
	ScWeldRecipe& operator=(const ScWeldRecipe& srcObj) = delete;
	static ScWeldRecipe& GetInstance();
	
	INT32		GetHoldTime() const;
	WELDMODES 	GetWeldMode() const;
	INT32		GetModeValue() const;
	INT32		GetRecipeNumber() const;
	INT32		GetTriggerForce() const;
	INT32		GetMaxWeldTimeout() const;
	
	/* Amplitude step interfaces */
	UINT16	InitialAmplitude() const;
	INT32	GetAmplitudeSteps() const;
	UINT8	GetAmplitudeStepAt() const;
	INT32	GetTriggerDistance() const;
	INT32	GetAmplitudeStep(UINT8 index) const;
	INT32	GetAmplitudeStepAtValue(UINT8 index) const;
	
	/* Force step interfaces */
	UINT16	GetForceStepAt() const;
	UINT16	GetNumberOfForceSteps() const;
	UINT32  GetForceStepAtValue(UINT8 index) const;
	
	Trigger     GetPreTrigger() const;
	Burst		GetAfterBurst() const;
	Brake		GetEnergyBrake() const;
	void	    GetUserName(std::string& userName);
	void		SetUserName(char* name);
	INT32		GetRecipeNumber();
	INT32		GetRecipeRevNumber();
	
	void 	    SetWeldRecipe(WeldRecipeSC& recipe);
	
	UINT32	    GetStackSerialNumber() const;
	void        UpdateForceStep(UINT16 noOfStep, UINT16 stepAt,UINT16 *stepValue);
	bool		IsGlobalLimitCheckEnabled(UINT8 typeOfLimit);
	bool		IsLimitCheckEnabled(UINT8 typeOfLimit,UINT8 typeOfMode);
	bool		ValidateRejectLimit(UINT8 typeOfMode,UINT32 value);
	bool		ValidateSuspectLimit(UINT8 typeOfMode,UINT32 value);
	UINT32		GetTimedSeek();
	bool 		IsPreWeldSeekEnabled();
	bool 		IsCoolingValveEnabled();
	bool 		IsPostWeldSeekEnabled();
	void		DisplaySuspectLimit();
	void		DisplayRejectLimit();
	void		DisplayForceStep();
	void		RecipeInformation();
	void		DisplayAmplitudeStep();
	void    	DisplayControlLimits();
	void   		DisplayPreTrigger();
	void    	DisplayAfterBurst();
	void		DisplayEnergyBrake();
	bool		IsTimedSeekEnabled();
	void		GetWeldRecipe(WeldRecipeSC& recipe);
	bool        ValidateCutoffLimit(UINT8 typeOfMode, UINT32 value);
	bool        IsCutoffLimitCheckEnabled(UINT8 typeOfMode);
	bool        IsGlobalCutOffLimitCheckEnabled();
	void        DisplaycutoffLimit();
	bool		IsRecipeValidated() const;
	
private:
	WeldRecipeSC m_Recipe;
	ScWeldRecipe();
	~ScWeldRecipe();
};

#endif /* WELDRECIPESC_H_ */
