/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * SocketReceiver.c
 *
 *  Created on: Apr 23, 2021
 *      Author: Kakdu
 *
 *
*/

#include "TcpClient.h"
#include "string.h"
#include "SocketReceiver.h"
#include "Main.h"
#include "arch\sys_arch.h"



#include "global.h"
#include "../../../_Branson_User_Common/Commons/Commons.h"
#include "../../../_Branson_User_Common/Commons/version_common.h"

#if SOCKET_DEBUG
	extern unsigned int message_sendfailcount;
	extern long unsigned int message_recvcount;
#endif

extern void getpdo();
extern void ReadSerNoEEPROM(char *pdata);
extern void WriteSerNoEEPROM (char *pdata);
unsigned char version[32] = "Version01.01.01";

#define SYSTEM_INFO_SIZE 				20
static unsigned char RecvSystemInfoBuffer[SYSTEM_INFO_SIZE];


/**************************************************************************//**
 *
 * \brief   - Decodes the incoming message received from socket
 *
 * \param   - INT32 MsgId, Command ID of Package
 * 		   - Const char *RecvBuffer, Read buffer of Socket
 * 		   - Client_Message *SockMsg, Parse the Receive buffer to Message
 *
 * \return  - None
 *
 ******************************************************************************/
void MessageDeCoder(unsigned int iMsgId, unsigned int iLen, const char *RecvBuffer,
		struct Client_Message *SockMsg)
{
	SockMsg->msgID = iMsgId;
	SockMsg->msgLen = iLen;

	memcpy(SockMsg->Buffer, RecvBuffer, iLen); //+sizeof(SockMsg->crc32)
	memcpy(&SockMsg->crc32, RecvBuffer + iLen, sizeof(SockMsg->crc32));
}

/**************************************************************************//**
 *
 * \brief   - CRC32 Calculate for the incoming message
 *
 * \param   - struct Client_Message *SockMsg.
 *
 * \return  - CRC value
 *
 ******************************************************************************/
unsigned int MessageCRCCal(struct Client_Message *SockMsg)
{
	char crcBuffer[MAX_SIZE_OF_MSG_LENGTH + 8] =
	{ 0x00 };
	unsigned int crcResult = 0, bufLen = 0;

	memcpy(crcBuffer, &SockMsg->msgID, sizeof(SockMsg->msgID));
	bufLen += sizeof(SockMsg->msgID);

	memcpy(crcBuffer + bufLen, &SockMsg->msgLen, sizeof(SockMsg->msgLen));
	bufLen += sizeof(SockMsg->msgLen);

	if (SockMsg->msgLen != 0)
	{
		memcpy(crcBuffer + bufLen, SockMsg->Buffer, SockMsg->msgLen);
		bufLen += SockMsg->msgLen;
	}

	crcResult = crc32_ccitt(crcBuffer, bufLen);

	return crcResult;
}

/**************************************************************************//**
 *
 * \brief   - Process incoming message from ASC
 *
 * \param   - struct Client_Message *SockMsg
 *
 * \return  - None
 *
 ******************************************************************************/
void ProcessDatafromASC(struct Client_Message *SockMsg)
{
	switch(SockMsg->msgID)
	{
		case FROM_ASC_PROCESS_Rx_PDO_DATA:
			// process incoming actuator data
			ASCPdoDownloadRequest (SockMsg);
			break;

		case FROM_ASC_SYSTEM_VERSION_SERIAL_NO_REQ:
			// process incoming actuator data
			ASCSendSerNoVerNoResponse (SockMsg);
			break;

		case FROM_ASC_SYSTEM_SYSINFO_WRITE_REQ:
			// process incoming actuator data
			memcpy(&RecvSystemInfoBuffer, SockMsg->Buffer, SYSTEM_INFO_SIZE);
			break;

		default:
			break;
	};

}

/**************************************************************************//**
 *
 * \brief   - Download and copy the Rxpdo data received from ASC
 *
 * \param   - Message& message.
 *
 * \return  - None
 *
 ******************************************************************************/
void ASCPdoDownloadRequest(struct Client_Message *SockMsg)
{
	memcpy(&rxpdoac, SockMsg->Buffer, sizeof(RxPDO_AC));
	// when actuator data received and stored report it as HB
	ProcessDatatoASC(SockMsg->msgID);
}

/**************************************************************************//**
 *
 * \brief   - Send AC version and serial no to ASC
 *
 * \param   - Message& message.
 *
 * \return  - None
 *
 ******************************************************************************/
void ASCSendSerNoVerNoResponse(struct Client_Message *SockMsg)
{
	ProcessDatatoASC(SockMsg->msgID);
}
/**************************************************************************//**
 *
 * \brief   - Process the outgoing data to be sent to ASC
 *
 * \param   - None.
 *
 * \return  - None
 *
 ******************************************************************************/
void ProcessDatatoASC(unsigned int MsgId)
{
	Client_Message sendMsg;
	int err = 0;

	memset(sendMsg.Buffer, 0x00, sizeof(sendMsg.Buffer));

	//stubbing txpdoac values for testing;
#if SOCKET_DEBUG
//	txpdoac.ACInputs = rxpdoac.SCState;
//	txpdoac.ActualForce = rxpdoac.SCState;
//	txpdoac.ActualDistance = rxpdoac.SCState;
//	txpdoac.ACStatusEvent = rxpdoac.SCState;
//	txpdoac.ACState = message_sendfailcount;
#endif

	switch(MsgId)
	{
		case FROM_ASC_PROCESS_Rx_PDO_DATA:
			sendMsg.msgID = TO_ASC_PROCESS_TX_PDO_DATA;
			memcpy(sendMsg.Buffer, &txpdoac, sizeof(TxPDO_AC));
			sendMsg.msgLen = sizeof(TxPDO_AC);
			break;

		case FROM_ASC_SYSTEM_SYSINFO_WRITE_REQ:
			sendMsg.msgID = TO_ASC_SYSTEM_SYSINFO_WRITE_RESP;
			WriteSerNoEEPROM((char *)&RecvSystemInfoBuffer);
			ReadSerNoEEPROM((char *)&sendMsg.Buffer);
			sendMsg.msgLen = strlen(sendMsg.Buffer);
			break;

		case FROM_ASC_SYSTEM_VERSION_SERIAL_NO_REQ:
			sendMsg.msgID = TO_ASC_SYSTEM_VERSION_SERIAL_NO_RESP;
			sendMsg.Buffer[0] = AC_FW_VERSION_MAJOR;
			sendMsg.Buffer[1] = AC_FW_VERSION_MINOR;
			sendMsg.Buffer[2] = AC_FW_VERSION_BUILD;
			sendMsg.Buffer[3] = AC_FW_VERSION_AUTOS;
			ReadSerNoEEPROM((char *)&sendMsg.Buffer[4]);
			sendMsg.msgLen = SER_VER_NO_BUFF_SIZE ;

#if SOCKET_DEBUG
			printf("\n\rAC_SER_VER_NO_IS = ");
			for(int i=0;i<SER_VER_NO_BUFF_SIZE;i++)
			{
				printf("0x%X, ",sendMsg.Buffer[i]);
			}
#endif

			break;

		default:
			break;
	}


	err = SendMessageToServer(&sendMsg);
	if (err < 0)
	{
#if SOCKET_DEBUG
		message_sendfailcount++;
#endif
	}

}

