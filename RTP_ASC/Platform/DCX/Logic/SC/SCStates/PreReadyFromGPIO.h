/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
    It contains the PreReady State related implementation 
***************************************************************************/


#ifndef PREREADY_FROM_GPIO_H_
#define PREREADY_FROM_GPIO_H_

#include "SCState.h"
#include "PreReady.h"
#include "PowerSupplyTask.h"

class PreReadyFromGPIO : public PreReady 
{
public:
	PreReadyFromGPIO();
	virtual ~PreReadyFromGPIO();

	virtual void Enter() override;
	virtual void Loop() override;
	virtual void Exit() override;
	virtual void Fail() override;
};

#endif /* PREREADY_FROM_GPIO_H_ */
