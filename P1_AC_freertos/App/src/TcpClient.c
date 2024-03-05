/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include "TcpClient.h"
#include "SocketReceiver.h"
#include "Main.h"
#include "lwip/opt.h"
#include "string.h"
#include "arch\lpc_arch.h"
#include "arch\sys_arch.h"

#include "global.h"


#if SOCKET_DEBUG
	extern unsigned int message_sendfailcount;
	extern long unsigned int message_recvcount;
#endif


Client_Message SockMsg;
BOOL SocketCommStatus;

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "lwip/tcpip.h"

/**************************************************************************//**
 *
 * \brief   - Socket message receiving and processing thread
 *
 * \param   - None
 *
 * \return  - None
 *
 ******************************************************************************/

static void GetMessageFromServer(void *arg)
{
	err_t err = 0;
	err_t err_shutdown;
	err_t err_close;

	LWIP_UNUSED_ARG(arg);
	int iRetVal;
	int iMsgId;
	char MsgIdLen[8] = { 0x00 };
	char RecvBuffer[200] = 	{ 0x00 };
	unsigned int timeOutCount = 0;
	unsigned int revdchecksum = 0;
	unsigned int iLen = 0;
	struct sockaddr_in serv_addr;



	while(tcp_link != LINK_CONNECTED);

	/* members are in network byte order */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		DEBUGOUT("Socket creation failure  : %d\r\n", sock);
	}
	else
		DEBUGOUT("\r\n Socket creation success, sock = %d", sock);

	// Fill in the address if possible
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.1.100");
	serv_addr.sin_port = htons(1601);

	do
	{
		err = connect(sock, (struct sockaddr* )&serv_addr, sizeof(serv_addr));
#if PRNT_DBG
	printf("\r\n Connect to server returned %d",err);
#endif
		if (-1 == err)
		{
			close(sock);
			sock = socket(AF_INET, SOCK_STREAM, 0);
			DEBUGOUT("Socket creation failure  : %d\r\n", sock);
		}
	} while (err != ERR_OK);

	if (ERR_OK == err)
	{
		DEBUGOUT("\r\n Socket Connection success, sock = %d", sock);
	}
	else
		DEBUGOUT("\r\n Socket Connection Failed ");

	while (1)
	{
		/* Process the new connection. */
		if (timeOutCount > SOCKET_RETRY_ATTEMPT)
		{
			//timeOutCount 	= 0;
			iRetVal = -1;
			SocketCommStatus = FALSE;
			printf("\nACTSocket_T : Server or socket connection broken");
		}
		else
		{
			SocketCommStatus = TRUE;
			memset(RecvBuffer, 0x00, sizeof(RecvBuffer));
			memset(MsgIdLen, 0x00, sizeof(MsgIdLen));
			memset(SockMsg.Buffer, 0x00, sizeof(SockMsg.Buffer));

#if SPLIT_RECV
			iRetVal = read_exact (sock,MsgIdLen,sizeof(MsgIdLen));
#else
			iRetVal = read_exact(sock, RecvBuffer, RXPDOLEN);
#endif

#if PRNT_DBG
#if SPLIT_RECV
			printf("\r\n MsgIdLen Buffer =");
			for (int i=0;i<sizeof(MsgIdLen);i++)
			{
				printf("%x,",(char *)MsgIdLen[i]);
			}
#else
			printf("\r\n RecvBuffer Buffer =");
			for (int i=0;i<RECV_BUFFER_SIZE;i++)
			{
				printf("%x,",(char *)RecvBuffer[i]);
			}
#endif
#endif
		}

		if (iRetVal < 0)
		{
			err_shutdown = shutdown(sock, SHUT_RDWR);
			err_close = close(sock);
			sock = socket(AF_INET, SOCK_STREAM, 0);
			err = connect(sock, (struct sockaddr* )&serv_addr,sizeof(serv_addr));
#if SOCKET_DEBUG
			printf("\r\n ReTrying to shutdown sock:%d", err_shutdown);
			printf("\r\n ReTrying to close sock:%d", err_close);
			printf("\r\n ReTrying to connect to server,sock:%d", sock);
			printf("\r\n connect to server returned %d,timeOutCount :%d;", err,timeOutCount);
#endif
			if (ERR_OK == err)
			{
				timeOutCount = 0;
				DEBUGOUT("\r\n socket ReConnection success, sock = %d", sock);
			}
			else
			{
				timeOutCount = timeOutCount + 1;
				DEBUGOUT("\r\n socket ReConnection Failed ");
			}
		}
		else if (0 == iRetVal)
		{
			/* Socket read time out and polling to read */
			timeOutCount = timeOutCount + 1;
		}
		else
		{
			timeOutCount = 0;

			// get the message ID and length from the header
#if SPLIT_RECV
			memcpy(&iMsgId, MsgIdLen, sizeof(iMsgId));
			memcpy(&iLen, MsgIdLen + sizeof(iMsgId), sizeof(iLen));
#else
			memcpy(&iMsgId, RecvBuffer, sizeof(iMsgId));
			memcpy(&iLen, RecvBuffer + sizeof(iMsgId), sizeof(iLen));
#endif
#if PRNT_DBG
			printf("\r\n  msgID  = %d",iMsgId);
			printf("\r\n  msgLen = %d",iLen);
#endif

			if (iLen <= 0)
			{
				DEBUGOUT("\r\n ACTSocket_T : Invalid message received: MsgID: %d,msgLen: %d, timeOutCount: %d",iMsgId, iLen, timeOutCount);
				timeOutCount++;
			}
			else
			{
#if SPLIT_RECV
				iRetVal = read_exact (sock,RecvBuffer,iLen+sizeof(SockMsg.crc32));
#endif
#if PRNT_DBG
				printf("\r\n RecvBuffer Buffer =");
				for (int i=0;i<RXPDOLEN;i++)
				{
					printf("%x,",(char *)RecvBuffer[i]);
				}
#endif
#if SPLIT_RECV
				if(iRetVal <= 0)
				{
					timeOutCount  = SOCKET_RETRY_ATTEMPT;
					printf("\r\n timeOutCount = %d",timeOutCount);
				}
				else if(iRetVal > 0)
#endif
				{
#if SPLIT_RECV
					MessageDeCoder(iMsgId, iLen, RecvBuffer, &SockMsg);
#else
					MessageDeCoder(iMsgId, iLen, &RecvBuffer[sizeof(MsgIdLen)], &SockMsg);
#endif
#if PRNT_DBG
					printf("\r\n SockMsg msgID  = %d",SockMsg.msgID);
					printf("\r\n SockMsg msgLen = %d",SockMsg.msgLen);

					printf("\r\n SockMsg Buffer =");
					for (int i=0;i<(SockMsg.msgLen);i++)
					{
						printf("%x,",(char *)SockMsg.Buffer[i]);
					}

					printf("\r\n Recv crc32 = %x",SockMsg.crc32);
					printf("\r\n calc crc32 = %x",MessageCRCCal(&SockMsg));
#endif

					revdchecksum = MessageCRCCal(&SockMsg);

					if (SockMsg.crc32 == revdchecksum)
					{
#if SOCKET_DEBUG
						message_recvcount++;
#endif
						ProcessDatafromASC(&SockMsg);
					}
					else
					{
						DEBUGOUT("checksum Mismatched: recvd: %x calc: %x\r\n",SockMsg.crc32, revdchecksum);
					}
#if SOCKET_DEBUG
					if (message_recvcount && message_recvcount % 1000 == 0) // for testing time taken for 1000 msgs, should be 1 Sec
					{
						printf("\r\n at %lu inside ProcessPDOC", message_recvcount);
						printf("\r\n ActualForce    = %x", rxpdoac.ACControlEvent);
						printf("\r\n ActualDistance = %x", rxpdoac.ACOutputs);
						printf("\r\n ACStatusEvent  = %x", rxpdoac.SCState);
						printf("\r\n Message send fail = %lu ",message_sendfailcount);
					}
#endif
				}
			}
		}
	}
}

/**************************************************************************//**
 *
 * \brief   - Send TCP message to connected server
 *
 * \param   - struct Client_Message *sendMsg.
 *
 * \return  - None
 *
 ******************************************************************************/
int SendMessageToServer(struct Client_Message *sendMsg)
{
	err_t bytesSent = 0;
	unsigned int bufLen = 0;
	char outbuf[100] = {0x00};
	memset(outbuf, 0x00, sizeof(outbuf));

	memcpy(outbuf, &sendMsg->msgID, sizeof(sendMsg->msgID));
	bufLen += sizeof(sendMsg->msgID);

	memcpy(outbuf + bufLen, &sendMsg->msgLen, sizeof(sendMsg->msgLen));
	bufLen += sizeof(sendMsg->msgLen);

	memcpy(outbuf + bufLen, sendMsg->Buffer, sendMsg->msgLen);
	bufLen += sendMsg->msgLen;

	sendMsg->crc32 = crc32_ccitt(outbuf, bufLen);

	memcpy(outbuf + bufLen, &sendMsg->crc32, sizeof(sendMsg->crc32));
	bufLen += sizeof(sendMsg->crc32);

#if PRNT_DBG
	printf("\r\n sendMsg msgID  = %d",sendMsg->msgID);
	printf("\r\n sendMsg msgLen = %d",sendMsg->msgLen);
	printf("\r\n sendMsg Buffer =");
	for (int i=0;i<(sendMsg->msgLen);i++)
	{
		printf("%x,",(char *)sendMsg->Buffer[i]);
	}
	printf("\r\n send crc32 = %x",sendMsg->crc32);
#endif

	bytesSent = send(sock, (char* )outbuf, bufLen, MSG_DONTWAIT);

	return bytesSent;
}

/**************************************************************************//**
 *
 * \brief   - start the Socket_ACT_Task
 *
 * \param   - None.
 *
 * \return  - None
 *
 ******************************************************************************/
void TcpClientInit(void)
{
	sys_thread_new("GetMessageFromServer", GetMessageFromServer, NULL,
	ASC_CLIENT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

#endif /* LWIP_NETCONN */
