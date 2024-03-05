/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
    It contains the Alarm State related implementation 
***************************************************************************/

#ifndef ALARM_FROM_GPIO_H_
#define ALARM_FROM_GPIO_H_

#include "SCState.h"
#include "Alarm.h"

class AlarmFromGPIO :public Alarm
{
public:
	AlarmFromGPIO();
	virtual ~AlarmFromGPIO();

	virtual void Enter() override;
	virtual void Loop() override;
	virtual void Exit() override;
	virtual void Fail() override;
};

#endif /* ALARM_FROM_GPIO_H_ */
