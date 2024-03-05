/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef INC_HOLDACEPRO_H_
#define INC_HOLDACEPRO_H_

#include <stdio.h>
#include "SCState.h"
#include "Hold.h"

class HoldAcePro :public Hold
{
public:
	HoldAcePro();
	virtual ~HoldAcePro();

public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;

};

#endif /* INC_HOLDACEPRO_H_ */
