/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------
 Power supply state machine  
***************************************************************************/

#ifndef PSSTATE_H_
#define PSSTATE_H_
#include "CommonProperty.h"
#include "Utils.h"
#include "GPIO.h"
#include "PowerSupplyTask.h"

#define	NO_ERROR 						0
#define	ERR_POWER_OVERLOAD				BIT(0)  //0x01
#define	ERR_WELDERROR					BIT(0) 	//0x01,
#define	ERR_CURRENT_OVERLOAD			BIT(1)  //0x02,
#define	ERR_VOLTAGE_OVERLOAD 			BIT(2)  //0x04,
#define	ERR_TEMP_OVERLOAD				BIT(3)  //0x08,
#define	ERR_DDSFREQ_LOWSEEKLIMIT		BIT(4)  //0x10,
#define	ERR_DDSFREQ_HIGHSEEKLIMIT 		BIT(5)  //0x20,

#define	ERR_DDSFREQ_LOWWELDLIMIT 		BIT(6)  //0x40,
#define	ERR_DDSFREQ_HIGHWELDLIMIT 		BIT(7)  //0x80,
#define	ERR_PHASELIMIT_TIMEERROR 		BIT(8)  //0x100,
#define	ERR_15V_LOST					BIT(11) //0x800,  
#define	ERR_PWR_AVG_OVERLOAD 			BIT(16) //0x10000,

class PCState 
{
public:
	enum PCSTATES
	{
		PC_POWERUP,
		PC_READY,
		PC_WELD_RUN,
		PC_SEEK_RUN,
		PC_WELD_HD_RUN,
		PC_ALARM, 
		PC_SCAN_RUN,
		PC_TEST_RUN,
		PC_ESTOP
	};
	
	enum PC_CONTROL_EVENTS
	{
		CTRL_PC_SONIC_DISABLE,
		CTRL_TMR_INTERVAL,
		CTRL_POWER_UP_RECIPE,
		CTRL_PC_CLEAR_ALARMS,
		CTRL_PREBURST_ENABLE,
		CTRL_WELDTEST,
		CTRL_AFTERBURST_ENABLE,
		CTRL_ESTOP
	};
	
	enum PC_STATUS_EVENTS
	{
		STATUS_TMR_INTERVAL,
		STATUS_PC_CLEAR_ALARMS,
		STATUS_PREBURST_ENABLE,
		STATUS_AFTERBURST_ENABLE,
		STATUS_SOURCE_LOST,
	};
public:
	virtual void 		Enter			() = 0;
	virtual void  		Loop			() = 0;
	virtual void  		Exit			() = 0;
	
	virtual void 		ChangeState		(PCSTATES nextState);
	virtual PCSTATES 	GetStateType	() {return  stateType;}	
	PCSTATES 			stateType;
};

#endif /* PSSTATE_H_ */
