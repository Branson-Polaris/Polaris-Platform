/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#include "EmrsnSocket.h"
#include <fstream>
#include <stdlib.h>
#include "SocketReceiver.h"
#include "CommunicationInterface.h"
#include "CommunicationInterface_ACT.h"
#include "CommonProperty.h"

ACT_SocketReceiver::ACT_SocketReceiver()
{
}

ACT_SocketReceiver::~ACT_SocketReceiver()
{
}

/**************************************************************************//**
* 
* \brief   - Process the incoming message received from client socket
* 			of the actuator:
* 			Client_Message
* 			 
* 			____________________________________________________________________
* 			|                                                                   |
* 			|UINT32	msgID | UINT32  msglen | 		char	Data				|	
* 			|___________________________________________________________________|
* 			
* \param   - Message& SockMsg
*
* \return  - None
*
******************************************************************************/
void ACT_SocketReceiver::ProcessTaskMessage(Message& SockMsg)
{
	switch(SockMsg.msgID)
	{
	case TO_ACT_SYSTEM_TASK_WELD_RECIPE_RESP:
		// ack weld recipe and reload
//	case TO_ACT_SYSTEM_TASK_ALARM_DATA_RESP:
//		// send back alarm data
	case TO_ACT_SYSTEM_TASK_VERSION_SERIAL_RESP:
		// send back version and other hard data
	case TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_RESP:
//	case TO_ACT_SYSTEM_TASK_CAL_DATA__RESP:
//		// ack calibration data
//	case TO_ACT_SYSTEM_TASK_CAL_READ_RESP:
		// send calibration data
		SendToMsgQ (SockMsg, CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[ACTUATOR_SYSTEM_T]));		
		break;
		
	case TO_ACT_PROCESS_TASK_TX_DATA:
		// send actuator data forward
		SendToMsgQ (SockMsg, CP->GetMsgQId(CommonProperty::cTaskName[ACTUATOR_PROCESS_T]));
		
		break;
			
	default:
		break;
	};
}
/**************************************************************************//**
* 
* \brief   - Closes the client socket descriptor and stops the system cycle
*
* \param   - INT32 fdClienSocket
*
* \return  - None
*
******************************************************************************/
void ACT_SocketReceiver::CloseClientConnection(INT32 fdClienSocket)
{
	close(fdClienSocket);
	SetActConnected(false);

	LOGERR((char *)(char *)"ACTSocket_T: CloseClientConnection: Client socket connection closed and waiting for client request",0,0,0);
}
/**************************************************************************//**
* 
* \brief   - Sets bActConnected flag in common property to true. Used as
*			an indicator whether or not the actuator is physically connected
*			and can at this point get preliminary data such as version and serial
*			number among other things
*
* \param   - bool status
*
* \return  - None
*
******************************************************************************/
void ACT_SocketReceiver::SetActConnected(bool status)
{
	Message message;

	CP->bActConnected = status;
	
	if (CP->bActConnected == true)
	{
		// do basics upon connection or re-connection here
		message.msgID = TO_ACT_SYSTEM_TASK_VERSION_SERIAL_REQ;
		SendToMsgQ(message, CP->GetMsgQId(CommonProperty::CommonProperty::cTaskName[ACTUATOR_SYSTEM_T]));
	}
	else
	{
		// do basics upon disconnection here
		CP->bActSrNoVerNoReceived = false;
	}
}

/**************************************************************************//**
* 
* \brief   - Sends the message to client
*
* \param   - Client_Message& SendBuffer
* 			 UINT32 SockMsgLen
*
* \return  - int bytesSent
*
******************************************************************************/
int ACT_SocketReceiver::SendMessageToClient(Client_Message &SendBuffer,UINT32 SockMsgLen)
{
	char outBuf[MAX_SIZE_OF_MSG_LENGTH]	= {0x00};
	UINT32 bufLen= 0;
	int bytesSent = ERROR;
		
	CommunicationInterface *InterfaceObject = ACT_CommunicationInterface::getinstance();
	
	if(SockMsgLen >= MAX_SIZE_OF_MSG_LENGTH)
	{
		LOGERR((char *)"ACTSocket_T : SendMessageToClient, Socket message length exceeded : %d",SockMsgLen, 0, 0);
	}
	else
	{
		SendBuffer.crc32 =  MessageCRCCal(SendBuffer);
		
		bufLen += (sizeof(SendBuffer.msgID)+sizeof(SendBuffer.msgLen));
		memcpy(outBuf, &SendBuffer, bufLen);
		
		memcpy(outBuf+bufLen, SendBuffer.Buffer, SendBuffer.msgLen);
		bufLen += SendBuffer.msgLen;
		
		memcpy(outBuf+bufLen, &SendBuffer.crc32, sizeof(SendBuffer.crc32));
		bufLen += sizeof(SendBuffer.crc32);
		
		bytesSent = InterfaceObject->Send(reinterpret_cast<char*>(outBuf),bufLen);
	
		if (bufLen != bytesSent)
			LOGERR((char *)"ACT_SocketReceiver: SendMessageToClient: ReqLen: %d bytesSent: %d",bufLen, bytesSent, 0);
	}
	
	return bytesSent;
}


/**************************************************************************//**
* 
* \brief   - Socket receiver task entry point
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void* ACT_SocketReceiver::Socket_ACT_Task(void *)
{
	INT32  iPort		= AC_SOCKET_PORT;
	INT32  iMsgId		= 0;
	UINT32  iLen		= 0;
	INT32  Client_SockId= 0;
	INT32  iRetVal		= 0;
	UINT32 timeOutCount = 0;
	char MsgIdLen[8]	= {0x00};
	char RecvBuffer[MAX_SIZE_OF_MSG_LENGTH-8]	= {0x00};	
	Client_Message SockMsg;
	Message SendMsg;
	EmrsnSocket socket;
	bool bOk;
	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[ACT_SOCKET_T], taskIdSelf());

	ACT_SocketReceiver* pSocketReceiver = new(nothrow) ACT_SocketReceiver();
	
	//Server is connecting with the new client 
	CommunicationInterface *InterfaceObject = ACT_CommunicationInterface::getinstance();
	
	if(NULL != pSocketReceiver)
	{
		bOk = socket.Create();
		if(bOk)
		{
			LOG("\nACTSocket_T: Socket create: OK\n");
		}
		
		socket.Bind(iPort);
		
		bOk = socket.Listen();
		
		if(!bOk)
		{
			LOGERR((char *)"ACTSocket_T: socket listen failed",0,0,0);
		}
		else
		{
			LOG("\nACTSocket_T: socket listen: OK\n");
		}
		
		// stay in accept mode until proper connection or error 
		do {
			Client_SockId = socket.Accept(ACT_SOCKET_CONNECTION);
		}
		while ((INT32 *)Client_SockId == NULL);

		if(Client_SockId != ERROR)
		{
			InterfaceObject->dwsock 		= Client_SockId;
			InterfaceObject->msockaddr_in 	= socket.msockaddr_in;
			InterfaceObject->bServer 		= socket.bServer;
			pSocketReceiver->SetActConnected(true);
			// actuator ready indication to UIC here...
			
			LOG("\nACTSocket_T: socket connection established (1)\n");
		}

		while (pSocketReceiver->bIsTaskRunStatus()) 
		{
			/* Each count is equal to 3 seconds, On 3rd count, closes the client connection and accepts new. 
			 * Condition will be executed only when connection time out between client and server */
			if(timeOutCount > SOCKET_RETRY_ATTEMPT)
			{
				timeOutCount 	= 0;
				iRetVal 		= ERROR;
				
				pSocketReceiver->LogSocketLostAlarm();
				LOGERR((char *)"ACTSocket_T : Heart beat not received from client or socket connection lost",0,0,0);
			}
			else
			{
				memset (RecvBuffer,0x00,sizeof(RecvBuffer));
				memset (MsgIdLen,0x00,sizeof(MsgIdLen));
				memset (SockMsg.Buffer,0x00,sizeof(SockMsg.Buffer));
				
				iRetVal = InterfaceObject->ReadExact (MsgIdLen,sizeof(MsgIdLen));
			}
			
			if(ERROR == iRetVal)
			{
				pSocketReceiver->CloseClientConnection (Client_SockId);
				Client_SockId = 0;
				
				// stay in accept mode until proper connection or error
				do {
					Client_SockId = socket.Accept(ACT_SOCKET_CONNECTION);
				}
				while ((INT32 *)Client_SockId == NULL);
				
				timeOutCount  = 0;

				if(Client_SockId != ERROR)
				{
					/* Server is connecting with the new client */ 
					CommunicationInterface *InterfaceObject = ACT_CommunicationInterface::getinstance();
					InterfaceObject->dwsock 		= Client_SockId;
					InterfaceObject->msockaddr_in 	= socket.msockaddr_in;
					InterfaceObject->bServer 		= socket.bServer;
					pSocketReceiver->SetActConnected(true);
					
					LOG("\nACTSocket_T: socket connection established (2)\n",Client_SockId);
				}
			}
			else if(0 == iRetVal)
			{
				/* Socket read time out and polling to read */
				timeOutCount = timeOutCount + 1;
			}
			else
			{
				timeOutCount  = 0;

				// get the message ID and length from the header
				memcpy(&iMsgId, MsgIdLen, sizeof(iMsgId));
				memcpy(&iLen, MsgIdLen + sizeof(iMsgId), sizeof(iLen));	

				if(iLen < 0)
				{
					LOGERR((char *)"ACTSocket_T : Invalid message received: MsgID: %d", iMsgId, 0, 0);
				}
				else
				{
				 	iRetVal = InterfaceObject->ReadExact(RecvBuffer,iLen+sizeof(SockMsg.crc32));

					if(ERROR == iRetVal)
				 	{
				 		pSocketReceiver->CloseClientConnection(Client_SockId);
				 		Client_SockId = 0;
				 		timeOutCount  = 0;
				 	}
				 	else
				 	{
				 		pSocketReceiver->MessageDeCoder(iMsgId,iLen,RecvBuffer,SockMsg);
				 		
				 		if(SockMsg.crc32 == pSocketReceiver->MessageCRCCal(SockMsg))
				 		{
				 			memcpy(&SendMsg.msgID, &SockMsg.msgID, sizeof(SendMsg.msgID));
							memcpy(&SendMsg.Buffer, &SockMsg.Buffer, sizeof(SendMsg.Buffer));
							pSocketReceiver->ProcessTaskMessage(SendMsg);
						}
						else
							LOGERR((char *)"ACTSocket_T : Invalid message received (CRC Error): MsgID: %d", iMsgId, 0, 0);
				 	}
				}
			}
		}
		
		delete pSocketReceiver;
	}
	else
	{
		LOGERR((char *)"ACTSocket_T: -------Memory allocation failed-----------",0,0,0);
	}
	
	pSocketReceiver = NULL;
	return nullptr;
}
