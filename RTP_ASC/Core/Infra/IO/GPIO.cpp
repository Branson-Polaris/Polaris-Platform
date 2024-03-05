/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2018
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

     GPIO Control functionality implementation
 
**********************************************************************************************************/
#include <vxWorks.h>        //for vxworks main
#include <iostream>
//#include <taskLib.h>        //for taskdelay()
//#include <subsys/gpio/vxbGpioLib.h> 
//#include "McSPI.h"
//#include <subsys/gpio/vxbGpioLib.h> 
//#include "McSPI.h"

extern "C"
{
	#include <customSystemCall.h>
}

#include "GPIO.h"

using namespace std;

/**************************************************************************//**
* \brief   - This function is to initialize GPIO lines.
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
INT16 GpioInit(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;
	
	//Initial GPIO reset line
	//The followings are used in DKM, not RTP
//	stat = GpioAlloc(GPIO_4_0);
//	stat |= GpioAlloc(GPIO_4_1);
//	stat |= GpioAlloc(GPIO_4_2);
//	stat |= GpioAlloc(GPIO_4_3);
//	stat |= GpioAlloc(GPIO_4_4);
//	stat |= GpioAlloc(GPIO_4_5);
//	stat |= GpioAlloc(GPIO_4_6);
//	stat |= GpioAlloc(GPIO_4_7);
//	stat = GpioFree(GPIO_EXT_PWR);
	stat = GpioAlloc(GPIO_IO_RESET);    //E4, O, /GPIO_IO_RESET
	stat |= GpioAlloc(GPIO_BLUE_LED);    //D3, O, GPIO drive blue led
	stat |= GpioAlloc(GPIO_INP_INT);   //B26, I, /GPIO_INP_INT
	stat |= GpioAlloc(GPIO_EXT_SONICS); //G13, I, GPIO_EXT_SONICS
	
	if (GPIO_OK == stat)
	{
		//The followings are used in DKM, not RTP
//		stat = GpioSetDir(GPIO_4_0, GPIO_DIR_INPUT);
//		stat |= GpioSetDir(GPIO_4_1, GPIO_DIR_INPUT);
//		stat |= GpioSetDir(GPIO_4_2, GPIO_DIR_INPUT);
//		stat |= GpioSetDir(GPIO_4_3, GPIO_DIR_INPUT);

//		stat |= GpioSetDir(GPIO_4_4, GPIO_DIR_OUTPUT);
//		stat |= GpioSetDir(GPIO_4_5, GPIO_DIR_OUTPUT);
//		stat |= GpioSetDir(GPIO_4_6, GPIO_DIR_OUTPUT);
//		stat |= GpioSetDir(GPIO_4_7, GPIO_DIR_OUTPUT);
		stat = GpioSetDir(GPIO_IO_RESET, GPIO_DIR_OUTPUT);
//		stat |= GpioSetDir(GPIO_EXT_PWR, GPIO_DIR_OUTPUT);  //F5, O, GPIO_EXT_PWR
		stat |= GpioSetDir(GPIO_BLUE_LED, GPIO_DIR_OUTPUT); //Blue Led
		stat |= GpioSetDir(GPIO_INP_INT, GPIO_DIR_INPUT);  //B26, I, /GPIO_INP_INT
		stat |= GpioSetDir(GPIO_EXT_SONICS, GPIO_DIR_INPUT); //G13, I, GPIO_EXT_SONICS
	}
	
	return stat;
}

/**************************************************************************//**
* \brief   - This function is to disable /IO_RESET pin,
* 			 which will be enable the devices connected
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
INT16 GpioIOResetDis(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;

	val = GpioGetDir(GPIO_IO_RESET);
	if(GPIO_DIR_OUTPUT == val)
	{
		//Disable /IO_RESET pin, which will be enable the devices connected
		stat = GpioSetValue(GPIO_IO_RESET, GPIO_VALUE_HIGH); 
	}
	
	return stat;
}

/**************************************************************************//**
* \brief   - This function is to enable /IO_RESET pin,
* 			 which will be reset the devices connected
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
INT16 GpioIOResetEn(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;

	val = GpioGetDir(GPIO_IO_RESET);
	if(GPIO_DIR_OUTPUT == val)
	{
		//Enable /IO_RESET pin, which will reset the devices connected
		stat = GpioSetValue(GPIO_IO_RESET, GPIO_VALUE_LOW); 
	}
	
	return stat;
}	

/**************************************************************************//**
* \brief   - This function is to get status of /IO_RESET pin
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
UINT16 GpioIOIsReset(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;

	val = GpioGetValue(GPIO_IO_RESET);
	if(LINE_LOW == val)
	{
		stat = GPIO_IS_RESET; 
	}
	else
	{
		stat = GPIO_IS_NOT_RESET; 	
	}
	
	return stat;
}	

/**************************************************************************//**
* \brief   - This function is to  enable powers v5_0EXT and V12_0EXT
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
INT16 GpioExtPwrEn(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;

	val = GpioGetDir(GPIO_EXT_PWR);
	if(GPIO_DIR_OUTPUT == val)
	{
		//Enable powers v5_0EXT and V12_0EXT
		stat = GpioSetValue(GPIO_EXT_PWR, GPIO_VALUE_LOW); 
	}
	
	return stat;
}	

/**************************************************************************//**
* \brief   - This function is to disable powers v5_0EXT and V12_0EXT
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/
INT16 GpioExtPwrDis(void)
{	
	INT16 stat = GPIO_ERROR;
	UINT16 val;

	val = GpioGetDir(GPIO_EXT_PWR);
	if(GPIO_DIR_OUTPUT == val)
	{
		//Disable powers v5_0EXT and V12_0EXT
		stat = GpioSetValue(GPIO_EXT_PWR, GPIO_VALUE_HIGH); 
	}
	
	return stat;
}	
