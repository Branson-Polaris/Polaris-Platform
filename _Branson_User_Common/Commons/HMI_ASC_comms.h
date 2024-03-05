/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
/*
  * shared_common.h
 *
 *  Created on: May 28, 2021
 *      Author: JWang
 *      
 *  All the definition that need to be used both on ASC and HMI software should be in here.
 *  
 *  
 */

#ifndef SHARED_COMMON_H_
#define SHARED_COMMON_H_

enum RequestIdentities
{
	SCBL_HEART_BEAT_REQ							= 0,
	SCBL_USER_DETAILS_READ_REQ					= 3,
	SCBL_PASSCODE_VALIDATE_REQ					= 4,
	SCBL_ACTIVE_RECIPE_BASIC_INFO_READ_REQ		= 5,
	SCBL_WELD_RECIPE_LIST_READ_REQ				= 6,
	SCBL_SYSINFO_READ_REQ						= 7,
	SCBL_WELDRECIPE_REQ							= 8,
	
	
	SCBL_EMMC_WEAR_LEVEL_REQ					= 373,
	SCBL_OPTIMIZE_DATABASE_REQ					= 377,
	DUMMY

};

//system information structure for the HMI response parsing 
#define SYSINFO_SIZE						16
#define MAC_ADDR_SIZE      					18
struct SYSTEMINFO
{
	INT32	psLifeCounter;
	INT32   actuatorlifecounter;
	INT32   generalAlarmCounter;
	INT32   overloadAlarmCounter;
	INT32	actuatorOverloads;
	INT32	actuatorStrokeLength;
	UINT16  psFrequency;
	INT32   psWatt;
	UINT8   calibrationStatus;
	UINT8   psType;
	UINT8   actuatorType;	
	char    modelName[SYSINFO_SIZE];
	char    version_SC[SYSINFO_SIZE];
	char    version_PC[SYSINFO_SIZE];
	char    version_AC[SYSINFO_SIZE];
//		char 	pc_FPGA_Versoin[SYSINFO_SIZE];
	char    psAssemblyNumber[SYSINFO_SIZE];
	char    actuatorAssembly[SYSINFO_SIZE];
	char    stackAssembly[SYSINFO_SIZE];
	char    psMacID[MAC_ADDR_SIZE];
	char    psIP[SYSINFO_SIZE];
	char    dateTime[2 * SYSINFO_SIZE];
	UINT16  crc_SC;
//		UINT16  crc_PC;
	UINT16  crc_AC;
};


#endif
