/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the Console App related implementation
***************************************************************************/

#ifndef CONSOLEAPP_H_
#define CONSOLEAPP_H_

#include "Common.h"
#include "WeldRecipe.h"
#include "CommonProperty.h"
#include "versions.h"
#include <sstream>
#include <istream>

/* User menu options available in ConsoleApp */
enum USER_MENU
{
	/* More user options */
	CA_FW_INFO = 1,
	CA_RESET_ALARM,
	CA_WELD_MODE,
	CA_WELD_VALUE,
	CA_WELD_AMP,
	CA_DIGITAL_TUNE,
	CA_WELD_HOLD,
	CA_AMPLITUDE_RAMP_TIME,
	CA_AMPLITUDE_P,
	CA_AMPLITUDE_I,
	CA_AMPLITUDE_D,
	CA_PHASE_P,
	CA_PHASE_I,
	CA_PHASE_D,
	CA_LAST_WELD_DSP_DATA,
	CA_PERFORM_SEEK,
	CA_END_OF_WELD_STORE,
	CA_SET_SYSTEM_FREQUENCY,
	CA_SET_SYSTEM_TYPE
};

typedef enum
{
	CA_NUMBER,
	CA_CHAR
}CA_ENTRY_TYPE;

class ConsoleApp : public SCTask
{
public:
	ConsoleApp();
	~ConsoleApp();
	
	static 				void* ConsoleApp_Task	(void *);
	bool				bIsTaskRunStatus		();
	void				ProcessUserOptions		();
	void 				PullActiveRecipeFromCP	();

private:
	INT32 				ConsoleRead(CA_ENTRY_TYPE entryType = CA_NUMBER);
	void				ResetAlarm();
	void 				SetWeldRecipe();
	void				SetScWeldRecipe();
	void				SetPcWeldRecipe();
	void				SetAcWeldRecipe();

	INT32 				iChoice,iCmd;
	Message 			message;
	
	// weld recipes
	WeldRecipe	 		Console_WeldRecipe;
	CommonProperty		*CP;
};


#endif /* CONSOLEAPP_H_ */
