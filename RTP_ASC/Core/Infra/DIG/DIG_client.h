/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef DIG_CLIENT_H_
#define DIG_CLIENT_H_

#include "SCTask.h"

//TO_BE_DONE - Remove this #define when DIG client implementation is complete.
//#define ENABLE_DIG_CLIENT 1

#define DIG_CLIENT_INTERFACE_NAME "cpsw1"
#define DIG_SERVER_IP "150.150.150.50"
#define DIG_CLIENT_GATEWAY "150.150.150.1"
#define DIG_CLIENT_SUBNET_MASK "255.255.255.0"

//Max Time in seconds to wait for Socket connection
#define MAX_DIG_SOCKET_CONNECT_WAIT_TIME 5 

//Max Time in seconds to wait for receiving data
#define MAX_DIG_SOCKET_READ_WAIT_TIME 2 

//Max retries done to send data
#define MAX_SEND_RETRY_COUNT 10


class DIGClient : public SCTask
{
public:
	static bool SetCPSW1IP();
	static void* Socket_DIG_Task(void *);
	
private:	
	DIGClient();
	~DIGClient();
	bool connectToDIGServer();
	bool sendDataToDIGServer(const char *pcData, const int nSize);
	bool receiveDataFromDIGServer(char *pcData, const int nSize, bool bReadExactBytes);
	bool readExactBytes(char *pcData, const int nSize);
	bool waitForConnect();
	int waitOnSelect(int nTimeOut, bool bReadFd);
	
	static bool getCPSW1IPAddressAndPort(std::pair<std::string, int> &pairDIGIPAddressAndPort);
	static int getCPSW1IPChoiceEnum();
	
	int m_nSocketFD;
};

#endif /* DIG_CLIENT_H_ */
