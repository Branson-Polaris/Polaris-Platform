/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
  	It contains the PC State Machine related implementation
***************************************************************************/

#ifndef PSSTATEMACHINE_H_
#define PSSTATEMACHINE_H_
#include "PCState.h"
#include "PCReady.h"
#include "PCWeldRun.h"
#include "PCEstop.h"
#include "PCAlarm.h"
#include "PCSeekRun.h"
#include "Powerup.h"

class PCStateMachine 
{
public:
	virtual						~PCStateMachine		();
	static void					RunStateMachine		();
	//Return pc current state
	static PCState::PCSTATES	GetPCState			();
	static void					ChangeState			(PCState::PCSTATES);
	static PCStateMachine*		GetInstance			();
protected:	
	Powerup*			m_PowerupObj;
	PCReady*			m_ReadyObj;
	PCWeldRun*			m_WeldRunObj;
	PCEstop*			m_EstopObj;
	PCAlarm*			m_AlarmObj;
	PCSeekRun*			m_SeekRunObj;
private:
	PCStateMachine();
	static PCState*			CurrentStateObj;
	static PCStateMachine* 	StateMachineObj;
	static PowerSupplyTask* ptrPSTask;
};
#endif /* PSSTATEMACHINE_H_ */
