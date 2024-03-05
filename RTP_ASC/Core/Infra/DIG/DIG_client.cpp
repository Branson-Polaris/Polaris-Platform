/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

 	 It contains the Data Interface Gateway (DIG) client implementation. 
 
**********************************************************************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <map>
#include<iterator>

#include "DIG_client.h"
#include "Common.h"
#include "Logger_old.h"

//Map containing CPSW1/DIG client IP Addresses and respective Port Numbers.
const std::map<int, std::pair<std::string, int>> g_mapOfDIGClientIPAddressAndPort = 
{
	  //User IP Choice Enum, IP Address, Port Number
	  { 0, { "150.150.150.10", 65100 }},
	  { 1, { "150.150.150.11", 65101 }},
	  { 2, { "150.150.150.12", 65102 }},
	  { 3, { "150.150.150.13", 65103 }},
	  { 4, { "150.150.150.14", 65104 }},
	  { 5, { "150.150.150.15", 65105 }},
	  { 6, { "150.150.150.16", 65106 }},
	  { 7, { "150.150.150.17", 65107 }},
	  { 8, { "150.150.150.18", 65108 }},
	  { 9, { "150.150.150.19", 65109 }},
};

/**************************************************************************//**
* 
* \brief   - Set CPSW1/DIG Client IP Address
*
* \param   - none
*
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::SetCPSW1IP()
{
	bool bResult = false;
	std::pair<std::string, int> pairOfIPAddressAndPort;
	
	//Get DIG client IP address and port number.	
	if( getCPSW1IPAddressAndPort(pairOfIPAddressAndPort) == true)
	{
		if (IPConfiguration((char *)pairOfIPAddressAndPort.first.c_str(), (char *)DIG_CLIENT_SUBNET_MASK, (char *)DIG_CLIENT_GATEWAY, (char *)DIG_CLIENT_INTERFACE_NAME) != SUCCESS)
		{
			LOGERR((char *)"DIGClient: SetCPSW1IP: IPConfiguration failure",0,0,0);
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		LOGERR((char *)"DIGClient:SetCPSW1IP: IP Address choice Invalid/Not allowed",0,0,0);
	}

	return bResult;
}

/**************************************************************************//**
* \brief  - Constructor
* 
* \param  - None
*
* \return - None
* 
******************************************************************************/
DIGClient::DIGClient()
{
	m_nSocketFD = -1;
}

/**************************************************************************//**
* \brief  - Destructor
* 
* \param  - None
*
* \return - None
* 
******************************************************************************/
DIGClient::~DIGClient()
{
	if( m_nSocketFD > -1 )
	{
		close(m_nSocketFD);
	}
	m_nSocketFD = -1;
}

/**************************************************************************//**
* 
* \brief   - Connect To DIG Server
*
* \param   - none
*
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::connectToDIGServer()
{
	bool bResult = false;
	struct sockaddr_in stServerAddress, stLocalAddress;
	
	//close previously opened socket if any.
	if(m_nSocketFD > -1 )
	{
		close(m_nSocketFD);		
	}
	m_nSocketFD = -1;
	
	if ((m_nSocketFD = socket(AF_INET, SOCK_STREAM, 0)) <= -1)
	{
		LOGERR((char *)"DIGClient: connectToDIGServer: Socket creation error.",0,0,0);
	} 
	else
	{	
		//Make a non-blocking socket connection.
		if(	fcntl(m_nSocketFD, F_SETFL, fcntl(m_nSocketFD, F_GETFL, 0) | O_NONBLOCK) < 0)
		{
			LOGERR((char *)"DIGClient: connectToDIGServer: fcntl error.",0,0,0);
		}
		else
		{
			std::pair<std::string, int> pairOfIPAddressAndPort;
	
			//Get local IP address and port number to bind to.	
			if( getCPSW1IPAddressAndPort(pairOfIPAddressAndPort) == true)
			{
				//Bind to a specific network interface and a specific local port.
				stLocalAddress.sin_family = AF_INET;
				stLocalAddress.sin_addr.s_addr = inet_addr(pairOfIPAddressAndPort.first.c_str());
				stLocalAddress.sin_port = htonl(pairOfIPAddressAndPort.second);
				
				if( bind(m_nSocketFD, (struct sockaddr *)&stLocalAddress, sizeof(stLocalAddress)) < 0)
				{
					LOGERR((char *)"DIGClient: connectToDIGServer: Bind Failed.",0,0,0);
				}	
				else
				{
					//Connect to DIG Server.
					stServerAddress.sin_family = AF_INET;
					stServerAddress.sin_addr.s_addr = inet_addr(DIG_SERVER_IP);
					stServerAddress.sin_port = htons(pairOfIPAddressAndPort.second);	
					
					if (connect(m_nSocketFD, (struct sockaddr *)&stServerAddress, sizeof(stServerAddress)) < 0)
					{				
						// If the connection is still in progress
						if (errno == EINPROGRESS) 
						{ 
							bResult = waitForConnect();	
						} 
						else 
						{ 
							// Connect failed.
							LOGERR((char *)"DIGClient: connectToDIGServer: Connect Failed.",0,0,0);
						} 					
					}
					else
					{
						bResult = true;
					}
				}
			}
			else
			{
				LOGERR((char *)"DIGClient: connectToDIGServer: getCPSW1IPAddressAndPort Failed.",0,0,0);
			}
		}
	}

	if(bResult != true && m_nSocketFD > -1 )
	{
		close(m_nSocketFD);
		m_nSocketFD = -1;
	}

	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Send Data To DIG Server
*
* \param:
* pcData: Data to be sent
* nSize: Size of Data to be sent
*
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::sendDataToDIGServer(const char *pcData, const int nSize)
{
	bool bResult = false;	
	bool bErrorOccured = false;
	int nTotalBytesSent = 0; 
	int nRetryCount = 0;
	int nActualBytesSent = 0;
	int nBytesLeftToBeSent = nSize;
	
	if(m_nSocketFD > -1 && pcData != nullptr && nSize > 0)
	{
		//loop to send complete data.
		while(nTotalBytesSent < nSize) 
		{
			nActualBytesSent = send(m_nSocketFD, pcData+nTotalBytesSent, nBytesLeftToBeSent, 0);
			if (nActualBytesSent < 0) 
			{
				bErrorOccured = true;
				LOGERR((char *)"DIGClient: sendDataToDIGServer error",0,0,0);
				break; 	
			}
			else if(nActualBytesSent == 0)
			{
				LOGINFO((char *)"DIGClient: sendDataToDIGServer , 0 bytes sent, trying again...",0,0,0);
				if(nRetryCount == MAX_SEND_RETRY_COUNT)
				{
					bErrorOccured = true;
					LOGERR((char *)"DIGClient: sendDataToDIGServer error, Max Retries done.",0,0,0);
					break;
				}
				nRetryCount++;
			}
			else
			{
				if(nActualBytesSent != nSize)
				{
					LOGINFO((char *)"DIGClient: sendDataToDIGServer, Sending Data in multiple go...",0,0,0);
				}
			}
			nTotalBytesSent += nActualBytesSent;
			nBytesLeftToBeSent -= nActualBytesSent;
		}
		
		if(nTotalBytesSent != nSize || bErrorOccured == true)
		{
			LOGERR((char *)"DIGClient: sendDataToDIGServer error, Total Bytes Sent: %d and Expected Bytes to be sent: %d",nTotalBytesSent,nSize,0);
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		LOGERR((char *)"DIGClient: sendDataToDIGServer: connection not established/connection closed to DIG Server or null pointer passed to sendDataToDIGServer or invalid data size passed to sendDataToDIGServer",0,0,0);
	}
	
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Receive Data From DIG Server
*
* \param:
* pcData: Data will be received inside this buffer
* nSize: Buffer size
* bReadExactBytes: Read exact number of bytes = nSize if the bReadExactBytes is set,
* else read whatever bytes are available.
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::receiveDataFromDIGServer(char *pcData, const int nSize, bool bReadExactBytes)
{
	bool bResult = false;
	int nActualBytesRead = 0;
	int nSelectRet = 0; 

	if(m_nSocketFD > -1 && pcData != nullptr && nSize > 0)
	{
		//Check if we need to read exact bytes or available bytes.
		if(bReadExactBytes == true)
		{
			//Read exact bytes.
			bResult = readExactBytes(pcData,nSize);
		}
		else
		{
			//Check if data is available on socket and then only go and read it.
			nSelectRet = waitOnSelect(MAX_DIG_SOCKET_READ_WAIT_TIME, true);
			if(nSelectRet == 0) 
			{
				//timeout!
				LOGERR((char *)"DIGClient: receiveDataFromDIGServer: select timeout",0,0,0);
			}
			else if(nSelectRet < 0) 
			{
				//error!
				LOGERR((char *)"DIGClient: receiveDataFromDIGServer: select error",0,0,0);
			}
			else
			{	
				//Read available bytes.
				nActualBytesRead = recv(m_nSocketFD,pcData,nSize,0);
				if (nActualBytesRead <= 0)
				{
					LOGERR((char *)"DIGClient: receiveDataFromDIGServer: recv error: nActualBytesRead: %d",nActualBytesRead,0,0);
				}
				else
				{
					bResult = true;
				}
			}
		}
	}
	else
	{
		LOGERR((char *)"DIGClient: receiveDataFromDIGServer: connection not established/connection closed to DIG Server or null pointer passed to receiveDataFromDIGServer or invalid data size passed to receiveDataFromDIGServer",0,0,0);
	}

	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Read Exact Bytes from socket
*
* \param:
* pcData: Data will be received inside this buffer
* nSize: Buffer size
*
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::readExactBytes(char *pcData, const int nSize)
{
	bool bResult = false;
	bool bErrorOccured = false;
	int nTotalBytesReceived = 0; 
	int nActualBytesRead = 0;
	int nSelectRet = 0;
	int nBytesLeftToReceive = nSize;
	
	if(m_nSocketFD > -1 && pcData != nullptr && nSize > 0)
	{
		//Loop to receive complete data.
		while(nTotalBytesReceived < nSize) 
		{
			nSelectRet = waitOnSelect(MAX_DIG_SOCKET_READ_WAIT_TIME, true);
			if(nSelectRet == 0) 
			{
				//timeout!
				LOGERR((char *)"DIGClient: readExactBytes: select timeout",0,0,0);
				bErrorOccured = true;
				break;
			}
			else if(nSelectRet < 0) 
			{
				//error!
				LOGERR((char *)"DIGClient: readExactBytes: select error:%d",nSelectRet,0,0);
				bErrorOccured = true;
				break;
			}
			else
			{
				//Data available, read it.
				nActualBytesRead = recv(m_nSocketFD,pcData+nTotalBytesReceived,nBytesLeftToReceive,0);
				if (nActualBytesRead <= 0)
				{
					LOGERR((char *)"DIGClient: readExactBytes: recv error,nActualBytesRead: %d",nActualBytesRead,0,0);
					bErrorOccured = true;
					break;
				}
				else
				{
					if(nActualBytesRead != nSize)
					{
						LOGINFO((char *)"DIGClient: readExactBytes, Receiving data in multiple go, nActualBytesRead: %d, Expected bytes to receive were nSize: %d",nActualBytesRead,nSize,0);
					}
				}
				
				nTotalBytesReceived += nActualBytesRead;
				nBytesLeftToReceive -= nActualBytesRead;
			}
		}//end of while(nTotalBytesReceived < nSize) 
		
		if(nTotalBytesReceived != nSize || bErrorOccured == true)
		{
			LOGERR((char *)"DIGClient: readExactBytes error, nTotalBytesReceived: %d, nBytesLeftToReceive: %d, Expected bytes to receive were nSize: %d",nTotalBytesReceived,nBytesLeftToReceive,nSize);
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		LOGERR((char *)"DIGClient: readExactBytes: connection not established/connection closed to DIG Server or null pointer passed to readExactBytes or invalid data size passed to readExactBytes",0,0,0);
	}
	
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Wait For Connect
*
* \param   - none
*
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::waitForConnect()
{
	bool bResult = false;
	int	nValOpt = 0; 
	socklen_t Len = 0; 
	int nSelectReturn = 0;
	
	nSelectReturn = waitOnSelect(MAX_DIG_SOCKET_CONNECT_WAIT_TIME, false);
	if(nSelectReturn > 0)	
	{ 
		Len = sizeof(int); 
		getsockopt(m_nSocketFD, SOL_SOCKET, SO_ERROR, &nValOpt, &Len);
		//Get the Socket error status.
		if (nValOpt) 
		{
			LOGERR((char *)"DIGClient: waitForConnect: getsockopt error.",0,0,0);
		}
		else
		{
			bResult = true;
		}
	} 
	else if(nSelectReturn == 0)
	{ 
		//Wait time expired.
		LOGERR((char *)"DIGClient: waitForConnect: select timeout",0,0,0);
	} 
	else
	{
		LOGERR((char *)"DIGClient: waitForConnect: select error:%d",nSelectReturn,0,0);
	}
	
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Wait On Select
*
* \param:
*  nTimeOut - Timeout Value in seconds 
* bReadFd - set to true for ReadFds and false for WriteFds
* \return  - select status
*
******************************************************************************/
int DIGClient::waitOnSelect(int nTimeOut, bool bReadFd)
{
	int nSelectReturn = -1;
	struct timeval stTimeout; 
	fd_set fdset; 
	
	//Specify the time to wait before getting timeout.
	stTimeout.tv_sec  = nTimeOut; 
	stTimeout.tv_usec = 0; 
	
	FD_ZERO(&fdset); 
	FD_SET(m_nSocketFD, &fdset); 
	
	if(bReadFd == true)
	{
		nSelectReturn = select(m_nSocketFD+1, &fdset, NULL, NULL, &stTimeout);
	}
	else
	{
		nSelectReturn = select(m_nSocketFD+1, NULL, &fdset, NULL, &stTimeout);
	}
	
	if(nSelectReturn == 0)
	{ 
		//Wait time expired.
		LOGERR((char *)"DIGClient: waitOnSelect: select timeout",0,0,0);
	} 
	else if(nSelectReturn < 0)
	{
		LOGERR((char *)"DIGClient: waitOnSelect: select error:%d",nSelectReturn,0,0);
	}
	
	return nSelectReturn;
}

/**************************************************************************//**
* 
* \brief   - Get CPSW1/DIG Client IP Address and Port Number
*
* \param:
*pairDIGIPAddressAndPort: DIG Client IP Address and Port Number is stored in it.
* 
* \return  - true on success else false
*
******************************************************************************/
bool DIGClient::getCPSW1IPAddressAndPort(std::pair<std::string, int> &pairDIGIPAddressAndPort)
{
	bool bResult = false;
	int nUserChoice = getCPSW1IPChoiceEnum();
	for (auto itr = g_mapOfDIGClientIPAddressAndPort.find(nUserChoice); itr != g_mapOfDIGClientIPAddressAndPort.end(); itr++) 
	{
       	if(itr->first == nUserChoice)
       	{
       		bResult = true;
       		pairDIGIPAddressAndPort = itr->second;
       		break;
       	}
   	}
   	return bResult;
}

/**************************************************************************//**
* 
* \brief   - Get CPSW1/DIG Client IP Address choice Enum
*
* \param: none
*
* 
* \return  - the IP address choice enum value stored in database/EEPROM for CPSW1
*
******************************************************************************/
int DIGClient::getCPSW1IPChoiceEnum()
{
	int nIpChoiceEnum = 0;

	//TO_BE_DONE
	//Add logic to fetch CPSW1 IP address choice enum value set by user from HMI.
	//e.g. We can save the DIG Client IP address choice enum in database (sample_common.db)/EEPROM.
	//The enum is mapped to g_mapOfDIGClientIPAddressAndPort from which we can return the corresponding IP address and port number pair.
	
   	return nIpChoiceEnum;
}


/**************************************************************************//**
* 
* \brief   - DIG client task entry point
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void* DIGClient::Socket_DIG_Task(void *)
{	
	const std::string strMessagetoDIGServer = "Hello From Socket_DIG_Task";
	bool bIsConnectionEstablished = false;
	char szReceiveBuffer[20] = {0};
	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[DIG_SOCKET_T], taskIdSelf());

	DIGClient objDIGClient;

	while(objDIGClient.bIsTaskRunStatus())
	{	
		//Connect to DIG Server first time or if error occurs/Connection lost.
		if(bIsConnectionEstablished == false)
		{	
			do
			{
				if( objDIGClient.connectToDIGServer() != true)
				{
					bIsConnectionEstablished = false;
				}
				else
				{
					bIsConnectionEstablished = true;			
				}
				
				//wait for some time and try to connect again.
				if(bIsConnectionEstablished == false)
				{
					taskDelay(FIVE_SEC_DELAY);
				}
				
			}while(bIsConnectionEstablished == false);
		}

		//Proceed ahead with data exchange once the connection with DIG is successful.
		
		//Send data to DIG server.
		if(objDIGClient.sendDataToDIGServer((char *) strMessagetoDIGServer.c_str(), strlen(strMessagetoDIGServer.c_str())) != true)
		{
			LOGERR((char *)"Socket_DIG_Task: sendDataToDIGServer failure.",0,0,0);
			bIsConnectionEstablished = false;
		}
		else
		{
			LOGINFO((char *)"Socket_DIG_Task: sendDataToDIGServer: success",0,0,0);
			//Receive data from DIG server.
			memset(szReceiveBuffer, 0x00, sizeof(szReceiveBuffer));
			if (objDIGClient.receiveDataFromDIGServer(szReceiveBuffer, sizeof(szReceiveBuffer), true) != true)
			{
				LOGERR((char *)"Socket_DIG_Task: receiveDataFromDIGServer failure.",0,0,0);
				bIsConnectionEstablished = false;
			}
			else
			{
				LOGINFO((char *)"Socket_DIG_Task: Received Data From DIG Server:",0,0,0);
				//TO_BE_DONE - remove this test code that prints received message 
				for (int nIndex = 0; nIndex < sizeof(szReceiveBuffer); nIndex++)
				{
					printf("%u ", szReceiveBuffer[nIndex]);				    
				}
				printf("\n");
			}							
		}
		
		//wait for some time and repeat send/receive data.
		taskDelay(HALF_SEC_DELAY);
			
	}//end of while(pobjDIGClient->bIsTaskRunStatus())
	
	LOGERR ((char *) "Socket_DIG_Task: Exiting.", 0, 0, 0);
	return nullptr;
}
