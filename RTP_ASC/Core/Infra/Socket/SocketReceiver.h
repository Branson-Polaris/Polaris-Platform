/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/


#ifndef SOCKETRECEIVER_H_
#define SOCKETRECEIVER_H_

#include "Common.h"
#include "CommonProperty.h"
#include "MainTask.h"
#include "EmrsnSocket.h"
#include "SCTask.h"

#define SOCKET_RETRY_ATTEMPT	2

class SocketReceiver : public SCTask
{
public:
	SocketReceiver() {
		
	};
	
	~SocketReceiver() {}

	virtual void	ProcessTaskMessage	(Message& SockMsg) = 0;
	void 			MessageDeCoder		(INT32 iMsgId, UINT32 iLen, const char *RecvBuffer, Client_Message& SockMsg);
	UINT32 			MessageCRCCal 		(Client_Message& message);
	void			LogSocketLostAlarm	();
	
protected:
	void 			SendEvent			(TASK_ID &tid, INT32 evt);

	Client_Message  Client;
	
};

/*
 * HMi socket receiver extension
 */  
class HMI_SocketReceiver : public SocketReceiver
{
public:
	bool				m_bIsFWTask;
	char 				m_RecvBuffer[MAX_SIZE_OF_MSG_LENGTH];
	int 				m_RecvBufLen;
	Message 			m_InternalMsg;
	Client_Message		m_SocketMsg;

	HMI_SocketReceiver();
	~HMI_SocketReceiver();
	
	static 			void * Socket_HMI_Task		(void *);
	void 			ProcessTaskMessage			(Message& SockMsg);
	void 			CloseClientConnection		(Message& sockMsg);
	
	static bool 	SendMessageToClient			(const Client_Message* ptrMsg, const UINT32 SockMsgLen);
	bool			TCPIPSocketEstablishing		();
	bool			SSLServerEstablishing		();
	bool			parseProtocolPackage		(const char* inBuffer, const int inBufferLen, Client_Message* ptrMsg);
private:
	void 			setHMILoginStatus			(char *buff);
	void			SendHeartBeatResponse		();
	static int		buildProtocolPackage		(const Client_Message* ptrMsg, char* outBuffer); 
	PowerUpData			PowerUpRecipe;
	bool				m_bFWTask;
};


/*
 * Actuator socket receiver extension
 */  
class ACT_SocketReceiver : public SocketReceiver
{
public:
	ACT_SocketReceiver();
	~ACT_SocketReceiver();
	
	static 			void* Socket_ACT_Task		(void *);

	void 			ProcessTaskMessage			(Message& SockMsg);
	void			CloseClientConnection		(INT32 fdClienSocket);
	void 			SetActConnected				(bool status);
	
private:
	int 			SendMessageToClient			(Client_Message& SendBuffer,UINT32 SockMsgLen);
	UINT32          cycleNum;
};

#endif /* SOCKETRECEIVER_H_ */
