/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for Quadrature linear Encoder.

Module name: QEI

Filename:    QEI.c

--------------------------- TECHNICAL NOTES -------------------------------

This code Handles the Initialization, Interrupt and reading the QEI.

------------------------------ REVISIONS ---------------------------------

-------------------------------------------------------------------------*/


//#include "stdio.h"
#include "qei.h"

#include "devicediagnostics.h"
#include "testmacros.h"

#include "../../board_Eval/inc/board.h"

//#include "qei_17xx_40xx.h"

//#include "core_cm3.h"

//#include "sysctl_17xx_40xx.h"
//#include "chip_lpc177x_8x.h"



UT_VARIABLE(tSINT32 QEInitDiag)
UT_VARIABLE(tSINT32 QEIHandler)
UT_VARIABLE(tSINT32 QEIRead)
UT_VARIABLE(tSINT32 QEIHandlerFault)

tSINT32 QEIPhaseErrorCnt;

/**************************************************************************//**
* \brief -		QuadratureEncoderInit
*
* \brief -		Initialize Quadrature Encoder Interface
*
* \param -		maxPos : Maximum Position
*
* \return -		none
*
*****************************************************************************/
void QuadratureEncoderInit(tSINT32 maxPos)
{
    FUNCTION1(QEInitDiag, "QuadratureEncoderInit()");


    // Enable power to this block
    LPC_SYSCTL->PCONP |= (PCONP_PCQEI_MASK);

    // Enable clock to this module
    LPC_SYSCTL->PCLKSEL &= ~(PCLKSEL1_PCLK_QEI_MASK); // AND OFF default value
    LPC_SYSCTL->PCLKSEL |= (PCLKSEL1_PCLK_QEI_FUN1); // CCLK/1

    // Configure the pins now
	Chip_IOCON_PinMuxSet(LPC_IOCON, PHA_PORT, PHA_PIN, IOCON_FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, PHB_PORT, PHB_PIN, IOCON_FUNC0);



//    LPC_IOCON->PINSEL3 &= ~(PHASEADISABLEMASK); // Phase A - P1.20
//    LPC_PINCON->PINSEL3 |= (PINSEL3_MCI0);
//    LPC_PINCON->PINSEL3 &= ~(PHASEBDISABLEMASK); // Phase B - P1.23
//    LPC_PINCON->PINSEL3 |= (PINSEL3_MCI1);
 //   LPC_PINCON->PINSEL3 &= ~(INDEXDISABLEMASK); // Index - P1.24
 //   LPC_PINCON->PINSEL3 |= (PINSEL3_MCI2);
 //   LPC_PINCON->PINMODE3 &= ~(PHASEADISABLEMASK); // Phase A - internal pull-up
 //   LPC_PINCON->PINMODE3 |= (ENABLE_PHAHEA_PULLUP);
//    LPC_PINCON->PINMODE3 &= ~(PHASEBDISABLEMASK); // Phase B - internal pull-up
//    LPC_PINCON->PINMODE3 |= (ENABLE_PHAHEB_PULLUP);
//    LPC_PINCON->PINMODE3 &= ~(INDEXDISABLEMASK); // Index - internal pull-up
//    LPC_PINCON->PINMODE3 |= (ENABLE_INDEX_PULLUP);

    // Control Register
    LPC_QEI->CON = QEICON_RESP_ENABLE; // reset the position counter

    // Configuration Configuration Register
    LPC_QEI->CONF = 0 | (QEICONF_DIRINV_ENABLE) // Direction Invert Bit
            // PhA and PhB are quadrature encoder inputs
            | (QEICONF_CAPMODE_ENABLE); // Both PhA & PhB edges are counted (4X)


    // Max position register
    LPC_QEI->MAXPOS = maxPos;

    // Digital Filter Sampling Delay
    LPC_QEI->FILTERPHA = 0;
    LPC_QEI->FILTERPHB = 0;
    // Enable the interrupts
    LPC_QEI->IES = 0
            | (QEIIES_ERR_EN_ENABLE); // encoder phase error detect


    // Set the priority of the interrupt now
    NVIC_SetPriority(QEI_IRQn, NVIC_EncodePriority(6, 1, 2));


    // Enable the interrupt now
    NVIC_EnableIRQ(QEI_IRQn);

}
/**
 *    Resets the position counter to 0
 */
inline void QEI_ResetPosition(void)
{
   LPC_QEI->CON = 1 << 0; // reset the position counter
}
/**************************************************************************//**
* \brief -		QEI_GetPosition
*
* \brief -		Reads the Current Encoder Position and update the variable. If the count is negative resets it to 0.
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void QEI_GetPosition(void)
{

    QEIPosition = LPC_QEI->POS;
    if(0 > QEIPosition)
    {
     	QEI_ResetPosition();
    	QEIPosition = 0;
    }

    return;
}

/**************************************************************************//**
* \brief -		QEI_IRQHandler
*
* \brief -		QEI interrupt handler
*
* \param -		none
*
* \return -		none
*
******************************************************************************/
void QEI_IRQHandler(void)
{
    tUINT32 status = LPC_QEI->INTSTAT;

    FAULT(QEIHandlerFault, {status = (1<<0);});
    FAULT(QEIHandlerFault, {status = (1<<3);});
    FAULT(QEIHandlerFault, {status = (1<<4);});

    // Change of Direction was detected
    if (status & (QEIINTSTAT_DIR_IntENABLE))
    {
//        printf("Direction changed \n");
        // Clear the interrupt now
        LPC_QEI->CLR |= (QEIINTSTAT_DIR_IntENABLE);
    }

    // Encoder phase error was detected
    if (status & (QEIINTSTAT_ERR_IntENABLE))
    {
//        printf("Phase Error\n");
        QEIPhaseErrorCnt++;
        // Clear the interrupt now
        LPC_QEI->CLR |= (QEIINTSTAT_ERR_IntENABLE);
    }
    else
    {
    	QEIPhaseErrorCnt = 0;
    	LEStatus = OK;

    }

    if(QEIPhaseErrorCnt >= QEIPhaseErrorCount)
    {
    	LEStatus = NOK;

    }

}


