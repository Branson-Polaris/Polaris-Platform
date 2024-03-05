/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   	 
  	 It contains the SC State Machine related implementation
***************************************************************************/

#ifndef SCSTATEMACHINE_H_
#define SCSTATEMACHINE_H_
#include "SCState.h"
#include <list>
#include <vector>
#include <map>
#include "SCAction.h"
#include "PowerSupplyTask.h"

class SCStateMachine {
public:
	enum OPERATION
	{
		NO_OPERATION = -1,
		POWER_UP,
		WELD,
		SEEK,
		FIND_PART_CONTACT_OP,
		HORN_RETRACT,
		RESET_ALARM,
		SCAN,
		HEIGHT_CALIBRATE_READY,
		TEST,
		TEACH_MODE,
		BATCH_WELD,
		RESET_ALL_ALARM,
		END_OPERATION
	};
	
public:
	SCStateMachine();
	virtual 				~SCStateMachine();
	void 					RunStateMachine();								// Member function to Run SC State Machine
	bool 					GetStateMachineStatus() const;					// SC State Machine status
	static SCSTATES			GetSCState();		    						// SC Current State
	int 					LoadStatesHandler(OPERATION operation);			// Load state objects in State List based on operation type
	UINT32 				    CycleTime ();									// Returns total weld cycle time
	
private:
	void deleteAll();
	PowerSupplyTask* ptrPSTask;
protected:
	vector<SCState*>* 				_objStateList;							// Vector contains list of states
	map<SCSTATES, SCState*>*		_objActionMap;							// Associates a key(SCSTATES) to a mapped value(SCState)
	unsigned int					m_StateIndex;							// Index of particular state
	bool							m_IsRunning;							// SC State Machine status running or not
	bool							m_IsLoading;							// Idle state
	static SCState* 				m_objState;								// stateMachine pointer to point to particular state or action
	static SCStateMachine* 			m_StateMachineObj;						// StateMachine object
	static SEM_ID 					m_semaphoreMutex; 						// Holds ID of mutex semaphore
	virtual void 					SelectWeldSequence() = 0;				// Member Function to execute sequence according to WELD operation
	virtual void 					SelectSeekSequence() = 0;				// Member Function to execute sequence according to SEEK operation

};

#endif /* SCSTATEMACHINE_H_ */
