/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
    
 
***************************************************************************/

#ifndef WELDSONICONACEPRO_H_
#define WELDSONICONACEPRO_H_
#include "SCState.h"
#include "WeldSonicOn.h"

class WeldSonicOnAcePro: public WeldSonicOn 
{
public:
	WeldSonicOnAcePro();
	virtual ~WeldSonicOnAcePro();
	
public:
	virtual void Enter() override;
	virtual void Loop () override;
	virtual void Exit () override;
	virtual void Fail () override;
};

#endif /* WELDSONICONACEPRO_H_ */
