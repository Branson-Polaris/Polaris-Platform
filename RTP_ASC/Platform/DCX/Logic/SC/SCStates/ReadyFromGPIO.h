/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
     It contains the Ready State from GPIO related implementation 
***************************************************************************/

#ifndef READY_FROM_GPIO_H_
#define READY_FROM_GPIO_H_

#include "SCState.h"
#include "Ready.h"
#include "ControlTask.h"

class ReadyFromGPIO :public Ready
{
public:
	ReadyFromGPIO();
	virtual ~ReadyFromGPIO();
	
	virtual void Enter() override;
	virtual void Loop() override;
	virtual void Exit() override;
	virtual void Fail() override;

};

#endif /* READY_FROM_GPIO_H_ */
