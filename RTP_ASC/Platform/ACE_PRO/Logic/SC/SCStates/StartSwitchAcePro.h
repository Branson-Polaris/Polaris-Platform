/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef STARTSWITCHACEPRO_H_
#define STARTSWITCHACEPRO_H_

#include "SCState.h"
#include "StartSwitch.h"

class StartSwitchAcePro: public StartSwitch {
public:
	StartSwitchAcePro();
	virtual ~StartSwitchAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* STARTSWITCHACEPRO_H_ */
