/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2019

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * QuickCRC32Algorithm.c
 *
 *  Created on: Apr 26, 2021
 *      Author: Kakdu
 *
 *
*/


#include "../../App/inc/QuickCRC32Algorithm.h"


/**************************************************************************//**
*
* \brief It is the interface to calculate the crc32 result.
*        The function is defined as the static so it can be recalled using the class name.
*
* \param buf is the first data address of the buffer that you want to calculate the crc32 for.
*        len is the buffer length.
*
* \return crc32 result.
*
******************************************************************************/
unsigned int crc32_ccitt(const void *buf,unsigned int len)
{
	unsigned int counter = 0;
	unsigned int crc32 = 0xFFFFFFFF;
    for (counter = 0; counter < len; counter++)
    {
        crc32 = (crc32 << 8)
            ^ crc32_table[((crc32 >> 24) ^ *(unsigned char *)buf) & 0x00FF];
        buf = ((char *) buf) + 1;
    }
    return crc32;
}
