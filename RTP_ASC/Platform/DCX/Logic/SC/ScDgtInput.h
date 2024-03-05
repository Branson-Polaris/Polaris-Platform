/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
   	 It contains the function is responsible for Digital IO Input Task
***************************************************************************/


#ifndef DGT_INPUT_H
#define DGT_INPUT_H

#include "SCTask.h"

class ScDgtInputTask: public SCTask 
{
public:
	ScDgtInputTask		();
	~ScDgtInputTask		();
	
	static void*				ScDgtInput_Task		(void *);

};

#endif  //DGT_INPUT_H

