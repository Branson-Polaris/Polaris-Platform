/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef PREREADYACEPRO_H_
#define PREREADYACEPRO_H_

#include "SCState.h"
#include "PreReady.h"

class PreReadyAcePro: public PreReady {
public:
	PreReadyAcePro();
	virtual ~PreReadyAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* PREREADYACEPRO_H_ */
