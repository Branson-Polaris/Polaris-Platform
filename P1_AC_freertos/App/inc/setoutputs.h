/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module to check if the other microprocessor is in sync with
this microprocessor.

Module name: SetOutputs

Filename:    SetOutputs.h

--------------------------- TECHNICAL NOTES -------------------------------

Function prototypes for SetOutputs module


-------------------------------------------------------------------------*/

#ifndef SETOUTPUTS_H_
#define SETOUTPUTS_H_


#define SV1_REQ1_PORT  1
#define SV1_REQ1_PIN   28
#define SV1_REQ2_PORT  1
#define SV1_REQ2_PIN   29
#define SV2_PORT       3
#define SV2_PIN        6
#define SV3_PORT       3
#define SV3_PIN        7
#define WL_PORT       3
#define WL_PIN        23
#define LEDR_PORT           4
#define LEDR_PIN            8
#define LEDG_PORT           4
#define LEDG_PIN            9
#define ON_REQ          false
#define OFF_REQ         true
/* Function prototypes */

void SetOutputs(void);
void SetPBs(void);
void SetSVRequests(void);
void ClearSVRequests(void);
void SetSV2(void);
void ClearSV2(void);
void SetSV3(void);
void ClearSV3(void);
void SetWorkLight(void);
void ClearWorkLight(void);
void SetLEDR(void);
void SetLEDG(void);
void ClearLEDR(void);
void ClearLEDG(void);

#endif /* SETOUTPUTS_H_ */
