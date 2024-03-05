/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
 	  It contains the Emergency Stop state related implementation
***************************************************************************/

#ifndef PSESTOPACEPRO_H_
#define PSESTOPACEPRO_H_

#include "PCEstop.h"

class PCEstopAcePro: public PCEstop 
{
public:
	PCEstopAcePro();
	virtual 			~PCEstopAcePro	();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;
};

#endif /* PSESTOPACEPRO_H_ */
