/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*
 * powerup.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Akhutale
 *
 *      Power Up State implementation
*/

#include "global.h"
#include "statemachine.h"
#include "Main.h"
#include "eeprom.h"


/***********************************************************************//*****
 * \brief  - Enter
 * 			This is Entry code for PowerUp State.
 * 			- Action read the eeprom serial number and actuator type.
 *
 * \param  - none
 *
 *
 * \return  - none
 *
 ******************************************************************************/
 void PowerUpEntry()
 {

		uint8_t *ptr = (uint8_t *)GetEepromBuffer();
		uint32_t stSize;

#if PRNT_DBG
	printf("\r\n In Power up Entry state");
#endif
		/* Read all data from EEPROM page */
		Chip_EEPROM_Read(LPC_EEPROM, 0, PAGE_ADDR, ptr, EEPROM_RWSIZE_8BITS, EEPROM_PAGE_SIZE);

		/* Check and display string if it exists */
		ShowString((char *) ptr);

		/* Get a string to save */
		stSize = MakeString(ptr);

 }

 /**************************************************************************//**
 * 	\brief  -  PowerUp State of the State Machine.
 *
 *  \brief -		Entry Conditions:
 *                     	1.> When power on or CPU reset.
 *
 *   \brief -		Action taken
 *                     	1.> Checks if palm buttons are not pressed during power up.
 *                     	2.> Checks ULS active and TRS inactive
 *
 *   \brief -		Exit condition transitions to State Ready
 *                     	1.> When both PB1 and PB2 are released
 *                     	2.> ULS active
 *                     	3.> TRS inactive
 *                     	4.> SC Ready
 *
 * \param  - none
 *
 * \return - none
 *
 ******************************************************************************************/
 void PowerUpStateLoop(void)
 {

#if PRNT_DBG
	printf("\r\n In Power up Loop state");
#endif
	if (ESTOP1 || ESTOP2)
	{
		ChangeState(AC_ESTOP);
	}
	else if ((ULS == OFF) || (TRS == ON) || (rxpdoac.SCState == SC_ALARM))
	{
		ChangeState (AC_ALARM);
	}
	else if ((PB1_NO_IN == OFF) && (PB2_NO_IN == OFF) && (ULS == ON) && (TRS == OFF) && (SocketCommStatus == TRUE))
 	{
 		ChangeState(AC_READY);
 	}
 }

 /******************************************************************************
 * \brief  - Exit
 * 			This is Exit code for PowerUp State.
 *
 * \param  - none
 *
 *
 * \return  - none
 *
 ******************************************************************************/
 void PowerUpExit()
 {
#if PRNT_DBG
	printf("\r\n In Power up Exit state");
#endif

 }
