/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Report Generation functions to generate the CSV and PDF Reports

 **********************************************************************************************************/
#include <iostream>
#include <ioLib.h>

#include "ReportGeneration.h"
#include "SystemType.h"

bool ReportGeneration::m_bReportGenerationCompleted = true;

/******************************************************************************
* \brief - Parameterized Constructor.
*
* \param - StReportMsg - input parameters structure "Report_Message".
*
* \return - None.
*
******************************************************************************/
ReportGeneration::ReportGeneration(Report_Message &StReportMsg)
{
	m_stReportMessage.reportID = StReportMsg.reportID;
	m_stReportMessage.storageFormat = StReportMsg.storageFormat;
	m_stReportMessage.deleteID = StReportMsg.deleteID;
	
	m_ptrDatabaseObj = nullptr;
	m_ptrSampleCommonDBObj = nullptr;
	
	//Open Connection to sample_common.db in case of UserID report as UserID info is present in sample_common.db.
	if(m_stReportMessage.reportID == USER_ID)
	{	
		m_ptrSampleCommonDBObj = std::make_unique<DBAccessCommonDB>();
		if(m_ptrSampleCommonDBObj != nullptr)
		{
			m_ptrSampleCommonDBObj->ConnectDB();
		}
	}
	else
	{	
		//Open connection to sample_p1_base.db OR sample_e1.db etc depending on system type.
		switch (g_enSystemType)
		{
			case SYSTEM_ACE_PRO:
			case SYSTEM_ACE_PRO_POWER_SUPPLY_ONLY_MODE:	
			{
				m_ptrDatabaseObj = std::make_unique<DBAccessP1BaseDB>();
			}
			break;
			
			default:
			{
				LOGERR((char *)"ReportGeneration - SYSTEM TYPE: %d UNKNOWN",g_enSystemType,0,0);
			}
			break;
		}
		
		if(m_ptrDatabaseObj != nullptr)
		{
			m_ptrDatabaseObj->ConnectDB();
		}
	}
}

/******************************************************************************
* \brief - Destructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
ReportGeneration::~ReportGeneration()
{
	m_ptrDatabaseObj = nullptr;
	m_ptrSampleCommonDBObj = nullptr;
}

/**************************************************************************//**
* \brief   - Returns the data member m_bReportGenerationCompleted value to see 
* if the generation of the report (PDF or CSV) is completed or not.
*
* \param   - None
*
* \return  - true (report generation completed) or false (not completed)
*
******************************************************************************/
bool ReportGeneration::IsReportGenerationCompleted()
{
	return m_bReportGenerationCompleted;
}

/******************************************************************************
* \brief - Generates Report path by adding datetime stamp, file count(if provided),

* \param: 
* nFileCount - FileCount to be appended in file name
*
* \return - Complete Report File Path Along with File Name.
*
******************************************************************************/
std::string ReportGeneration::reportNameGeneration(int nFileCount)
{
	std::string strReportFileName = "", strDateTimeStamp = "";

	switch(m_stReportMessage.reportID)
	{
		case WELDRESULT_TYPE:
		{
			strReportFileName = (std::string)USB_DEVICEPATH + PATH_SEPARATOR + REPORT_GEN_DIRECTORY + PATH_SEPARATOR + WELDRESULT_FILE_NAME;
		}
		break;
		
		case WELDSIGNATURE_TYPE:
		{
			strReportFileName = (std::string)USB_DEVICEPATH + PATH_SEPARATOR + REPORT_GEN_DIRECTORY + PATH_SEPARATOR + WELDSIGNATURE_FILE_NAME;
		}
		break;

		default:
		{
			//Sending back an empty string
			strReportFileName.clear();
			LOGERR((char *)"ReportGeneration - Unsupported Report Type: %d",m_stReportMessage.reportID,0,0);
		}
		break;
	}

	if(!strReportFileName.empty())
	{
		//Append Date And Timestamp string
		getDateTimeStamp(strDateTimeStamp);
		strReportFileName.append("_");
		strReportFileName.append(strDateTimeStamp);
		
		//append file count if provided.
		if(nFileCount > -1)
		{
			strReportFileName.append("_");
			strReportFileName.append(std::to_string(nFileCount));
		}
		
		//Append the storage format extension
		switch(m_stReportMessage.storageFormat)
		{
			case CSV_FORMAT:
			{
				strReportFileName.append(".csv");
			}
			break;
			
			case PDF_FORMAT:
			{
				strReportFileName.append(".pdf");
			}
			break;
			
			default:
			{
				//Sending back an empty string
				strReportFileName.clear();
				LOGERR((char *)"ReportGeneration - Unsupported Report Format: %d",m_stReportMessage.storageFormat,0,0);
			}
			break;
		}
	}

	return strReportFileName;
}

/******************************************************************************
* \brief - Check if USB storage device is connected

* \param: none
*
* \return - USB_MOUNT_SUCCESS on Success else appropriate USB related error code.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGeneration::checkStorageDevice()
{
	REPORT_ERROR_CODE enReturn = USB_STORAGE_NOT_PRESENT;
		
	int nStorageFd = open(USB_DEVICEPATH, 0, 0);
	
	if(nStorageFd > -1)
	{	
		enReturn = openDirectoryFileDescriptor();
		close(nStorageFd);		
	}
	else
	{
		LOGERR((char *)"ReportGeneration : checkStorageDevice: USB Device not connected",0,0,0);
	}

	return enReturn;
}

/**************************************************************************//**
* \brief   - Opens Report Generation Directory. If not there, creates new directory.
*
* \param   - None
*
* \return  - USB_MOUNT_SUCCESS on Success else USB_MOUNT_ERROR.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGeneration::openDirectoryFileDescriptor()
{
	REPORT_ERROR_CODE enReturn = USB_MOUNT_ERROR;
	
	DIR *ptrReportDirFd=opendir(REPORT_GEN_DIRECTORY_PATH);

	//Create new Directory for storing Report Generation Files if directory not present
	if(ptrReportDirFd == nullptr)
	{
		if((ERROR == mkdir(REPORT_GEN_DIRECTORY_PATH, 0644)))
		{
			LOGERR((char *)"ReportGeneration : OpenDirectoryFileDescriptor: Error in Creating Report File Directory",0,0,0);
		}
		else
		{
			enReturn = USB_MOUNT_SUCCESS;
		}
	}
	else
	{
		enReturn = USB_MOUNT_SUCCESS;
		closedir(ptrReportDirFd);
		ptrReportDirFd=nullptr;
	}	
	
	return enReturn;
}

/******************************************************************************
* \brief - Get DateTime Stamp in required format to append to report file name.
*
* \param - strTimeStamp - TimeStap Value is stored in this.
*
* \return - None.
*
******************************************************************************/
void ReportGeneration::getDateTimeStamp(std::string &strTimeStamp)
{	 
	char szTimeBuf[TIMESTAMP] = {0x00};
	RTCtimerStr SysTime={0x00};
	
	GetRTC(&SysTime);
	
	SysTime.tm_year = 1900 + SysTime.tm_year;
	SysTime.tm_mon  = 1 + SysTime.tm_mon;
	sprintf(szTimeBuf,"%d%02d%02d_%02d%02d%02d",SysTime.tm_year,SysTime.tm_mon,SysTime.tm_mday,SysTime.tm_hour,SysTime.tm_min,SysTime.tm_sec);
	
	strTimeStamp = szTimeBuf;
}

