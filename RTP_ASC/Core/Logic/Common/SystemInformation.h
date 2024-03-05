/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * SystemInformation.h
 *
 *  Created on: Apr 28, 2021
 *      Author: DShilonie
 */

#ifndef SYSTEMINFORMATION_H_
#define SYSTEMINFORMATION_H_

#include <string.h>
//#include "RunTimeFeature.h"
//#include "Eeprom.h"
//#include "SysConfigEeprom.hpp"
//#include "FirmwareUpgrade.h"
//#include "Counters.h"
#include "version_common.h"
#include "Common.h"

#define SYSINFO_SIZE						16
#define MAC_ADDR_SIZE      					18

using namespace std;
class SystemInformation 
{
public:
	static UINT16 AccessSystemInformation(char *pSysInfData);
private:
	static void UpdateFirmwareUpgradeEvent(char *fwVersionSC, char *fwVersionPC, char *fwVersionAC);
	static string GetDateAndTime();
};




#endif /* SYSTEMINFORMATION_H_ */
