/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SRC_INC_SC_H_
#define SRC_INC_SC_H_

#include "SCStateMachine.h"

class SC
{
public:
	SC();
	virtual ~SC();
	
	static SCStateMachine *stateMachine;	//Declaration of static pointer
};

#endif /* SRC_INC_SC_H_ */
