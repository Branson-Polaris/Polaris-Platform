/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------
This module has the implementation of the State Machine of the Plastic
 Welder
 Module name: StateMachine
 File name: StateMachine.h
 -------------------------- TECHNICAL NOTES --------------------------------


-------------------------------------------------------------------------*/


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "../../App/inc/global.h"

#include "global.h"
#include "../../../_Branson_User_Common/Commons/Commons.h"


/* Enum Structure for various states of Palm Button Status.*/
enum PALMBUTTON_STATUS
{
   BOTHHANDS_OFF,
   ONEHAND_OFF,
   BOTHHANDS_ON,
   SECONDHANDTOOLATE,
};
/* Enum Structure for various states of Pilot Light Status.*/
enum BEEPER
{
   OFF,
   ON,
   BEEPING
};
/* Enum Structure for various states of EStop Status.*/
enum ESTOPBUTTONSTATUS
{
   NOTPRESSED,
   PRESSED
};
/* Enum Structure for various states of Palm Button output Status.*/
enum PBOUTSTATUS
{
   PB_ENABLED,
   PB_DISABLED
};


enum ALARM
{
	ALARM_0,
	ALARM_1,
	ALARM_2,
	ALARM_3,
};





typedef void (*StateFunc)(void);

typedef struct State {

     StateFunc              Entry;         /* Pointer to executable function      */
     StateFunc  			Loop;        /* Pointer to next state if flag true  */
     StateFunc              Exit;       /* Pointer to next state if flag false */
} STATE;

extern STATE *CurrState;

void ChangeState(ACSTATES);
void StateMachine(void);

//States loop function

void ReadyStateLoop(void);
void DownStrokeStateLoop(void);
void AlarmStateLoop(void);
void ReturnStrokeStateLoop(void);
void PowerUpStateLoop(void);
void EStopStateLoop(void);
void WeldHoldStateLoop(void);


// States Entry functions

void ReadyEntry(void);
void DownStrokeEntry(void);
void AlarmEntry(void);
void ReturnStrokeEntry(void);
void PowerUpEntry(void);
void EStopEntry(void);
void WeldHoldEntry(void);



// States Exit functions

void ReadyExit(void);
void DownStrokeExit(void);
void AlarmExit(void);
void ReturnStrokeExit(void);
void PowerUpExit(void);
void EStopExit(void);
void WeldHoldExit(void);


void Timer0Callback(void);


#endif /* STATEMACHINE_H_ */
