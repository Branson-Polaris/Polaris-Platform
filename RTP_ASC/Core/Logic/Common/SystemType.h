/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SYSTEM_TYPE_H_
#define SYSTEM_TYPE_H_

enum SYSTEM_TYPE
{
	SYSTEM_UNKNOWN = 0,
	//Add new system types here (after/below of SYSTEM_UNKNOWN)
	SYSTEM_ACE_PRO,
	SYSTEM_ACE_PRO_POWER_SUPPLY_ONLY_MODE,
	SYSTEM_L20,
	//Add new system types here (before/above of SYSTEM_TYPE_ENUM_MAX)
	SYSTEM_TYPE_ENUM_MAX 
};

extern SYSTEM_TYPE g_enSystemType;

SYSTEM_TYPE GetSystemTypeFromStorage();
bool SetSystemType(SYSTEM_TYPE enSystemType);
std::string GetSystemTypeName();

#endif //SYSTEM_TYPE_H_
