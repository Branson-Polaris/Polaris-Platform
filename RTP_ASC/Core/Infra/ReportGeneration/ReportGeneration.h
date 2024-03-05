/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

Report Generation functions to generate the CSV and PDF Reports  
 
***************************************************************************/

#ifndef REPORT_GENERATION_H_
#define REPORT_GENERATION_H_
#include <dirent.h>
#include <memory>
#include "DBAccess_common_db.h"
#include "DBAccess_p1_base_db.h"

#define NEW_LINE "\n"

#define USB_DEVICEPATH					"/bd0a"
#define REPORT_GEN_DIRECTORY			"ReportGenerationFiles"
#define REPORT_GEN_DIRECTORY_PATH		USB_DEVICEPATH PATH_SEPARATOR REPORT_GEN_DIRECTORY
#define WELDRESULT_FILE_NAME			"WeldResult"
#define WELDSIGNATURE_FILE_NAME			"WeldSignature"

//This Enum Structures indicates the type of report
typedef enum
{
	WELDRESULT_TYPE,
	ALARM_LOG,
	SYSTEM_SETUP,
	EVENT_LOG,
	USER_ID,
	RECIPE_SETTING,
	WELDSIGNATURE_TYPE,
	WELDRESULT_AND_WELDSIGNATURE_TYPE
} ReportID;

//This Enum Structures indicates the type of report format
typedef enum
{
	CSV_FORMAT,
	PDF_FORMAT
} ReportType;

//This Enum Structures indicates that error information that is reported to UIC
typedef enum
{
	SC_INVALID_STATE					= 0,
	REPORT_GENERATE_SUCCESS				= 1,
	
	//USB related codes
	USB_STORAGE_NOT_PRESENT				= 16,
	USB_STORAGE_FULL					= 17,
	USB_INSUFFICIENT_MEMORY				= 18,
	USB_MOUNT_ERROR						= 19,
	USB_MOUNT_SUCCESS					= 20,
	
	//DB related error code
	DB_READ_ERROR 						= 32,
	DATA_NOT_COMPLETE 					= 33,
	DB_EMPTY							= 34,
	DB_DELETE_ERROR						= 35,
	NO_GOLDEN_WELD_SIGNATURE_PRESENT	= 36,
	
	REPORT_GENERATION_FAILED			= 0xff,
} REPORT_ERROR_CODE;

//Report Structure defined for UIC request
typedef struct
{
	uint8_t reportID;
	uint8_t storageFormat;
	//char  reportBuff[REPORT_BUF_SIZE];
	uint8_t deleteID;
} Report_Message;



//ReportGeneration Base class. An Abstract class whose object can not be created.
class ReportGeneration
{
public: 
	ReportGeneration(Report_Message &StReportMsg);
	virtual ~ReportGeneration();
	
	//Pure virtual function.
	virtual REPORT_ERROR_CODE GenerateReport()=0;
	static bool IsReportGenerationCompleted();
	
	
protected:
	std::string reportNameGeneration(int nFileCount = -1);
	REPORT_ERROR_CODE checkStorageDevice();
	
	
	std::unique_ptr<DBAccess> m_ptrDatabaseObj;
	std::unique_ptr<DBAccessCommonDB> m_ptrSampleCommonDBObj;
	Report_Message m_stReportMessage;
	static bool    m_bReportGenerationCompleted;
	
private:
	REPORT_ERROR_CODE openDirectoryFileDescriptor();
	void getDateTimeStamp(std::string &strTimeStamp);
};


#endif // REPORT_GENERATION_H_ 


