/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef READYACEPRO_H_
#define READYACEPRO_H_

#include "SCState.h"
#include "Ready.h"

class ReadyAcePro: public Ready {
public:
	ReadyAcePro();
	virtual ~ReadyAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* READYACEPRO_H_ */
