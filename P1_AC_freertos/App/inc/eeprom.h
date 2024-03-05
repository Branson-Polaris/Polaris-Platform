/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for Reading and writing data to on chip eeprom

Module name: eeprom

Filename:    eeprom.h

-------------------------------------------------------------------------*/

#ifndef __EEPROM_H__
#define __EEPROM_H__

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


void ShowString(char *str);
uint32_t MakeString(uint8_t *str);
uint32_t * const GetEepromBuffer(void);

#endif /*__EEPROM_H__*/
