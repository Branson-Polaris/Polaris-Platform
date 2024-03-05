/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Contains Sc Weld Recipe which is edit and set by user in UIC   
 
****************************************************************************/

#include "WeldRecipeSC.h"

/**************************************************************************//**
* 
* \brief   - Initialization of class members and memory for object.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
ScWeldRecipe::ScWeldRecipe()
{
	ParamDescriptor::MODEVALUE modeValue;
	WeldRecipeSC	SCRecipe;
	// defaults for SC recipe
	SCRecipe.WeldMode = SC_WELDMODE_DEFAULT;
	modeValue.mode = SCRecipe.WeldMode.Get();
	modeValue.value = SC_WELDMODE_VALUE_DEFAULT;
	SCRecipe.ModeValue = modeValue;
	SCRecipe.HoldTime	= SC_HOLD_TIME_IN_MS_DEFAULT;
	SCRecipe.AmplitudeStep[0] = WELDAMPLITUDE_DEFAULT;
	SCRecipe.NumAmplitudeSteps = 1;

	SetWeldRecipe(SCRecipe);
}

/**************************************************************************//**
* \brief   - Object destruction and memory release of object.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
ScWeldRecipe::~ScWeldRecipe()
{	
}


/**************************************************************************//**
* 
* \brief   - get singleton instance of ScWeldRecipe.
*
* \param   - None.
*
* \return  - ScWeldRecipe instance.
*
******************************************************************************/
ScWeldRecipe& ScWeldRecipe::GetInstance()
{
	static ScWeldRecipe instance; 
					   
	return instance;
}

/**************************************************************************//**
* 
* \brief   - Returns the weld mode of UW system.
*
* \param   - None.
*
* \return  - WELDMODES.
*
******************************************************************************/
WELDMODES ScWeldRecipe::GetWeldMode() const
{
	return (WELDMODES)m_Recipe.WeldMode.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns the weld value of UW system based on WELD.
*
* \param   - None.
*
* \return  - INT32 - ModeValue.
*
******************************************************************************/
INT32 ScWeldRecipe::GetModeValue() const
{
	return m_Recipe.ModeValue.Get(m_Recipe.WeldMode.Get());
}

/**************************************************************************//**
* 
* \brief   - Returns the hold time which will be applied in weld.
*
* \param   - None.
*
* \return  - UINT32 - HoldTime.
*
******************************************************************************/
INT32 ScWeldRecipe::GetHoldTime() const
{
	return m_Recipe.HoldTime.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns the SC recipe number which is used for weld.
*
* \param   - None.
*
* \return  - INT32 - RecipeNumber.
*
******************************************************************************/
INT32 ScWeldRecipe::GetRecipeNumber() const
{
	return m_Recipe.RecipeNumber.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns the trigger force which will be reference to SC.
*
* \param   - None.
*
* \return  - INT32 - TriggerForce.
*
******************************************************************************/
INT32 ScWeldRecipe::GetTriggerForce() const
{
	return m_Recipe.TriggerForce.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns amplitude base value.
*
* \param   - None.
*
* \return  - UINT16 - AmplitudeStep.
*
******************************************************************************/
UINT16 ScWeldRecipe::InitialAmplitude() const
{
	return (m_Recipe.AmplitudeStep[0] * 10);
}

/**************************************************************************//**
* 
* \brief   - Returns number of amplitude step configured.
*
* \param   - None.
*
* \return  - UINT8 - NumAmplitudeSteps.
*
******************************************************************************/
INT32 ScWeldRecipe::GetAmplitudeSteps() const
{
	return m_Recipe.NumAmplitudeSteps.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns amplitude step at position.
*
* \param   - None.
*
* \return  - UINT8 - StepAt.
*
******************************************************************************/
UINT8 ScWeldRecipe::GetAmplitudeStepAt() const
{
	return m_Recipe.AmplitudeStepAt;
}

/**************************************************************************//**
* 
* \brief   - Returns the trigger distance - reference to SC -WELD.
*
* \param   - None.
*
* \return  - INT32 - TriggerDistance.
*
******************************************************************************/
INT32 ScWeldRecipe::GetTriggerDistance() const
{
	return m_Recipe.TriggerDistance.Get();
}

/**************************************************************************//**
* \brief   - Returns the max weld timeout- reference to SC -WELD
*
* \param   - None
*
* \return  - UINT32 - MaxWeldTimeout
*
******************************************************************************/
INT32 ScWeldRecipe::GetMaxWeldTimeout() const
{
	return m_Recipe.MaxWeldTimeout.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns amplitude step value present at index.
*
* \param   - UINT8 - index.
*
* \return  - UINT32 - AmplitudeStepValue.
*
******************************************************************************/
INT32 ScWeldRecipe::GetAmplitudeStepAtValue(UINT8 index) const
{
	INT32 stepValue = 0;
	if(index < m_Recipe.NumAmplitudeSteps.Get())
	{
		stepValue = m_Recipe.AmplitudeStepValue[index];
	}
	
	return stepValue;
}

/**************************************************************************//**
* 
* \brief   - Returns amplitude step present at index.
*
* \param   - UINT8 - index.
*
* \return  - UINT16 - AmplitudeStep.
*
******************************************************************************/
INT32 ScWeldRecipe::GetAmplitudeStep(UINT8 index) const
{
	INT32 step = 0;
	if(index < m_Recipe.NumAmplitudeSteps.Get())
	{
		step = m_Recipe.AmplitudeStep[index];
	}

	return step;
}

/**************************************************************************//**
* 
* \brief   - Returns the number of force step.
*
* \param   - None.
*
* \return  - UINT16 - m_NumOfForceStep.
*
******************************************************************************/
UINT16 ScWeldRecipe::GetNumberOfForceSteps() const
{
	return m_Recipe.NumForceSteps;
}

/**************************************************************************//**
* 
* \brief   - Returns the step at mode of force.
*
* \param   - None.
*
* \return  - UINT16 - m_ForceStepAt.
*
******************************************************************************/
UINT16 ScWeldRecipe::GetForceStepAt() const
{
	return m_Recipe.ForceStepAt;
}

/**************************************************************************//**
* 
* \brief   - Returns the force step value.
*
* \param   - UINT8 index.
*
* \return  - UINT32 - stepValue.
*
******************************************************************************/
UINT32 ScWeldRecipe::GetForceStepAtValue(UINT8 index) const
{
	UINT16 stepValue = 0;
	
	if(index < m_Recipe.NumForceSteps)
	{
		stepValue = m_Recipe.ForceStepAtValue[index]; 
	}
	return stepValue;
}

/**************************************************************************//**
* 
* \brief   - Updates the enabled force step and step values.
*
* \param   - UINT16 noOfStep, UINT16 stepAt ,UINT16 &stepValue.
*
* \return  - None.
*
******************************************************************************/
void ScWeldRecipe::UpdateForceStep(UINT16 noOfStep, UINT16 stepAt,UINT16 *stepValue)
{
	m_Recipe.NumForceSteps= noOfStep;
	m_Recipe.ForceStepAt	= stepAt;
	
	for(UINT8 idx = 0; idx < MAX_NO_OF_FORCE_STEP; idx++)
	{
		m_Recipe.ForceStepAtValue[idx] = stepValue[idx];
	}
}

/**************************************************************************//**
* 
* \brief   - Returns active user name of UW system.
*
* \param   - string& - userName.
*
* \return  - None.
*
******************************************************************************/
void ScWeldRecipe::GetUserName(std::string& userName)
{
	strcpy((char *)userName.c_str(),m_Recipe.User);
}

/**************************************************************************//**
* 
* \brief   - Sets active user name of UW system.
*
* \param   - char* - userName.
*
* \return  - None.
*
******************************************************************************/
void ScWeldRecipe::SetUserName(char* name)
{
	strncpy(m_Recipe.User, name, sizeof(m_Recipe.User));
}

/**************************************************************************//**
* 
* \brief   - Gets Active recipe number.
*
* \param   - None.
*
* \return  - UINT32.
*
******************************************************************************/
INT32 ScWeldRecipe::GetRecipeNumber()
{
	return m_Recipe.RecipeNumber.Get();
}

/**************************************************************************//**
* 
* \brief   - Gets Active recipe version number.
*
* \param   - None.
*
* \return  - UINT32.
*
******************************************************************************/
INT32 ScWeldRecipe::GetRecipeRevNumber()
{
	return m_Recipe.RecipeRevNumber.Get();
}

/**************************************************************************//**
* 
* \brief   - Returns stack serial number of UW system.
*
* \param   - None.
*
* \return  - UINT32 stackSerialNumber.
*
******************************************************************************/
UINT32 ScWeldRecipe::GetStackSerialNumber() const
{
	return m_Recipe.StackSerialNo;
}

/**************************************************************************//**
* \brief   - Returns active weld recipe structure of SC.
*
* \param   - WeldRecipeSC& recipe (structure of object of weld recipe SC)
*
* \return  - None.
*
******************************************************************************/
void ScWeldRecipe::GetWeldRecipe(WeldRecipeSC& recipe)
{
	//TODO:DSS may need to implement a deep copy instead  
	memcpy(&recipe, &m_Recipe,sizeof(m_Recipe));
	
//	recipe.RecipeNumber		= m_Recipe.RecipeNumber;
//	recipe.WeldMode			= m_Recipe.WeldMode;
//	recipe.RecipeRevNumber	= m_Recipe.RecipeRevNumber;
//	recipe.ModeValue		= m_Recipe.ModeValue;
//	recipe.HoldTime			= m_Recipe.HoldTime;
//	recipe.AmplitudeStep[0] = m_Recipe.AmplitudeStep[0]; 
//	recipe.NumAmplitudeSteps = m_Recipe.NumAmplitudeSteps; 

	// add more here...
}

/**************************************************************************//**
* \brief   - Updates SC weld recipe parameters with latest data which is 
* 			 modified by user from UIC.
*
* \param   - WeldRecipeSC& recipe (structure of object of weld recipe SC)
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::SetWeldRecipe(WeldRecipeSC& recipe)
{
	//TODO:DSS may need to implement a deep copy instead
	memcpy(&m_Recipe,&recipe,sizeof(m_Recipe));
	
//	m_Recipe.RecipeNumber		= recipe.RecipeNumber;
//	m_Recipe.WeldMode			= recipe.WeldMode;
//	m_Recipe.RecipeRevNumber	= recipe.RecipeRevNumber;
//	m_Recipe.ModeValue		= recipe.ModeValue;
//	m_Recipe.HoldTime			= recipe.HoldTime;
//	m_Recipe.AmplitudeStep[0] = recipe.AmplitudeStep[0]; 
//	m_Recipe.NumAmplitudeSteps = recipe.NumAmplitudeSteps;
	
	// add more here...
}

/**************************************************************************//**
* \brief   - Returns the cooling valve seek status as enabled or disabled
*
* \param   - None
*
* \return  - bool (true /false )
*
******************************************************************************/
bool ScWeldRecipe::IsCoolingValveEnabled()
{
	return m_Recipe.bCoolingValveEnabled;
}

/**************************************************************************//**
* \brief   - Returns the Preweld seek status as enabled or disabled
*
* \param   - None
*
* \return  - bool (true /false )
*
******************************************************************************/
bool ScWeldRecipe::IsPreWeldSeekEnabled()
{
	return m_Recipe.bPreWeldSeekEnabled;
}


/**************************************************************************//**
* \brief   - Returns the Postweld seek status as enabled or disabled
*
* \param   - None
*
* \return  - bool (true /false )
*
******************************************************************************/
bool ScWeldRecipe::IsPostWeldSeekEnabled()
{
	return m_Recipe.bPostWeldSeekEnabled;
}

/**************************************************************************//**
* \brief   - Returns the Timed seek value if enabled
*
* \param   - None
*
* \return  - UINT32 
*
******************************************************************************/
UINT32 ScWeldRecipe::GetTimedSeek()
{
	UINT32 TimedSeekValue=0;
	
	if(m_Recipe.bTimedSeekEnabled)
	{
		TimedSeekValue=m_Recipe.TimedSeekPeriod;
	}
	
	return TimedSeekValue;
}

/**************************************************************************//**
* \brief   - Returns the Timed seeked is enabled or not
*
* \param   - None
*
* \return  - bool(true / fail) 
*
******************************************************************************/
bool ScWeldRecipe::IsTimedSeekEnabled()
{
	return m_Recipe.bTimedSeekEnabled;
}

/**************************************************************************//**
* \brief   - Validates the suspect and reject limits are global option 
* 			 enabled or not.
*
* \param   - UINT8 typeOfLimit (Suspect or Reject)
*
* \return  - bool - true on enable
*
******************************************************************************/
bool ScWeldRecipe::IsGlobalLimitCheckEnabled(UINT8 typeOfLimit)
{
	bool bEnabled = false;
	
	if(SUSPECT_LIMIT == typeOfLimit)
	{
		bEnabled = m_Recipe.bSuspectLimitEnabled;
	}
	else if(REJECT_LIMIT == typeOfLimit)
	{
		bEnabled = m_Recipe.bRejectLimitEnabled;
	}
	
	return bEnabled;
}

/**************************************************************************//**
* \brief   - Checks , Is suspect and reject limits validation enabled
*      		 or not against all the modes
*
* \param   - UINT8 typeOfLimit(Suspect or Reject), UINT8 typeOfMode
*
* \return  - bool bEnabled (true or false)
*
******************************************************************************/
bool ScWeldRecipe::IsLimitCheckEnabled(UINT8 typeOfLimit,UINT8 typeOfMode)
{
	bool bEnabled = false;

	if(SUSPECT_LIMIT == typeOfLimit)
	{
		switch(typeOfMode)
		{
			case TIME_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.Time.bLowEnabled;
				break;
			case TIME_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.Time.bHighEnabled;
				break;
			case ENERGY_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.Energy.bLowEnabled;
				break;
			case ENERGY_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.Energy.bHighEnabled;
				break;
			case PEAKPOWER_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.PeakPower.bLowEnabled;
				break;
			case PEAKPOWER_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.PeakPower.bHighEnabled;
				break;	
			case COLLAPSE_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.CollapseDistance.bLowEnabled;
				break;
			case COLLAPSE_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.CollapseDistance.bHighEnabled;
				break;	
			case ABSOLUTE_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.AbsoluteDistance.bLowEnabled;
				break;
			case ABSOLUTE_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.AbsoluteDistance.bHighEnabled;
				break;	
			case TRIGGER_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.TriggerDistance.bLowEnabled;
				break;
			case TRIGGER_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.TriggerDistance.bHighEnabled;
				break;	
			case WELDFORCE_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.WeldForce.bLowEnabled;
				break;
			case WELDFORCE_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.WeldForce.bHighEnabled;
				break;
			case FREQUENCY_LIMIT_ML:
				bEnabled = m_Recipe.SuspectLimit.Frequency.bLowEnabled;
				break;	
			case FREQUENCY_LIMIT_PL:
				bEnabled = m_Recipe.SuspectLimit.Frequency.bHighEnabled;
				break;
			default:
				LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
				break;
		}
	}
	else if(REJECT_LIMIT == typeOfLimit)
	{
		switch(typeOfMode)
		{
		case TIME_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.Time.bLowEnabled;
			break;
		case TIME_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.Time.bHighEnabled;
			break;
		case ENERGY_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.Energy.bLowEnabled;
			break;
		case ENERGY_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.Energy.bHighEnabled;
			break;
		case PEAKPOWER_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.PeakPower.bLowEnabled;
			break;
		case PEAKPOWER_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.PeakPower.bHighEnabled;
			break;
		case COLLAPSE_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.CollapseDistance.bLowEnabled;
			break;
		case COLLAPSE_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.CollapseDistance.bHighEnabled;
			break;
		case ABSOLUTE_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.AbsoluteDistance.bLowEnabled;
			break;
		case ABSOLUTE_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.AbsoluteDistance.bHighEnabled;
			break;
		case TRIGGER_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.TriggerDistance.bLowEnabled;
			break;
		case TRIGGER_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.TriggerDistance.bHighEnabled;
			break;
		case WELDFORCE_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.WeldForce.bLowEnabled;
			break;
		case WELDFORCE_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.WeldForce.bHighEnabled;
			break;
		case FREQUENCY_LIMIT_ML:
			bEnabled = m_Recipe.RejectLimit.Frequency.bLowEnabled;
			break;
		case FREQUENCY_LIMIT_PL:
			bEnabled = m_Recipe.RejectLimit.Frequency.bHighEnabled;
			break;
		default:
			LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
			break;
		}
	}

	return bEnabled;
}

/**************************************************************************//**
* \brief   - Validates reject low and high limits based on input passed.
*
* \param   - UINT8 typeOfMode, UINT32 value - value to be check
*
* \return  - bool bIsValid (true or false)
*
******************************************************************************/
bool ScWeldRecipe::ValidateRejectLimit(UINT8 typeOfMode,UINT32 value)
{
	bool bValid = false;
//
//	switch(typeOfMode)
//	{
//	case TIME_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.Time.LowLimit) 
//		{
//			bIsValid = true;
//		}
//		break;
//	case TIME_LIMIT_PL:
//		if(value > m_Recipe.RejectLimit.Time.HighLimit)
//		{
//			bIsValid = true;
//		}
//       break;
//	case ENERGY_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.Energy.LowLimit) 
//		{
//			bIsValid = true; 
//		}
//		break;
//	case ENERGY_LIMIT_PL:
//		if(value > m_Recipe.RejectLimit.Energy.HighLimit)
//		{
//			bIsValid = true;
//		}
//        break;
//	case PEAKPOWER_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.PeakPower.LowLimit)
//		{
//			bIsValid = true;
//		}
//		break;
//	case PEAKPOWER_LIMIT_PL:
//		if (value > m_Recipe.RejectLimit.PeakPower.HighLimit)
//		{
//		   bIsValid =  true;	
//		}
//		break;
//	case COLLAPSE_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.CollapseDistance.LowLimit) 
//		{
//			bIsValid = true;
//		}
//		break;
//	case COLLAPSE_LIMIT_PL:
//		if(value > m_Recipe.RejectLimit.CollapseDistance.HighLimit)
//		{
//			bIsValid = true;	
//		}
//		break;
//	case ABSOLUTE_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.AbsoluteDistance.LowLimit)
//		{
//			bIsValid = true;
//		}
//		break;
//	case ABSOLUTE_LIMIT_PL:
//		if(value > m_Recipe.RejectLimit.AbsoluteDistance.HighLimit)
//		{
//			bIsValid = true;
//		}
//		break;
//	case TRIGGER_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.TriggerDistance.LowLimit) 
//		{
//			bIsValid = true;
//		}
//		break;
//	case TRIGGER_LIMIT_PL:
//		if(value > m_Recipe.RejectLimit.TriggerDistance.HighLimit)
//		{
//			bIsValid = true;
//		}
//	   break;
//	case WELDFORCE_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.WeldForce.LowLimit) 
//		{
//			bIsValid = true;
//		}
//		break; 
//	case WELDFORCE_LIMIT_PL:
//		if(value>m_Recipe.RejectLimit.WeldForce.HighLimit)
//		{
//			bIsValid = true;
//		}
//		break;
//	case FREQUENCY_LIMIT_ML:
//		if(value < m_Recipe.RejectLimit.Frequency.LowLimit*10)
//		{
//			bIsValid = true;
//		}
//		break;
//	case FREQUENCY_LIMIT_PL:
//	    if(value >  m_Recipe.RejectLimit.Frequency.HighLimit*10)
//	    {
//	    	bIsValid = true;
//	    }
//	    break;
//	default:
//		LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
//		break;
//	}
//	
//	if(bIsValid)
//	{
//		bRejectStatus = true;
//	}
	
	return bValid;
}

/**************************************************************************//**
* \brief   - Validates suspect low and high limits based on input passed.
*
* \param   - UINT8 typeOfMode, UINT32 value - value to be check
*
* \return  - bool bIsValid (true or false)
*
******************************************************************************/
bool ScWeldRecipe::ValidateSuspectLimit(UINT8 typeOfMode,UINT32 value)
{
	bool bValid = false;
	
//	switch(typeOfMode)
//	{
//		case TIME_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.Time.LowLimit) 
//			{
//				bIsValid = true;
//			}
//			break;
//		case TIME_LIMIT_PL:
//			if(value > m_Recipe.SuspectLimit.Time.HighLimit)
//			{
//				bIsValid = true;
//			}
//	       break;
//		case ENERGY_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.Energy.LowLimit) 
//			{
//				bIsValid = true; 
//			}
//			break;
//		case ENERGY_LIMIT_PL:
//			if(value > m_Recipe.SuspectLimit.Energy.HighLimit)
//			{
//				bIsValid = true;
//			}
//	        break;
//		case PEAKPOWER_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.PeakPower.LowLimit)
//			{
//				bIsValid = true;
//			}
//			break;
//		case PEAKPOWER_LIMIT_PL:
//			if (value > m_Recipe.SuspectLimit.PeakPower.HighLimit)
//			{
//			   bIsValid =  true;	
//			}
//			break;
//		case COLLAPSE_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.CollapseDistance.LowLimit) 
//			{
//				bIsValid = true;
//			}
//			break;
//		case COLLAPSE_LIMIT_PL:
//			if(value > m_Recipe.SuspectLimit.CollapseDistance.HighLimit)
//			{
//				bIsValid = true;
//			}
//			break;
//		case ABSOLUTE_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.AbsoluteDistance.LowLimit)
//			{
//				bIsValid = true;
//			}
//			break;
//		case ABSOLUTE_LIMIT_PL:
//			if(value > m_Recipe.SuspectLimit.AbsoluteDistance.HighLimit)
//			{
//				bIsValid = true;
//			}
//			break;
//		case TRIGGER_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.TriggerDistance.LowLimit) 
//			{
//				bIsValid = true;
//			}
//			break;
//		case TRIGGER_LIMIT_PL:
//			if(value > m_Recipe.SuspectLimit.TriggerDistance.HighLimit)
//			{
//				bIsValid = true;
//			}
//		   break;
//		case WELDFORCE_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.WeldForce.LowLimit) 
//			{
//				bIsValid = true;
//			}
//			break; 
//		case WELDFORCE_LIMIT_PL:
//			if(value>m_Recipe.SuspectLimit.WeldForce.HighLimit)
//			{
//				bIsValid = true;
//			}
//			break;
//		case FREQUENCY_LIMIT_ML:
//			if(value < m_Recipe.SuspectLimit.Frequency.LowLimit*10)
//			{
//				bIsValid = true;
//			}
//			break;
//		case FREQUENCY_LIMIT_PL:
//		    if(value >  m_Recipe.SuspectLimit.Frequency.HighLimit*10)
//		    {
//		    	bIsValid = true;
//		    }
//		    break;
//		default:
//			LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
//			break;
//	}
//	
//	if(bIsValid)
//	{
//		bSuspectStatus = true;
//	}
		
	return bValid;
}


/**************************************************************************//**
* \brief   - return Afterburst parameters of Weldrecipe
*
* \param   - None
*
* \return  - AfterBurst
*
******************************************************************************/
Burst ScWeldRecipe::GetAfterBurst() const
{
	return m_Recipe.AfterBurst;
}

/**************************************************************************//**
* \brief   - return PreTrigger parameters of Weldrecipe
*
* \param   - None
*
* \return  - PreTrigger
*
******************************************************************************/
Trigger ScWeldRecipe::GetPreTrigger() const
{
	return m_Recipe.PreTrigger;
}

/**************************************************************************//**
* \brief   - return EnergyBrake parameters of Weldrecipe
*
* \param   - None
*
* \return  - EnergyBrake
*
******************************************************************************/
Brake ScWeldRecipe::GetEnergyBrake() const
{
	return m_Recipe.EnergyBrake;
}

/**************************************************************************//**
* \brief   - Display suspect limits, Only when flag is enabled.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void ScWeldRecipe::DisplaySuspectLimit()
{
//	if(IsGlobalLimitCheckEnabled(SUSPECT_LIMIT))
//	{
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,TIME_LIMIT_ML))
//		{
//			LOGDBG("SuspectLimit.Time.IsEnabled				: %d",m_Recipe.SuspectLimit.Time.bLowEnabled,0,0);
//			LOGDBG("SuspectLimit.Time.Low 					: %d",m_Recipe.SuspectLimit.Time.LowLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,TIME_LIMIT_PL))
//		{
//			LOGDBG("SuspectLimit.Time.IsEnabled				: %d",m_Recipe.SuspectLimit.Time.bHighEnabled,0,0);
//			LOGDBG("SuspectLimit.Time.High 					: %d",m_Recipe.SuspectLimit.Time.HighLimit,0,0);
//		}
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,ENERGY_LIMIT_ML))
//		{
//			LOGDBG("SuspectLimit.Energy.IsEnabled 			: %d",m_Recipe.SuspectLimit.Energy.bLowEnabled,0,0);
//			LOGDBG("SuspectLimit.Energy.Low 				: %d",m_Recipe.SuspectLimit.Energy.LowLimit,0,0);
//		}
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,ENERGY_LIMIT_PL))
//		{
//			LOGDBG("SuspectLimit.Energy.IsEnabled 			: %d",m_Recipe.SuspectLimit.Energy.bHighEnabled,0,0);
//			LOGDBG("SuspectLimit.Energy.High 				: %d",m_Recipe.SuspectLimit.Energy.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,PEAKPOWER_LIMIT_ML))
//		{
//			LOGDBG(" SuspectLimit.PeakPower.IsEnabled 		: %d",m_Recipe.SuspectLimit.PeakPower.bLowEnabled,0,0);
//			LOGDBG("SuspectLimit.PeakPower.Low				: %d",m_Recipe.SuspectLimit.PeakPower.LowLimit,0,0);	  
//		}
//		
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,PEAKPOWER_LIMIT_PL))
//		{
//			LOGDBG(" SuspectLimit.PeakPower.IsEnabled 		: %d",m_Recipe.SuspectLimit.PeakPower.bHighEnabled,0,0);	  
//			LOGDBG("SuspectLimit.PeakPower.High 			: %d",m_Recipe.SuspectLimit.PeakPower.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,COLLAPSE_LIMIT_ML))
//		{
//			LOGDBG("SuspectLimit.CollapseDistance.IsEnabled	: %d",m_Recipe.SuspectLimit.CollapseDistance.bLowEnabled,0,0);
//			LOGDBG("SuspectLimit.CollapseDistance.Low		: %d",m_Recipe.SuspectLimit.CollapseDistance.LowLimit,0,0);
//			LOGDBG("SuspectLimit.CollapseDistance.High		: %d",m_Recipe.SuspectLimit.CollapseDistance.HighLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,COLLAPSE_LIMIT_PL))
//		{
//			LOGDBG("SuspectLimit.CollapseDistance.IsEnabled	: %d",m_Recipe.SuspectLimit.CollapseDistance.bHighEnabled,0,0);
//			LOGDBG("SuspectLimit.CollapseDistance.High		: %d",m_Recipe.SuspectLimit.CollapseDistance.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,ABSOLUTE_LIMIT_ML))
//		{
//			LOGDBG("SuspectLimit.AbsoluteDistance.IsEnabled : %d",m_Recipe.SuspectLimit.AbsoluteDistance.bLowEnabled,0,0);
//			LOGDBG("SuspectLimit.AbsoluteDistance.Low 		: %d",m_Recipe.SuspectLimit.AbsoluteDistance.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,ABSOLUTE_LIMIT_PL))
//		{
//			LOGDBG("SuspectLimit.AbsoluteDistance.IsEnabled : %d",m_Recipe.SuspectLimit.AbsoluteDistance.bHighEnabled,0,0);
//			LOGDBG("SuspectLimit.AbsoluteDistance.High 		: %d",m_Recipe.SuspectLimit.AbsoluteDistance.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,TRIGGER_LIMIT_ML))
//		{
//			LOGDBG(" SuspectLimit.TriggerDistance.IsEnabled : %d",m_Recipe.SuspectLimit.TriggerDistance.bLowEnabled,0,0);
//			LOGDBG(" SuspectLimit.TriggerDistance.Low 		: %d", m_Recipe.SuspectLimit.TriggerDistance.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,TRIGGER_LIMIT_PL))
//		{
//			LOGDBG(" SuspectLimit.TriggerDistance.IsEnabled : %d",m_Recipe.SuspectLimit.TriggerDistance.bHighEnabled,0,0);
//			LOGDBG(" SuspectLimit.TriggerDistance.High 		: %d", m_Recipe.SuspectLimit.TriggerDistance.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,WELDFORCE_LIMIT_ML))
//		{
//			LOGDBG(" SuspectLimit.WeldForce.IsEnabled		: %d",m_Recipe.SuspectLimit.WeldForce.bLowEnabled,0,0);
//			LOGDBG(" SuspectLimit.WeldForce.Low				: %d",m_Recipe.SuspectLimit.WeldForce.LowLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,WELDFORCE_LIMIT_PL))
//		{
//			LOGDBG(" SuspectLimit.WeldForce.IsEnabled		: %d",m_Recipe.SuspectLimit.WeldForce.bHighEnabled,0,0);
//			LOGDBG(" SuspectLimit.WeldForce.High			: %d",m_Recipe.SuspectLimit.WeldForce.HighLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,FREQUENCY_LIMIT_ML))
//		{
//			LOGDBG(" SuspectLimit.Frequency.IsEnabled		: %d",m_Recipe.SuspectLimit.Frequency.bLowEnabled,0,0);
//			LOGDBG(" SuspectLimit.Frequency.Low				: %d",m_Recipe.SuspectLimit.Frequency.LowLimit,0,0);
//		}
//		if(IsLimitCheckEnabled(SUSPECT_LIMIT,FREQUENCY_LIMIT_PL))
//		{
//			LOGDBG(" SuspectLimit.Frequency.IsEnabled		: %d",m_Recipe.SuspectLimit.Frequency.bHighEnabled,0,0);
//			LOGDBG(" SuspectLimit.Frequency.High			: %d",m_Recipe.SuspectLimit.Frequency.HighLimit,0,0);
//		}
//	}
//	else
//	{
//		LOGDBG("Suspect limit disabled",0,0,0);
//	}
}

/**************************************************************************//**
* \brief   - Display reject limits, Only when flag is enabled.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayRejectLimit()
{
//	if(IsGlobalLimitCheckEnabled(REJECT_LIMIT))
//	{
//		if(IsLimitCheckEnabled(REJECT_LIMIT,TIME_LIMIT_ML))
//		{
//			LOGDBG("RejectLimit.Time.IsEnabled 				: %d",m_Recipe.RejectLimit.Time.bLowEnabled,0,0);
//			LOGDBG("RejectLimit.Time.Low 	 				: %d",m_Recipe.RejectLimit.Time.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,TIME_LIMIT_PL))
//		{
//			LOGDBG("RejectLimit.Time.IsEnabled 				: %d",m_Recipe.RejectLimit.Time.bHighEnabled,0,0);
//			LOGDBG("RejectLimit.Time.High 					: %d",m_Recipe.RejectLimit.Time.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,ENERGY_LIMIT_ML))
//		{
//			LOGDBG("RejectLimit.Energy.IsEnabled			: %d",m_Recipe.RejectLimit.Energy.bLowEnabled,0,0);
//			LOGDBG("RejectLimit.Energy.Low 					: %d",m_Recipe.RejectLimit.Energy.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,ENERGY_LIMIT_PL))
//		{
//			LOGDBG("RejectLimit.Energy.IsEnabled			: %d",m_Recipe.RejectLimit.Energy.bHighEnabled,0,0);
//			LOGDBG("RejectLimit.Energy.High 				: %d",m_Recipe.RejectLimit.Energy.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,PEAKPOWER_LIMIT_ML))
//		{
//			LOGDBG(" RejectLimit.PeakPower.IsEnabled		: %d",m_Recipe.RejectLimit.PeakPower.bLowEnabled,0,0);
//			LOGDBG("RejectLimit.PeakPower.Low				: %d",m_Recipe.RejectLimit.PeakPower.LowLimit,0,0);	  
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,PEAKPOWER_LIMIT_PL))
//		{
//			LOGDBG(" RejectLimit.PeakPower.IsEnabled		: %d",m_Recipe.RejectLimit.PeakPower.bHighEnabled,0,0);
//			LOGDBG("RejectLimit.PeakPower.High 				: %d",m_Recipe.RejectLimit.PeakPower.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,COLLAPSE_LIMIT_ML))
//		{
//			LOGDBG("RejectLimit.CollapseDistance.IsEnabled	: %d",m_Recipe.RejectLimit.CollapseDistance.bLowEnabled,0,0);
//			LOGDBG("RejectLimit.CollapseDistance.Low		: %d",m_Recipe.RejectLimit.CollapseDistance.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,COLLAPSE_LIMIT_PL))
//		{
//			LOGDBG("RejectLimit.CollapseDistance.IsEnabled	: %d",m_Recipe.RejectLimit.CollapseDistance.bHighEnabled,0,0);
//			LOGDBG("RejectLimit.CollapseDistance.High		: %d",m_Recipe.RejectLimit.CollapseDistance.HighLimit,0,0);
//		} 
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,ABSOLUTE_LIMIT_ML))
//		{
//			LOGDBG("RejectLimit.AbsoluteDistance.IsEnabled 	: %d",m_Recipe.RejectLimit.AbsoluteDistance.bLowEnabled,0,0);
//			LOGDBG("RejectLimit.AbsoluteDistance.Low 		: %d",m_Recipe.RejectLimit.AbsoluteDistance.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,ABSOLUTE_LIMIT_PL))
//		{
//			LOGDBG("RejectLimit.AbsoluteDistance.IsEnabled 	: %d",m_Recipe.RejectLimit.AbsoluteDistance.bHighEnabled,0,0);
//			LOGDBG("RejectLimit.AbsoluteDistance.High 		: %d",m_Recipe.RejectLimit.AbsoluteDistance.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,TRIGGER_LIMIT_ML))
//		{
//			LOGDBG(" RejectLimit.TriggerDistance.IsEnabled 	: %d",m_Recipe.RejectLimit.TriggerDistance.bLowEnabled,0,0);
//			LOGDBG(" RejectLimit.TriggerDistance.Low 		: %d", m_Recipe.RejectLimit.TriggerDistance.LowLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,TRIGGER_LIMIT_PL))
//		{
//			LOGDBG(" RejectLimit.TriggerDistance.IsEnabled 	: %d",m_Recipe.RejectLimit.TriggerDistance.bHighEnabled,0,0);
//			LOGDBG(" RejectLimit.TriggerDistance.High 		: %d", m_Recipe.RejectLimit.TriggerDistance.HighLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,WELDFORCE_LIMIT_ML))
//		{
//			LOGDBG(" RejectLimit.WeldForce.IsEnabled		: %d",m_Recipe.RejectLimit.WeldForce.bLowEnabled,0,0);
//			LOGDBG(" RejectLimit.WeldForce.Low				: %d",m_Recipe.RejectLimit.WeldForce.LowLimit,0,0);
//		}
//		
//		if(IsLimitCheckEnabled(REJECT_LIMIT,WELDFORCE_LIMIT_PL))
//		{
//			LOGDBG(" RejectLimit.WeldForce.IsEnabled		: %d",m_Recipe.RejectLimit.WeldForce.bHighEnabled,0,0);
//			LOGDBG(" RejectLimit.WeldForce.High				: %d",m_Recipe.RejectLimit.WeldForce.HighLimit,0,0);
//		}
//
//		if(IsLimitCheckEnabled(REJECT_LIMIT,FREQUENCY_LIMIT_ML))
//		{
//			LOGDBG(" RejectLimit.Frequency.IsEnabled		: %d",m_Recipe.RejectLimit.Frequency.bLowEnabled,0,0);
//			LOGDBG(" RejectLimit.Frequency.Low				: %d",m_Recipe.RejectLimit.Frequency.LowLimit,0,0);
//		}
//		if(IsLimitCheckEnabled(REJECT_LIMIT,FREQUENCY_LIMIT_PL))
//		{
//			LOGDBG(" RejectLimit.Frequency.IsEnabled		: %d",m_Recipe.RejectLimit.Frequency.bHighEnabled,0,0);
//			LOGDBG(" RejectLimit.Frequency.High				: %d",m_Recipe.RejectLimit.Frequency.HighLimit,0,0);
//		}
//	}
//	else
//	{
//		LOGDBG("Reject limit disabled",0,0,0);
//	}
}

/**************************************************************************//**
* \brief   - Display core weld parameters and user information of recipe.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::RecipeInformation()
{
#ifdef ACTIVE_RECIPE_DBG
	printf((char *)"------ScWeldRecipe::RecipeInformation::Weld Recipe SC--------");
	printf((char *)"Weld mode 				: %d\n",m_Recipe.WeldMode.Get());
	printf((char *)"Mode value 				: %d\n",m_Recipe.ModeValue.Get(m_Recipe.WeldMode.Get()));
	printf((char *)"Hold time 				: %d\n",m_Recipe.HoldTime.Get());
	printf((char *)"Trigger distance		: %d\n",m_Recipe.TriggerDistance.Get());
	printf((char *)"Trigger force 			: %d\n",m_Recipe.TriggerForce.Get());
	printf((char *)"Weld time out   		: %d\n",m_Recipe.MaxWeldTimeout.Get());
	printf((char *)"bIsCoolingValveEnabled 	: %d\n",m_Recipe.bCoolingValveEnabled);
	printf((char *)"bIsTimedSeekEnabled 	: %d\n",m_Recipe.bTimedSeekEnabled);
	printf((char *)"TimedSeekPeriod 		: %d\n",m_Recipe.TimedSeekPeriod);
	printf((char *)"bIsPreWeldSeekEnabled 	:%d\n",m_Recipe.bPreWeldSeekEnabled);
	printf((char *)"bIsPostWeldSeekEnabled 	:%d\n",m_Recipe.bPostWeldSeekEnabled);
	printf((char *)"Recipe No 				:%d\n",m_Recipe.RecipeNumber.Get());
	printf((char *)"Recipe Rev Num			:%d\n",m_Recipe.RecipeRevNumber.Get());
	printf((char *)"User name 				:%s\n",(_Vx_usr_arg_t)m_Recipe.User);
	printf((char *)"Serial No 				:%s\n",(_Vx_usr_arg_t)m_Recipe.StackSerialNo);
#endif
}

/**************************************************************************//**
* \brief   - Display amplitude stepping related information.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayAmplitudeStep()
{
#ifdef ACTIVE_RECIPE_DBG
	printf((char *)"No.AmpStep 		: %d\n",m_Recipe.NumAmplitudeSteps.Get());
	printf((char *)"AmplitudeStepAt	: %d\n",m_Recipe.AmplitudeStepAt);

	for(UINT8 idx = 0; idx < m_Recipe.NumAmplitudeSteps.Get(); idx++)
	{
		printf((char *)"Step%d	 	: %d\n",idx,m_Recipe.AmplitudeStep[idx]);
	}

	for(UINT8 idx = 0; idx < m_Recipe.NumAmplitudeSteps.Get(); idx++)
	{
		printf((char *)"StepValue%d : %d\n",idx,m_Recipe.AmplitudeStepValue[idx]);
	}
#endif
}

/**************************************************************************//**
* \brief   - Display force stepping related information.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayForceStep()
{
#ifdef ACTIVE_RECIPE_DBG
	printf((char *)"No.ForceStep 		: %d\n",m_Recipe.NumForceSteps);
	printf((char *)"ForceStepAt	 		: %d\n",m_Recipe.ForceStepAt);

	for(UINT8 idx = 0; idx < m_Recipe.NumForceSteps; idx++)
	{
		printf((char *)"StepAtValue%d 	: %d\n",idx,m_Recipe.ForceStepAtValue[idx]);
	}
#endif
}

/**************************************************************************//**
* \brief   - Display pre-trigger parameters, Only when is it enabled.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayPreTrigger()
{
#ifdef ACTIVE_RECIPE_DBG
	if((m_Recipe.PreTrigger.bIsAutoEnabled) || (m_Recipe.PreTrigger.bEnabled)) 
	{
		printf((char *)"PreTrigger.bIsAutoEnabled    : %d\n",m_Recipe.PreTrigger.bIsAutoEnabled);
		printf((char *)"PreTrigger.bIsEnabled        : %d\n",m_Recipe.PreTrigger.bEnabled);
		printf((char *)"PreTrigger.TriggerAmplitude  : %d\n",m_Recipe.PreTrigger.TriggerAmplitude);
		printf((char *)"PreTrigger.bIsDistanceEnabled : %d\n",m_Recipe.PreTrigger.bIsDistanceEnabled);
		printf((char *)"PreTrigger.PreTriggerDistance : %d\n",m_Recipe.PreTrigger.PreTriggerDistance);
	}
#endif
}

/**************************************************************************//**
* \brief   - Display after burst parameters, Only when is it enabled.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayAfterBurst()
{
#ifdef ACTIVE_RECIPE_DBG

	if(m_Recipe.AfterBurst.bEnabled)
	{
		printf((char *)"AfterBurst.bIsEnabled    	: %d\n",m_Recipe.AfterBurst.bEnabled);
		printf((char *)"AfterBurst.BurstAmplitude	: %d\n",m_Recipe.AfterBurst.BurstAmplitude);
		printf((char *)"AfterBurst.BurstDelay    	: %d\n",m_Recipe.AfterBurst.BurstDelay);
		printf((char *)"AfterBurst.BurstTime     	: %d\n",m_Recipe.AfterBurst.BurstTime);
	}
#endif
}

/**************************************************************************//**
* \brief   - Display after EnergyBrake parameters
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplayEnergyBrake()
{
#ifdef ACTIVE_RECIPE_DBG
	if(m_Recipe.EnergyBrake.bEnabled)
	{
		printf((char *)"EnergyBrake.bIsEnabled    			: %d\n",m_Recipe.EnergyBrake.bEnabled);
		printf((char *)"EnergyBrake.EnergyBrakeAmplitude	: %d\n",m_Recipe.EnergyBrake.EnergyBrakeAmplitude);
		printf((char *)"EnergyBrake.EnergyBrakeTime    	    : %d\n",m_Recipe.EnergyBrake.EnergyBrakeTime);
	}
#endif
}  

/**************************************************************************//**
* \brief   - Validates control limits based on the input
*
* \param   - UINT8 Type of value to check
*            UINT32 value - value to be check
*     
* \return  - bool bIsValid (true or false)
*
******************************************************************************/
bool ScWeldRecipe::ValidateCutoffLimit(UINT8 typeOfMode, UINT32 value)
{
	bool bValid = false;
	
	switch(typeOfMode)
	{
	case PEAK_POWER_CUTOFF:
		if(value >= m_Recipe.CutoffLimit.PeakPowerCutoff.Value) 
		{
			bValid = true;
		}
		break;
	case COLLAPSE_DISTANCE_CUTOFF:
	    if(value >= m_Recipe.CutoffLimit.CollapseDistanceCutoff.Value) 
	    {
	      	bValid = true;
	    }
	    break;	   
	case ABSOLUTE_DISTANCE_CUTOFF:
		if (value >= m_Recipe.CutoffLimit.AbsoluteDistanceCutoff.Value) 
		{
	      	bValid = true;
	    }
	    break;
	case FREQUENCY_LOW_CUTOFF:
		if (value <= m_Recipe.CutoffLimit.FrequencyLowCutoff.Value)
		{
			bValid = true;
		}
		break;
	case FREQUENCY_HIGH_CUTOFF:
		if (value >= m_Recipe.CutoffLimit.FrequencyHighCutoff.Value)
		{
			bValid = true;
		}
		break;
	case ENERGY_CUTOFF:
		if (value >= m_Recipe.CutoffLimit.EnergyCutoff.Value)
		{
			bValid = true;
		}
		break;
	case TIME_CUTOFF:
	   if (value >=m_Recipe.CutoffLimit.TimeCutoff.Value)
	   {
		    bValid = true;
	   }
	   break;
	default:
		LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
		break;
	}
	
	return bValid;	
}

/**************************************************************************//**
* \brief   - Display cutoff limits, Only when flag is enabled.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ScWeldRecipe::DisplaycutoffLimit()
{
#ifdef ACTIVE_RECIPE_DBG
	if(IsGlobalCutOffLimitCheckEnabled())
	{
		if(IsCutoffLimitCheckEnabled(PEAK_POWER_CUTOFF))
		{
			printf((char *)"cutoffLimits.peakpower.IsEnabled 		: %d",m_Recipe.CutoffLimit.PeakPowerCutoff.bEnabled);
			printf((char *)"cutoffLimits.peakpower.value	 		: %d",m_Recipe.CutoffLimit.PeakPowerCutoff.Value);
		}

		if(IsCutoffLimitCheckEnabled(COLLAPSE_DISTANCE_CUTOFF))
		{
			printf((char *)"cutoffLimit.collapse.IsEnabled			: %d",m_Recipe.CutoffLimit.CollapseDistanceCutoff.bEnabled);
			printf((char *)"cutoffLimit.collapse.value 				: %d",m_Recipe.CutoffLimit.CollapseDistanceCutoff.Value);
		}

		if(IsCutoffLimitCheckEnabled(ABSOLUTE_DISTANCE_CUTOFF))
		{
			printf((char *)"cutoffLimit.Absolute.IsEnabled		    : %d",m_Recipe.CutoffLimit.AbsoluteDistanceCutoff.bEnabled);
			printf((char *)"cutoffLimit.Absolute.value				: %d",m_Recipe.CutoffLimit.AbsoluteDistanceCutoff.Value,0,0);	  
		}

		if(IsCutoffLimitCheckEnabled(FREQUENCY_LOW_CUTOFF))
		{
			printf((char *)"cutoffLimit.FrequencyLow.IsEnabled	    : %d",m_Recipe.CutoffLimit.FrequencyLowCutoff.bEnabled);
			printf((char *)"cutoffLimit.FrequencyLow.value  		: %d",m_Recipe.CutoffLimit.FrequencyLowCutoff.Value);
		} 

		if(IsCutoffLimitCheckEnabled(FREQUENCY_HIGH_CUTOFF))
		{
			printf((char *)"cutoffLimit.FrequencyHigh.IsEnabled 	: %d",m_Recipe.CutoffLimit.FrequencyHighCutoff.bEnabled);
			printf((char *)"cutoffLimit.FrequencyHigh.value 		: %d",m_Recipe.CutoffLimit.FrequencyHighCutoff.Value);
		}

		if(IsCutoffLimitCheckEnabled(ENERGY_CUTOFF))
		{
			printf((char *)" cutoffLimit.Energy.IsEnabled       	: %d",m_Recipe.CutoffLimit.EnergyCutoff.bEnabled);
			printf((char *)" cutoffLimit.Energye.value      		: %d", m_Recipe.CutoffLimit.EnergyCutoff.Value);
		}

		if(IsCutoffLimitCheckEnabled(TIME_CUTOFF))
		{
			printf((char *)" cutoffLimit.Time.IsEnabled	        	: %d",m_Recipe.CutoffLimit.TimeCutoff.bEnabled);
			printf((char *)" cutoffLimit.Time.value 				: %d ",m_Recipe.CutoffLimit.TimeCutoff.Value);
		}
	
	}
	else
	{
		printf((char *)"cutoff limit disabled");
	}
#endif
}

/**************************************************************************//**
* \brief   - Checks , Is suspect and reject limits validation enabled
*      		 or not against all the modes
*
* \param   - UINT8 typeOfLimit(Suspect or Reject), UINT8 typeOfMode
*
* \return  - bool bEnabled (true or false)
*
******************************************************************************/
bool ScWeldRecipe::IsCutoffLimitCheckEnabled(UINT8 typeOfMode)
{
	bool bEnabled = false;

	switch(typeOfMode)
	{
		case PEAK_POWER_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.PeakPowerCutoff.bEnabled;
			break;
		case COLLAPSE_DISTANCE_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.CollapseDistanceCutoff.bEnabled;
			break;
		case ABSOLUTE_DISTANCE_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.AbsoluteDistanceCutoff.bEnabled;
			break;
		case TIME_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.TimeCutoff.bEnabled;
			break;
		case FREQUENCY_LOW_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.FrequencyLowCutoff.bEnabled;
			break;
		case FREQUENCY_HIGH_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.FrequencyHighCutoff.bEnabled;
			break;	
		case ENERGY_CUTOFF:
			bEnabled = m_Recipe.CutoffLimit.EnergyCutoff.bEnabled;
			break;
		case GROUND_DETECT_CUTOFF:
	     	bEnabled = m_Recipe.CutoffLimit.bGroundDetectCutoff;
			break;
		default:
			LOGERR((char *)"Invalid Limit validation : %d",typeOfMode,0,0);
			break;
	}

	return bEnabled;
}

/**************************************************************************//**
* \brief   - Validates the cutoff limits are global option 
* 			 enabled or not.
*
* \param   - UINT8 typeOfLimit (Suspect or Reject)
*
* \return  - bool - true on enable
*
******************************************************************************/
bool ScWeldRecipe::IsGlobalCutOffLimitCheckEnabled()
{
	bool bEnabled = false;
	
	bEnabled = m_Recipe.bCutoffLimitEnabled;
	
	return bEnabled;
}

/**************************************************************************//**
* \brief   - Returns active recipe validation status.
*
* \param   - None.
*
* \return  - bool - true on recipe validated.
*
******************************************************************************/
bool ScWeldRecipe::IsRecipeValidated() const
{
	return m_Recipe.bRecipeValidated;
}

