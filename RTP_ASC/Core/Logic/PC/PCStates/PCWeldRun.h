/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
  	It contains functions that gets executed when PC state machine goes to WeldRun state.
***************************************************************************/

#ifndef PSWELDRUN_H_
#define PSWELDRUN_H_

#include "PCState.h"

class PCWeldRun: public PCState 
{
public:
	PCWeldRun();
	virtual 			~PCWeldRun	();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;
	PowerSupplyTask* ptrPSTask;
	
};

#endif /* PSWELDRUN_H_ */
