/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2018
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef SSLSOCKET_H_
#define SSLSOCKET_H_

#include <stdio.h>
#include <string.h>

#include <netinet/tcp.h>
#include <errno.h>
#include <netdb.h>

#include "inetLib.h"
#include "sockLib.h"

#include <openssl/ssl.h>
#include <openssl/err.h>


#define SSL_PEM_PATH			"/romfs/server.pem"
#define SSL_RETRY_ATTEMPT		2
class SSLSocket
{
public:
	SSLSocket ();
	~SSLSocket ();
	bool SSL_Init();
	bool SSL_Create();
	bool SSL_Bind(int tmpSocketDescription);
	bool SSL_Accept();
	bool SSL_Reset();
	int SSL_Send(char *buff, const unsigned int bufflen);
	int SSL_Read(char *buff, const unsigned int bufflen);
//	static SSLSocket*	getInstance();
private:	
	SSL_CTX 			*m_ptr_SSL_CTX;
	SSL  				*m_SSL_Descriptor;
private:					/* Private member functions */
	void           		Init_openssl();
	void            	Cleanup_openssl();
	SSL_CTX*			Create_context();
	bool            	Configure_context(SSL_CTX *ptrCTX);
	
//	static SSLSocket	*m_SSLObj;

};
#endif /* SSLSOCKET_H_ */
