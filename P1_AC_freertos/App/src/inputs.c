/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for All the Inputs.

Module name: Input

Filename:    Input.c

--------------------------- TECHNICAL NOTES -------------------------------

This code handle all the Digital and Analog Inputs as well as the Debouncing of Digital inputs..



-------------------------------------------------------------------------*/

#include "global.h"
#include "inputs.h"

#include "ADCTest.h"
#include "../../board_Eval/inc/board.h"
#include "../../chip/inc/gpio_17xx_40xx.h"

#include "global.h"
#include "../../../_Branson_User_Common/Commons/Commons.h"
#include "Main.h"

#define DEBOUNCE_TIME 2
#define OFF 0
#define ON 1


static tUINT32 InputValues[DEBOUNCE_TIME] =
        { 0, 0};
static tUINT16 DebounceIndex = 0;
tSINT32 ULS;

//union Input lastInputs;
Digital_Inputs CurrInputs;//Will hold the current debounced input values.
Digital_Inputs TempCurrInputs;//Will hold the current values only.
extern void App_Interrupt_Test();
extern TxPDO_AC txpdoac;
/**************************************************************************//**
* \brief -		ReadDigitalInputs
*
* \brief -		Read all the digital input value.
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void ReadDigitalInputs(void)
{

	static unsigned int temp;//added for testing purpose , need to remove once we know which pin to read for which member.

#ifdef PRODUCTION
    TempCurrInputs.InputBits.EN_Alarm0 = Chip_GPIO_GetPinState(LPC_GPIO, EN_ALARM0_PORT,EN_ALARM0_PIN) ?1:0;
    TempCurrInputs.InputBits.EN_Alarm1 = Chip_GPIO_GetPinState(LPC_GPIO, EN_ALARM1_PORT,EN_ALARM1_PIN) ?1:0;
    TempCurrInputs.InputBits.EN_Alarm2 = Chip_GPIO_GetPinState(LPC_GPIO, EN_ALARM2_PORT,EN_ALARM2_PIN) ?1:0;
    TempCurrInputs.InputBits.EN_Alarm3 = Chip_GPIO_GetPinState(LPC_GPIO, EN_ALARM3_PORT,EN_ALARM3_PIN) ?1:0;
    TempCurrInputs.InputBits.EStop1 = Chip_GPIO_GetPinState(LPC_GPIO, ESTOP1_PORT,ESTOP1_PIN) ?1:0;
    TempCurrInputs.InputBits.EStop2 = Chip_GPIO_GetPinState(LPC_GPIO, ESTOP2_PORT,ESTOP2_PIN) ?1:0;
    TempCurrInputs.InputBits.PB2_OUT = Chip_GPIO_GetPinState(LPC_GPIO, PB_OUT2_PORT,PB_OUT2_PIN) ?1:0;
    TempCurrInputs.InputBits.PB1_OUT = Chip_GPIO_GetPinState(LPC_GPIO, PB_OUT1_PORT,PB_OUT1_PIN) ?1:0;
	TempCurrInputs.InputBits.TRS = Chip_GPIO_GetPinState(LPC_GPIO, TRS_PORT,TRS_PIN) ?1:0;
    TempCurrInputs.InputBits.ULS = Chip_GPIO_GetPinState(LPC_GPIO, ULS_PORT,ULS_PIN) ?1:0;
#else
    TempCurrInputs.InputBits.ULS = Chip_GPIO_GetPinState(LPC_GPIO, 2,25) ?1:0;
#endif
//	DEBUGOUT("ULS bit: %d\r\n",TempCurrInputs.AllInputs );
	InputValues[DebounceIndex++] = TempCurrInputs.AllInputs;
    DebounceIndex %= DEBOUNCE_TIME;


	txpdoac.ACInputs = temp++;
	if (TRS == ON)
	{
		txpdoac.ActualForce = 50;
	}
	else
	{
		txpdoac.ActualForce = 0;
	}
	txpdoac.ActualDistance = 0;
	txpdoac.ACStatusEvent = 0;
	txpdoac.ACState = State;

}
/**************************************************************************//**
* \brief -		DoDebouncing
*
* \brief -		Debouncing the digital input value.
*
* \param -		void
*
* \return -	void
*
*****************************************************************************/
void DoDebouncing(void)
{

    tUINT32 ANDMask;
    tUINT32 ORMask;
    tUINT32 Index;
    tUINT32 Result;

    /* Now do debouncing */
    // Initialize the masks
    ANDMask = 0xFFFFFFFF;
    ORMask  = 0x00000000;

    // Initialize with data from last time around
    Result = CurrInputs.AllInputs;
        for (Index = 0; Index < DEBOUNCE_TIME; Index++)
        {

            ANDMask &= InputValues[Index];
            ORMask  |= InputValues[Index];
        }


        Result &= ORMask;
        Result |= ANDMask;
        CurrInputs.AllInputs = Result;
}
/**************************************************************************//**
* \brief -		CheckMachineConfiguration
*
* \brief -		To check what kind of machine is it. GSX-E/P or GSXI.
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void CheckMachineConfiguration(void)
{

 //  FAULT(MachineConFault, {ADC0Value[1] = 100;});
 //  FAULT(MachineConFault, {ADC0Value[1] = 0;});

   if ((ADC0Value[1] > ADC_0VOLT_RANGE) && (ADC0Value[0] > ADC_0VOLT_RANGE))
   {

      MachineConfiguration = GSXE; //Servo
   }
   else
   {

      if((ADC0Value[1] < ADC_0VOLT_RANGE) && (ADC0Value[0] < ADC_0VOLT_RANGE))
      {

    	  MachineConfiguration = GSXP1; //Pneumatic
      }
      else
      {

    	  if((ADC0Value[1] > ADC_0VOLT_RANGE) && (ADC0Value[0] < ADC_0VOLT_RANGE))
    	  {
    		  MachineConfiguration = GSXP1PLUS; //
    	  }
      }
   }
}
/**************************************************************************//**
* \brief -		UpdateInputGlobalVars
*
* \brief -		Function Updates globals variables according to the current input value.
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void UpdateInputGlobalVars(void)
{



//    TRS = (LPC_GPIO->FIOPIN & TRS_MASK)?1:0;
//    DRIVE_FAIL = !CurrInputs.InputBits.DriveFail;     //Active low
//    SV2_FAIL = !CurrInputs.InputBits.SV2Fail;     //Active low
//    SONICS_FAIL = !CurrInputs.InputBits.SONICSFail; //Active low



    ESTOP1 = CurrInputs.InputBits.EStop1;
    ESTOP2 = CurrInputs.InputBits.EStop2;
    if(CurrInputs.InputBits.ULS == 0)
    {
    	ULS = 0;
    }
    else
    {
    	ULS = 1;
    }
//	DEBUGOUT("ULS bit: %d\r\n",CurrInputs.InputBits.ULS );

//.	App_Interrupt_Test();//Need to fix this as enabling it, causing code to get stuck in this api
    //    PB2_NO_IN = CurrInputs.InputBits.PB2_NO;
//    PB1_NO_IN = CurrInputs.InputBits.PB1_NO;
//    UFAIL24V = CurrInputs.InputBits.UFail24V;


//    FAULT(UpdateInputFault, {ESTOP1 = ESTOP1PRESSEDCPU1; ESTOP2 = ESTOP2PRESSEDCPU1;});
//    FAULT(UpdateInputFault, {ESTOP1 = ESTOP1NOTPRESSEDCPU1; ESTOP2 = ESTOP2NOTPRESSEDCPU1;});
//    FAULT(UpdateInputFault, {ESTOP1 = ESTOP1PRESSEDCPU2; ESTOP2 = ESTOP2PRESSEDCPU2;});
//    FAULT(UpdateInputFault, {ESTOP1 = ESTOP1NOTPRESSEDCPU2; ESTOP2 = ESTOP2NOTPRESSEDCPU2;});
//    if(IsThisCPU1)
//    {

//    }
//    else
//    {

//    }
    // Check Machine Configuration Type

}
/**************************************************************************//**
* \brief -		GetInputs
*
* \brief -		Function called every millisecond to read all inputs.
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void GetInputs(void)
{

   /* First read all inputs */
   ReadDigitalInputs();
   DoDebouncing();
   UpdateInputGlobalVars();

}

/**************************************************************************//**
* \brief -		InitInputs
*
* \brief -		Function called at first time after Input initialized so that
*  				InputValues buffer can be filled up by valid values.
*
* \param -		none
*
* \return -		none
*
*****************************************************************************/
void InitInputs(void)
{
   uint32_t Index;

   ReadDigitalInputs();
   for (Index = 0; Index < DEBOUNCE_TIME; Index++)
   {
        InputValues[Index] = TempCurrInputs.AllInputs;
   }
   UpdateInputGlobalVars();
}

#if UNIT_TESTING
/**************************************************************************//**
* \brief -		ResetHandler
*
* \brief -		ResetHandler is the entry point for Inputs test unit testing.
*
* \param -		none
*
* \return -	none
*
*****************************************************************************/
void ResetHandler(void)
{


}
#endif
