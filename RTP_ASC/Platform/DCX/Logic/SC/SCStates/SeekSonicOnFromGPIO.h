/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------
	 It contains the Seek Sonic On State from GPIO related implementation   
**********************************************************************************************************/
    

#ifndef _SEEKSONICONFROMGPIO_H_
#define _SEEKSONICONFROMGPIO_H_

#include "SeekSonicOn.h"

class SeekSonicOnFromGPIO : public SeekSonicOn
{
public:
	SeekSonicOnFromGPIO();
	virtual ~SeekSonicOnFromGPIO();

	virtual void Enter() override;
	virtual void Loop() override;
	virtual void Exit() override;
	virtual void Fail() override;
	
private:	
	UINT32 SeekTime;				//Member variable to hold seektime 
	UINT32 SeekTimeCounter;			//SeekTimeCounter increaments when seek starts 
	UINT32 SonicsOnCounter;			//variable to count Sonics 
	UINT32 sonicsDelayCounter;		//Delay Counter
	PowerSupplyTask* ptrPSTask;		//Pointer to get powersupplyTask instance
};

#endif // _SEEKSONICONFROMGPIO_H_
