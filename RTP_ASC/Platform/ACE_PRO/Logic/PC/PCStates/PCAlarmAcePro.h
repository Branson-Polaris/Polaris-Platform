/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------
    It contains the PC Alarm State related implementation 
***************************************************************************/

#ifndef PSALARMACEPRO_H_
#define PSALARMACEPRO_H_

#include "PCAlarm.h"

class PCAlarmAcePro: public PCAlarm 
{
public:
	PCAlarmAcePro();
	virtual 			~PCAlarmAcePro	();
protected:
	virtual void 		Enter		() override;
	virtual void		Loop		() override;
	virtual void		Exit		() override;
};

#endif /* PSALARMACEPRO_H_ */
