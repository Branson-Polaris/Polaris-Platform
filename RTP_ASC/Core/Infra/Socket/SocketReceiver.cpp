/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#include <fstream>

#include "QuickCRC32Algorithm.h"
#include "SocketReceiver.h"
//#include "AlarmManager.h"

using namespace std;

/**************************************************************************//**
* 
* \brief   - Decodes the incoming message received from Q
*
* \param   - INT32 MsgId, Command ID of Package
* 		   - Const char *RecvBuffer, Read buffer of Socket
* 		   - Client_Message& message, Parse the Receive buffer to Message
*
* \return  - None
*
******************************************************************************/
void SocketReceiver::MessageDeCoder (INT32 iMsgId , UINT32 iLen, const char *RecvBuffer, Client_Message& message) 
{	
	message.msgID = iMsgId;
	message.msgLen = iLen;
	
	memcpy(message.Buffer, RecvBuffer, iLen+sizeof(message.crc32));
	
	memcpy(&message.crc32, RecvBuffer+iLen, sizeof(message.crc32));
	
}

/**************************************************************************//**
* 
* \brief   - CRC32 Calculate for the incoming message
*
* \param   - Message& message.
*
* \return  - True or False
*
******************************************************************************/
UINT32 SocketReceiver::MessageCRCCal (Client_Message& message) 
{
	char crcBuffer[MAX_SIZE_OF_MSG_LENGTH+8]= {0x00};
	UINT32 crcResult= 0, bufLen= 0;

	memcpy(crcBuffer, &message.msgID, sizeof(message.msgID));
	bufLen += sizeof(message.msgID);
	
	memcpy(crcBuffer + bufLen, &message.msgLen, sizeof(message.msgLen));
	bufLen += sizeof(message.msgLen);
	
	if(message.msgLen != 0)
	{
		memcpy(crcBuffer + bufLen, message.Buffer, message.msgLen);
		bufLen += message.msgLen;
	}
	
	crcResult = QuickCRC32Algorithm::crc32_ccitt(crcBuffer, bufLen);

	return crcResult;
}

/**************************************************************************//**
* 
* \brief   - Log alarm when socket connection lost.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SocketReceiver::LogSocketLostAlarm()
{

}

/**************************************************************************//**
* 
* \brief   - Send events to consoleApp or MainTask
*
* \param   - TASK_ID& tid, INT32 evt
*
* \return  - None
*
******************************************************************************/
void SocketReceiver::SendEvent(TASK_ID &tid, INT32 evt)
{
	if(eventSend(tid,evt) != OK)
	{
		LOGERR((char *) "SocketReceiver::SendEvent: Event failed",0,0,0);
	}
}
