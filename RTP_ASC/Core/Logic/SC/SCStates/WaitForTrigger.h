/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
SC Wait For Trigger State
***************************************************************************/

#ifndef WAITFORTRIGGER_H_
#define WAITFORTRIGGER_H_

#include "SCState.h"

class WaitForTrigger: public SCState {

public:
	WaitForTrigger();
	virtual ~WaitForTrigger();
public:
	virtual void Enter() = 0;	/* Function to call on entry          */
	virtual void Loop() = 0;	/* Function to call every pass        */
	virtual void Exit() = 0;	/* Function to call on exit           */
	virtual void Fail() = 0;	/* Function to call on alarm handling */
};

#endif /* WAITFORTRIGGER_H_ */
