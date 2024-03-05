/*
 * @brief EEPROM example
 * This example show how to use the EEPROM interface
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */



#include "string.h"
#include "../../board_Eval/inc/board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Page used for storage */
#define PAGE_ADDR       0x01/* Page number */

/* Tag for checking if a string already exists in EEPROM */
#define CHKTAG          "NxP"
#define CHKTAG_SIZE     3

/* ASCII ESC character code */
#define ESC_CHAR        27

/* Read/write buffer (32-bit aligned) */
uint32_t Buffer[EEPROM_PAGE_SIZE / sizeof(uint32_t)];


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/**************************************************************************//**
* \brief  - Show current string stored in UART
*
* \param  - char *str
*
*
* \return  - none
*
******************************************************************************/
void ShowString(char *str) {
	int stSize;

	/* Is data tagged with check pattern? */
	if (strncmp(str, CHKTAG, CHKTAG_SIZE) == 0) {
		/* Get next byte, which is the string size in bytes */
		stSize = (uint32_t) str[3];
		if (stSize > 32) {
			stSize = 32;
		}

		/* Add terminator */
		str[4 + stSize] = '\0';

		/* Show string stored in EEPROM */
		DEBUGSTR("Stored string found in EEEPROM\r\n");
		DEBUGSTR("-->");
		DEBUGSTR((char *) &str[4]);
		DEBUGSTR("<--\r\n");
	}
	else {
		DEBUGSTR("No string stored in the EEPROM\r\n");
	}
}

/**************************************************************************//**
* \brief  - Get a string to save from the UART
*
* \param  - uint8_t *str
*
*
* \return  - none
*
******************************************************************************/
uint32_t MakeString(uint8_t *str)
{
	int index, byte;
	char strOut[2];

	/* Get a string up to 32 bytes to write into EEPROM */
	DEBUGSTR("\r\nEnter a string to write into EEPROM\r\n");
	DEBUGSTR("Up to 32 bytes in length, press ESC to accept\r\n");

	/* Setup header */
	strncpy((char *) str, CHKTAG, CHKTAG_SIZE);

	/* Read until escape, but cap at 32 characters */
	index = 0;
	strOut[1] = '\0';
	byte = DEBUGIN();
	while ((index < 32) && (byte != ESC_CHAR)) {
		if (byte != EOF) {
			strOut[0] = str[4 + index] = (uint8_t) byte;
			DEBUGSTR(strOut);
			index++;
		}

		byte = DEBUGIN();
	}

	str[3] = (uint8_t) index;

	return (uint32_t) index;
}

/**************************************************************************//**
* \brief  - Read Serial No from EEPROM
*
* \param  -char *pdata to store Serial No
*
*
* \return  - none
*
******************************************************************************/
void ReadSerNoEEPROM(char *pdata)
{
	 /* Read all data from EEPROM page */
	Chip_EEPROM_Read(LPC_EEPROM, 0, PAGE_ADDR, pdata, EEPROM_RWSIZE_8BITS, 20);
	DEBUGSTR("\r\n-->");
	DEBUGSTR(pdata);
	DEBUGSTR("<--\r\n");

}

/**************************************************************************//**
* \brief  - Write Serial No into  EEPROM
*
* \param  - char *pdata which holds the Serial No to write.
*
*
* \return  - none
*
******************************************************************************/
void WriteSerNoEEPROM (char *pdata)
{
	 /* Read all data from EEPROM page */
	Chip_EEPROM_Write(LPC_EEPROM, 0, PAGE_ADDR, pdata, EEPROM_RWSIZE_8BITS, 20);
	DEBUGSTR("\r\n-->");
	DEBUGSTR(pdata);
	DEBUGSTR("<--\r\n");

}

/**************************************************************************//**
* \brief  - Return the Read/write buffer address
*
* \param  - none.
*
*
* \return  - Read/write buffer address
*
******************************************************************************/
uint32_t * const GetEepromBuffer(void)
{
	return Buffer;
}



