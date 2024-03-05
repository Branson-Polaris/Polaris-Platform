/*
 * @brief ADC example
 * This example show how to  the ADC in 3 mode : Polling, Interrupt and DMA
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "global.h"

#include "../../board_Eval/inc/board.h"


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#ifdef BOARD_NXP_LPCXPRESSO_1769
#define _ADC_CHANNLE ADC_CH0
#else
#define _ADC_CHANNLE ADC_CH2
#endif
#define _LPC_ADC_ID LPC_ADC
#define _LPC_ADC_IRQ ADC_IRQn


static ADC_CLOCK_SETUP_T ADCSetup;


static volatile uint8_t Burst_Mode_Flag = 0, Interrupt_Continue_Flag;
static volatile uint8_t ADC_Interrupt_Done_Flag, channelTC;
uint32_t ADC_Done = 0;
void App_Interrupt_Test(void);
void ADCInit(void);

/**************************************************************************//**
* *\brief  - Print ADC value and delay
*
* \param  - uint16_t data adc value
*
*
* \return  - none
*
******************************************************************************/
static void App_print_ADC_value(uint16_t data)
{
	volatile uint32_t j;
	j = 5000000;
	DEBUGOUT("ADC value is : 0x%04x\r\n", data);
	/* Delay */
	while (j--) {}
}

/**************************************************************************//**
* *\brief  - ADC0 interrupt handler sub-routine
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ADC_IRQHandler(void)
{
	uint16_t dataADC = 0;
	/* Interrupt mode: Call the stream interrupt handler */
	DEBUGOUT("irq: %d\r\n",dataADC );
	NVIC_DisableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, 2, 0);
	Chip_ADC_ReadValue(_LPC_ADC_ID, 2, &dataADC);
	ADC_Interrupt_Done_Flag = 1;
	App_print_ADC_value(dataADC);
	Interrupt_Continue_Flag = 0;
}

/**************************************************************************//**
* *\brief  - *ADC Initialization
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void ADCInit(void){

	Chip_ADC_Init(_LPC_ADC_ID, &ADCSetup);
	DEBUGOUT("adcsetup: %d\r\n",ADCSetup.bitsAccuracy );
    Chip_ADC_EnableChannel(_LPC_ADC_ID, ADC_CH2, 1);
    ADC_Done =1;
}

/**************************************************************************//**
* *\brief  - Interrupt routine for ADC example
*
* \param  - none
*
*
* \return  - none
*
******************************************************************************/
void App_Interrupt_Test(void)
{

//	uint16_t dataADC;

	/* Enable ADC Interrupt */
	NVIC_EnableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, 2, 1);
	DEBUGOUT("apptest: %d\r\n",_LPC_ADC_IRQ );


	Interrupt_Continue_Flag = 1;
	ADC_Interrupt_Done_Flag = 1;
	while (Interrupt_Continue_Flag) {
		if (ADC_Interrupt_Done_Flag) {
			ADC_Interrupt_Done_Flag = 0;
			Chip_ADC_SetStartMode(_LPC_ADC_ID, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		}
	}

	/* Disable ADC interrupt */
	NVIC_DisableIRQ(_LPC_ADC_IRQ);

}
