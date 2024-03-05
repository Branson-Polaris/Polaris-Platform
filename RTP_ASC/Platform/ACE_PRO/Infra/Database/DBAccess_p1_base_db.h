/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef DBACCESS_P1_BASE_DB_H_
#define DBACCESS_P1_BASE_DB_H_

#include "DBAccess.h"

//Columns to read from database for WeldResult CSV Report Generation for P1_Base System.
//Also this will act as CSV report header (first) line for WeldResult CSV Report for P1_Base System.
const std::string strP1BaseWeldResultCSVParamString = 
	"WeldRecipeNumber,"
	"WeldRecipeVersionNumber,"
	"DateTime,"
	"RecipeStatus,"
	"CycleCounter,"
	"WeldMode,"
	"WeldTime,"
	"WeldEnergy,"
	"WeldPeakPower,"
	"StartFrequency,"
	"FrequencyChange,"
	"CycleTime,"
	"UserName,"
	"PartID,"
	"TriggerPoint,"
	"WeldSonicPoint,"
	"HoldPoint,"
	"AlarmID";

//Columns to read from database for WeldSignature CSV Report Generation for P1_Base System.	
const std::string strP1BaseWeldSignatureCSVParamString = 
	"Name,"
	"WeldRecipeNumber,"
	"WeldRecipeVersionNumber,"
	"CycleCounter,"
	"DateTime";
	
//CSV report first header line for WeldSignature CSV Report for P1_Base System.	
const std::string strP1BaseWeldSignatureCSVReportHeader1 = 
	"Name,"
	"WeldRecipeNumber,"
	"WeldRecipeVersionNumber,"
	"CycleCounter,"
	"DateTime";
	
//CSV report second header line for WeldSignature CSV Report for P1_Base System.	
const std::string strP1BaseWeldSignatureCSVReportHeader2 = 
	"Time,"
	"Frequency,"
	"Power,"
	"Current,"
	"Amplitude,"
	"Phase,"
	"Energy";		
	
	
#define BLOB_PARAMETERS_NUMBER_P1_BASE 7 


//Class DBAccessP1BaseDB
class DBAccessP1BaseDB : public DBAccess
{
public:	
	DBAccessP1BaseDB();
	~DBAccessP1BaseDB();
	
	int ConnectDB() override;
	
	//Methods to fetch data from database needed for CSV reports generation.		
	std::string GetWeldResultCSVParameters(int nRowID,  int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT) override;
	std::string GetWeldResultCSVReportHeader() override;	
		
	std::string GetWeldSignatureCSVParameters(int nRowID, int &nBlobParamNumber, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT) override;
	std::string GetWeldSignatureCSVReportHeader1() override;
	std::string GetWeldSignatureCSVReportHeader2() override;
	//End of methods to fetch data from database needed for CSV reports generation.	
};

#endif // DBACCESS_P1_BASE_DB_H_
