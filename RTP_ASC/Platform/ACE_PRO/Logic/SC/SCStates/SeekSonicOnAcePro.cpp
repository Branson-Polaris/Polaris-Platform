/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 SC Seek SonicOnAcePro State
***************************************************************************/

#include "SeekSonicOnAcePro.h"

/**************************************************************************//**
*
* \brief   - Constructor.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SeekSonicOnAcePro::SeekSonicOnAcePro() 
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
SeekSonicOnAcePro::~SeekSonicOnAcePro() 
{	
}

/**************************************************************************//**
*
* \brief   - SeekSonicOn Enter.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSonicOnAcePro::Enter()
{
	SeekSonicOn::Enter();	//Call the base class Enter() to call common code part
}

/**************************************************************************//**
*
* \brief   - SeekSonicOn Loop.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSonicOnAcePro::Loop()
{
	SeekSonicOn::Loop();	//Call the base class Loop() to call common code part
}

/**************************************************************************//**
*
* \brief   - SeekSonicOn Exit.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSonicOnAcePro::Exit()
{
	SeekSonicOn::Exit();	//Call the base class Exit() to call common code part
}

/**************************************************************************//**
*
* \brief   - SeekSonicOn Fail.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSonicOnAcePro::Fail()
{
	SeekSonicOn::Fail();	//Call the base class Fail() to call common code part
}
