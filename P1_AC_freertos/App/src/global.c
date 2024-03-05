/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for All the Global variables.

Module name: Global

Filename:    Global.c

--------------------------- TECHNICAL NOTES -------------------------------

This code holds all Global variables.



-------------------------------------------------------------------------*/


#include "global.h"


// indicates Current Weld Status
tUINT8 State;

// indicates Device or CM faults
tSINT32 FaultFlag;

int LastFault = 0;

// indicates whether E -Stop button is pressed or not
BOOL EStop;

// indicates status of 2Hand operation
tSINT32 BothHandStatus;

//Output Received from SC
tSINT32 SV1_REQ;

//Output Received from SC
tSINT32 SV2_REQ;

// SV/STO Relay Status is set from state machine whether to ON or OFF.
//Used by SetOuputs function
tSINT32 SV1;

//Used by SetOuputs function
tSINT32 SV2;

//Used by SetOutputs function
tSINT32 SONICS_EN;

// Beeper Status is set from state machine whether to ON or OFF or BEEPING
//Beeper Used by SetOuputs function
tSINT32 BEEPER;

//Output to indicate Palm button enabled or not
tSINT32 PB_OUT;

//Output to indicate the status of alarm
tSINT32 ALARM;

BOOL Estop = false;
BOOL Alarm = false;


//Flag Set by State machine to clear error
tSINT32 FaultReset;

// indicates whether whether part contact is detected or not
tSINT32 PartContactStatus = 0;
// UFAIL24V status
tSINT32 UFAIL24Status;
tSINT32 UFAIL24V;
//LE Position.
tSINT32 QEIPosition = 0;
//Old LE Position
tSINT32 QEIPositionOld = 0;
//ESTop Status
tSINT32 EStopStatus;
//EStop1 button
tSINT32 ESTOP1;
//EStop2 Button
tSINT32 ESTOP2;
//DRIVEFail status.
tSINT32 DRIVE_FAIL;
//SV2Fail status
tSINT32 SV2_FAIL;
//SONICSFail status
tSINT32 SONICS_FAIL;
//Drive Status.
tSINT32 DriveStatus;
//SonicsEn Status
tSINT32 SonicsEnStatus;
//SBeam Status
tSINT32 SBeamStatus;
//ULS status
tSINT32 ULS;
//LE status
tSINT32 LEStatus;
//TRS Status
tSINT32 TRSStatus;
//TRS Switch Input status.
tSINT32 TRS;
//Logic Unit test status
tSINT32 LUTestStatus;
//Logic Unit test error mask
tSINT32 LUTestErrMask;
//SVFail Input status
tSINT32 SV_FAIL;
//PB1 input status
tSINT32 PB1_NO_IN;
//PB2 Input status
tSINT32 PB2_NO_IN ;
//ULSPosition
tSINT32 ULSPosition;
//ADC Status
tSINT32 ADCStatus;
//Current Average Force reading from ADC
tSINT32 CurrForce;
tSINT32 volatile IsThisCPU1;
//Current Input on CPU input Pin for PB1.
tSINT32 volatile PB1_NO_INPUT;
//Current Input on CPU input Pin for PB2.
tSINT32 volatile PB2_NO_INPUT;

tSINT32 PBStatus;
//Function return value for logic unit diagnostics.
tSINT32 ChkFunReturn;
//ADC interrupt done
volatile tUINT32 ADC0IntDone;
//Number of bytes to transmit that is used in Crossmonitoring.c
tSINT32 BytesToTx;
tSINT32 WDCount;

//Machine Configuration
tSINT32 MachineConfiguration;
tSINT32 MsInterruptCounter;
tSINT32 InterruptTestResult = TRUE;
BOOL NotMyFault = FALSE;
