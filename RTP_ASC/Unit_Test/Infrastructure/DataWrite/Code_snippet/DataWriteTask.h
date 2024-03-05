/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/


#ifndef DATAWRITEINTERFACE_H_
#define DATAWRITEINTERFACE_H_

#include "SCTask.h"
#include "Common.h"
#include "logger.h"
#include <stdio.h>
#include "DBAccess_common_db.h"
#include "DBAccess_p1_base_db.h"

class DataWriteInterface : public SCTask
{
public:
	enum DATA_WRITE_MESSSAGE
	{
		LAST_WELD_RESULT_DATA_WRITE,
		LAST_WELD_SIGNATURE_DATA_WRITE,
	};
	DataWriteInterface();
	~DataWriteInterface();
	
	static void* Data_Write_Task(void*);
protected:

	void ProcessTaskMessage(DataReadWrite_Message& requestBuffer);
	void DecodeDataWriteMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage);
private:
	static size_t static_log_id;
};


#endif /* DATAWRITEINTERFACE_H_ */
