/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

Report Generation functions to generate the CSV Reports  
 
***************************************************************************/

#ifndef REPORT_GENERATION_CSV_H_
#define REPORT_GENERATION_CSV_H_

#include"ReportGeneration.h"

# define MAX_GOLDEN_WELD_SIGNATURES_COUNT 3

//ReportGenerationCSV class.
class ReportGenerationCSV : public ReportGeneration
{
public: 
	ReportGenerationCSV(Report_Message &StReportMsg);
	~ReportGenerationCSV();
	
	REPORT_ERROR_CODE GenerateReport() override;
	
private:
	REPORT_ERROR_CODE generateWeldReusltCSVReport();	
	REPORT_ERROR_CODE generateWeldSignatureCSVReport();
	REPORT_ERROR_CODE parseWeldSignatureGraphBlob(const std::string &strGraphData, const int &nGraphBlobParamNumber, std::ofstream &CSVReprtFileDesc);
};



#endif //REPORT_GENERATION_CSV_H_
