/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2018
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     Functions for SLL-Socket communication
 
**********************************************************************************************************/

#include "SSLSocket.h"
#include "Logger_old.h"

/**************************************************************************//**
* \brief    - SSLSocket Class constructor
*
* \param    - None
*
* \return   - None
*
******************************************************************************/
SSLSocket::SSLSocket()
	: m_ptr_SSL_CTX(NULL)
	, m_SSL_Descriptor(NULL)
{

}

/**************************************************************************//**
* 
* \brief   - SSLSocket class destructor
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
SSLSocket::~SSLSocket()
{
	SSL_CTX_free(m_ptr_SSL_CTX);
	Cleanup_openssl();
}

/**************************************************************************//**
* 
* \brief   - SSL initialization for SSL CTX configuration
*
* \param   - None
*
* \return  - If there is any issue in the initialization, it will return false
*
******************************************************************************/
bool SSLSocket::SSL_Init()
{
	bool bResult = false;
	Init_openssl();
	m_ptr_SSL_CTX = Create_context();
	if(m_ptr_SSL_CTX == NULL)
	{
		LOGERR((char *)"SSL Socket: Error on Initialize SSL\n", 0, 0, 0);
		return bResult;
	}
	bResult = Configure_context(m_ptr_SSL_CTX);
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - SSL creating
*
* \param   - None
*
* \return  - If there is any issue in the initialization, it will return false
*
******************************************************************************/
bool SSLSocket::SSL_Create()
{
	bool bResult = false;

	if(m_ptr_SSL_CTX == NULL)
		return false;
	m_SSL_Descriptor = SSL_new(m_ptr_SSL_CTX);
	if(m_SSL_Descriptor == NULL)
	{
		LOGERR((char *)"SSL Socket: Error on Create SSL\n", 0, 0, 0);
		bResult = false;
	}
	else
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - SSL binding to create a socket BIO between ssl and fd.
*
* \param   - TCP/IP socket connected descriptor 
*
* \return  - If there is any issue during the binding, it will return false
*
******************************************************************************/
bool SSLSocket::SSL_Bind(int tmpSocketDescription)
{
	bool bResult = false;
	if(m_SSL_Descriptor == NULL)
		return false;
	if(SSL_set_fd(m_SSL_Descriptor, tmpSocketDescription) == 0)
	{
		LOGERR((char*)"SSL Socket: Error on Bind SSL to Socket\n", 0, 0, 0);
		bResult = false;
	}
	else
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**s
* 
* \brief   - SSL accept function to wait for a SSL client to initiate the SSL handshake.
*
* \param   - None
*
* \return  - If there is any issue during the accepting, it will return false
*
******************************************************************************/
bool SSLSocket::SSL_Accept()
{
	bool bResult = false;
	if(m_SSL_Descriptor == NULL)
		return false;
	if(SSL_accept(m_SSL_Descriptor) > 0)
	{
		bResult = true;
	}
	else
	{
		LOGERR((char *)"SSL Socket: Error on ssl_socket accept", 0, 0, 0);
//		ERR_print_errors_fp(stderr);
		bResult = false;
	}
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - To reset the SSL object to allow for another connection.s
*
* \param   - None
*
* \return  - If there is any issue during the accepting, it will return false
*
******************************************************************************/
bool SSLSocket::SSL_Reset()
{
	bool bResult = false;
	if(m_SSL_Descriptor == NULL)
		return false;
	if(SSL_clear(m_SSL_Descriptor) == 0)
	{
		LOGERR((char *)"SSL Socket: Error on ssl_socket clear", 0, 0, 0);
//		ERR_print_errors_fp(stderr);
		bResult = false;
	}
	else
		bResult = true;
	return bResult;
}

/**************************************************************************//**
* 
* \brief   - To send bufflen bytes from the buffer buff into the specified SSL connection.
*
* \param   - buffer and buffer length
*
* \return  - >0 is the write operation was successful, 
* 			 the return value is the number of bytes actually written to the SSL connection.
* 			 <=0 is the write operation was not successful.  
*
******************************************************************************/
int SSLSocket::SSL_Send(char *buff, const unsigned int bufflen)
{
	if(m_SSL_Descriptor == NULL)
		return ERROR;
	return SSL_write(m_SSL_Descriptor, reinterpret_cast<void*>(buff), bufflen);	
}

/**************************************************************************//**
* 
* \brief   - Try To read bufflen bytes from the specified SSL connection into the buffer buff.
*
* \param   - buffer and buffer length
*
* \return  - >0 is the read operation was successful, 
* 			 the return value is the number of bytes actually read from the SSL connection.
* 			 <=0 is the read operation was not successful.  
*
******************************************************************************/
int SSLSocket::SSL_Read(char *buff, const unsigned int bufflen)
{
	int iActualBufLen = 0, iTriedCount = 0;
	if(m_SSL_Descriptor == NULL)
		return ERROR;
	
	do
	{
		iActualBufLen = SSL_read(m_SSL_Descriptor, reinterpret_cast<void*>(buff), bufflen);
		if(iActualBufLen == 0)
		{
			iTriedCount++;
			if(iTriedCount > SSL_RETRY_ATTEMPT)
				iActualBufLen = ERROR;
		}
		
	}while(iActualBufLen == 0);
	
	return iActualBufLen;
}

/**************************************************************************//**
* 
* \brief   - Initialize the OpenSSL lib before using
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void SSLSocket::Init_openssl()
{
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

/**************************************************************************//**
* 
* \brief   - Cleanup the OpenSSL
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void SSLSocket::Cleanup_openssl()
{
	EVP_cleanup();
}

/**************************************************************************//**
* 
* \brief   - Create the OpenSSL Context
*
* \param   - None
*
* \return  - SSL_CTX *
*
******************************************************************************/
SSL_CTX* SSLSocket::Create_context()
{
	const SSL_METHOD *ptrSSLMethod;
	SSL_CTX* ptrCTX;

	ptrSSLMethod = SSLv23_server_method();
	ptrCTX = SSL_CTX_new(ptrSSLMethod);
	if (!ptrCTX) 
	{
		LOGERR((char *)"SSLSocket: Unable to create SSL context", 0, 0, 0);
//		ERR_print_errors_fp(stderr);
//		exit(EXIT_FAILURE);
		ptrCTX = NULL;
	}
	return ptrCTX;
}

/**************************************************************************//**
* 
* \brief   - Configure the OpenSSL Context
*
* \param   - None
*
* \return  - SSL_CTX *
*
******************************************************************************/
bool SSLSocket::Configure_context(SSL_CTX *ptrCTX)
{	
	bool bResult = false;
	SSL_CTX_set_ecdh_auto(ptrCTX, 1);
	
	/* Set the key and cert */
	if (SSL_CTX_use_certificate_file(ptrCTX, SSL_PEM_PATH, SSL_FILETYPE_PEM) <= 0)
	{
		LOGERR((char *)"SSLSocket: Unable to use Certificate file",0,0,0);
//		ERR_print_errors_fp(stderr);
//		exit(EXIT_FAILURE);
		return bResult;
	}

	if (SSL_CTX_use_PrivateKey_file(ptrCTX, SSL_PEM_PATH, SSL_FILETYPE_PEM) <= 0 )
	{
		LOGERR((char *)"SSLSocket: Unable to use PrivateKey file",0,0,0);
//		ERR_print_errors_fp(stderr);
//		exit(EXIT_FAILURE);
		return bResult;
	}
	bResult = true;
	return bResult;
}
