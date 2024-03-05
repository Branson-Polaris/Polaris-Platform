/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for State machine implementation.

Module name: StateMachine

Filename:    StateMachine.c

--------------------------- TECHNICAL NOTES -------------------------------

The code is for different states involved in state machine and conditions
under which state transition takes place.

--------------------------------------------------------------------------*/
#include "statemachine.h"
#include "SetOutputs.h"
#include "global.h"
#include "main.h"
#include "../../board_Eval/inc/board.h"



//		States						Entry code			Loop code			        Exit code
 STATE PowerUpState	    	    =		{PowerUpEntry		,PowerUpStateLoop       ,PowerUpExit};
 STATE ReadyState 			    = 		{ReadyEntry			,ReadyStateLoop			,ReadyExit};
 STATE AlarmState 			    = 		{AlarmEntry			,AlarmStateLoop			,AlarmExit};
 STATE DownStrokeState 	        = 		{DownStrokeEntry	,DownStrokeStateLoop	,DownStrokeExit};
 STATE ReturnStrokeState	    =	    {ReturnStrokeEntry	,ReturnStrokeStateLoop	,ReturnStrokeExit};
 STATE EStopState	            =	    {EStopEntry	        ,EStopStateLoop     	,EStopExit};
 STATE WeldHoldState	        =	    {WeldHoldEntry	     ,WeldHoldStateLoop     ,WeldHoldExit};



 STATE *CurrState = &PowerUpState;


 /**************************************************************************
 * \brief  - Jump to the next state.
 *
 * \param  - NextState.
 *
 * \return  - none.
 *
 ******************************************************************************/

 void ChangeState(ACSTATES NextState)
 {

 	static int FirstTime = TRUE;  //Avoids execute exit code at power up
 	if(FirstTime)
 	{
 		FirstTime = FALSE;
 	}
 	else
 	{
 		#if UNIT_TESTING
 		#else
 		CurrState->Exit();
 		#endif
 	}

 	State = NextState;

 	switch (State)
    {
		case AC_READY:
			CurrState = &ReadyState;
		break;

		case AC_ALARM:
			CurrState = &AlarmState;
		break;

		case DOWN_STROKE:
			CurrState = &DownStrokeState;
		break;

		case RETURN_STROKE:
			CurrState = &ReturnStrokeState;
		break;

		case POWERUP:
			CurrState = &PowerUpState;
		break;

		case AC_ESTOP:
			CurrState = &EStopState;
		break;

		case WELD_HOLD:
			CurrState = &WeldHoldState;
		break;

		default:
			CurrState = &AlarmState;
		break;
	}

 	#if UNIT_TESTING
 	#else
 	CurrState->Entry();
 	#endif
}

 /**************************************************************************
 * \brief  - StateMachine().
 *
 * \param  - none.
 *
 * \return  - none.
 *
 ******************************************************************************/
void StateMachine()
{

	CurrState->Loop();

}
