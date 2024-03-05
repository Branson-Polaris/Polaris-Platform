/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef HEADER_FILES_STATE_H_
#define HEADER_FILES_STATE_H_

#include <stdio.h>
#include "vxWorks.h"
#include "Common.h"


class state
{
public:
	state(){};
	virtual ~state(){};
	
protected:
	
	virtual void  	Enter	() = 0;
	virtual void 	Loop	() = 0;
	virtual void 	Exit	() = 0;
};


#endif /* HEADER_FILES_STATE_H_ */
