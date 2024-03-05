/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------
      It contains power-up state ACEPRO related implementation 
***************************************************************************/

#ifndef PSPOWERUPACEPRO_H_
#define PSPOWERUPACEPRO_H_

#include "Powerup.h"

class PowerupAcePro : public Powerup 
{
public:
	PowerupAcePro			();
	virtual ~PowerupAcePro	();
	
protected:
	virtual void 		Enter		() override; 		 
	virtual void		Loop		() override;    	
	virtual void		Exit		() override;

};

#endif /* PSPOWERUPACEPRO_H_ */
