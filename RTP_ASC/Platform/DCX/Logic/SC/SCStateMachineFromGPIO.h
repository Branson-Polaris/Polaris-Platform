/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
   	 It contains the GPIO related SC State Machine implementation
***************************************************************************/

#ifndef SCSTATEMACHINEFROMGPIO_H_
#define SCSTATEMACHINEFROMGPIO_H_
#include <list>
#include "SCState.h"
#include "SCAction.h"
#include "SCStateMachine.h"

class SCStateMachineFromGPIO : public SCStateMachine 
{
public:
	SCStateMachineFromGPIO();
	virtual ~SCStateMachineFromGPIO();
protected:
	virtual void SelectWeldSequence()override;	//Member function used to execute the sequence according to operation
	virtual void SelectSeekSequence()override;	//Member function used to execute the sequence according to operation

};

#endif /* SCSTATEMACHINEFROMGPIO_H_ */
