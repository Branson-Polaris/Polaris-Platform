/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Report Generation functions to generate the CSV Reports.

 **********************************************************************************************************/
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <cstring>
#include <string>

#include "ReportGeneration_CSV.h"
#include "DataBaseConfiguration.h"

/******************************************************************************
* \brief - Parameterized Constructor.
*
* \param - StReportMsg - input parameters structure "Report_Message".
*
* \return - None.
*
******************************************************************************/
ReportGenerationCSV::ReportGenerationCSV(Report_Message &StReportMsg) : ReportGeneration(StReportMsg)
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
ReportGenerationCSV::~ReportGenerationCSV()
{
	
}

/******************************************************************************
* \brief - Generate CSV Report.
*
* \param - none.
*
* \return - REPORT_ERROR_CODE enum.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGenerationCSV::GenerateReport()
{
	REPORT_ERROR_CODE enResult = REPORT_GENERATION_FAILED;
		
	//TO_BE_DONE if((SC::stateMachine.GetStateType() == READY) || (SC::stateMachine.GetStateType() == SC_ALARM))
	//{
		m_bReportGenerationCompleted = false;
		enResult = checkStorageDevice();
		if(enResult == USB_MOUNT_SUCCESS)
		{
			switch(m_stReportMessage.reportID)
			{
				case WELDRESULT_TYPE:
				{
					enResult = generateWeldReusltCSVReport();
				}
				break;
				
				case WELDSIGNATURE_TYPE:
				{
					enResult = generateWeldSignatureCSVReport();

				}
				break;
				
				default:
				{
					LOGERR((char *)"ReportGenerationCSV: - GenerateReport - Unsupported CSV Report Request",m_stReportMessage.reportID,0,0);
				}			
			}
		}
	//}
	//else
	//{
		//enResult = SC_INVALID_STATE;
		//LOGERR("ERROR: SC_INVALID_STATE\n",0,0,0);
	//}
	
	m_bReportGenerationCompleted = true;
	return enResult;
}

/******************************************************************************
* \brief - Generate CSV WeldReuslt Report.
*
* \param - none.
*
* \return - REPORT_ERROR_CODE enum.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGenerationCSV::generateWeldReusltCSVReport()
{
	REPORT_ERROR_CODE enResult = REPORT_GENERATION_FAILED;
	bool bErrorOccured = false;
	
	if(m_ptrDatabaseObj != nullptr)
	{
		int nRowCount = m_ptrDatabaseObj->GetNumberOfRows(TABLE_WELD_RESULT);
		
		if(nRowCount > 0)
		{
			int nMinRowID = m_ptrDatabaseObj->GetMinRowID(TABLE_WELD_RESULT);	
			int nMaxRowID = m_ptrDatabaseObj->GetMaxRowID(TABLE_WELD_RESULT);

			//Check if database has more rows than the supported max limit.
			//If yes, then generate CSV report for max limit records only and do not show older data/rows from database table. 
			if(nRowCount > DB_RECORDS_STORAGE_WELD_RESULT_LIMIT)
			{
				int nDifference = nRowCount - DB_RECORDS_STORAGE_WELD_RESULT_LIMIT;
				nMinRowID = nMinRowID + nDifference;
			}	
			
			//Generate CSV report.
			std::string strReportName = reportNameGeneration();	
			std::ofstream CSVReprtFile;
			CSVReprtFile.open(strReportName);
			if(CSVReprtFile.good())
			{
				//Add CSV Report Header line containing column names.
				std::string strReportHeader = m_ptrDatabaseObj->GetWeldResultCSVReportHeader();					
				CSVReprtFile << strReportHeader << NEW_LINE;			
			
				//Add data in CSV report for each row present in database table.
				for(int nRowNumber = nMinRowID; nRowNumber <= nMaxRowID; nRowNumber++)
				{
					int nResult = 0;  
					
					std::string strResult = m_ptrDatabaseObj->GetWeldResultCSVParameters(nRowNumber, &nResult);
					if(nResult == SQLITE_OK)
					{
						if(strResult != "")
						{
							//Write the data to CSV report file.
							CSVReprtFile << strResult << NEW_LINE;
							if(!CSVReprtFile.good())
							{
								LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - ERROR: %d",nResult,0,0);
									
								enResult = USB_STORAGE_FULL;
								bErrorOccured = true;
								break;
							}
						}
					}
					else
					{
						LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - ERROR: %d",nResult,0,0);
	
						enResult = DATA_NOT_COMPLETE;
						bErrorOccured = true;
						break;
					}
				}
				
				if(bErrorOccured == false)
				{
					enResult = REPORT_GENERATE_SUCCESS;
					
					//Delete the records from database if user has requested to delete them.
					if(m_stReportMessage.deleteID == true)
					{
						if (m_ptrDatabaseObj->DeleteMultipleTableRows(TABLE_WELD_RESULT, nMinRowID, nMaxRowID) == SQLITE_OK)
						{
							//PostDeleteResponse(); //TO_BE_DONE
							m_ptrDatabaseObj->Vacuum();
						}
						else
						{
							LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - Database Record Deletion Failure",0,0,0);
							enResult = DB_DELETE_ERROR;
						}
					}
				}
				
				CSVReprtFile.close();
			}
			else
			{
				LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - Report File Open Error",0,0,0);
				enResult = REPORT_GENERATION_FAILED;
			}
		}
		else
		{
			LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - Database Empty",0,0,0);
			enResult = DB_EMPTY;
		}
	}
	else
	{
		LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - m_ptrDatabaseObj is NULL",0,0,0);
		enResult = DB_READ_ERROR;
	}
		
	return enResult;
}

/******************************************************************************
* \brief - Generate  Weld Signature CSV Report.
*
* \param - none.
*
* \return - REPORT_ERROR_CODE enum.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGenerationCSV::generateWeldSignatureCSVReport()
{
	REPORT_ERROR_CODE enResult = REPORT_GENERATION_FAILED;
	bool bErrorOccured = false;
	
	if(m_ptrDatabaseObj != nullptr)
	{
		int nRowCount = m_ptrDatabaseObj->GetNumberOfRows(TABLE_WELD_SIGNATURE);
		
		//Check if WeldSignature table is not empty.
		if(nRowCount > 0)
		{		
			std::vector<int> vRowIDs = m_ptrDatabaseObj->GetGoldenWeldSignatureRowNumbers();
			
			if(vRowIDs.size() > MAX_GOLDEN_WELD_SIGNATURES_COUNT)
			{
				LOGERR((char *)"More Than 3 Golden Weld Signatures Found, generating report for all of them, Golden Signature Count: %d",vRowIDs.size(),0,0);
			}
			
			//Check if WeldSignature table has golden weld signatures.
			if(vRowIDs.size() > 0)
			{
				int nReportCount = 0;
				
				//Generate separate CSV report for each golden signature/row in WeldSignature table.
				for(auto nRowNumber: vRowIDs)
				{				
					//Generate CSV report name.
					std::string strReportName = reportNameGeneration(nReportCount + 1);	
					std::ofstream CSVReprtFile;
					CSVReprtFile.open(strReportName);
					if(CSVReprtFile.good())
					{
						//Add CSV Report Header1 line containing column names.
						std::string strReportHeader = m_ptrDatabaseObj->GetWeldSignatureCSVReportHeader1();					
						CSVReprtFile << strReportHeader << NEW_LINE;	
						
						int nGraphBlobParamNumber = 0;
						int nResult = 0;  
						std::string strResult = m_ptrDatabaseObj->GetWeldSignatureCSVParameters(nRowNumber, nGraphBlobParamNumber, &nResult);
						if(nResult == SQLITE_OK)
						{
							//Add non-blob data in CSV Report.
							CSVReprtFile << strResult << NEW_LINE;
							
							//Add CSV Report Header2 line containing column names for Graph Blob Data.
							strReportHeader = m_ptrDatabaseObj->GetWeldSignatureCSVReportHeader2();					
							CSVReprtFile << strReportHeader << NEW_LINE;	
							
							//Parse and add Graph Blob Data in CSV report.
							std::string strGraphData = m_ptrDatabaseObj->GetWeldSignatureGraphBlob(nRowNumber, &nResult);
							if(nResult == SQLITE_OK)
							{		
								if(strGraphData != "")
								{
								    REPORT_ERROR_CODE enParseResult = parseWeldSignatureGraphBlob(strGraphData, nGraphBlobParamNumber, CSVReprtFile);
								    if(enParseResult != REPORT_GENERATE_SUCCESS)
								    {
								    	LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - parseWeldSignatureGraphBlob Failure",0,0,0);
								    	enResult = enParseResult;
								    	bErrorOccured = true;
								    } 									
								}
							}
							else
							{
								LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - ERROR in GetWeldSignatureGraphBlob, nResult: %d",nResult,0,0);
								enResult = DATA_NOT_COMPLETE;
								bErrorOccured = true;
							}
						}
						else
						{
							LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - ERROR in GetWeldSignatureCSVParameters, nResult: %d",nResult,0,0);
							enResult = DATA_NOT_COMPLETE;
							bErrorOccured = true;
						}
						
						//Close the CSV report file descriptor.
						CSVReprtFile.close();
						
						if(bErrorOccured == true)
						{
							//break from for loop if error occurs.
							break;
						}			
					}
					else
					{
						LOGERR((char *)"ReportGenerationCSV: generateWeldReusltCSVReport - Report File Open Error",0,0,0);
						bErrorOccured = true;
						enResult = USB_STORAGE_FULL;
						break;
					}
					
					nReportCount++;	
				}//End of for(auto nRowNumber: vRowIDs)
			}
			else
			{
				LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - No Golden Signature",0,0,0);
				bErrorOccured = true;
				enResult = NO_GOLDEN_WELD_SIGNATURE_PRESENT;
			}

			//Make sure no error occured during report generation, then only go ahead and delete records from database.
			if(bErrorOccured == false)
			{
				enResult = REPORT_GENERATE_SUCCESS;
				
				//Delete the records from database if user has requested to delete them.
				/*		
				if(m_stReportMessage.deleteID == true)
				{
					//TO_BE_DONE - Which rows to delete from TABLE_WELD_SIGNATURE table ? All rows or only golden rows ?
					
					bool bDeleteGoldenRowsOnly = true;
					if(bDeleteGoldenRowsOnly)
					{
						//Implementation if we wish to delete golden signatures/rows only from TABLE_WELD_SIGNATURE.
						for (auto nRowNumber : vRowIDs)
						{
							if( m_ptrDatabaseObj->DeleteOneTableRow(TABLE_WELD_SIGNATURE, nRowNumber) != SQLITE_OK)
							{
								LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - Database Record Deletion Failure",0,0,0);
								enResult = DB_DELETE_ERROR;
							}
						}
					}
					else
					{
						//Implementation if we wish to delete all rows from TABLE_WELD_SIGNATURE.
						if( m_ptrDatabaseObj->DeleteAllTableRows(TABLE_WELD_SIGNATURE) != SQLITE_OK)
						{
							LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - Database Record Deletion Failure",0,0,0);
							enResult = DB_DELETE_ERROR;
						}
					}
									
					//PostDeleteResponse(); //TO_BE_DONE
					m_ptrDatabaseObj->Vacuum();
				}
				*/
			}
		}
		else
		{
			LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - Database Empty",0,0,0);
			enResult = DB_EMPTY;
		}
	}
	else
	{
		LOGERR((char *)"ReportGenerationCSV: generateWeldSignatureCSVReport - m_ptrDatabaseObj is NULL",0,0,0);
		enResult = DB_READ_ERROR;
	}
		
	return enResult;
}

/******************************************************************************
* \brief - parse Weld Signature Graph Blob Data and write it into CSV file.
*
* \param: 
* strGraphData - Graph Blob Data read from database as comma separated values.
* nGraphBlobParamNumber - Number of parameters/columns in 1 set of Graph Data.
* CSVReprtFileDesc - CSV Report File Descriptor to which we will write Graph Data.

* \return - REPORT_ERROR_CODE enum.
*
******************************************************************************/
REPORT_ERROR_CODE ReportGenerationCSV::parseWeldSignatureGraphBlob(const std::string &strGraphData, const int &nGraphBlobParamNumber, std::ofstream &CSVReprtFileDesc)
{
	REPORT_ERROR_CODE enResult = REPORT_GENERATE_SUCCESS;
	
	std::size_t colPos = 0, firstPos = 0;
 	std::string strRecordBuffer="";

	//Logic to extract 1 set of Graph Blob data from complete Graph Blob data
	//and write it to CSV report 1 set/row at a time.
    for(int ncolIndex = 0; ncolIndex < nGraphBlobParamNumber; ncolIndex++)
	{
		colPos = strGraphData.find(DB_VALUE_SEPARATOR, colPos + 1);

		if(ncolIndex == (nGraphBlobParamNumber - 1) )
		{									
			strRecordBuffer = strGraphData.substr(firstPos, colPos - firstPos);

			firstPos = colPos + 1;
			ncolIndex = -1;
			
			//Write the parsed graph data to CSV report file.
			CSVReprtFileDesc  << strRecordBuffer << NEW_LINE;

			strRecordBuffer.clear();
			
			if(!CSVReprtFileDesc.good())
			{
				LOGERR((char *)"ReportGenerationCSV: parseWeldSignatureGraphBlob - ERROR in Writing Data to CSV File",0,0,0);
					
				enResult = USB_STORAGE_FULL;
				break;
			}
					
		}

		if(colPos == std::string::npos)
		{
			break;
		}
	}
	
	return enResult;		
}

