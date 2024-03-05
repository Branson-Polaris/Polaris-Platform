/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
   	It contains functions that gets executed when PC state machine goes to WeldRun state.
***************************************************************************/

#ifndef PSWELDRUNACEPRO_H_
#define PSWELDRUNACEPRO_H_

#include "PCWeldRun.h"

class PCWeldRunAcePro: public PCWeldRun 
{
public:
	PCWeldRunAcePro();
	virtual 			~PCWeldRunAcePro	();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;	
};

#endif /* PSWELDRUNACEPRO_H_ */
