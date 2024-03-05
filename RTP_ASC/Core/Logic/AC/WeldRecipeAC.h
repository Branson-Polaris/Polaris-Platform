/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * WeldRecipeAC.h
 *
 *  Created on: Apr 29, 2021
 *      Author: DShilonie
 */

#ifndef WELDRECIPEAC_H_
#define WELDRECIPEAC_H_

#include "Common.h"
#include "Utils.h"

/* Macro defined for set max range value of AC-Weld recipe */ 
#define AC_MAX_WeldForce					3500
#define AC_MAX_ForceRampTime				1000
#define AC_MAX_HoldMode						10
#define AC_MAX_HoldTime						30000
#define AC_MAX_HoldForce					3500
#define AC_MAX_HoldForceRampTime			1000		// changed on 11/12/2017
#define AC_MAX_ExpectedPartContactPosition	125000	
#define AC_MAX_TotalCollapseTarget			50000		// changed on 11/12/2017
#define AC_MAX_ReadyPosition				125000
#define AC_MAX_DownAcceleration				10000
#define AC_MAX_DownMaxVelocity				500
#define AC_MAX_DownDeceleration				10000
#define AC_MAX_ReturnAcceleration			10000
#define AC_MAX_ReturnMaxVelocity			500
#define AC_MAX_ReturnDeceleration			10000
#define AC_MAX_NumForceSteps				10
#define AC_MAX_ForceStepAt					7			// changed on 11/12/2017
#define AC_MAX_ForceStepForce				3500		// changed on 11/12/2017
#define AC_MAX_ForceStepRampTime			1000		// changed on 11/12/2017
#define AC_MAX_PartContactWindowPlus		1			/* Need to get default values */
#define AC_MAX_PartContactWindowMinus		1
#define AC_MAX_ExcepectedPartContactOffset	1


/* Macro defined for set min range value of AC-Weld recipe */
#define AC_MIN_WeldForce					3
#define AC_MIN_ForceRampTime		        0
#define AC_MIN_HoldMode				        0
#define AC_MIN_HoldTime						0	
#define AC_MIN_HoldForce					3	
#define AC_MIN_HoldForceRampTime			0
#define AC_MIN_ExpectedPartContactPosition	0
#define AC_MIN_TotalCollapseTarget			0		// changed on 11/12/2017
#define AC_MIN_ReadyPosition				0
#define AC_MIN_DownAcceleration				1
#define AC_MIN_DownMaxVelocity				1		
#define AC_MIN_DownDeceleration				1
#define AC_MIN_ReturnAcceleration		    1
#define AC_MIN_ReturnMaxVelocity			1
#define AC_MIN_ReturnDeceleration		    1
#define AC_MIN_NumForceSteps				0		// changed on 11/12/2017
#define AC_MIN_ForceStepAt					1		// changed on 11/12/2017
#define AC_MIN_ForceStepForce				3		// changed on 11/12/2017
#define AC_MIN_ForceStepRampTime		    0
#define AC_MIN_ForceStepAtValue				1
#define AC_MIN_PartContactWindowPlus		1		/* Need to get default values */
#define AC_MIN_PartContactWindowMinus		1
#define AC_MIN_ExcepectedPartContactOffset	1

/* Default value of weld recipe for the AC */
#define WELDFORCE_DEFAULT           		10
#define FORCERAMPTIME_DEFAULT      			0
#define TOTALCOLLAPSETARGET_DEFAULT 		0
#define HOLDFORCE_DEFAULT           		10
#define HOLDFORCERAMPTIME_DEFAULT  			0
#define PARTCONTACTPOSITION_DEFAULT			0
#define TOTALCOLLAPSETAR_DEFAULT    		0
#define READYPOSITION_DEFAULT       		0
#define DOWNACCELERATION_DEFAULT    		1000
#define DOWNMAXVELOCITY_DEFAULT     		200
#define DOWNDECELERATION_DEFAULT    		10000
#define RETURNACCELERATION_DEFAULT  		10000
#define RETURNMAXVELOCITY_DEFAULT   		200
#define RETURNDECELERATION_DEFAULT  		10000
#define NUMFORCESTEPS_DEFAULT       		1		// changed 11/12/2017
#define	MAX_NO_OF_FORCE_STEP 				10
#define FORCE_AT 							1


typedef struct  WeldRecipeAC
{
public:
	WeldRecipeAC();

public:
	INT32	WeldForce;
	INT32	ForceRampTime;
	INT32	HoldMode;
	INT32	TotalCollapseTarget;
	INT32	HoldForce;
	INT32	HoldForceRampTime;
	INT32	ExpectedPartContactPosition;
	INT32	ReadyPosition;
	INT32	DownAcceleration;
	INT32	DownMaxVelocity;
	INT32	DownDeceleration;
	INT32	ReturnAcceleration;
	INT32	ReturnMaxVelocity;
	INT32	ReturnDeceleration;
	INT32  ExpectedPartContactOffset;
	INT32  PartContactWindowMinus; 
	INT32  PartContactWindowPlus;
	INT32	NumForceSteps;
    INT32	ForceStepRampTime[MAX_NO_OF_FORCE_STEP];
    INT32	ForceStepForce[MAX_NO_OF_FORCE_STEP]; 		// i.e. the amplitudes themselves
    INT32	ReadyPositionToggle;
    INT32	WeldForceControl;
}WeldRecipeAC;


class AcWeldRecipe
{
public:
	AcWeldRecipe			(const AcWeldRecipe& srcObj) = delete;
	AcWeldRecipe& operator=	(const AcWeldRecipe& srcObj) = delete;
	static AcWeldRecipe& GetInstance();
	
	UINT32	GetPartContactPos	() const;
	UINT16  GetWeldForce		() const;
	void   	SetPartContactPos	(UINT32 position);
	void   	GetWeldRecipe		(WeldRecipeAC& recipe);
	void 	SetWeldRecipe		(WeldRecipeAC& recipe);

private:
	WeldRecipeAC m_Recipe;
	AcWeldRecipe();
	~AcWeldRecipe();
		
};
#endif /* WELDRECIPEAC_H_ */
