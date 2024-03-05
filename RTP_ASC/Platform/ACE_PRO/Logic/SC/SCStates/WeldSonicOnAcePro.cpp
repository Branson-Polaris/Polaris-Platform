/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
 SC Welding State
 
***************************************************************************/

#include "WeldSonicOnAcePro.h"

/**************************************************************************//**
* 
* \brief   - Constructor - initialize the data members of WeldSonicOn.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
WeldSonicOnAcePro::WeldSonicOnAcePro() 
{
}

/**************************************************************************//**
* 
* \brief   - Destructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
WeldSonicOnAcePro::~WeldSonicOnAcePro() 
{
}

/**************************************************************************//**
*
* \brief   - Weld Sonic On Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnAcePro::Enter()
{
	WeldSonicOn::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
*
* \brief   - Weld Sonic On Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnAcePro::Loop()
{
	WeldSonicOn::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
*
* \brief   - Weld Sonic On Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnAcePro::Exit()
{
	WeldSonicOn::Exit();	//Call the base class Exit() to call common code part
}

/**************************************************************************//**
*
* \brief   - Weld Sonic On Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSonicOnAcePro::Fail()
{
	WeldSonicOn::Fail();	//Call the base class Fail() to call common code part
}
