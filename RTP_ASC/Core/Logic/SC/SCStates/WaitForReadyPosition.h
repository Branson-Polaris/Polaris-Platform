/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
SC Wait for Ready Position State
***************************************************************************/

#ifndef WAITFORREADYPOSITION_H_
#define WAITFORREADYPOSITION_H_

#include "SCState.h"

class WaitForReadyPosition: public SCState {
public:
	WaitForReadyPosition();
	virtual ~WaitForReadyPosition();
public:
	virtual void Enter() = 0;	/* Function to call on entry          */
	virtual void Loop () = 0;	/* Function to call every pass        */
	virtual void Exit () = 0;	/* Function to call on exit           */
	virtual void Fail () = 0;	/* Function to call on alarm handling */
};

#endif /* WAITFORREADYPOSITION_H_ */
