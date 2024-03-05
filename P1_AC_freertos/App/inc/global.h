/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------
This module has  the list of all the Global variables used.

Module name: Global

Filename:    Global.h

--------------------------- TECHNICAL NOTES -------------------------------


-------------------------------------------------------------------------*/

#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "../../chip/inc/lpc_types.h"

// SW Revision number
#define SWREVISION 0x31

#define BIT_MASK(x)		(1<<x)
//#define PROTOTYPEBOARD  // Comment me for official release.

typedef unsigned char   BOOL;
typedef   signed char  tSINT8;
typedef unsigned char  tUINT8;
typedef   signed short tSINT16;
typedef unsigned short tUINT16;
typedef   signed long  tSINT32;
typedef unsigned long  tUINT32;


typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef   signed short INT16;
typedef unsigned long  UINT32;


#define WDTIMEOUT 300


extern BOOL Timer0Expired;

extern tSINT32 WDCount;
extern BOOL NotMyFault;
extern tUINT8 State;
extern tSINT32 FaultFlag;
extern BOOL EStop;
extern tSINT32 BothHandStatus;
extern tSINT32 SV1_REQ;
extern tSINT32 SV2_REQ;
extern tSINT32 SV2;
extern tSINT32 SV1;
extern tSINT32 SONICS_EN;


extern tSINT32 FaultReset;
extern tSINT32 PartContactStatus;
extern tSINT32 UFAIL24Status;
extern tSINT32 UFAIL24V;
extern tUINT32 DebouncedInputs;
extern tSINT32 EStopStatus;
extern tSINT32 LUTestStatus;
extern tSINT32 LUTestErrMask;
extern tSINT32 ESTOP1;
extern tSINT32 ESTOP2;
extern tSINT32 DRIVE_FAIL;
extern tSINT32 SV2_FAIL;
extern tSINT32 FaultReset;
extern tSINT32 SVRelayCount;
extern tSINT32 DriveStatus;
extern tSINT32 SonicsEnStatus;
extern tSINT32 SBeamStatus;
extern tSINT32 LEStatus;
extern tSINT32 QEIPosition;
extern tSINT32 QEIPositionOld;
extern tSINT32 ULS;
extern tSINT32 ULSPosition;
extern tUINT32 OldULSPosition;
extern tSINT32 TRSStatus;
extern tSINT32 TRS;
extern tSINT32 DRIVE_FAIL;
extern tSINT32 SONICS_FAIL;
extern tSINT32 ESTOP_LO;
extern tSINT32 PB1_NO_IN;
extern tSINT32 PB2_NO_IN ;
extern tSINT32 ADCStatus;
extern tSINT32 EStopCount;
extern tSINT32 CurrForce;
extern tSINT32 WDStatus;
extern tSINT32 CurrVelocity;
extern tSINT32 PCForce;
extern tSINT32 PCLeftindex;
extern tSINT32 PeakVelocity;
extern tSINT32 volatile PB1_NO_INPUT;
extern tSINT32 volatile PB2_NO_INPUT;
extern tSINT32 volatile IsThisCPU1;
extern tSINT32 BytesToTx;
extern tUINT32 PrintfEnabled;
extern tUINT32 StoredFlashCRC;
extern tSINT32 ALARM;
extern BOOL Estop;
extern BOOL Alarm;



extern tSINT32 PBStatus;
//Current Input on CPU input Pin for PB1.
extern tSINT32 volatile PB1_INPUT;
//Current Input on CPU input Pin for PB2.
extern tSINT32 volatile PB2_INPUT;

tUINT32 BIST();
tSINT32 LogicUnitTest(void);
extern void LEDInit(void);
extern void IOInit(void);
extern void SerialInit(tSINT32 port);
extern void InitSSP();
extern void QuadratureEncoderInit(tSINT32 maxPos);
extern void TestWD();
extern void ResetExternalWatchdog(void);
extern tSINT32 ChkFunReturn;
extern volatile tUINT32 ADC0IntDone;
extern tSINT32 MsInterruptCounter;
extern tSINT32 InterruptTestResult;
typedef union {
tSINT32 AllInputs;
   struct bitInput {
      unsigned TRS:1;
      unsigned EN_Alarm0:1;
      unsigned EN_Alarm1:1;
      unsigned EN_Alarm2:1;
      unsigned EN_Alarm3:1;
      unsigned EStop1:1;
      unsigned EStop2:1;
      unsigned ULS:1;
      unsigned PB2_OUT:1;
      unsigned PB1_OUT:1;
      unsigned unused:22;
   } InputBits;
}Digital_Inputs;

//Machine Configuration
extern tSINT32 MachineConfiguration;
extern int LastFault;
enum MACHINETYPE
{
   GSXP1,
   GSXP1PLUS,
   GSXIW,
   GSXE
};

enum TESTRESULT
{
   FAIL,
   PASS,
};



// Enum for BIST Test. Total of 16ms and one test will be done at a time
// either on each ms or on every other ms according to the TEST number in this enum.
enum BIST_TEST
{
   BIST_REGISTER_TEST = 0,
   BIST_RAMSAFEAREA_TEST = 2,
   BIST_PC_TEST = 5,
   BIST_RAMDATAAREA_TEST = 6,
   BIST_ADC_TEST = 10,
   BIST_RAMSTACKAREA_TEST = 12,
   BIST_FLASH_TEST1 = 16,
   BIST_FLASH_TEST2 = 19,
   BIST_FLASH_TEST3 = 22,
   BIST_FLASH_TEST4 = 25,
   BIST_END = 27
};

#define FaultClr    0
tSINT32 PCDummy1(void);
tSINT32 PCDummy2 (void);
tSINT32 PCDummy3 (void);
tSINT32 PCDummy4(void);
tSINT32 PCDummy5 (void);

#if SOCKET_DEBUG
unsigned int message_sendfailcount;
long unsigned int message_recvcount;
#endif

#endif /* GLOBAL_H_ */

