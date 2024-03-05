/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * WeldRecipeAC.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: DShilonie
 */

#include "WeldRecipe.h"
#include "CommonProperty.h"

/**************************************************************************//**
* 
* \brief   - Initialization of class members and memory for object.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AcWeldRecipe::AcWeldRecipe()
{
	WeldRecipeAC	ACData;
	// defaults for AC weld recipe
	ACData.WeldForce = WELDFORCE_DEFAULT;
	SetWeldRecipe(ACData);
}

/**************************************************************************//**
* 
* \brief   - Memory release of object. 
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
AcWeldRecipe::~AcWeldRecipe()
{
}

/**************************************************************************//**
* 
* \brief   - get singleton instance of AcWeldRecipe.
*
* \param   - None.
*
* \return  - AcWeldRecipe instance.
*
******************************************************************************/
AcWeldRecipe& AcWeldRecipe::GetInstance()
{
	static AcWeldRecipe instance; 
					   
	return instance;
}

/**************************************************************************//**
* 
* \brief   - returns the updated part contact position .
*
* \param   - None.
*
* \return  - UINT32 - ExpectedPartContactPosition.
*
******************************************************************************/
UINT32 AcWeldRecipe::GetPartContactPos() const
{
	return m_Recipe.ExpectedPartContactPosition;
}

/**************************************************************************//**
* 
* \brief   - returns the updated part contact position .
*
* \param   - None.
*
* \return  - UINT16 - WeldForce.
*
******************************************************************************/
UINT16 AcWeldRecipe::GetWeldForce() const
{
	return m_Recipe.WeldForce;
}

/**************************************************************************//**
* 
* \brief   - updates the part contact position.
*
* \param   - UINT32 - position.
*
* \return  - None.
*
******************************************************************************/
void AcWeldRecipe::SetPartContactPos(UINT32 position)
{	
	m_Recipe.ExpectedPartContactPosition = position;
}

/**************************************************************************//**
* 
* \brief   - Get the member data of ACWeldRecipe.
*
* \param   - WeldRecipeAC& recipe.
*
* \return  - None.
*
******************************************************************************/
void AcWeldRecipe::GetWeldRecipe(WeldRecipeAC& recipe)
{
	recipe = m_Recipe;
}

/**************************************************************************//**
* 
* \brief   - Assign recipe values to member data. 
*
* \param   - WeldRecipeAC& recipe.
*
* \return  - None.
*
******************************************************************************/
void AcWeldRecipe::SetWeldRecipe(WeldRecipeAC& recipe)
{
	m_Recipe = recipe;
}

WeldRecipeAC::WeldRecipeAC()		/* Constructor of WeldRecipeAC structure which is defined in WeldRecipe.h */
{
		/* default constructor initializes each parameter with the min value */
		WeldForce 				= AC_MIN_WeldForce;
		ForceRampTime 			= AC_MIN_ForceRampTime;
		HoldMode 				= AC_MIN_HoldMode;
		TotalCollapseTarget 	= AC_MIN_TotalCollapseTarget;
		HoldForce 				= AC_MIN_HoldForce ;
		HoldForceRampTime 		= AC_MIN_HoldForceRampTime;
		ExpectedPartContactPosition = AC_MIN_ExpectedPartContactPosition;
		ReadyPosition  			= AC_MIN_ReadyPosition;
		DownAcceleration 		= AC_MIN_DownAcceleration;
		DownMaxVelocity 		= AC_MIN_DownMaxVelocity;
		DownDeceleration 		= AC_MIN_DownDeceleration;
		ReturnAcceleration 		= AC_MIN_ReturnAcceleration;
		ReturnMaxVelocity 		= AC_MIN_ReturnMaxVelocity;
		ReturnDeceleration 		= AC_MIN_ReturnDeceleration;
		NumForceSteps 			= AC_MIN_NumForceSteps;
		ForceStepForce[0] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[0] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[1] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[1] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[2] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[2] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[3] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[3] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[4] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[4] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[5] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[5] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[6] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[6] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[7] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[7] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[8] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[8] 	= AC_MIN_ForceStepRampTime;
		ForceStepForce[9] 		= AC_MIN_ForceStepForce;
		ForceStepRampTime[9] 	= AC_MIN_ForceStepRampTime;
		
		PartContactWindowMinus	= AC_MIN_PartContactWindowMinus; 
		PartContactWindowPlus	= AC_MIN_PartContactWindowPlus;
		ExpectedPartContactOffset = AC_MIN_ExcepectedPartContactOffset;
		WeldForceControl		= (UINT16)CONTROL_HIGH;
}


