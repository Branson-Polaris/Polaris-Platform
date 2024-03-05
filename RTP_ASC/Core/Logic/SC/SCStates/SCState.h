/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	 This file processes the messages based on MsgQ-ID
***************************************************************************/

#ifndef SCSTATE_H_
#define SCSTATE_H_
#include "CommonProperty.h"
#include "GPIO.h"
#include "Logger_old.h"
#include "commons.h"

class SCState {
public:
	enum ACTIONS
	{
		INIT = 0,
		LOOP,						// Normal state, move on to next value        
		FAIL,						// Set FailFlag for later checking            
		ABORT,						// Set AbortFlag for later checking           
		JUMP,						// This state is complete, go to next state  
		ALJUMPNORM,					// This state is complete, go to next state,with alarms  
		POP,						// Return to PUSHed state previously saved   
		PUSH,						// Save current state index for possible POP 
	};

	ACTIONS			m_Actions;		// To access particular Action
	SCSTATES		m_State;		// To access particular State
	unsigned int	m_StepIndex;	// Index of particular step

	SCState();
	virtual ~SCState();

	virtual void Enter() = 0;		// Function to call on entry          
	virtual void Loop () = 0;		// Function to call every pass       
	virtual void Exit () = 0;		// Function to call on exit           
	virtual void Fail () = 0;		// Function to call on alarm handling
	
	CommonProperty*	CP;				//Instance of CommonProperty
};

#endif /* SCSTATE_H_ */
