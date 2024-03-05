/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 It contains setter and getter functions of parameter
***************************************************************************/
#include "WeldRecipe.h"
#include <fstream>
#include "CommonProperty.h"
#include "commons.h"

FREQUENCY SystemFrequency::m_SystemFrequency = FREQ_UNKNOWN;

/**************************************************************************//**
* 
* \brief   - Initialization of class members and memory for object.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
PcWeldRecipe::PcWeldRecipe()
{
	WeldRecipePC PCData;
	SetWeldRecipe(PCData);
}

/**************************************************************************//**
* 
* \brief   - Memory release of object.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
PcWeldRecipe::~PcWeldRecipe()
{
}

/**************************************************************************//**
* 
* \brief   - get singleton instance of PcWeldRecipe.
*
* \param   - None.
*
* \return  - PcWeldRecipe instance.
*
******************************************************************************/
PcWeldRecipe& PcWeldRecipe::GetInstance()
{
	static PcWeldRecipe instance; 
					   
	return instance;
}


/**************************************************************************//**
* 
* \brief   - return the digital tune + Memory Offset + Freq Offset.
*
* \param   - None.
*
* \return  - INT32 digital tune + Memory Offset in 10's of Hz + Freq Offset in 10's of Hz.
*
******************************************************************************/
INT32 PcWeldRecipe::GetDigitalTuneWithOffsets()
{
	return (m_Recipe.DigitalTune + ( m_Recipe.MemoryOffset * DIGITAL_TUNE_IN_TENS_OF_HZ ) + ( m_Recipe.FrequencyOffset * DIGITAL_TUNE_IN_TENS_OF_HZ )); 
}

/**************************************************************************//**
* 
* \brief   - return the DigitalTune.
*
* \param   - None.
*
* \return  - UINT32 DigitalTune in 10's of Hz.
*
******************************************************************************/
INT32 PcWeldRecipe::GetDigitalTune()
{
	return m_Recipe.DigitalTune;
}

/**************************************************************************//**
* 
* \brief   - return the MemoryOffset.
*
* \param   - None.
*
* \return  - UINT32 MemoryOffset.
*
******************************************************************************/
INT32 PcWeldRecipe::GetMemoryOffset()
{
	return m_Recipe.MemoryOffset;
}

/**************************************************************************//**
* 
* \brief   - return the FrequencyOffset.
*
* \param   - None.
*
* \return  - UINT32 FrequencyOffset.
*
******************************************************************************/
INT32 PcWeldRecipe::GetFrequencyOffset()
{
	return m_Recipe.FrequencyOffset;
}

/**************************************************************************//**
* 
* \brief   - return the WeldRampTime.
*
* \param   - None.
*
* \return  - INT32 WeldRampTime.
*
******************************************************************************/
INT32 PcWeldRecipe::GetWeldRampTime()
{
	return m_Recipe.WeldRampTime;
}

/**************************************************************************//**
* 
* \brief   - return the AmpProportionalGain.
*
* \param   - None.
*
* \return  - INT32 AmpProportionalGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetAmplitudePGain()
{
	return m_Recipe.AmpProportionalGain;
}

/**************************************************************************//**
* 
* \brief   - return the AmpIntegralGain.
*
* \param   - None.
*
* \return  - INT32 AmpIntegralGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetAmplitudeIGain()
{
	return m_Recipe.AmpIntegralGain;
}

/**************************************************************************//**
* 
* \brief   - return the AmpDerivativeGain.
*
* \param   - None.
*
* \return  - INT32 AmpDerivativeGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetAmplitudeDGain()
{
	return m_Recipe.AmpDerivativeGain;
}

/**************************************************************************//**
* 
* \brief   - return the PhaseProportionalGain.
*
* \param   - None.
*
* \return  - INT32 PhaseProportionalGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetPhasePGain()
{
	return m_Recipe.PhaseProportionalGain;
}

/**************************************************************************//**
* 
* \brief   - return the PhaseIntegralGain.
*
* \param   - None.
*
* \return  - INT32 PhaseIntegralGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetPhaseIGain()
{
	return m_Recipe.PhaseIntegralGain;
}

/**************************************************************************//**
* 
* \brief   - return the PhaseDerivativeGain.
*
* \param   - None.
*
* \return  - INT32 PhaseDerivativeGain.
*
******************************************************************************/
INT32 PcWeldRecipe::GetPhaseDGain()
{
	return m_Recipe.PhaseDerivativeGain;
}

/**************************************************************************//**
* 
* \brief   - Set the MemoryOffset.
*
* \param   - UINT32 MemoryOffset.
*
* \return  - None.
*
******************************************************************************/
void PcWeldRecipe::SetMemoryOffset(INT32 MemoryOffset)
{
	m_Recipe.MemoryOffset = MemoryOffset;
	
}

/**************************************************************************//**
* 
* \brief   - Set the DigitalTune.
*
* \param   - UINT32 DigitalTune.
*
* \return  - None.
*
******************************************************************************/
void PcWeldRecipe::SetDigitalTune(INT32 DigitalTune)
{
	m_Recipe.DigitalTune = DigitalTune;
}

/**************************************************************************//**
* 
* \brief   - Set the FrequencyOffset.
*
* \param   - UINT32 FrequencyOffset.
*
* \return  - None.
*
******************************************************************************/
void PcWeldRecipe::SetFrequencyOffset(INT32 FreqOffset)
{
	m_Recipe.FrequencyOffset = FreqOffset;
}

/**************************************************************************//**
* 
* \brief   - Get the member data PCWeldRecipe.
*
* \param   - WeldRecipePC& recipe.
*
* \return  - None.
*
******************************************************************************/
void PcWeldRecipe::GetWeldRecipe(WeldRecipePC& recipe)
{
	recipe = m_Recipe;
	recipe.StartFrequency = recipe.StartFrequency * 10;		/* convert Hz -> 10s of Hz */
}

/**************************************************************************//**
* 
* \brief   - Assign recipe values to member data. 
*
* \param   - WeldRecipePC& recipe.
*
* \return  - None.
*
******************************************************************************/
void PcWeldRecipe::SetWeldRecipe(WeldRecipePC& recipe)
{
	recipe.FrequencyHigh = recipe.FrequencyHigh * 10;  /* convert Hz -> 10s of Hz */
	recipe.FrequencyLow = recipe.FrequencyLow * 10;
	recipe.PhaseLimitTime = PHASELIMITTIME_DEFAULT;
	m_Recipe = recipe;
	m_Recipe.StartFrequency = m_Recipe.StartFrequency / 10;		/* convert 10s of Hz -> Hz */
}

/**************************************************************************//**
* \brief   - Constructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
WeldRecipePC::WeldRecipePC()			/* Constructor of WeldRecipePC structure which is defined in WeldRecipe.h */
{	
		/*Initialize the all parameter with the min value	*/
	
		SetParametersAsPerSystemFrequency();
		
		PhaseLimitTime 			= PC_MIN_PhaseLimitTime;
		PhaseLimit 				= PC_MIN_PhaseLimit;
		ControlMode 			= PC_MIN_ControlMode;
		BlindtimeSeek 			= PC_MIN_BlindtimeSeek;
		Blindtimeweld 			= PC_MIN_Blindtimeweld;
		WeldRampTime			= WELD_RAMP_TIME_DEFAULT;
		bEndOfWeldStore 		= true; 
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
void WeldRecipePC::SetParametersAsPerSystemFrequency()
{
	switch(SystemFrequency::GetSystemFrequency())
	{
		case FREQ_20KHZ:
		{
			DigitalTune	    		= START_FREQUENCY20KDEFAULT;
			AmpProportionalGain 	= AMPLITUDE_PGAIN_20KDEFAULT;
			AmpIntegralGain 		= AMPLITUDE_IGAIN_20KDEFAULT;
			AmpDerivativeGain 		= AMPLITUDE_DGAIN_20KDEFAULT;
			PhaseProportionalGain 	= PHASE_PGAIN_20KDEFAULT;
			PhaseIntegralGain		= PHASE_IGAIN_20KDEFAULT;
			PhaseDerivativeGain 	= PHASE_DGAIN_20KDEFAULT;
		}	
		break;
		
		case FREQ_30KHZ:
		{
			DigitalTune	    		= START_FREQUENCY30KDEFAULT;
			AmpProportionalGain 	= AMPLITUDE_PGAIN_30KDEFAULT;
			AmpIntegralGain 		= AMPLITUDE_IGAIN_30KDEFAULT;
			AmpDerivativeGain 		= AMPLITUDE_DGAIN_30KDEFAULT;
			PhaseProportionalGain 	= PHASE_PGAIN_30KDEFAULT;
			PhaseIntegralGain		= PHASE_IGAIN_30KDEFAULT;
			PhaseDerivativeGain 	= PHASE_DGAIN_30KDEFAULT;
		}	
		break;
		
		case FREQ_40KHZ:
		{
			DigitalTune	    		= START_FREQUENCY40KDEFAULT;
			AmpProportionalGain 	= AMPLITUDE_PGAIN_40KDEFAULT;
			AmpIntegralGain 		= AMPLITUDE_IGAIN_40KDEFAULT;
			AmpDerivativeGain 		= AMPLITUDE_DGAIN_40KDEFAULT;
			PhaseProportionalGain 	= PHASE_PGAIN_40KDEFAULT;
			PhaseIntegralGain		= PHASE_IGAIN_40KDEFAULT;
			PhaseDerivativeGain 	= PHASE_DGAIN_40KDEFAULT;
		}	
		break;
		
		default:
		{
			DigitalTune	    		= START_FREQUENCY20KDEFAULT;
			AmpProportionalGain 	= AMPLITUDE_PGAIN_20KDEFAULT;
			AmpIntegralGain 		= AMPLITUDE_IGAIN_20KDEFAULT;
			AmpDerivativeGain 		= AMPLITUDE_DGAIN_20KDEFAULT;
			PhaseProportionalGain 	= PHASE_PGAIN_20KDEFAULT;
			PhaseIntegralGain		= PHASE_IGAIN_20KDEFAULT;
			PhaseDerivativeGain 	= PHASE_DGAIN_20KDEFAULT;
			LOGERR((char *)"\nWeldRecipePC : Unknown System Frequency",0,0,0);
		}
		break;
	}
	
	MemoryOffset = 0;
	FrequencyOffset = 0;		
	StartFrequency = DigitalTune + MemoryOffset + FrequencyOffset;
}

/**************************************************************************//**
* 
* \brief   - return the bEndOfWeldStore flag.
*
* \param   - None.
*
* \return  - bool bEndOfWeldStore flag.
*
******************************************************************************/
bool PcWeldRecipe::GetEndOfWeldStore()
{
	return m_Recipe.bEndOfWeldStore;
}

/**************************************************************************//**
* 
* \brief   - set the bEndOfWeldStore flag.
*
* \param   - bEndOfWeldStoreFlag - flag value.
*
* \return  - none.
*
******************************************************************************/
void PcWeldRecipe::SetEndOfWeldStore(bool bEndOfWeldStoreFlag)
{
	m_Recipe.bEndOfWeldStore = bEndOfWeldStoreFlag;
}

/**************************************************************************//**
* \brief   - Return the reference to powerupRecipe.
*
* \param   - None.
*
* \return  - reference to powerupRecipe
*
******************************************************************************/
PowerUpData& PcWeldRecipe::GetPowerUpRecipe()
{
	return m_powerupRecipe;
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
void PcWeldRecipe::SetParametersAsPerSystemFrequency()
{
	m_Recipe.SetParametersAsPerSystemFrequency();
}

/**************************************************************************//**
* \brief   - Constructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SystemFrequency::SystemFrequency()
{
	
}

/**************************************************************************//**
* \brief   - Destructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SystemFrequency::~SystemFrequency()
{
	
}

/**************************************************************************//**
* \brief   - Get the system frequency value
*
* \param   - None.
*
* \return  - system frequency value "m_SystemFrequency"
*
******************************************************************************/
FREQUENCY SystemFrequency::GetSystemFrequency()
{
	return m_SystemFrequency;
}

/**************************************************************************//**
* \brief   - Get the system frequency value stored in non-volatile memory
*
* \param   - None.
*
* \return  - FREQUENCY value stored in non-volatile memory
*
******************************************************************************/
FREQUENCY SystemFrequency::GetSystemFrequencyFromStorage()
{
	FREQUENCY enSystemFrequency = FREQ_UNKNOWN;

	std::fstream SystemFrequencyFile;
	SystemFrequencyFile.open(SYSTEM_FREQUENCY_FILE_PATH_EMMC, std::ios::in); 
	if (SystemFrequencyFile.is_open())
	{   
		std::string strSystemFrequency = "";
		getline(SystemFrequencyFile, strSystemFrequency);
		enSystemFrequency = (FREQUENCY)atoi(strSystemFrequency.c_str());
		SystemFrequencyFile.close();
	}
	
	if(enSystemFrequency != FREQ_20KHZ && enSystemFrequency != FREQ_30KHZ && enSystemFrequency != FREQ_40KHZ)
	{
		enSystemFrequency = FREQ_UNKNOWN;
	}
	
	return enSystemFrequency;
}

/**************************************************************************//**
* \brief   - Set the system frequency
*
* \param   - enSystemFrequency - Frequency to be set.
*
* \return  - SUCCESS/FAILURE
*
******************************************************************************/
bool SystemFrequency::SetSystemFrequency(FREQUENCY enSystemFrequency)
{
	bool bResult = FAILURE;
	if(enSystemFrequency == FREQ_20KHZ || enSystemFrequency == FREQ_30KHZ || enSystemFrequency == FREQ_40KHZ)
	{
		bResult = saveSystemFrequencyToStorage(enSystemFrequency);
		if(bResult == SUCCESS)
		{
			m_SystemFrequency = enSystemFrequency;
			
			PcWeldRecipe::GetInstance().SetParametersAsPerSystemFrequency();
			SeekRecipe::GetInstance().SetParametersAsPerSystemFrequency();
		}
	}
	return bResult;
}

/**************************************************************************//**
* \brief   - Save the system frequency value in non-volatile memory
*
* \param   - enSystemFrequency - Frequency value to be saved.
*
* \return  - SUCCESS/FAILURE
*
******************************************************************************/
bool SystemFrequency::saveSystemFrequencyToStorage(FREQUENCY enSystemFrequency)
{
	bool bResult = FAILURE;	

	std::fstream SystemFrequencyFile;
	SystemFrequencyFile.open(SYSTEM_FREQUENCY_FILE_PATH_EMMC, std::ios::out);
	if (SystemFrequencyFile) 
	{
		SystemFrequencyFile << enSystemFrequency;
		SystemFrequencyFile.close(); 
		bResult = SUCCESS;
	}
	
	return bResult;
}

