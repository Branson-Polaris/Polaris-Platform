/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------    
 	 It contains the Weld Sonic On State from GPIO related implementation 	 	 
***************************************************************************/


#ifndef SRC_INC_WELDSONICONFROMGPIO_H_
#define SRC_INC_WELDSONICONFROMGPIO_H_

#include "WeldSonicOn.h"
#include "MainTask.h"

class WeldSonicOnFromGPIO :public WeldSonicOn
{
public:
	WeldSonicOnFromGPIO();
	virtual ~WeldSonicOnFromGPIO();	
	static bool PerformWeldSonicOnFromGPIO();

	virtual void Enter() override;
	virtual void Loop() override;
	virtual void Exit() override;
	virtual void Fail() override;

private:
	UINT32 				weldSonicOnTime; 	//Sonic on Time
	WELDMODES 			modes;			 	//different types of WELD mode
	INT32  				modeValue;		 	//Mode values
	UINT32 				SonicsOnCounter;	//variable to count Sonics 
	UINT32 				sonicsDelayCounter;	//Delay Counter
	PowerSupplyTask* 	ptrPSTask;			//Pointer to get powersupplyTask instance
};

#endif /* SRC_INC_WELDSONICONFROMGPIO_H_ */
