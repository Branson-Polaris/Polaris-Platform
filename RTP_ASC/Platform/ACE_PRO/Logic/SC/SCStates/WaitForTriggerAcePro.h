/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef WAITFORTRIGGERACEPRO_H_
#define WAITFORTRIGGERACEPRO_H_

#include "SCState.h"
#include "WaitForTrigger.h"

class WaitForTriggerAcePro: public WaitForTrigger {

public:
	WaitForTriggerAcePro();
	virtual ~WaitForTriggerAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* WAITFORTRIGGERACEPRO_H_ */
