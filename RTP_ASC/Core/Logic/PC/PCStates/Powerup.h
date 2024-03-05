/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------
      It contains power-up related implementation 
***************************************************************************/

#ifndef PSPOWERUP_H_
#define PSPOWERUP_H_

#include "PCState.h"
#include "PowerSupplyTask.h"
class Powerup : public PCState 
{
public:
	Powerup();
	virtual 			~Powerup	();
	
protected:
	virtual void 		Enter		();		// Function to call on entry  
	virtual void		Loop		();    	// Function to call every pass
	virtual void		Exit		();     // Function to call on exit 
   
private:
	PowerSupplyTask* ptrPSTask;
	//powerup transition time in msec
	static constexpr int POWERUP_TRANSITION_TIME_IN_MS	= 500;

};

#endif /* PSPOWERUP_H_ */
