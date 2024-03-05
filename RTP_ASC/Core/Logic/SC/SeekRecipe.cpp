/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Contains seek recipe which is edit and set by user in UIC   
 
****************************************************************************/

#include "SeekRecipe.h"
#include "WeldRecipePC.h"

/**************************************************************************//**
* 
* \brief   - Constructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
structSeekRecipe::structSeekRecipe()
{
	SetParametersAsPerSystemFrequency();
	SeekMemClearBeforeSeek = SEEK_MEMORY_CLEAR;
	SeekTime = SEEK_TIME_DEFAULT;
	SeekAmplitudeRampTime = WELD_RAMP_TIME_DEFAULT;	
	SeekAmplitude = PC_MIN_WeldAmplitude;
}

/**************************************************************************//**
* 
* \brief   - Set Parameters as per System Frequency.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void structSeekRecipe::SetParametersAsPerSystemFrequency()
{
	switch(SystemFrequency::GetSystemFrequency())
	{
		case FREQ_20KHZ:
		{
			SeekFreqOffset = SEEK_FREQUENCY_OFFSET_20KDEFAULT;
			SeekAmpProportionalGain = AMPLITUDE_PGAIN_20KDEFAULT;
			SeekAmpIntegralGain = AMPLITUDE_IGAIN_20KDEFAULT;
			SeekAmpDerivativeGain = AMPLITUDE_DGAIN_20KDEFAULT;
			SeekPhaseProportionalGain = PHASE_PGAIN_20KDEFAULT;
			SeekPhaseIntegralGain = PHASE_IGAIN_20KDEFAULT;
			SeekPhaseDerivativeGain = PHASE_DGAIN_20KDEFAULT;
		}	
		break;
		
		case FREQ_30KHZ:
		{
			SeekFreqOffset = SEEK_FREQUENCY_OFFSET_30KDEFAULT;
			SeekAmpProportionalGain = AMPLITUDE_PGAIN_30KDEFAULT;
			SeekAmpIntegralGain = AMPLITUDE_IGAIN_30KDEFAULT;
			SeekAmpDerivativeGain = AMPLITUDE_DGAIN_30KDEFAULT;
			SeekPhaseProportionalGain = PHASE_PGAIN_30KDEFAULT;
			SeekPhaseIntegralGain = PHASE_IGAIN_30KDEFAULT;
			SeekPhaseDerivativeGain = PHASE_DGAIN_30KDEFAULT;
		}	
		break;
		
		case FREQ_40KHZ:
		{
			SeekFreqOffset = SEEK_FREQUENCY_OFFSET_40KDEFAULT;
			SeekAmpProportionalGain = AMPLITUDE_PGAIN_40KDEFAULT;
			SeekAmpIntegralGain = AMPLITUDE_IGAIN_40KDEFAULT;
			SeekAmpDerivativeGain = AMPLITUDE_DGAIN_40KDEFAULT;
			SeekPhaseProportionalGain = PHASE_PGAIN_40KDEFAULT;
			SeekPhaseIntegralGain = PHASE_IGAIN_40KDEFAULT;
			SeekPhaseDerivativeGain = PHASE_DGAIN_40KDEFAULT;
		}	
		break;
		
		default:
		{
			SeekFreqOffset = SEEK_FREQUENCY_OFFSET_20KDEFAULT;
			SeekAmpProportionalGain = AMPLITUDE_PGAIN_20KDEFAULT;
			SeekAmpIntegralGain = AMPLITUDE_IGAIN_20KDEFAULT;
			SeekAmpDerivativeGain = AMPLITUDE_DGAIN_20KDEFAULT;
			SeekPhaseProportionalGain = PHASE_PGAIN_20KDEFAULT;
			SeekPhaseIntegralGain = PHASE_IGAIN_20KDEFAULT;
			SeekPhaseDerivativeGain = PHASE_DGAIN_20KDEFAULT;
			LOGERR((char *)"structSeekRecipe : Unknown System Frequency",0,0,0);
		}
		break;
	}
}

/**************************************************************************//**
* 
* \brief   - Constructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SeekRecipe::SeekRecipe()
{	
}

/**************************************************************************//**
* \brief   - Destructor
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
SeekRecipe::~SeekRecipe()
{
}

/**************************************************************************//**
* 
* \brief   - get singleton instance of SeekRecipe.
*
* \param   - None.
*
* \return  - SeekRecipe instance.
*
******************************************************************************/
SeekRecipe& SeekRecipe::GetInstance()
{
	static SeekRecipe instance; 
					   
	return instance;
}

/**************************************************************************//**
* 
* \brief   - Set Parameters As Per System Frequency
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void SeekRecipe::SetParametersAsPerSystemFrequency()
{
	m_Recipe.SetParametersAsPerSystemFrequency();
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekFreqLimitHigh.
*
* \param   - None.
*
* \return  - INT32  SeekFreqLimitHigh.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekFreqLimitHigh() const
{
	return m_Recipe.SeekFreqLimitHigh;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekFreqLimitLow.
*
* \param   - None.
*
* \return  - INT32  SeekFreqLimitLow.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekFreqLimitLow() const
{
	return m_Recipe.SeekFreqLimitLow;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekFreqOffset.
*
* \param   - None.
*
* \return  - INT32  SeekFreqOffset.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekFreqOffset() const
{
	return m_Recipe.SeekFreqOffset;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekMemClearBeforeSeek.
*
* \param   - None.
*
* \return  - INT8  SeekMemClearBeforeSeek.
*
******************************************************************************/
INT8 SeekRecipe::GetSeekMemClearBeforeSeek() const
{
	return m_Recipe.SeekMemClearBeforeSeek;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekTime.
*
* \param   - None.
*
* \return  - UINT32 SeekTime.
*
******************************************************************************/
UINT32 SeekRecipe::GetSeekTime() const
{
	return m_Recipe.SeekTime;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekAmplitudeRampTime.
*
* \param   - None.
*
* \return  - UINT32 SeekAmplitudeRampTime.
*
******************************************************************************/
UINT32 SeekRecipe::GetSeekAmplitudeRampTime() const
{
	return m_Recipe.SeekAmplitudeRampTime;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekAmplitude.
*
* \param   - None.
*
* \return  - UINT32 SeekAmplitude.
*
******************************************************************************/
UINT32 SeekRecipe::GetSeekAmplitude() const
{
	return m_Recipe.SeekAmplitude * 10;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekAmpProportionalGain.
*
* \param   - None.
*
* \return  - INT32 SeekAmpProportionalGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekAmpProportionalGain() const
{
	return m_Recipe.SeekAmpProportionalGain;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekAmpIntegralGain.
*
* \param   - None.
*
* \return  - INT32 SeekAmpIntegralGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekAmpIntegralGain() const
{
	return m_Recipe.SeekAmpIntegralGain;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekAmpDerivativeGain.
*
* \param   - None.
*
* \return  - INT32 SeekAmpDerivativeGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekAmpDerivativeGain() const
{
	return m_Recipe.SeekAmpDerivativeGain;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekPhaseProportionalGain.
*
* \param   - None.
*
* \return  - INT32 SeekPhaseProportionalGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekPhaseProportionalGain() const
{
	return m_Recipe.SeekPhaseProportionalGain;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekPhaseIntegralGain.
*
* \param   - None.
*
* \return  - INT32 SeekPhaseIntegralGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekPhaseIntegralGain() const
{
	return m_Recipe.SeekPhaseIntegralGain;
}

/**************************************************************************//**
* 
* \brief   - Returns the SeekPhaseDerivativeGain.
*
* \param   - None.
*
* \return  - INT32 SeekPhaseDerivativeGain.
*
******************************************************************************/
INT32 SeekRecipe::GetSeekPhaseDerivativeGain() const
{
	return m_Recipe.SeekPhaseDerivativeGain;
}

/**************************************************************************//**
* \brief   - Updates seek recipe parameter with latest data which is 
* 			 modified by user from UIC or DB.
*
* \param   - structSeekRecipe& recipe
*
* \return  - None
*
******************************************************************************/
void SeekRecipe::UpdateSeekRecipe(structSeekRecipe& recipe)
{
	m_Recipe = recipe;
}

/**************************************************************************//**
* 
* \brief   - Returns the latest seek recipe.
*
* \param   - None.
*
* \return  - structSeekRecipe& m_Recipe.
*
******************************************************************************/
structSeekRecipe& SeekRecipe::GetSeekRecipe()
{
	return m_Recipe;
}


