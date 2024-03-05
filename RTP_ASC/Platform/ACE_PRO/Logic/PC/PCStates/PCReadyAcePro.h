/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
    It contains functions that gets executed when PC state machine goes to  ready state.
***************************************************************************/

#ifndef PSREADYACEPRO_H_
#define PSREADYACEPRO_H_

#include "PCReady.h"

class PCReadyAcePro: public PCReady 
{
public:
	PCReadyAcePro();
	virtual 			~PCReadyAcePro();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;
};
#endif /* PSREADYACEPRO_H_ */
