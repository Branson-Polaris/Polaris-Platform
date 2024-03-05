/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for Initializing the Inputs and Outputs.

Module name: IOInit

Filename:    IOInit.c

--------------------------- TECHNICAL NOTES -------------------------------

This code Initializes the Inputs and Outputs.
-------------------------------------------------------------------------*/

#include "setoutputs.h"

#include "../../board_Eval/inc/board.h"

/**************************************************************************//**
* \brief -		InitializeInputs
*
* \brief -		Initializes all Input Pins
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void InitializeInputs(void)
{

#if PRODUCTION
	Chip_GPIO_SetPinDIR(LPC_GPIO, EN_ALARM1_PORT, EN_ALARM0_PIN, false); // false = input
	Chip_GPIO_SetPinDIR(LPC_GPIO, EN_ALARM2_PORT, EN_ALARM2_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, EN_ALARM3_PORT, EN_ALARM3_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, EN_ALARM4_PORT, EN_ALARM4_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, ESTOP1_PORT, ESTOP1_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, ESTOP2_PORT, ESTOP2_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, GDS_PORT, GDS_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, PB_OUT1_PORT, PB_OUT1_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, PB_OUT2_PORT, PB_OUT2_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, PB1_NO_IN_PORT, PB1_NO_IN_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, PB2_NO_IN_PORT, PB2_NO_IN_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SONICS_HI_FAIL_PORT, SONICS_HI_FAIL_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SV1_LO_FAIL_PORT, SV1_LO_FAIL_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, TRS_PORT, TRS_PIN, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, ULS_PORT, ULS_PIN, false);

#endif
}

/**************************************************************************//**
* \brief -		InitializeOutputs
*
* \brief -		Initializes all Output Pins
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void InitializeOutputs(void)
{

#if PRODUCTION
	Chip_GPIO_SetPinDIR(LPC_GPIO, SV1_REQ1_PORT, SV1_REQ1_PIN, true); // true = output
	Chip_GPIO_SetPinDIR(LPC_GPIO, SV1_REQ2_PORT, SV1_REQ2_PIN, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SV2_PORT, SV2_PIN, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SV3_PORT, SV3_PIN, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, WL_PORT, WL_PIN, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, LEDR_PORT, LEDR_PIN, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, LEDG_PORT, LEDG_PIN, true);

#endif
}
