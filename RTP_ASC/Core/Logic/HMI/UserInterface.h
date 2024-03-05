/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#define SEND_POWERUP_RECIPE_TO_SLAVES

#include "Common.h"
#include "CommonProperty.h"
#include "WeldRecipe.h"
#include "CommunicationInterface.h"
#include "SCTask.h"
#include "WeldRecipeSC.h"

#define VALID_STATE 	1
#define CONTINUE_CMD 	1
#define BRASON_KEY_SIZE	8


#define DB_COPY_SD		"/sd0:1/emmcDB"
#define DB_COPY_USB		"/bd0:1/emmcDB"


//#define UI_RESPONSE_DEBUG

#define SYSTEM_READY_IND_NOT_SENT	-1
#define BUS_SCAN_TIMEOUT 			10
#define FIRST_LEVEL_KEY		"BRNBuiltMe"
#define SECOND_LEVEL_KEY	"BMXBuiltMe"

/* firmware upgrade eeprom variables */

#define   FW_UPGRADE_SUCCESS         0x11
#define   FW_UPGRADE_RESET			 0x00

typedef struct Calibration
{	
	UINT8	CommandId;
	UINT32  FirstReading;
	UINT32  SecondReading;
}Calibration;

enum BUS_SCAN_STATUS
{
	SCAN_IN_PROGRESS = 2,
	SCAN_FAILED
};


enum CALIBRATION_CMD
{
	START_REQ = 1,
	NEXT_REQ,
	FINISH_REQ,
	ABORT_REQ
};

enum POWER_ON_SEQ
{
	FW_VERSION = 1,
	POWER_UP_RECIPE,
	POWER_ON_RECIPE_READ,
	CALIBRATION_TIME_STAMP
};

enum STORAGE_DEVICE
{
	SD_DEVICE		= 1,
	USB_DEVICE,
	SD_EMMC_DEVICE,
	USB_EMMC_DEVICE
};


class UserInterface : public SCTask
{	
public:
	UserInterface();
	~UserInterface();
	
	static 			void* UserInterface_Task	( void *);
	void			PowerOnRequest				(UINT8 typeOfReq);
	void			ProcessTaskMessage			(Message& message);	    		
	void			DeCoder						(char *pRecvBuffer, Message& ProcessBuffer);
	bool			NotifyResponseToClient		(Message& message, UINT32 msgLen);
	static 			void UserInterface_Task		(void);

private:
	void			SendMessageToACTDSPTask		(Message& message);
	void			SendMessageToControlTask	(Message& message);
	INT32			ActiveAlarmData				(char *pAlarmData);
	void			UpdateAlarmPendingList		();
	bool			ValidateAlarmReq			(char *alarmData);
	
    bool					bPowerOnSeek, bFirstReadDone,bSecondReadDone,bActiveRecipe,bPendingRecipe;
    UINT8 					ErrCode;
    UINT32					m_alarmID;
	WeldRecipePC   			RecipePC, WeldMinValPC, WeldMaxValPC;
	WeldRecipeAC   			RecipeAC, WeldMinValAC, WeldMaxValAC;
	WeldRecipeSC			ActiveRecipeSC;
	Calibration				m_CalibrationInput;
	CalibrationReadings	 	m_ReadingSDO;
	char					*m_ActiveAlarm;
	
	USERIO  				m_UserIO;			
	CommunicationInterface *socketInterface;
	PowerUpData				PowerUpRecipe;
	
	char 					m_pBarcodeData[BARCODE_DATA_SIZE];
	string 					CalTimeStamp;
	char 					cal_temp_data[TIMESTAMP];

};

#endif /* USERINTERFACE_H_ */
