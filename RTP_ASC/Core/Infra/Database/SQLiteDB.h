/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/

#ifndef SQLITEDB_H_
#define SQLITEDB_H_

#include  <iostream>
#include "sqlite3.h"
#include "Common.h"

//Values read from database are separated by comma
#define DB_VALUE_SEPARATOR	","

//Retry interval in case SQLITE_BUSY/SQLITE_LOCKED error returned.
#define SQLITE_BUSY_RETRY_INTERVAL	FIFTY_MS_DELAY
					
//Retry count in case SQLITE_BUSY/SQLITE_LOCKED error returned.
//Thus, default SQLITE_BUSY/SQLITE_LOCKED timeout becomes 4 retries of 50 milliseconds gap = 200 milliseconds. 
#define SQLITE_BUSY_DEFAULT_RETRY_COUNT 4

//Database access wrapper class.
//Abstract class.Use DBAccessP1BaseDB, DBAccessCommonDB classes to access the database files.
class SQLiteDB
{
public:	
	SQLiteDB();
	virtual ~SQLiteDB();
	
	//Pure virtual function. Each child class (e.g. DBAccessCommonDB) must provide a ConnectDB() implementation based on the database file name that it will operate on.
	virtual int ConnectDB()=0;
	int CloseDataBaseConnection();
	std::string ExecuteQuery(std::string strSqlStatement, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);	
	int SingleTransaction(std::string strSqlStatement, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int BulkTransaction(std::string strSqlStatement, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int Commit(int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int Vacuum(int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);	
	std::string GetDBColumnNames(std::string strTableName, int *pnStatus = nullptr);
	int GetDBColumnCount(std::string strTableName, int *pnStatus = nullptr);
	int GetNumberOfRows(std::string strTableName, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int GetMinRowID(std::string strTableName, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int GetMaxRowID(std::string strTableName, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int DeleteOneTableRow(std::string strTableName, int nRowID, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int DeleteMultipleTableRows(std::string strTableName, int nMinRowID, int nMaxRowID, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int DeleteAllTableRows(std::string strTableName, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
		
protected:	
	int EstablishDataBaseConnection(std::string strDBPath);
	
private:
	bool m_bIsDBOpen;
	sqlite3 *m_ptrDB;
	
	int executeDBQuery(std::string strSqlStatement, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);
	int getMinMaxRowID(std::string strTableName, bool bIsMinRowIDRequest, int *pnStatus = nullptr, int nRetryCounter = SQLITE_BUSY_DEFAULT_RETRY_COUNT);			
};

#endif /* SQLITEDB_H_ */
