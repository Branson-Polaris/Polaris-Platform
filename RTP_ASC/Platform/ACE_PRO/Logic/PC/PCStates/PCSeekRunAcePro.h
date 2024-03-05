/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
 	It contains functions that gets executed when PC state machine goes to SeekRun state. 
***************************************************************************/

#ifndef PSSEEKRUNACEPRO_H_
#define PSSEEKRUNACEPRO_H_

#include "PCSeekRun.h"

class PCSeekRunAcePro: public PCSeekRun 
{
public:
	PCSeekRunAcePro();
	virtual ~PCSeekRunAcePro();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;
};

#endif /* PSSEEKRUNACEPRO_H_ */
