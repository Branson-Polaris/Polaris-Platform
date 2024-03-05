/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module to check if all the devices that are related to the
safety function are functioning properly.

Module name: DeviceDiagnostics

Filename:    DeviceDiagnostics.h

--------------------------- TECHNICAL NOTES -------------------------------

This code checks the status of the fault variables, that belong to the
devices.


-------------------------------------------------------------------------*/

#ifndef DEVICEDIAGNOSTICS_H_
#define DEVICEDIAGNOSTICS_H_


enum DEVICEDIAGSTATUS
{
   OK,
   NOK,
   INDETERMINATE,
};
enum FaultFlags
{
	PBFaultFlag = 1,
	UFAIL24FaultFlag = 2,
	EStopFaultFlag = 4,
	LEFaultFlag = 8,
	SBeamFaultFlag = 16,
	TRSFaultFlag = 32,
	DriveFaultFlag = 64,
	CMFaultFlag = 128,
	LUFaultFlag = 256,
	SonicsEnFaultFlag = 512

};


/* Function prototypes */
void ADC_Test(void);
void UFAIL24VDiagnostics(void);
void DriveDiagnostics(void) ;
void SBeamDiagnostics(void);
void TRSDiagnostics(void);
void ULSLEDiagnostics(void);
void EStopDiagnostics();
void DeviceDiagnostics(void);
void SonicsEnDiagnostics(void);
tUINT16 FirstBitFoundPos(tUINT32);

#endif /* DEVICEDIAGNOSTICS_H_ */
