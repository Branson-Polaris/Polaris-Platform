/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------        
 
***************************************************************************/
#include "EmrsnSocket.h"
#include <fstream>
#include "SocketReceiver.h"
#include "CommunicationInterface.h"
#include "CommunicationInterface_HMI.h"
#include "ControlTask.h"
#include "CommonProperty.h"
#include "QuickCRC32Algorithm.h"
#include "SC.h"


/**************************************************************************//**
* \brief    - SocketReciever Class constructor
*
* \param    - None
*
* \return   - None
*
******************************************************************************/
HMI_SocketReceiver::HMI_SocketReceiver() 
{
	CommonProperty 	*CP = CommonProperty::getInstance();	
}


/**************************************************************************//**
* 
* \brief   - Process the incoming message received from Client Socket
*
* \param   - Message& SockMsg.
*
* \return  - None
*
******************************************************************************/
void HMI_SocketReceiver::ProcessTaskMessage(Message& SockMsg)
{
	switch(SockMsg.msgID)
	{
		case SCBL_HEART_BEAT_REQ:
			SendHeartBeatResponse();
			break;
			
		case SCBL_SYSINFO_READ_REQ:
			SendToMsgQ (SockMsg, CP->GetMsgQId(CommonProperty::cTaskName[UI_T]));
			break;	

		case SCBL_SYSINFO_WRITE_REQ:
			SockMsg.msgID = TO_UI_TASK_SYS_INFO_WRITE_REQ;
			SendToMsgQ (SockMsg, CP->GetMsgQId(CommonProperty::cTaskName[UI_T]));
			break;	

		case SCBL_WELDRECIPE_REQ:
			SockMsg.msgID = TO_UI_TASK_WELD_RECIPE;
			SendToMsgQ (SockMsg, CP->GetMsgQId(CommonProperty::cTaskName[UI_T]));
			break;

		default:

			break;
	}
}

/**************************************************************************//**
* 
* \brief   - Sends the message to client
*
* \param   - Client_Message& SendBuffer,UINT32 SockMsgLen
*
* \return  - boolean socket data sending status 
*
******************************************************************************/
bool HMI_SocketReceiver::SendMessageToClient(const Client_Message* ptrMsg, const UINT32 SockMsgLen)
{
	int bytesSent = 0;
	char onePackageBuffer[MAX_SIZE_OF_MSG_LENGTH]= {0x00};
	int bufferLen = 0;
	HMI_CommunicationInterface* _ptrSocketObj = HMI_CommunicationInterface::getInstance();
	bool bSocketSendResponse = false;
	

	if(SockMsgLen >= MAX_SIZE_OF_MSG_BUFF)
	{
		LOGERR( (char *)"HMISocket_T : SendMessageToClient, Socket message length exceeded : %d",SockMsgLen, 0, 0);
	}
	else
	{
		bufferLen = buildProtocolPackage(ptrMsg, onePackageBuffer);
//		bytesSent = InterfaceObject->Send(reinterpret_cast<char*>(outBuf),bufLen);
		bytesSent = _ptrSocketObj->SSL_Send(onePackageBuffer, bufferLen);	
		if(bytesSent > 0)
			bSocketSendResponse = true;
	}
	
	return bSocketSendResponse;
}


/**************************************************************************//**
* 
* \brief   - Closes the client socket descriptor and stops the system cycle
*
* \param   - INT32 fdClienSocket
* \param   - Message& sockMsg
*
* \return  - None
*
******************************************************************************/
void HMI_SocketReceiver::CloseClientConnection(Message& sockMsg)
{
	HMI_CommunicationInterface::getInstance()->SSL_Reset();
	close(HMI_CommunicationInterface::getInstance()->m_SocketConnectedDescriptor);
	HMI_CommunicationInterface::getInstance()->Close();

	CP->bUIConnected = false;

	if (!CommonProperty::getInstance()->bWebServicesLogged)
	{
		/* When client socket closed(UIC) then SC-BL changes to NO_OPERATION operation type */
		UINT8 opType = NO_OPERATION;
		memset(sockMsg.Buffer,0x00,sizeof(sockMsg.Buffer));
		/* TODO(Evan-Socket): Implement the Client_Message Later */
		sockMsg.msgID = SCBL_SET_NEXT_OPERATION_REQ;
		memcpy(sockMsg.Buffer, &opType, sizeof(opType));
		ProcessTaskMessage(sockMsg);
	}

	LOGERR((char *)"HMISocket_T: CloseClientConnection: Client socket connection closed and waiting for client request",0,0,0);
}

/**************************************************************************//**
* 
* \brief   - Sends response to UIC for heart beat request with parts  per minute
* 			 counter. 
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void HMI_SocketReceiver::SendHeartBeatResponse()
{
	CP->bUIConnected = true;
	UINT32 bufLen= 0, position = 0;
	char outBuf[MAX_SIZE_OF_MSG_LENGTH]	= {0x00};
	
	Client_Message sendMsg;
	memset(sendMsg.Buffer, 0x00, sizeof(sendMsg.Buffer));
	
	sendMsg.msgID 	= UIC_HEART_BEAT_RES;
	sendMsg.msgLen 	= 0;
	sendMsg.rspCode = 0;
	
#if SOCKET_DBG
	RTCtimerStr rtcTime;	
	static UINT32 cycleNum;
	UINT32 activeRecipeNum = cycleNum;
	UINT32 alarmID = cycleNum;
	UINT32 cycleTime = cycleNum;
	GetRTC(&rtcTime);
	UINT32 powerValue = rtcTime.tm_sec;
	cycleNum++;
#else
	UINT32 cycleNum = ControlTask::GetCycleCounter();
	UINT32 activeRecipeNum = 0;
	UINT32 alarmID = 0;
	UINT32 powerValue = 0;
	UINT32 cycleTime = SC::stateMachine->CycleTime();
#endif
	
	memcpy(sendMsg.Buffer + position, &cycleNum, sizeof(UINT32));
	position += sizeof(UINT32);
	memcpy(sendMsg.Buffer + position, &activeRecipeNum, sizeof(UINT32));
	position += sizeof(UINT32);
	memcpy(sendMsg.Buffer + position, &alarmID, sizeof(UINT32));
	position += sizeof(UINT32);
	memcpy(sendMsg.Buffer + position, &powerValue, sizeof(UINT32));
	position += sizeof(UINT32);
	memcpy(sendMsg.Buffer + position, &cycleTime, sizeof(UINT32));
	position += sizeof(UINT32);
	sendMsg.msgLen = position;
	
	SendMessageToClient(&sendMsg, sendMsg.msgLen);
}

/**************************************************************************//**
* 
* \brief   - package building for the incoming message
*
* \param   - Client_Message* ptrMsg. outBuffer
*
* \return  - outBuffer length
*
******************************************************************************/
int HMI_SocketReceiver::buildProtocolPackage(const Client_Message* ptrMsg, char* outBuffer)
{
	char onePackageBuffer[MAX_SIZE_OF_MSG_LENGTH]= {0x00};
	UINT32 crcResult= 0, bufLen= 0, msgLen = 0;

	if((ptrMsg == NULL) || (outBuffer == NULL))
		return 0;
	
	memcpy(onePackageBuffer, &ptrMsg->msgID, sizeof(ptrMsg->msgID));
	bufLen += sizeof(ptrMsg->msgID);
	
	msgLen = sizeof(ptrMsg->rspCode) + ptrMsg->msgLen;
	memcpy(onePackageBuffer + bufLen, &msgLen, sizeof(ptrMsg->msgLen));
	bufLen += sizeof(ptrMsg->msgLen);
	
	memcpy(onePackageBuffer + bufLen, &ptrMsg->rspCode, sizeof(ptrMsg->rspCode));
	bufLen += sizeof(ptrMsg->rspCode);
	
	memcpy(onePackageBuffer + bufLen, ptrMsg->Buffer, ptrMsg->msgLen);
	bufLen += ptrMsg->msgLen;
	
	crcResult = QuickCRC32Algorithm::crc32_ccitt(onePackageBuffer, bufLen);
	
	memcpy(onePackageBuffer + bufLen, &crcResult, sizeof(crcResult));
	bufLen += sizeof(crcResult);
	
	memcpy(outBuffer, onePackageBuffer, bufLen);
	
	return bufLen;
}

/**************************************************************************//**
* 
* \brief   - This method is used to parse the received data 
* 			 and check if the received data has the integrated package. 
*            
* \param   - Input variable: const char* inBuffer, const int inBufferLen,
* 			 Output variable: Client_Message *ptrMsg 
*
* \return  - return bResult
*
******************************************************************************/
bool HMI_SocketReceiver::parseProtocolPackage(const char* inBuffer, const int inBufferLen, Client_Message* ptrMsg)
{
	bool bResult = false;
	int offset = 0, len = 0;
	memcpy(&ptrMsg->msgID, inBuffer, sizeof(UINT32));
	offset += sizeof(UINT32);
	len += sizeof(UINT32);
	if(offset > inBufferLen)
		return false;
	
	memcpy(&ptrMsg->msgLen, inBuffer + offset, sizeof(UINT32));
	offset += sizeof(UINT32);
	len += sizeof(UINT32);
	if(offset > inBufferLen)
		return false;
	
	memcpy(ptrMsg->Buffer, inBuffer + offset, ptrMsg->msgLen);
	offset += ptrMsg->msgLen;
	len += ptrMsg->msgLen;
	if(offset > inBufferLen)
		return false;
	
	memcpy(&ptrMsg->crc32, inBuffer + offset, sizeof(UINT32));
	
	if(ptrMsg->crc32 == QuickCRC32Algorithm::crc32_ccitt(inBuffer, len))
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - TCP/IP socket link establishing. 
*            
* \param   - none
*
* \return  - return bResult
*
******************************************************************************/

bool HMI_SocketReceiver::TCPIPSocketEstablishing()
{
	INT32 iPort = HMI_SOCKET_PORT;
	bool bResult = false;
	HMI_CommunicationInterface* _ptrSocketObj = HMI_CommunicationInterface::getInstance();

	if(_ptrSocketObj->Create() == false)
	{
		LOGINFO((char *)"HMISocket_T: Socket creation failed", 0, 0, 0);
		return false;
	}

	if(_ptrSocketObj->Bind(iPort) == false)
	{
		LOGINFO((char *)"HMISocket_T: socket binding failed", 0, 0, 0);
		return false;
	}
	
	if(_ptrSocketObj->Listen() == false)
	{
		LOGERR((char *)"HMISocket_T: socket listen failed", 0, 0, 0);
		return false;
	}
	
	LOG("\nHMISocket_T: socket listening on Port: %d\n", iPort, 0, 0);

	// stay in accept mode until proper connection or error 
	_ptrSocketObj->m_SocketConnectedDescriptor = _ptrSocketObj->Accept(HMI_SOCKET_CONNECTION);
	
	if(_ptrSocketObj->m_SocketConnectedDescriptor == ERROR)
	{
		LOGERR((char *)"HMISocket_T: Error on socket accept",0,0,0);
		bResult = false;
	}
	else
	{
		LOGINFO((char *) "HMISocket_T: socket connection established, Client_SockId: %d\n", _ptrSocketObj->m_SocketConnectedDescriptor, 0, 0);
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - SSL link establishing that should include Creating, Binding and Accept three processes.
*            
* \param   - none
*
* \return  - If there is anyone process is false, it will return false.
*
******************************************************************************/

bool HMI_SocketReceiver::SSLServerEstablishing()
{
	HMI_CommunicationInterface* _ptrSocketObj = HMI_CommunicationInterface::getInstance();
	if(_ptrSocketObj->SSL_Create() == false)
		return false;
	if(_ptrSocketObj->SSL_Bind(_ptrSocketObj->m_SocketConnectedDescriptor) == false)
		return false;
	if(_ptrSocketObj->SSL_Accept() == false)
		return false;
	return true;
}

/**************************************************************************//**
* 
* \brief   - Set whether main HMI is logged in or not
*
* \param   - char *pRecv_Msg
*
* \return  - None
*
******************************************************************************/
void HMI_SocketReceiver::setHMILoginStatus(char *pRecv_Msg)
{
	UINT8 opStatus;
		
	memcpy(&opStatus, pRecv_Msg, sizeof(opStatus));
	
	CP->bHMILogged = (HMISTATUS)opStatus;
}


/**************************************************************************//**
* 
* \brief   - Socket receiver class destructor
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
HMI_SocketReceiver::~HMI_SocketReceiver()
{	
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
void* HMI_SocketReceiver::Socket_HMI_Task(void *)
{
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[HMI_SOCKET_T], taskIdSelf());

	HMI_CommunicationInterface* _ptrSocketObj = HMI_CommunicationInterface::getInstance();
	
	HMI_SocketReceiver* pSocketReceiver = new(nothrow) HMI_SocketReceiver();
	
	if(NULL == pSocketReceiver)
	{
		LOGERR((char *)"HMISocket_T: -------Memory allocation failed-----------", 0, 0, 0);
		return nullptr;
	}
	
	if(_ptrSocketObj->SSL_Init() == false)
	{
		LOGERR((char *)"HMISocket_T: -------Memory allocation failed-----------", 0, 0, 0);
		return nullptr;
	}
	
	while (pSocketReceiver->bIsTaskRunStatus()) 
	{
		switch(_ptrSocketObj->m_CommunicationStatus)
		{
		case HMI_CommunicationInterface::SOCKET_LINK:
			if(pSocketReceiver->TCPIPSocketEstablishing() == true)
				_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::SSL_LINK;
			else
				_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::ERROR_LINK;
			break;
		case HMI_CommunicationInterface::SSL_LINK:
			if(pSocketReceiver->SSLServerEstablishing() == true)
				_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::SSL_MESSAGE;
			else 
				_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::ERROR_LINK;
			break;
		case HMI_CommunicationInterface::SSL_MESSAGE:
			memset (pSocketReceiver->m_RecvBuffer, 0x00, sizeof(pSocketReceiver->m_RecvBuffer));
			memset (pSocketReceiver->m_SocketMsg.Buffer, 0x00, sizeof(pSocketReceiver->m_SocketMsg.Buffer));
			pSocketReceiver->m_RecvBufLen = _ptrSocketObj->SSL_Read(pSocketReceiver->m_RecvBuffer, sizeof(pSocketReceiver->m_RecvBuffer));
			
			if(pSocketReceiver->m_RecvBufLen > 0)
			{
				// get the message ID and length from the header
				if(pSocketReceiver->parseProtocolPackage(pSocketReceiver->m_RecvBuffer, pSocketReceiver->m_RecvBufLen, &pSocketReceiver->m_SocketMsg) == true)
				{
					pSocketReceiver->m_InternalMsg.msgID = pSocketReceiver->m_SocketMsg.msgID;
					memset(pSocketReceiver->m_InternalMsg.Buffer, 0x00, sizeof(pSocketReceiver->m_InternalMsg.Buffer));
					memcpy(pSocketReceiver->m_InternalMsg.Buffer, pSocketReceiver->m_SocketMsg.Buffer, pSocketReceiver->m_SocketMsg.msgLen);
					pSocketReceiver->ProcessTaskMessage(pSocketReceiver->m_InternalMsg);
				}
				else
					LOGERR((char *)"HMISocket_T : Invalid message received (CRC Error): MsgID: %d", pSocketReceiver->m_SocketMsg.msgID, 0, 0);
			}
			else
				_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::ERROR_LINK;
			break;
		default:
			pSocketReceiver->CloseClientConnection(pSocketReceiver->m_InternalMsg);
			_ptrSocketObj->m_CommunicationStatus = HMI_CommunicationInterface::SOCKET_LINK;
		}
	}
	
	delete pSocketReceiver;
	pSocketReceiver = NULL;
	LOGINFO ((char *) "HMISocket_T: Socket Receiver Task Terminated", 0, 0, 0);
	return nullptr;
}
