/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Updating Weld Recipe to slaves( PC and AC )  
 
**********************************************************************************************************/


//#include "RunTimeFeature.h"
#include <WeldRecipe.h>
#include "CommonProperty.h"

using namespace std;

// static initialization
RECIPE_STATUS WeldRecipeStatus::recipeStatus = UNSAVED;

/**************************************************************************//**
* 
* \brief   - Custom constructor for an SC recipe, setting system enabled 
* 			considering basic or advanced P/S together with various
* 			actuator.   
*
******************************************************************************/
WeldRecipeSC::WeldRecipeSC()
{
//	RunTime RT;
//	RT.FeaturesFlagRead(EEPROM_MODEL_ADDRESS);		/* Needs to place in different place , Read should happen only when model changed */
//	
//	// always enabled here
//	WeldMode.systemEnabled = true;
//	ModeValue.systemEnabled = true;
//
//	// per system setup here
//	if (ENABLE == RT.ModelFeature.RtFeature3.Basic_PS)
//	{
//		// always enabled with this P/S here
//		
//	}
//	else if (ENABLE == RT.ModelFeature.RtFeature3.Advanced_PS)
//	{
//		// always enabled with this P/S here
//		RecipeNumber.systemEnabled = true;
//		RecipeRevNumber.systemEnabled = true;
//		MaxWeldTimeout.systemEnabled = true;
//		
//		if (ENABLE == RT.ModelFeature.RtFeature3.Base_AE || ENABLE == RT.ModelFeature.RtFeature3.Plus_AED || ENABLE == RT.ModelFeature.RtFeature3.Plus_E1)
//		{
//			// works with all actuators
//			HoldTime.systemEnabled = true;
//		}
//		else if (DISABLE == RT.ModelFeature.RtFeature3.Base_AE && (ENABLE == RT.ModelFeature.RtFeature3.Plus_AED || ENABLE == RT.ModelFeature.RtFeature3.Plus_E1))
//		{
//			// works with Plus_AED or Plus_E1 actuators but not Basic_AE
//			TriggerForce.systemEnabled = true;
//		}
//		else if ((ENABLE == RT.ModelFeature.RtFeature3.Base_AE || ENABLE == RT.ModelFeature.RtFeature3.Plus_AED) && DISABLE == RT.ModelFeature.RtFeature3.Plus_E1)
//		{
//			// works with Basic_AE or Plus_AED actuators but not Plus_E1
//		}
//		else if (DISABLE == RT.ModelFeature.RtFeature3.Base_AE && DISABLE == RT.ModelFeature.RtFeature3.Plus_AED && ENABLE == RT.ModelFeature.RtFeature3.Plus_E1)
//		{
//			// works with Plus_E1 actuators only 
//			TriggerDistance.systemEnabled = true;
//		}
//		else if (DISABLE == RT.ModelFeature.RtFeature3.Base_AE && DISABLE == RT.ModelFeature.RtFeature3.Plus_AED && DISABLE == RT.ModelFeature.RtFeature3.Plus_E1)
//		{
//			// works with Plus_E1 actuators only 
//		}
//	}
}

/**************************************************************************//**
* 
* \brief   - Value validation method for the encapsulated recipe member
* 			in all of its possible forms all at the same time, an efficient
* 			way that allows it to support an active system configuration for
* 			the ASC, combining basic and advanced P/S together with various
* 			actuators and other configuration parameters.   
*
******************************************************************************/
INT32 ParamDesc_WELDMODE::ValidateValue	(INT32 value)
{
	INT32 val = value;
//	CommonProperty *CP = CommonProperty::getInstance();
//	
//	if (ENABLE == CP->RT.ModelFeature.RtFeature3.Basic_PS)
//	{
//		if (value != ::CONTINUOUS)
//			val = VALUE_INVALID;
//	}
//	else if (ENABLE == CP->RT.ModelFeature.RtFeature3.Advanced_PS)
//	{
//		if (value == ::CONTINUOUS)
//		{
//			val = VALUE_INVALID;
//		}
//		else
//		{
//			if (value == ::COLLAPSEMODE || value == ::ABSMODE)
//			{
//				if (DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_AED && DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_E1)
//					val = VALUE_INVALID;
//			}
//			else if (value == ::GRDDETECTMODE)
//			{
//				if (DISABLE == CP->RT.ModelFeature.RtFeature3.Base_AE && DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_AED && DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_E1)
//					val = VALUE_INVALID;
//			}
//		}
//	}
	
	return val;
}

/**************************************************************************//**
* 
* \brief   - Value validation method for the encapsulated recipe member
* 			in all of its possible forms all at the same time, an efficient
* 			way that allows it to support an active system configuration for
* 			the ASC, combining basic and advanced P/S together with various
* 			actuators and other configuration parameters.   
*
******************************************************************************/
INT32 ParamDesc_MODEVALUE::ValidateValue (INT32 value)
{
	INT32 val = value;
//	CommonProperty *CP = CommonProperty::getInstance();
//
//	if (ENABLE == CP->RT.ModelFeature.RtFeature3.Basic_PS)
//		if (DISABLE == CP->RT.ModelFeature.RtFeature3.Base_AE && DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_AED && DISABLE == CP->RT.ModelFeature.RtFeature3.Plus_E1)
//			val = 0;
	
	return val;
}

/**************************************************************************//**
* 
* \brief   - Value validation method for the encapsulated recipe member
* 			in all of its possible forms all at the same time, an efficient
* 			way that allows it to support an active system configuration for
* 			the ASC, combining basic and advanced P/S together with various
* 			actuators and other configuration parameters.   
*
******************************************************************************/
INT32 ParamDesc_AMPSTEPS::ValidateValue (INT32 value)
{
	INT32 val = value;
	
	// this is a member that can be affected by system type and other RT
	// parameters independent of the system type

	return val;
}
