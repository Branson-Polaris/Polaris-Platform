/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef INC_ALARMACEPRO_H_
#define INC_ALARMACEPRO_H_

#include <stdio.h>
#include "SCState.h"
#include "Alarm.h"


class AlarmAcePro :public Alarm
{
public:
	AlarmAcePro();
	virtual ~AlarmAcePro();

public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;

};

#endif /* INC_ALARMACEPRO_H_ */
