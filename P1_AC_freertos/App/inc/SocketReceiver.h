/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This module implements Socket communication with SC board

Module name: SocketReceiver

Filename:    SocketReceiver.h

-------------------------------------------------------------------------*/

#ifndef INC_SOCKETRECEIVER_H_
#define INC_SOCKETRECEIVER_H_

#define SOCKET_DEBUG						0

#define SOCKET_RETRY_ATTEMPT				2

#define RXPDOLEN							32
#define MAX_SIZE_OF_MSG_LENGTH				768


#define TO_ASC_PROCESS_TX_PDO_DATA 			167
#define FROM_ASC_PROCESS_Rx_PDO_DATA 		168

#define FROM_ASC_SYSTEM_SYSINFO_WRITE_REQ			230
#define TO_ASC_SYSTEM_SYSINFO_WRITE_RESP			231

#define FROM_ASC_SYSTEM_VERSION_SERIAL_NO_REQ       43
#define TO_ASC_SYSTEM_VERSION_SERIAL_NO_RESP		44
#define SER_VER_NO_BUFF_SIZE                        24

typedef struct Client_Message
{
	unsigned int msgID;
	unsigned int msgLen;
	char Buffer[200];
	unsigned int crc32;
} Client_Message;

int sock;
int tcp_link;

void ProcessDatatoASC(unsigned int MsgId);
void ProcessDatafromASC(struct Client_Message*);

void MessageDeCoder(unsigned int iMsgId, unsigned int iLen, const char *RecvBuffer,struct Client_Message*);
void ASCPdoDownloadRequest(struct Client_Message*);
void ASCSendSerNoVerNoResponse(struct Client_Message *);
int SendMessageToServer(struct Client_Message*);

unsigned int MessageCRCCal(struct Client_Message*);
unsigned int crc32_ccitt(const void *buf, unsigned int len);


#endif /* INC_SOCKETRECEIVER_H_ */
