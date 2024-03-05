/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
/*
 * CommunicationInterface_HMI.h
 *
 *  Created on: Mar 25, 2021
 *      Author: DShilonie
 */

#ifndef COMMUNICATIONINTERFACE_HMI_H_
#define COMMUNICATIONINTERFACE_HMI_H_


#include "EmrsnSocket.h"
#include "CommunicationInterface.h"
#include "Common.h"
#include "SSLSocket.h"
// defines command exchanges between an HMI and the back-end
//enum HMICommandID
//{
//    REQ_WELD_RECIPE_LIST = 201,
//    RES_WELD_RECIPE_LIST,
//
//    REQ_GET_WELD_RECIPE_PARAM,
//    RES_GET_WELD_RECIPE_PARAM,
//
//    REQ_SET_WELD_RECIPE_PARAM,
//    RES_SET_WELD_RECIPE_PARAM,
//
//    REQ_GET_ACTIVE_RECIPE,
//    RES_GET_ACTIVE_RECIPE,
//
//    REQ_GET_PRODUCTION_WELD_RESULT,
//    RES_GET_PRODUCTION_WELD_RESULT,
//
//    REQ_GET_LAST_WELD_RESULT,
//    RES_GET_LAST_WELD_RESULT,
//
//    REQ_GET_LAST_WELD_PEAKPOWER,
//    RES_GET_LAST_WELD_PEAKPOWER,
//
//    REQ_GET_ALARM_LOG,
//    RES_GET_ALARM_LOG,
//
//    REQ_GET_DEFAULT_HORN_RECIPE,
//    RES_GET_DEFAULT_HORN_RECIPE,
//
//    REQ_GET_HORN_SIGNATURE_DATA,
//    RES_GET_HORN_SIGNATURE_DATA,
//
//    REQ_GET_HORN_SCAN_RESULTS,
//    RES_GET_HORN_SCAN_RESULTS,
//
//    REQ_GET_HORN_SCAN_HISTORY,
//    RES_GET_HORN_SCAN_HISTORY,
//
//    REQ_SET_HORN_SCAN_ID,
//    RES_SET_HORN_SCAN_ID,
//
//    REQ_GET_RECIPE_INFO,
//    RES_GET_RECIPE_INFO,
//
//    REQ_GET_RECIPE_SETUP_INFO,
//    RES_GET_RECIPE_SETUP_INFO,
//
//    REQ_SET_RECIPE_SETUP_INFO,
//    RES_SET_RECIPE_SETUP_INFO,
//
//    REQ_SET_WELD_RECIPE_SETUP_INFO,
//    RES_SET_WELD_RECIPE_SETUP_INFO,
//
//    REQ_USER_LOGIN,
//    RES_USER_LOGIN,
//
//    REQ_GET_ALL_USERS,
//    RES_GET_ALL_USERS,
//
//    REQ_SET_USER_INFO,
//    RES_SET_USER_INFO,
//
//    REQ_SET_ACTIVE_RECIPE,
//    RES_SET_ACTIVE_RECIPE,
//
//    REQ_GET_EVENTS_LOG,
//    RES_GET_EVENTS_LOG,
//
//    REQ_SET_EVENT_LOG,
//    RES_SET_EVENT_LOG,
//
//    REQ_GET_WELD_SIGNATURE_DATA,
//    RES_GET_WELD_SIGNATURE_DATA,
//
//    REQ_GET_WELD_TWH_DATA,
//    RES_GET_WELD_TWH_DATA,
//
//    REQ_GET_WELD_HISTORY_DATA,
//    RES_GET_WELD_HISTORY_DATA,
//
//    REQ_GET_LAST_WELD_HISTORY_DATA,
//    RES_GET_LAST_WELD_HISTORY_DATA,
//
//    REQ_GET_NEXT_WELD_HISTORY_DATA,
//    RES_GET_NEXT_WELD_HISTORY_DATA,
//
//    REQ_UPDATE_WELD_HISTORY_ID,
//    RES_UPDATE_WELD_HISTORY_ID,
//
//    REQ_GET_ALL_AUTHORITY_LEVEL,
//    RES_GET_ALL_AUTHORITY_LEVEL,
//
//    REQ_UPDATE_ALL_AUTHORITY_LEVEL,
//    RES_UPDATE_ALL_AUTHORITY_LEVEL,
//
//    REQ_GET_USER_PASSWORD,
//    RES_GET_USER_PASSWORD,
//
//    REQ_SET_USER_PASSWORD,
//    RES_SET_USER_PASSWORD,
//
//    REQ_GET_USER_DETAILS,
//    RES_GET_USER_DETAILS,
//
//    REQ_SET_GLOBAL_SETTINGS,
//    RES_SET_GLOBAL_SETTINGS,
//
//    REQ_GET_GLOBAL_SETTINGS,
//    RES_GET_GLOBAL_SETTINGS,
//
//    REQ_SET_HORN_RECIPE_DATA,
//    RES_SET_HORN_RECIPE_DATA,
//
//    REQ_SET_SEEK_SCAN_ID,
//    RES_SET_SEEK_SCAN_ID,
//
//    REQ_GET_SEEK_SCAN_HISTORY,
//    RES_GET_SEEK_SCAN_HISTORY,
//
//    REQ_GET_DEFAULT_SEEK_RECIPE,
//    RES_GET_DEFAULT_SEEK_RECIPE,
//
//    REQ_SET_SEEK_RECIPE_DATA,
//    RES_SET_SEEK_RECIPE_DATA,
//
//    REQ_GET_SEEK_SCAN_RESULTS,
//    RES_GET_SEEK_SCAN_RESULTS,
//
//    REQ_GET_SEEK_SIGNATURE_DATA,
//    RES_GET_SEEK_SIGNATURE_DATA,
//
//    REQ_SET_SUSPECT_REJECT_LIMITS_INFO,
//    RES_SET_SUSPECT_REJECT_LIMITS_INFO,
//
//    REQ_GET_SUSPECT_REJECT_LIMITS_INFO,
//    RES_GET_SUSPECT_REJECT_LIMITS_INFO,
//   
// 	REQ_GET_TEST_MODE_DATA,
//    RES_GET_TEST_MODE_DATA,
//
//    REQ_GET_TEST_RECIPE_DATA,
//    RES_GET_TEST_RECIPE_DATA,
//
//    REQ_SET_TEST_RECIPE_DATA,
//    RES_SET_TEST_RECIPE_DATA,
//
//    REQ_GET_TEST_PROGRESS_INFO,
//    RES_GET_TEST_PROGRESS_INFO,
//
//    REQ_GET_DB_VERSION,
//    RES_GET_DB_VERSION,
//
//	REQ_GET_ADD_RECIPENUMBER,
//    RES_SET_ADD_RECIPENUMBER,
//
//	REQ_GET_COPY_RECIPENUMBER,
//    RES_SET_COPY_RECIPENUMBER,
//
//    REQ_SET_WELD_RECIPE_PARAM_FOR_NEW_RECIPE,
//    RES_SET_WELD_RECIPE_PARAM_FOR_NEW_RECIPE,
//
//    REQ_RESONANT_FREQUENCY,
//    RES_RESONANT_FREQUENCY,
//
//    REQ_SET_SUSPECT_REJECT_LIMITS_INFO_FOR_UPDATED,
//    RES_SET_SUSPECT_REJECT_LIMITS_INFO_FOR_UPDATED,
//
//    REQ_SET_RECIPE_SETUP_INFO_FOR_UPDATED,
//    RES_SET_RECIPE_SETUP_INFO_FOR_UPDATED,
//
//    REQ_GET_ACTUATOR_SETUP_PARAMS,
//    RES_GET_ACTUATOR_SETUP_PARAMS,
//
//    REQ_SET_ACTUATOR_SETUP_PARAMS,
//    RES_SET_ACTUATOR_SETUP_PARAMS,
//
//    REQ_GET_ANALYTICS_ALARM,
//    RES_GET_ANALYTICS_ALARM,
//
//    REQ_SET_ANALYTICS_ALARM,
//    RES_SET_ANALYTICS_ALARM,
//
//    REQ_GET_STACK_RECIPE_DATA,
//    RES_GET_STACK_RECIPE_DATA,
//
//    REQ_SET_STACK_RECIPE_DATA,
//    RES_SET_STACK_RECIPE_DATA,
//
//    REQ_SET_BRANSONONLY_PARAMS,
//    RES_SET_BRANSONONLY_PARAMS,
//
//    REQ_GET_BRANSONONLY_PARAMS,
//    RES_GET_BRANSONONLY_PARAMS,
//
//    REQ_SET_BRANSONONLY_PARAMS_UPDATED,
//    RES_SET_BRANSONONLY_PARAMS_UPDATED,
//
//    REQ_GET_ACTIVE_RECIPE_NUMBER,
//    RES_GET_ACTIVE_RECIPE_NUMBER,
//
//    REQ_GET_BATCH_COUNT,
//    RES_GET_BATCH_COUNT,
//
//    REQ_RESET_BATCH_COUNTER,
//    RES_RESET_BATCH_COUNTER,
//
//    REQ_GET_ALL_WELD_RESULT_DATA,
//    RES_GET_ALL_WELD_RESULT_DATA,
//
//    REQ_GET_LAST_ALL_WELD_RESULT_DATA,
//    RES_GET_LAST_ALL_WELD_RESULT_DATA,
//
//    REQ_GET_TRENDSGRAPH_SIGNATURE_DATA,
//    RES_GET_TRENDSGRAPH_SIGNATURE_DATA,
//
//    REQ_GET_SUSPECT_REJECT_LIMITS_TRENDSGRAPH,
//    RES_GET_SUSPECT_REJECT_LIMITS_TRENDSGRAPH,
//
//    REQ_SET_PRODUCT_DATE_PARAM,
//    RES_SET_PRODUCT_DATE_PARAM,
//
//    REQ_GET_USERIO_DATA,
//    RES_GET_USERIO_DATA,
//
//    REQ_SET_USERIO_DATA,
//    RES_SET_USERIO_DATA,
//
//    REQ_GET_SETUP_LIMITS,
//    RES_GET_SETUP_LIMITS,
//
//    REQ_SET_SETUP_LIMITS,
//    RES_SET_SETUP_LIMITS,
//
//    REQ_GET_ACTIVE_RECIPE_FOR_ACTUATOR,
//    RES_GET_ACTIVE_RECIPE_FOR_ACTUATOR,
//
//    REQ_SET_RECIPE_VALIDATE,
//    RES_SET_RECIPE_VALIDATE,
//
//    REQ_SET_RECIPE_BLOB,
//    RES_SET_RECIPE_BLOB,
//
//    REQ_GET_RECIPE_BLOB,
//    RES_GET_RECIPE_BLOB,
//
//    REQ_SET_WELDFORCE_FOR_ACTUATOR,
//    RES_SET_WELDFORCE_FOR_ACTUATOR,
//
//    REQ_SET_RECIPE_UNVALIDATE,
//    RES_SET_RECIPE_UNVALIDATE,
//
//    REQ_FACTORY_RESET,
//    RES_FACTORY_RESET,
//
//    REQ_UPDATE_SYSTEM_DATA,
//    RES_UPDATE_SYSTEM_DATA,
//
//    REQ_UPDATE_USER_LOGIN,
//    RES_UPDATE_USER_LOGIN,
//	
//	SCBL_EMMC_WEAR_LEVEL_REQ,
//	UIC_EMMC_WEAR_LEVEL_RESP,
//	
//	REQ_STOP_COLLECT_GRAPH_DATA,
//	RES_STOP_COLLECT_GRAPH_DATA,
//	
//	SCBL_OPTIMIZE_DATABASE_REQ,
//    UIC_OPTIMIZE_DATABASE_RESP,
//
//    REQ_SAVE_WEBSERVICES_DATA,
//    RES_SAVE_WEBSERVICES_DATA,
//
//    REQ_GET_WEBSERVICES_DATA,
//    RES_GET_WEBSERVICES_DATA,
//
//	DUMMY
//};

class HMI_CommunicationInterface: public CommunicationInterface, public SSLSocket
{
public:
	enum COMMUNICATION_STATUS
	{
		ERROR_LINK = -1,
		SOCKET_LINK = 0,
		SSL_LINK = 1,
		SSL_MESSAGE = 2,
	};
public:
	COMMUNICATION_STATUS m_CommunicationStatus;
	int m_SocketConnectedDescriptor;
public:
	~HMI_CommunicationInterface ();
	static HMI_CommunicationInterface*  getInstance();

private:
	HMI_CommunicationInterface ();
	static HMI_CommunicationInterface *obj;
	static int 						count;

};

#endif /* COMMUNICATIONINTERFACE_HMI_H_ */
