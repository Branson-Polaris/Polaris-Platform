/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for testing the ADC as part of Logic Unit Testing.

Module name: ADCTest

Filename:    ADCTest.h

--------------------------- TECHNICAL NOTES -------------------------------

This code modifies the values of the registers that are related to the
ADC of LPC 1786 microprocessor.



-------------------------------------------------------------------------*/

#ifndef __ADC_H
#define __ADC_H
#include "../../chip/inc/lpc_types.h"

#define ADC_ADINT    0x00010000

#define ADC_NUM      8        /* for LPCxxxx */
#define ADC_CLK      1000000     /* set to 1Mhz */
#define MAX_ADCCHANNEL_USED   6
#define ADC_IDSEL1     0x01
#define ADC_IDSEL2     0x02
#define ADC_FORCE      0x04
#define ADC_2_5_REF    0x08
#define ADC_GND        0x10
#define ADC_PRESSURE   0x20
#define ADC_CH_6      0x40
#define ADC_CH_7      0x80
#define ADC_CH_8      0x100 // For Module testing only
#define ADC_0VOLT_RANGE 25
#define ADCErrorCount 10
extern tUINT32 ADC0Value[ADC_NUM];

// for Testing
#define TESTCHNUMBERVAL1   1
#define TESTCHNUMBERVAL2   8

#define  TESTADCTESTVALCH0_0   5
#define  TESTADCTESTVALCH1_0   5

#define  TESTADCTESTVALCH0_1   3100
#define  TESTADCTESTVALCH1_1   3100

#define  TESTADCTESTVALCH0_2   3100
#define  TESTADCTESTVALCH1_2   5

#define  TESTADCTESTVALCH0_3   5
#define  TESTADCTESTVALCH1_3   3100

#define TESTADCTESTVALCH3_0	  3100
#define TESTADCTESTVALCH4_0   5

#define TESTADCTESTVALCH3_1	  5
#define TESTADCTESTVALCH4_1   5

#define TESTADCTESTVALCH3_2	  3100
#define TESTADCTESTVALCH4_2	  3100

#define TESTADCTESTVALCH3_3	  5
#define TESTADCTESTVALCH4_3   3100



//void ADCInit( tUINT32 ADC_Clk );
void EnableReadADCInterrupt( tUINT8 channelNum );
void ADC_Test(void);
#endif /* end __ADC_H */

