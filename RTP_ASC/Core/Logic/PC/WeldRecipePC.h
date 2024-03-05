/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
#ifndef WELDRECIPEPC_H_
#define WELDRECIPEPC_H_

#include "Common.h"
#include "Utils.h"

#define DIGITAL_TUNE_IN_TENS_OF_HZ 10

/* Macro defined for set MAX range value of PC-Weld recipe */
#define PC_MAX_20KFrequencyLow	    		500    	
#define PC_MAX_30KFrequencyLow		    	750     
#define PC_MAX_40KFrequencyLow			    1000    

#define PC_MAX_20KFrequencyHigh			    500    	
#define PC_MAX_30KFrequencyHigh			    750    
#define PC_MAX_40KFrequencyHigh			    1000    

//////////////////// Future
#define PC_MAX_PhaseLimitTime				20000    
#define PC_MAX_PhaseLimit					9765	
#define PC_MAX_ControlMode					2		 		
#define PC_MAX_BlindtimeSeek				1000     
#define PC_MAX_Blindtimeweld				1000
#define PC_MAX_AmpProportionalGain			500
#define PC_MAX_AmpIntegralGain				500
#define PC_MAX_AmpDerivativeGain			500
#define PC_MAX_PhaseProportionalGain		500
#define PC_MAX_PhaseIntegralGain			500
#define PC_MAX_PhaseDerivativeGain			500  
////////////////////////////////////////////////////////

#define PC_MAX_WeldRampTime                 999
#define PC_MAX_SeekAmplitude				100
#define PC_MAX_WeldAmplitude				100             

/* Macro defined for set MIN range value of PC-Weld recipe */
#define PC_MIN_20KFrequencyLow   		    1	 
#define PC_MIN_30KFrequencyLow  		    1	 
#define PC_MIN_40KFrequencyLow  		    1	 

#define PC_MIN_20KFrequencyHigh  			1	 
#define PC_MIN_30KFrequencyHigh	    		1	 
#define PC_MIN_40KFrequencyHigh 			1	 

//////////////////// Future
#define PC_MIN_PhaseLimitTime				1				
#define PC_MIN_PhaseLimit					4					
#define PC_MIN_ControlMode					1	
#define PC_MIN_BlindtimeSeek				0			
#define PC_MIN_Blindtimeweld				0	
#define PC_MIN_AmpProportionalGain			1			
#define PC_MIN_AmpIntegralGain				1
#define PC_MIN_AmpDerivativeGain			1
#define PC_MIN_PhaseProportionalGain		1
#define PC_MIN_PhaseIntegralGain			0
#define PC_MIN_PhaseDerivativeGain			1
////////////////////////////////////////////////////////
				
#define PC_MIN_SeekAmplitude  				10		
#define PC_MIN_WeldRampTime				    1
#define PC_MIN_WeldAmplitude				10	   	

#define MAX_NO_OF_AMPLITUDE_STEP 			10

/* Macro defined for set default value of Weld recipe */
#define PHASELIMITTIME_DEFAULT        		500   
#define PHASELIMIT_DEFAULT	          		1000  
#define BLINDTIMESEEK_DEFAULT         		0     
#define BLINDTIMEWELD_DEFAULT 	     		0     

#define WELD_RAMP_TIME_DEFAULT			    80    //Milliseconds

#define AMPLITUDE_PGAIN_20KDEFAULT			20
#define AMPLITUDE_PGAIN_30KDEFAULT			20
#define AMPLITUDE_PGAIN_40KDEFAULT			80	

#define AMPLITUDE_IGAIN_20KDEFAULT		    0
#define AMPLITUDE_IGAIN_30KDEFAULT			0
#define AMPLITUDE_IGAIN_40KDEFAULT		    0

#define AMPLITUDE_DGAIN_20KDEFAULT			0
#define AMPLITUDE_DGAIN_30KDEFAULT			0
#define AMPLITUDE_DGAIN_40KDEFAULT			0

#define PHASE_PGAIN_20KDEFAULT			    4000 	
#define PHASE_PGAIN_30KDEFAULT			    16000
#define PHASE_PGAIN_40KDEFAULT			    16000

#define PHASE_IGAIN_20KDEFAULT			    100		
#define PHASE_IGAIN_30KDEFAULT			    400		
#define PHASE_IGAIN_40KDEFAULT			    2000	

#define PHASE_DGAIN_20KDEFAULT			    0		
#define PHASE_DGAIN_30KDEFAULT			    -500	
#define PHASE_DGAIN_40KDEFAULT			    -500	

#define WELDAMPLITUDE_DEFAULT         		100   

#define START_FREQUENCY20KDEFAULT			199500
#define START_FREQUENCY30KDEFAULT			300000
#define START_FREQUENCY40KDEFAULT			399900

#define F20KHZMIDBAND   (199500)
#define F20KHZMINABS (F20KHZMIDBAND - 5000)
#define F20KHZMAXABS (F20KHZMIDBAND + 5000)

#define F30KHZMIDBAND (300000)
#define F30KHZMINABS (F30KHZMIDBAND - 7500)
#define F30KHZMAXABS (F30KHZMIDBAND + 7500)

#define F40KHZMIDBAND (399900)
#define F40KHZMINABS (F40KHZMIDBAND - 10000)
#define F40KHZMAXABS (F40KHZMIDBAND + 10000)

typedef struct WeldRecipePC
{
public :
	WeldRecipePC();
	void SetParametersAsPerSystemFrequency();
	
public:
	INT32	PhaseLoop; 
	INT32	PhaseLoopCF;
	INT32	FrequencyLow;
	INT32	FrequencyHigh; 
	INT32	PhaseLimitTime;
	INT32	PhaseLimit;
	INT32	ControlMode;
	INT32	BlindtimeSeek; 
	INT32	Blindtimeweld;
	INT32	AmpProportionalGain;
	INT32	AmpIntegralGain;
	INT32	AmpDerivativeGain;
	INT32	PhaseDerivativeGain;
	INT32 	PhaseIntegralGain;
	INT32	PhaseProportionalGain;
	INT32	WeldRampTime;
	INT32   StartFrequency;
	INT32   MemoryOffset;
	INT32   DigitalTune;
	INT32   FrequencyOffset;
	bool 	bEndOfWeldStore;  
}WeldRecipePC;


class PcWeldRecipe
{
public:
	PcWeldRecipe			(const PcWeldRecipe& srcObj) = delete;
	PcWeldRecipe& operator=	(const PcWeldRecipe& srcObj) = delete;
	static PcWeldRecipe& GetInstance();
	INT32	GetDigitalTuneWithOffsets();
	INT32	GetMemoryOffset		();
	INT32	GetDigitalTune		();
	INT32	GetFrequencyOffset	();
	INT32   GetWeldRampTime();
	INT32   GetAmplitudePGain();
	INT32   GetAmplitudeIGain();
	INT32   GetAmplitudeDGain();
	INT32   GetPhasePGain();
	INT32   GetPhaseIGain();
	INT32   GetPhaseDGain();
	void    SetMemoryOffset		(INT32 MemoryOffset);
	void    SetDigitalTune		(INT32 DigitalTune);
	void    SetFrequencyOffset	(INT32 FreqOffset);	
	void   	GetWeldRecipe		(WeldRecipePC& recipe);
	void	SetWeldRecipe		(WeldRecipePC& recipe);
	bool    GetEndOfWeldStore();
	void    SetEndOfWeldStore(bool bEndOfWeldStoreFlag);
	void 	SetParametersAsPerSystemFrequency();
	PowerUpData & GetPowerUpRecipe();
	
private:
	WeldRecipePC m_Recipe;
	PcWeldRecipe			();
	~PcWeldRecipe			();
	PowerUpData m_powerupRecipe;
};

class SystemFrequency
{
public:
	SystemFrequency();
	~SystemFrequency();
	static FREQUENCY GetSystemFrequency();
	FREQUENCY GetSystemFrequencyFromStorage();
	bool SetSystemFrequency(FREQUENCY enSystemFrequency);
	
private:
	static FREQUENCY m_SystemFrequency;
	bool saveSystemFrequencyToStorage(FREQUENCY enSystemFrequency);
};




#endif /* WELDRECIPEPC_H_ */
