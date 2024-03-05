/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Get/Set System Type Implementation

 **********************************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "SystemType.h"
#include "commons.h"

SYSTEM_TYPE g_enSystemType = SYSTEM_UNKNOWN;

/******************************************************************************
* \brief - Read the system type from persistent storage.
* \param - none
*
* \return - System Type
*
******************************************************************************/
SYSTEM_TYPE GetSystemTypeFromStorage()
{
	SYSTEM_TYPE enSystemType = SYSTEM_UNKNOWN;
	std::fstream SystemTypeFile;
	SystemTypeFile.open(SYSTEM_TYPE_FILE_PATH_EMMC, std::ios::in); 
	if (SystemTypeFile.is_open())
	{   
		std::string strSystemTypeValue = "";
		getline(SystemTypeFile, strSystemTypeValue);
		enSystemType = (SYSTEM_TYPE)atoi(strSystemTypeValue.c_str());
		SystemTypeFile.close();
	}
	
	if(enSystemType < SYSTEM_UNKNOWN || enSystemType >= SYSTEM_TYPE_ENUM_MAX)
	{
		enSystemType = SYSTEM_UNKNOWN;
	}
	return enSystemType;
}

/******************************************************************************
* \brief - Set/Save the System Type value in persistent storage.
*
* \param - enSystemType: System Type value
*
* \return - true/false
*
******************************************************************************/
bool SetSystemType(SYSTEM_TYPE enSystemType)
{
	bool bResult = false;
	if(enSystemType > SYSTEM_UNKNOWN && enSystemType < SYSTEM_TYPE_ENUM_MAX)
	{
		std::fstream SystemTypeFile;
		SystemTypeFile.open(SYSTEM_TYPE_FILE_PATH_EMMC, std::ios::out);
		if (SystemTypeFile.is_open())
		{
			SystemTypeFile << enSystemType;
			SystemTypeFile.close(); 
			bResult = true;
		}
	}
	
	return bResult;
}


/******************************************************************************
* \brief - Read the system type name
* \param - none
*
* \return - System Type Name
*
******************************************************************************/
std::string GetSystemTypeName()
{
	std::string strSystemType = "Unknown";
	const std::map<SYSTEM_TYPE, std::string> mapOfSystemTypeEnumToName = 
	{
		  { SYSTEM_ACE_PRO, "ACE Pro"},
		  { SYSTEM_ACE_PRO_POWER_SUPPLY_ONLY_MODE, "ACE Pro Power Supply Only Mode"},
	};
	
	for (auto iterator = mapOfSystemTypeEnumToName.begin(); iterator != mapOfSystemTypeEnumToName.end(); ++iterator) 
	{
	   if(iterator->first == g_enSystemType) 
	   {
		   strSystemType = iterator->second;
		   break;
	   }
	}
	
	return strSystemType;
}
