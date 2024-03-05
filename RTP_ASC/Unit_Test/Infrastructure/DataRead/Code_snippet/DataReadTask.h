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


using namespace std;

class DataReadInterface : public SCTask
{
public:
	DataReadInterface();
	~DataReadInterface();
	
	static void* Data_Read_Task(void*);
protected:
	void ProcessTaskMessage(DataReadWrite_Message& requestBuffer);
	void DecodeDataReadMessage(const char *pRecvBuffer, DataReadWrite_Message& ReqMessage);
private:


};


#endif /* DATAREADINTERFACE_H_ */
