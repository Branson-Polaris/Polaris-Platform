/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the function is responsible for Digital IO Input Task
***************************************************************************/
#include "ScDgtInput.h"
#include "WeldSonicOnFromGPIO.h"
#include "GPIO.h"
#include "Logger_old.h"

/**************************************************************************//**
* \brief   - This function is responsible for Digital IO Input Task
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void* ScDgtInputTask:: ScDgtInput_Task(void *)
{
	UINT16 val = 0;
	UINT32 iEvents	= 0;
	bool bMessageSent = true;		//low->high transition---> send message according to gpio switch transition

	LOGINFO((char *)"------------------------ DgtInput Task spawned ------------------------",0,0,0);
	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[DGTIN_T], taskIdSelf());
	
	while(1)
	{	
		//Wait on an event here. ControlTask should trigger this event every 1 millisecond.
		if(eventReceive(DIGITAL_INPUT_TASK_EVENT, EVENTS_WAIT_ANY, WAIT_FOREVER, &iEvents) != ERROR)
		{
			val = GpioGetValue(GPIO_EXT_SONICS);
			if(LINE_HIGH == val)
			{		
				if(bMessageSent == false)
				{
					bMessageSent = true;
					WeldSonicOnFromGPIO::PerformWeldSonicOnFromGPIO();
				}
			}
			else
			{
				bMessageSent = false;
			}
		}
		else
		{
			LOGERR("ScDgtInput_Task :Event DIGITAL_INPUT_TASK_EVENT receive failed",0,0,0);
		}
	}
	return nullptr;
}

