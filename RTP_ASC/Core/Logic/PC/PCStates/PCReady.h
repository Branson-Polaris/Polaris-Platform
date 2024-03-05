/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
   It contains functions that gets executed when PC state machine goes to  ready state.
***************************************************************************/

#ifndef PSREADY_H_
#define PSREADY_H_

#include "PCState.h"

class PCReady: public PCState 
{
public:
	PCReady();
	virtual 			~PCReady();
protected:
	virtual void 		Enter		();
	virtual void		Loop		();
	virtual void		Exit		();
	PowerSupplyTask* ptrPSTask;
};

#endif /* PSREADY_H_ */
