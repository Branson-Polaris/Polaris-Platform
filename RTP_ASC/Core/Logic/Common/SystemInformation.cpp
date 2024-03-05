/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * SystemInformation.cpp
 * 
 *  Created on: Apr 28, 2021
 *      Author: DShilonie
 *      
 *      Encapsulates system info access
 */

#include "SystemInformation.h"
#include "versions.h"

/**************************************************************************//**
* \brief   - System information details collected and sends to UIC 
*
* \param   - char *pSysInfData
*
* \return  - UINT16 length of byte read or written
*
******************************************************************************/
UINT16 SystemInformation::AccessSystemInformation(char *pSysInfData)
{
//	RunTime RunTimeModel;
//	SystemConfiguration SysConfigObj;
//	intf_SysConfig_t sysConfigData;
	SYSTEMINFO stSystemInfo;
	string timeStamp;
	
	bool UbootVersionFlag = 1;
//	FirmwareUpgrade Fwupdate;
//	Eeprom eeprom;
	char macaddr[6];
	char macAddr[20]={0x00};

	memset(&stSystemInfo, 0x00, sizeof(SYSTEMINFO));
	/*HardCoded Values*/
//	sysInfObj.psLifeCounter			= Counters::getCounter(LIFETIME_WELDS);
//	sysInfObj.overloadAlarmCounter  = Counters::getCounter(LIFETIME_OVERLOADS);
//	sysInfObj.actuatorlifecounter	= Counters::getCounter(LIFETIME_ACTUATIONS);
//	sysInfObj.generalAlarmCounter	= Counters::getCounter(LIFETIME_ALARMS);
	stSystemInfo.psLifeCounter			= 0;
	stSystemInfo.overloadAlarmCounter	= 0;
	stSystemInfo.actuatorlifecounter	= 0;
	stSystemInfo.generalAlarmCounter	= 0;
	stSystemInfo.actuatorOverloads		= 0;
	stSystemInfo.calibrationStatus		= 0;
	
	/*System Configuration Values*/
//	memset(&sysConfigData, 0x00, sizeof(intf_SysConfig_t));
//	SysConfigObj.SysConfigGet((char *)&sysConfigData);
	
//	sysInfObj.psFrequency			= sysConfigData.PcConfig.PSFreq;
//	sysInfObj.psWatt				= sysConfigData.PcConfig.PSWatt;
//	sysInfObj.psType				= sysConfigData.PcConfig.PsTypeIs;
//	sysInfObj.actuatorType			= sysConfigData.ActConfig.ActuatorTypeIs;
//	sysInfObj.actuatorStrokeLength 	= sysConfigData.ActConfig.MaxStrokelength;
	stSystemInfo.psFrequency		= 0;
	stSystemInfo.psWatt				= 0;
	stSystemInfo.psType				= 0;
	stSystemInfo.actuatorType		= 0;
	stSystemInfo.actuatorStrokeLength = 0;
	
		
//	RunTimeModel.CheckModelName(sysInfObj.modelName); 

#ifdef MAINLINE_BUGFIX_BUILD
	sprintf(stSystemInfo.version_SC,"%d.%d.%d.%d", FWVersion::Get(FW_VERSION_SC, VERSION_MAJOR),
												FWVersion::Get(FW_VERSION_SC, VERSION_MINOR),
												FWVersion::Get(FW_VERSION_SC, VERSION_BUILD),
												SC_FW_VERSION_AUTOS);

	sprintf(stSystemInfo.version_PC,"%d.%d.%d.%d",	FWVersion::Get(FW_VERSION_PC,VERSION_MAJOR),
												FWVersion::Get(FW_VERSION_PC, VERSION_MINOR),
												FWVersion::Get(FW_VERSION_PC, VERSION_BUILD),
												((FWVersion::Get(FW_VERSION_PC, VERSION_MAJOR) == 2 && FWVersion::Get(FW_VERSION_PC, VERSION_MINOR) == 0) ? 1 : PC_FW_VERSION_AUTOS));

	sprintf(stSystemInfo.version_AC,"%d.%d.%d.%d",	FWVersion::Get(FW_VERSION_AC,VERSION_MAJOR),
												FWVersion::Get(FW_VERSION_AC, VERSION_MINOR),
												FWVersion::Get(FW_VERSION_AC, VERSION_BUILD),
												AC_FW_VERSION_AUTOS);
	
#else
	sprintf(stSystemInfo.version_SC,"%d.%d.%d",FWVersion::Get(FW_VERSION_SC, VERSION_MAJOR), 
											FWVersion::Get(FW_VERSION_SC, VERSION_MINOR),
											FWVersion::Get(FW_VERSION_SC, VERSION_BUILD));

//	sprintf(stSystemInfo.version_PC,"%d.%d.%d",FWVersion::Get(FW_VERSION_PC, VERSION_MAJOR),
//											FWVersion::Get(FW_VERSION_PC, VERSION_MINOR),
//											FWVersion::Get(FW_VERSION_PC, VERSION_BUILD));

	sprintf(stSystemInfo.version_AC,"%d.%d.%d",FWVersion::Get(FW_VERSION_AC, VERSION_MAJOR),
											FWVersion::Get(FW_VERSION_AC, VERSION_MINOR),
											FWVersion::Get(FW_VERSION_AC, VERSION_BUILD));
#endif	
	
	
//	sprintf(stSystemInfo.pc_EPGA_Versoin,"%s", " ");
	
	/*HardCoded Values*/
	sprintf(stSystemInfo.psAssemblyNumber, "%s", "xxxxxxxxxx");
	sprintf(stSystemInfo.actuatorAssembly, "%s", "xxxxxxxxxx");
	sprintf(stSystemInfo.stackAssembly, "%s", "xxxxxxxxxx");
	
	
	/* read the MAC address for CPSW1 */
//	eeprom.Read((char *) macaddr, EEPROM_MAC_ADDRESS_SIZE, EEPROM_MAC_ADDRESS_OFFSET);
	snprintf(macAddr, sizeof(macAddr), "%02X:%02X:%02X:%02X:%02X:%02X",
			macaddr[0],
			macaddr[1],
			macaddr[2],
			macaddr[3],
			macaddr[4],
			macaddr[5]);

	sprintf(stSystemInfo.psMacID, "%s", macAddr);
	sprintf(stSystemInfo.psIP, "%s", "192.168.1.100");
	
	// Getting Date and Time Format. Note: This used to return last calibration time
	timeStamp = GetDateAndTime();
	sprintf(stSystemInfo.dateTime, "%s", (char *)timeStamp.c_str());
	
	/*Changed by MOUNIKA*/
//	UbootVersionFlag = Fwupdate.IsNewBootloaderForCRC();
	
	if(UbootVersionFlag)
	{
		stSystemInfo.crc_SC	= FWCrc::Get(FW_CRC_SC);
//		stSystemInfo.crc_PC	= FWCrc::Get(FW_CRC_PC);
		stSystemInfo.crc_AC	= FWCrc::Get(FW_CRC_AC);
	}
	else
	{
		stSystemInfo.crc_SC	= 0;
//		stSystemInfo.crc_PC	= 0;
		stSystemInfo.crc_AC	= 0;
	}
	
	memcpy(pSysInfData, (char *)&stSystemInfo, sizeof(SYSTEMINFO));
//	UpdateFirmwareUpgradeEvent(stSystemInfo.version_SC, stSystemInfo.version_PC, stSystemInfo.version_AC);
	
	return sizeof(stSystemInfo);
}

/**************************************************************************//**
* 
* \brief   - Updates firmware upgrade event.
*
* \param   - char *fwVersionSC, char *fwVersionPC, char *fwVersionAC
*
* \return  - None.
*
******************************************************************************/
void SystemInformation::UpdateFirmwareUpgradeEvent(char *fwVersionSC, char *fwVersionPC, char *fwVersionAC)
{
//	char fwUpgradeFlag= 0x00;
//	Eeprom eepromObj;
//	char prevFwVersionSC[SYSINFO_SIZE] = { 0x00 };
//	char prevFwVersionPC[SYSINFO_SIZE] = { 0x00 };
//	char prevFwVersionAC[SYSINFO_SIZE] = { 0x00 };
//	
//	eepromObj.Read((char *)&fwUpgradeFlag,sizeof(fwUpgradeFlag), FW_FLAG_EEPROM_OFFSET);
//	
//	if ( fwUpgradeFlag == FW_UPGRADE_SUCCESS )
//	{
//		/* Write Upgrade Success Flag to EEPROM */
//		fwUpgradeFlag = FW_UPGRADE_RESET;
//		eepromObj.Write((char *) &fwUpgradeFlag, sizeof(fwUpgradeFlag), FW_FLAG_EEPROM_OFFSET); 
//		eepromObj.Read((char *) prevFwVersionSC, SYSINFO_SIZE, SC_FW_VER_EEPROM_OFFSET);
//		eepromObj.Read((char *) prevFwVersionPC, SYSINFO_SIZE, PC_FW_VER_EEPROM_OFFSET);
//		eepromObj.Read((char *) prevFwVersionAC, SYSINFO_SIZE, AC_FW_VER_EEPROM_OFFSET); 
//		
//		if (( strcmp(prevFwVersionSC,fwVersionSC) != 0 ) || (strcmp(prevFwVersionPC,fwVersionPC) != 0) 
//																			|| (strcmp(prevFwVersionAC,fwVersionAC) != 0))
//		{
//		}		
//	}	
}


/*************************************************************************//**
* \brief   -  Gets RTC date and time.
*
* \param   -  string DateTime 
*
* \return  -  current Date & Time 
*
******************************************************************************/
string SystemInformation::GetDateAndTime()
{
	RTCtimerStr SysTime;
	char temp[TIMESTAMP] = {0x00};
	GetRTC(&SysTime);
	
	SysTime.tm_year = 1900 + SysTime.tm_year;
	SysTime.tm_mon  = 1 + SysTime.tm_mon;
	sprintf(temp,"%d/%02d/%02d %02d:%02d:%02d",SysTime.tm_year,SysTime.tm_mon,SysTime.tm_mday,SysTime.tm_hour,SysTime.tm_min,SysTime.tm_sec);
	return temp;
}

