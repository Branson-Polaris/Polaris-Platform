/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

 	 It contains DBAccess class implementation.
 
**********************************************************************************************************/

#include "DBAccess.h"
#include "DataBaseConfiguration.h"


/******************************************************************************
* \brief - Constructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
DBAccess::DBAccess()
{

}

/******************************************************************************
* \brief - Destructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
DBAccess::~DBAccess()
{

}


/******************************************************************************
* \brief - Read WeldSignature Graph Blob Data from database for passed ROWID. 
*
* \param:
* nRowID - ROWID to read.
* pnStatus - Query execution status/result.
* nRetryCounter - Number of retries in case SQLITE_BUSY/SQLITE_LOCKED error.
*
* \return - The read database values are returned as comma separated values.
*
******************************************************************************/
std::string DBAccess::GetWeldSignatureGraphBlob(int nRowID,  int *pnStatus, int nRetryCounter)
{
	std::string strQuery = "SELECT " + (std::string)COLUMN_GRAPHDATA + " FROM " + TABLE_WELD_SIGNATURE + " WHERE ROWID=" + std::to_string(nRowID) + ";";
	return ExecuteQuery(strQuery, pnStatus, nRetryCounter);	
}

/******************************************************************************
* \brief - Get Row Numbers which are marked as Golden Weld Signatures in database. 
*
* \param: 
* pnStatus - Query execution status/result.
* nRetryCounter - Number of retries in case SQLITE_BUSY/SQLITE_LOCKED error.
*
* \return - vector containing RowIDs marked as golden signatures in database.
*
******************************************************************************/
std::vector<int> DBAccess::GetGoldenWeldSignatureRowNumbers(int *pnStatus, int nRetryCounter)
{
	size_t position = 0;	
	std::string strRowID = "";
	std::string strDelimiter = DB_VALUE_SEPARATOR;
	std::vector<int> vRowIDs;
	vRowIDs.clear();
	
	std::string strQuery = "SELECT ROWID FROM " + (std::string)TABLE_WELD_SIGNATURE + " WHERE " + (std::string)COLUMN_GOLDEN + "=1;";
	std::string strResult = ExecuteQuery(strQuery, pnStatus, nRetryCounter);
	
	//Convert/Parse the RowIDs string returned from database (e.g. 1,2,3) into vector of int ROWID.	
	if(strResult != "")
	{
		while ((position = strResult.find(strDelimiter)) != std::string::npos) 
		{
		    strRowID = strResult.substr(0, position);
		    
		    vRowIDs.push_back(atoi(strRowID.c_str()));

		    strResult.erase(0, position + strDelimiter.length());
		}
		vRowIDs.push_back(atoi(strResult.c_str()));
	}
	
	return vRowIDs;
}




