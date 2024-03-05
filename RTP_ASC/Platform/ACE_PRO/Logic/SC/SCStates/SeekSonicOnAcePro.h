/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SEEKSONICONACEPRO_H_
#define SEEKSONICONACEPRO_H_

#include "SCState.h"
#include "SeekSonicOn.h"

class SeekSonicOnAcePro: public SeekSonicOn
{
public:
	SeekSonicOnAcePro();
	virtual ~SeekSonicOnAcePro();
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* SEEKSONICONACEPRO_H_ */
