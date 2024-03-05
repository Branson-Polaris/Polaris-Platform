/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

 Module name: QEI
 File name: QEI.h
 -------------------------- TECHNICAL NOTES --------------------------------


-------------------------------------------------------------------------*/

#ifndef QEI_H_
#define QEI_H_

#include "stdint.h"

#include "../../App/inc/global.h"

#define MAXQEIPOS      0xffffffff
#define QEITESTVALUE   32767
#define QEIPhaseErrorCount   100
//#define QEITESTVALUE2   100
#define QEICON_RESP_ENABLE     (1 << 0)
#define QEIIES_ERR_EN_ENABLE (1<<4)
#define QEIINTSTAT_DIR_IntENABLE (1 << 3)
#define QEIINTSTAT_ERR_IntENABLE (1 << 4)

#define QEICONF_DIRINV_ENABLE  (1 << 0)
#define QEICONF_CAPMODE_ENABLE (1 << 2)
#define PCONP_PCQEI_MASK       (1 << 18)
#define PCLKSEL1_PCLK_QEI_MASK (3 << 0)
#define PCLKSEL1_PCLK_QEI_FUN1 (1 << 0)

#define PHA_PORT             1
#define PHA_PIN              20
#define PHB_PORT             1
#define PHB_PIN              23

void QuadratureEncoderInit(tSINT32 maxPos);
void QEI_IRQHandler(void);
void QEI_GetPosition(void);
//void QEI_ResetPosition(void);
inline void QEI_ResetPosition(void);
#endif /* QEI_H_ */
