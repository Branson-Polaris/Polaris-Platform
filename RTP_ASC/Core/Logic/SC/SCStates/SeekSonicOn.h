/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  SC Seek Sonic State
***************************************************************************/

#ifndef SEEK_H_
#define SEEK_H_

#include "SCState.h"
#include "ControlTask.h"
class SeekSonicOn: public SCState
{
public:
	SeekSonicOn();
	virtual ~SeekSonicOn();
public:
	virtual void Enter() = 0;	/* Function to call on entry          */
	virtual void Loop () = 0;	/* Function to call every pass        */
	virtual void Exit () = 0;	/* Function to call on exit           */
	virtual void Fail () = 0;	/* Function to call on alarm handling */	
protected:
	static constexpr unsigned int MAX_SONIC_DELAY_IN_MS = (10 * (1000/CTRL_CYCLE_TIME_IN_US));	//used constant expression instead of macro

};

#endif /* SEEK_H_ */
