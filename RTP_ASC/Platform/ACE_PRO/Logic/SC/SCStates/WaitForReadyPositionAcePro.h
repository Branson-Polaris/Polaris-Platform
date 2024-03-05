/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef WAITFORREADYPOSITIONACEPRO_H_
#define WAITFORREADYPOSITIONACEPRO_H_

#include "SCState.h"
#include "WaitForReadyPosition.h"

class WaitForReadyPositionAcePro: public WaitForReadyPosition
{
public:
	WaitForReadyPositionAcePro();
	virtual ~WaitForReadyPositionAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* WAITFORREADYPOSITIONACEPRO_H_ */
