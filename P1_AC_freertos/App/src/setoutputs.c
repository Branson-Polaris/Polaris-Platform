/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for writing on particular Micro Controller  port.

Module name: SetOutputs

Filename:    SetOutputs.c

--------------------------- TECHNICAL NOTES -------------------------------

The code is for writing values of value of SV,PilotLight and PB_OUT to port.


-------------------------------------------------------------------------*/
#include "setoutputs.h"
#include "global.h"
#include "../../board_Eval/inc/board.h"


#define WDTIME   5

static tSINT32 WDFeedTimer;




/**************************************************************************//**
* \brief -      Functions Sets the PinOutput for SV1
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetSVRequests(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV1_REQ1_PORT, SV1_REQ1_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV1_REQ2_PORT, SV1_REQ2_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -    Functions clears the PinOutput for SV1
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearSVRequests(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV1_REQ1_PORT, SV1_REQ1_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV1_REQ2_PORT, SV1_REQ2_PIN,OFF_REQ);
#else
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,true);
#endif
}

/**************************************************************************//**
* \brief -        Functions Sets the PinOutput for SV2
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetSV2(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV2_PORT, SV2_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV2_PORT, SV2_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions clears the PinOutput for SV2
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearSV2(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV2_PORT, SV2_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV2_PORT, SV2_PIN,OFF_REQ);
#else
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,true);
#endif
}

/**************************************************************************//**
* \brief -        Functions Sets the PinOutput for SV3
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetSV3(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV3_PORT, SV3_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV3_PORT, SV3_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions clears the PinOutput for SV3
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearSV3(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,SV3_PORT, SV3_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,SV3_PORT, SV3_PIN,OFF_REQ);
#else
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,true);
#endif
}

/**************************************************************************//**
* \brief -        Functions Sets the PinOutput to turn on the work light
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetWorkLight(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,WL_PORT, WL_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,WL_PORT, WL_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions clears the PinOutput to turn off the work light
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearWorkLight(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,WL_PORT, WL_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,WL_PORT, WL_PIN,OFF_REQ);
#else
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,true);
#endif
}

/**************************************************************************//**
* \brief -        Functions Sets the PinOutput for LEDR
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetLEDR(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,LEDR_PORT, LEDR_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,LEDR_PORT, LEDR_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions Sets the PinOutput for LEDG
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void SetLEDG(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,LEDG_PORT, LEDG_PIN,ON_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,LEDG_PORT, LEDG_PIN,ON_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions Clears the PinOutput for LEDR
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearLEDR(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,LEDR_PORT, LEDR_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,LEDR_PORT, LEDR_PIN,OFF_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}

/**************************************************************************//**
* \brief -        Functions Clears the PinOutput for LEDG
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ClearLEDG(void)
{
#ifdef PRODUCTION
	Chip_GPIO_SetPinState(LPC_GPIO,LEDG_PORT, LEDG_PIN,OFF_REQ);
	Chip_GPIO_SetPinState(LPC_GPIO,LEDG_PORT, LEDG_PIN,OFF_REQ);
#else
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 26,false);
#endif
}


/**************************************************************************//**
* \brief -	ResetExternalWatchdog
*
* \brief -	Functions Send the reset pulse to Reset the external WatchDog.
*
* \param -	none
*
* \return -	none
*
*****************************************************************************/
void ResetExternalWatchdog(void)
{

   WDFeedTimer++;
   static tSINT32 WDResetPulse = 0;
   if (WDFeedTimer > WDTIME)
   {

      WDFeedTimer = 0;
     // PINSEL_SetOutput(1, 18,WDResetPulse);
      WDResetPulse = !WDResetPulse;

   }

}

/**************************************************************************//**
* \brief -       SetOutputs
*
* \brief -       Functions call different functions to set current outputs.
*
* \param -       none
*
* \return -      none
*
*****************************************************************************/
void SetOutputs(void)
{

	SetSVRequests();

   ResetExternalWatchdog();

}

#if UNIT_TESTING
/**************************************************************************//**
* \brief -		ResetHandler
*
* \brief -		ResetHandler is the entry point for SetOutputs test unit testing.
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ResetHandler(void)
{
   DiagInit();
   IOInit();

// Set SV relay
   SetSVRelayDiagnostics = 1;
   pinSelSetOutputDiagnostics = 0;
   SetSVRelay();
   DiagPrintInt(1, 1);

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();
   SetSVRelayDiagnostics = 0;

//OFFBeeper Test case 1
   OFFBeeperDiagnostics =1;
   FlashingTimer = 4000;
   OFFBeeper();
   DiagPrintInt(1, 1);

//OFFBeeper Test case 2
   FlashingTimer = 6000;
   OFFBeeper();
   DiagPrintInt(1, 1);

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

   OFFBeeperDiagnostics = 0;

   BeepBeeperDiagnostics = 1;
//Test case 1
   Beeper = ON;
   FlashingTimer = 1100;
   BeepBeeper();
   DiagPrintInt(1, 1);

//Test case 2
   Beeper = ON;
   FlashingTimer = 900;
   BeepBeeper();
   DiagPrintInt(1, 1);

//Test case 3
   Beeper =BEEPING;
   FlashingTimer = 1100;
   BeepBeeper();
   DiagPrintInt(1, 1);

//Test case 4
   Beeper = BEEPING;
   FlashingTimer = 900;
   BeepBeeper();
   DiagPrintInt(1, 1);

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

   BeepBeeperDiagnostics = 0;

   HandleBeeperDiagnostics = 1;
//Handle Beeper
//Beeper test 1
   BEEPER = ON;
   OFFBeeperFault = 1;
   OFFBeeperFault1 = 1;
   HandleBeeperFault = 1;
   OFFBeeperFault2 =1;

   HandleBeeper();
   DiagPrintInt(1, 1);

//Beeper test 2
   BEEPER = BEEPING;
   FlashCounter = 0;
   OFFBeeperFault = 1;
   OFFBeeperFault1 = 0;
   HandleBeeperFault = 0;
   OFFBeeperFault2 =1;
   Beeping = TRUE;
   Beeper = OFF;
   Beeping = 1;
   BeeperOFF = 1;
   HandleBeeper();
   DiagPrintInt(1, 1);

//Beeper test 3
   BEEPER = BEEPING;
   FlashCounter = 0;
   HandleBeeperFault = 1;
   OFFBeeperFault1 = 1;
   OFFBeeperFault2 =1;
   OFFBeeperFault = 0;
   BeeperOFF = 1;
   FaultFlag = FALSE;
   Beeping = TRUE;
   Beeper = OFF;
   HandleBeeper();
   DiagPrintInt(1, 1);

//Beeper test 4  **
   BEEPER = BEEPING;
   FlashCounter = 0;
   BeeperOFF = 1;
   HandleBeeperFault = 1;
   OFFBeeperFault = 1;
   OFFBeeperFault1 = 1;
   OFFBeeperFault2 =1;
   FaultFlag = TRUE;
   Beeping = 0;
   Beeper = OFF;
   HandleBeeper();
   DiagPrintInt(1, 1);

//Beeper test 5
   BEEPER = BEEPING;
   FlashCounter = 0;
   BeeperOFF = 0;
   HandleBeeperFault = 1;
   OFFBeeperFault1 = 1;
   OFFBeeperFault = 0;
   OFFBeeperFault2 =1;
   FaultFlag = TRUE;
   Beeper = OFF;
   FlashCounter = 0;
   Beeping = 1;
   HandleBeeper();
   DiagPrintInt(1, 1);

//Beeper test 6
  BEEPER = BEEPING;
  FlashCounter = 0;
  BeeperOFF = 1;
  Beeping = 0;
  HandleBeeperFault = 1;
  OFFBeeperFault1 = 1;
  OFFBeeperFault = 1;
  OFFBeeperFault2 = 0;
  FaultFlag = FALSE;
  Beeper = OFF;
  HandleBeeper();
  DiagPrintInt(1, 1);

//Beeper test 7
  BEEPER = BEEPING;
  FlashCounter = 0;
  BeeperOFF = 0;
  HandleBeeperFault = 1;
  OFFBeeperFault1 = 1;
  OFFBeeperFault = 1;
  OFFBeeperFault2 =1;
  FaultFlag = FALSE;
  Beeper = OFF;
  FlashCounter = 0;
  Beeping = 0;
  HandleBeeper();
  DiagPrintInt(1, 1);

  //Beeper test 9
   BEEPER = ON;
   NotMyFault = TRUE;

   HandleBeeper();
   DiagPrintInt(1, 1);

  HandleBeeperDiagnostics = 0;
// Print Summary
   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

// Set Beep
   SetEN_ALARMcodeDiagnostics = 1;
   pinSelSetOutputDiagnostics = 0;
   SetEN_ALARMcode();
   DiagPrintInt(1, 1);
   SetEN_ALARMcodeDiagnostics = 0;

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

// Set PBs
   SetPBsDiagnostics = 1;
   pinSelSetOutputDiagnostics = 0;
   SetPBs();
   DiagPrintInt(PB_OUT, PB1_NO_IN);
   SetPBsDiagnostics = 0;

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

// ResetExternalWatchdog test case no 1
   SetResetWDDiag = 1;
   WDFeedTimer = 6;
   pinSelSetOutputDiagnostics = 0;
   ResetExternalWatchdog();
   DiagPrintInt(1, 1);

// ResetExternalWatchdog test case no 2
   SetResetWDDiag = 1;
   WDFeedTimer = 2;
   ResetExternalWatchdog();
   DiagPrintInt(1, 1);

   SetResetWDDiag = 0;

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

// PINSEL_SetOutput case no 1
   pinSelSetOutputDiagnostics = 1;
   ChkFunReturn = 0;
   PINSEL_SetOutput(0,10,1);
   DiagPrintInt(ChkFunReturn, 1);

// PINSEL_SetOutput case no 2
   ChkFunReturn = 0;
   PINSEL_SetOutput(0,10,0);
   DiagPrintInt(ChkFunReturn, 0);

   pinSelSetOutputDiagnostics = 0;

   DiagSummary();
   ResetdiagTests();
   ResetdiagErrors();

// Set outputs
   SetOutputsDiagnostics = 1;
   SetOutputs();
   DiagPrintInt(1, 1);
   SetOutputsDiagnostics = 0;

   DiagSummary();
}

#endif
