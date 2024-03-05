/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SCSTATEMACHINEACEPRO_H_
#define SCSTATEMACHINEACEPRO_H_
#include <list>
#include "SCStateMachine.h"

class SCStateMachineAcePro : public SCStateMachine 
{
public:
	SCStateMachineAcePro();
	virtual ~SCStateMachineAcePro();
	
protected:
	virtual void SelectWeldSequence()override;
	virtual void SelectSeekSequence()override;
};
#endif /* SCSTATEMACHINEACEPRO_H_ */
