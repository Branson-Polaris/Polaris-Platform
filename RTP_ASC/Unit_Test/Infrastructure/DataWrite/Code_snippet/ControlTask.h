/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  		This file Controls state machine functionalities
***************************************************************************/

#ifndef CONTROLTASK_H_
#define CONTROLTASK_H_

#include <taskLib.h>
#include "Common.h"
#include "CommonProperty.h"
#include "SCTask.h"
#include "commons.h"
#include "SCState.h"
#include "SCStateMachine.h"
#include "PCStateMachine.h"
#include "SCStateMachineAcePro.h"
#include "SCStateMachineFromGPIO.h"
#include "SystemType.h"

typedef enum {
	FREQ_NONE,
	FREQ_SERIES,
	FREQ_PARALLEL
} RESONANCE_FREQ_TYPE;

enum OPERATION
{
	NO_OPERATION	= 0,
	WELD,		 	
	SEEK,
	FIND_PART_CONTACT_OP,
	JOG_UP_OP,
	JOG_DOWN_OP,
	JOG_READY_POSITION,
	HORN_DOWN_CLAMP_ON,
	HORN_DOWN_CLAMP_OFF,
	HORN_RETRACT,
	ALARM,
	RESET_ALARM,
	SCAN,
	ABORT,
	CALIBRATION,
	TEST,
	STOPTEST,
	ABORT_TEST,
	RESET_ALL_ALARM,
	AC_GO_HOME,
	AC_GO_READY
};

// state machine common defines
#define CALIBRATION_FINISH 			3
#define CALIBRATION_ABORT			4
#define PB_ACTIVE_TIME_OUT_IN_US	6000000
#define PP_ACTIVE_TIME_OUT_IN_US	4000000
#define	PDO_CYCLE_TIME_IN_US 		1000
#define CLIENT_TIME_OUT_IN_US		100000
#define STAGGER_TIME_IN_US    		200000
#define INTERVAL_INDICATION			1000				
#define WAIT_FOR_RDY_POS_TIME_IN_US	4000000

#define ACT_RX_EVENT_INTERVAL		(5 * (1000 / CTRL_CYCLE_TIME_IN_US))
#define DSP_1MS_EVENT_INTERVAL       (1 * (1000 / CTRL_CYCLE_TIME_IN_US))
constexpr int CTRL_CYCLE_TIME_IN_US	= 250;

typedef enum ACTUATOR_SETUP
{
	ABS_POSITION,
	PRE_PART_CONTACT,
	VELOCITY,
	EXP_PART_CONTACT,
	ACTUAL_FORCE,
	ACTUAL_DISTANCE
}ACTUATOR_SETUP;

/* The structure used for sending response to UIC, While performing any of actuator setup operations */
typedef struct ActuatorSetup
{
	UINT8	ResponseType;			/* FIND_PART_CONTACT_OP, JOG-UP/DOWN, HORN_DOWN, HORN_RETRACT, READY POSITION */
	UINT8	ResponseStatus;			/* Indicates operation status - Success or fail */		
	UINT32 	AbsolutePosition;
	UINT16 	PrePartContactVelocity;
	UINT32 	PrePartContact;
	UINT32 	ExpectedPartContact;
	UINT16	ActualForce;
	UINT32  ActualDistance;
}ActuatorSetup;

class ControlTask : public SCTask
{
public:
	enum MESSAGE_IDENTIFY
	{
		/* Macro defined to UIC */
		TO_CTRL_OPERATE_MODE_SET = 0,
	};

	ControlTask();
	~ControlTask();
    static void* 		Control_Task					(void *);
	static OPERATION 	GetOperationType				();
	void				TriggerConsoleTask				();
	void				StateMachineHandler				();
	static void			SetOperationType				(OPERATION typeofOp);
	static void			UpdateCycleCounter				();
	static unsigned int	GetCycleCounter					();
	static bool			IsAlarmReset					();
	static bool			IsSuspectStatus					();
	static bool			IsRejectStatus					();
	static void			SetIsAlarmReset					(bool set);
	static void			SetIsSuspectStatus				(bool set);
	static void			SetIsRejectStatus				(bool set);

public:
	static bool		bIndicateUIC;
	static bool		bHornClampOn;
	
	static	UINT8			emmcWearLevel;
	static OPERATION 		nextOpType;
	static OPERATION 		OpType, PrevOpType;	//operation type (Weld or Seek) 
	static bool				bResultConfig;
	static UINT8			calibrationStep;	
	static bool 			bPostWeldDone;
	static bool 			bPreWeldDone;
	static bool 			bWeldOp;
	static UINT32			m_CycleCounter;
	bool					bAlarmData;
	bool					bPowerup;
	static bool				bWeldAllowed;
	static bool				bLimitExceed;
	UINT8					m_Setup;
	static ActuatorSetup 	m_SetupData;
	static UINT32			m_PartsPerMinCounter;
	static bool 			bAlarmReset;
	static bool				bSuspectStatus, bRejectStatus;
	void					ProcessTaskMessage				(Message& message);	
};
#endif /* CONTROL_TASK_H_ */
