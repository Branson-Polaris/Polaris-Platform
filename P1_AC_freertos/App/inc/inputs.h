/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module to declare the inputs.

Module name: Input

Filename:    Input.h

--------------------------- TECHNICAL NOTES -------------------------------*/




#ifndef INPUT_H_
#define INPUT_H_


/* Function prototypes */
void GetInputs(void);
void InitInputs(void);
void CheckMachineConfiguration(void);


#define EN_ALARM0_PORT       4
#define EN_ALARM0_PIN        0
#define EN_ALARM1_PORT       4
#define EN_ALARM1_PIN        1
#define EN_ALARM2_PORT       4
#define EN_ALARM2_PIN        2
#define EN_ALARM3_PORT       4
#define EN_ALARM3_PIN        3
#define ESTOP1_PORT          1
#define ESTOP1_PIN           21
#define ESTOP2_PORT          1
#define ESTOP2_PIN           22
#define GDS_PORT             0
#define GDS_PIN              14
#define PB_OUT1_PORT         0
#define PB_OUT1_PIN          27
#define PB_OUT2_PORT         0
#define PB_OUT2_PIN          28
#define PB1_NO_IN_PORT       1
#define PB1_NO_IN_PIN        26
#define PB2_NO_IN_PORT       1
#define PB2_NO_IN_PIN        25
#define SONICS_HI_FAIL_PORT  0
#define SONICS_HI_FAIL_PIN   21
#define SONICS_LO_FAIL_PORT  0
#define SONICS_LO_FAIL_PIN   22
#define SV1_HI_FAIL_PORT     0
#define SV1_HI_FAIL_PIN      4
#define SV1_LO_FAIL_PORT     0
#define SV1_LO_FAIL_PIN      5
#define TRS_PORT             0
#define TRS_PIN              1
#define ULS_PORT             1
#define ULS_PIN              24






/*Enum structure for value of ULS depending on the Machine Configuration*/
enum ULSPOSITION
{
   AWAYPOSITION,
   HOMEPOSITION
};

#endif /* INPUT_H_ */
