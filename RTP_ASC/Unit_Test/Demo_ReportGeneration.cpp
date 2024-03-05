/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Report Generation unit test code for CSV WeldResult and WeldSignature Reports.
You may e.g. call the ReportGenerationDemo() function from MainTask.cpp file and test the working.

 **********************************************************************************************************/
#include <iostream>
#include "../ReportGeneration/ReportGeneration_CSV.h"

/******************************************************************************
* \brief - Report Generation Demo code. 

* \param - none.
*
* \return - None.
*
******************************************************************************/
void ReportGenerationDemo(void)
{	
	std::cout << "ReportGenerationDemo Started..." << std::endl;
	
	Report_Message reportMessage = {0x00};
	reportMessage.storageFormat = CSV_FORMAT;//CSV_FORMAT, PDF_FORMAT
	reportMessage.reportID = WELDSIGNATURE_TYPE;// WELDRESULT_TYPE, WELDSIGNATURE_TYPE
	reportMessage.deleteID = 0; //Set to 1 if you wish to delete the database entries after report is generated successfully.

	std::unique_ptr<ReportGeneration> pobjReportGen = nullptr;

	switch(reportMessage.storageFormat)
	{
		case CSV_FORMAT:
		{
			pobjReportGen = std::make_unique<ReportGenerationCSV>(reportMessage);
		}
		break;
		
		case PDF_FORMAT:
		{
			std::cout << "Report Format PDF Selected, NEED TO ADD SUPPORT" << std::endl;
		}
		break;
		
		default:
		{
			std::cout << "Report Format Not Supported" << std::endl;
		}
		break;
	}

	if(pobjReportGen != nullptr)
	{
		REPORT_ERROR_CODE enResult = pobjReportGen->GenerateReport();
		if( enResult == REPORT_GENERATE_SUCCESS)
		{
			std::cout << "ReportGenerationDemo - REPORT GENERATION SUCCESSFUL" << std::endl;	
		}
		else
		{
			std::cout << "ReportGenerationDemo - REPORT GENERATION FAILURE, ERROR: " << enResult << std::endl;
		}
	}
	else
	{
		std::cout << "ReportGenerationDemo - pobjReportGen nullptr" << std::endl;
	}
		
	std::cout << "ReportGenerationDemo FINISHED..." << std::endl;
}

