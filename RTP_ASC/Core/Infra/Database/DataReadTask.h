/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/


#ifndef DATAREADINTERFACE_H_
#define DATAREADINTERFACE_H_

#include "SCTask.h"
#include "Common.h"
#include "logger.h"
#include <stdio.h>
class DataReadInterface : public SCTask
{
public:
	enum DATA_READ_MESSSAGE
	{
		/* Macro defined to DATA READ TASK */
		LAST_WELD_RESULT_DATA_READ,
		LAST_WELD_SIGNATURE_DATA_READ,
	};
	DataReadInterface();
	~DataReadInterface();
	
	static void* Data_Read_Task(void*);
protected:
	void ProcessTaskMessage(DataReadWrite_Message& requestBuffer);
	void DecodeDataReadMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage);
private:
	static size_t static_log_id;
	size_t log_id;
};


#endif /* DATAREADINTERFACE_H_ */
