/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Database Access unit test code for accessing sample_p1_base.db and sample_common.db.
You may e.g. call the DatabaseAccessDemo() function from MainTask.cpp file and test the working.

 **********************************************************************************************************/
#include <iostream>
#include <memory>

#include  <dirent.h>
#include <usrFsLib.h>

#include "../SystemType.h"
#include "../DBAccess/DBAccess_common_db.h"
#include "../DBAccess/DBAccess_p1_base_db.h"

/******************************************************************************
* \brief - Database Access Demo code. 

* \param - none.
*
* \return - None.
*
******************************************************************************/
void DatabaseAccessDemo(void)
{	
	std::cout << "\nDatabaseAccessDemo Started...\n" << std::endl;
	
	std::unique_ptr<DBAccess> ptrDatabaseObj;
	
	//Demo code to access sample_p1_base.db or sample_e1.db(in future) depending on system type (GSX_P1_BASE or GSX_E1).
	
	//Open connection to sample_p1_base.db OR sample_e1.db(in future) depending on system type.
	switch (g_enSystemType)
	{
			case SYSTEM_ACE_PRO:
			case SYSTEM_ACE_PRO_POWER_SUPPLY_ONLY_MODE:
			{
				ptrDatabaseObj = std::make_unique<DBAccessP1BaseDB>();
			}
			break;
			
			/*case SYSTEM_GSX_E1:
			{
				//In future we can add/implement DBAccessE1DB class to access sample_e1.db file.
				//ptrDatabaseObj = std::make_unique<DBAccessE1DB>();
				std::cout << "\nDatabaseAccessDemo  - GSX_E1 System not supported yet\n" << std::endl;
			}
			break;
			*/
			
			default:
			{
				std::cout << "\nDatabaseAccessDemo - SYSTEM TYPE UNKNOWN\n" << std::endl;
			}
			break;
	}
	
	if(ptrDatabaseObj != nullptr)
	{
		if (ptrDatabaseObj->ConnectDB() == SQLITE_OK)
		{
			std::cout << "ConnectDB SUCCESS for system database" << std::endl;
			
			std::string strResult = "", StrQuery="";
			int errorCode = 0;
		
			//SELECT Query Demo
			StrQuery = "SELECT * FROM OperatorAuthorityOption;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			std::cout << "Data Read:" << strResult << std::endl;
			
			//Update Query Demo
			StrQuery = "UPDATE OperatorAuthorityOption SET ResetAlarm=1;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			StrQuery = "SELECT * FROM OperatorAuthorityOption;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			std::cout << "Data After Update:" << strResult << std::endl;
					
			//BulkTransaction Demo	
			StrQuery = "INSERT INTO OperatorAuthorityOption VALUES(NULL,0,0,0,0,0); INSERT INTO OperatorAuthorityOption VALUES(NULL,0,0,0,0,0); INSERT INTO OperatorAuthorityOption VALUES(NULL,0,0,0,0,0);";
			int nReturn = ptrDatabaseObj->BulkTransaction(StrQuery);
			if(nReturn != SQLITE_OK)
			{
				std::cout << "BulkTransaction FAILURE" << std::endl;
			}
			else
			{
				std::cout << "BulkTransaction SUCCESS" << std::endl;
			}
			StrQuery = "SELECT * FROM OperatorAuthorityOption;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			std::cout << "Data After BulkTransaction INSERT:" << strResult << std::endl;	
			
	
			//GetDBColumnCount, GetDBColumnNames, GetNumberOfRows, GetMinRowID, GetMaxRowID Demo
			int nColCount = ptrDatabaseObj->GetDBColumnCount("OperatorAuthorityOption");
			std::string strColNames =  ptrDatabaseObj->GetDBColumnNames("OperatorAuthorityOption");
			int nNumOfRows = ptrDatabaseObj->GetNumberOfRows("OperatorAuthorityOption");
			int nMinRowID = ptrDatabaseObj->GetMinRowID("OperatorAuthorityOption");
			int nMaxRowID = ptrDatabaseObj->GetMaxRowID("OperatorAuthorityOption");
			
			std::cout << "Column Count: " << nColCount << std::endl;
			std::cout << "Column Names: " << strColNames << std::endl;
			std::cout << "Number of Rows: " << nNumOfRows << std::endl;
			std::cout << "Min RowID: " << nMinRowID << std::endl;
			std::cout << "Max RowID: " << nMaxRowID << std::endl;
			
			
			//DELETE Query Demo
			ptrDatabaseObj->DeleteAllTableRows("OperatorAuthorityOption");
			StrQuery = "SELECT * FROM OperatorAuthorityOption;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			std::cout << "Data After Delete:" << strResult << std::endl;
			
			//INSERT Query Demo
			StrQuery = "INSERT INTO OperatorAuthorityOption VALUES(NULL,0,0,0,0,0)";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			StrQuery = "SELECT * FROM OperatorAuthorityOption;";
			strResult = ptrDatabaseObj->ExecuteQuery(StrQuery);
			std::cout << "Data After INSERT:" << strResult << std::endl;
			
			
			//Vacuum Demo
			if(ptrDatabaseObj->Vacuum() != SQLITE_OK)
			{
				std::cout << "Vacuum FAILURE" << std::endl;
			}
			else
			{
				std::cout << "Vacuum SUCCESS" << std::endl;
			}
			
			
			//Foreign Key Demo.
			//For testing purpose, add 1 row in WeldResult Table and 1 row in AlarmLog Table.
			//Link the Primary Key number (WeldResultIndex Column value of WeldResult Table)  as Foreign Key number (WeldResultIndex Column value of AlarmLog Table).
			//Since the ON DELETE ACTION for Foreign Key is set to "SET NULL" in AlarmLog Table, upon deletion of the row from WeldResult Table,
			//corresponding row in AlarmLog Table will get the Foreign Key value set to NULL.
		
			std::string readData = "", query = "";		
			query = "SELECT * FROM AlarmLog;";
			readData = ptrDatabaseObj->ExecuteQuery((char*) query.c_str());
			printf("\nAlarmLogs:\n");
			std::cout << readData << std::endl;
			
			query = "SELECT * FROM WeldResult;";
			readData = ptrDatabaseObj->ExecuteQuery((char*) query.c_str());
			printf("\nWeldResult Table:\n");
			std::cout << readData << std::endl;
					 
			ptrDatabaseObj->DeleteAllTableRows("WeldResult");
			
			query = "SELECT * FROM AlarmLog;";
			readData = ptrDatabaseObj->ExecuteQuery((char*) query.c_str());
			printf("\nAlarmLog Table AFTER WeldResult Table DELETE:\n");
			std::cout << readData << std::endl;	
			
			query = "SELECT * FROM WeldResult;";
			readData = ptrDatabaseObj->ExecuteQuery((char*) query.c_str());
			printf("\nWeldResult Table AFTER WeldResult Table DELETE:\n");
			std::cout << readData << std::endl;		
		}
		else
		{
			std::cout << "ConnectDB FAILURE for system database" << std::endl;
		}
 	}
 	else
	{
		std::cout << "DB Pointer is NULL" << std::endl;
	}
	
	//Demo code to access sample_common.db
	DBAccessCommonDB CommonDBObj;
	if (CommonDBObj.ConnectDB() == SQLITE_OK)
	{
		std::cout << "ConnectDB SUCCESS for common database" << std::endl;
		
		//SELECT Query Demo
		std::string StrQuery = "SELECT * FROM GlobalUserSetting;";
		std::string  strResult = CommonDBObj.ExecuteQuery(StrQuery);
		std::cout << "Data Read:" << strResult << std::endl;
		
		//Update Query Demo
		StrQuery = "UPDATE GlobalUserSetting SET PasswordExpiryInDays=100;";
		strResult = CommonDBObj.ExecuteQuery(StrQuery);
		StrQuery = "SELECT * FROM GlobalUserSetting;";
		strResult = CommonDBObj.ExecuteQuery(StrQuery);
		std::cout << "Data After Update:" << strResult << std::endl;
		
		//DELETE Query Demo
		CommonDBObj.DeleteAllTableRows("GlobalUserSetting");
		StrQuery = "SELECT * FROM GlobalUserSetting;";
		strResult = CommonDBObj.ExecuteQuery(StrQuery);
		std::cout << "Data After Delete:" << strResult << std::endl;
		
		//INSERT Query Demo
		StrQuery = "INSERT INTO GlobalUserSetting VALUES(NULL,90,30,0)";
		strResult = CommonDBObj.ExecuteQuery(StrQuery);
		StrQuery = "SELECT * FROM GlobalUserSetting;";
		strResult = CommonDBObj.ExecuteQuery(StrQuery);
		std::cout << "Data After INSERT:" << strResult << std::endl;
		
	}
	else
	{
		std::cout << "ConnectDB FAILURE for common database" << std::endl;
	}
		
	std::cout << "\nDatabaseAccessDemo Finished...\n" << std::endl;
}

