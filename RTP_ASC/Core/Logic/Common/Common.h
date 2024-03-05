/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

/* VxWorks API support header files */
#include  <sys/types.h>
#include  <taskLib.h>
#include  <msgQLib.h>
#include  <eventLib.h>
#include  <timerLib.h>
#include  <sysLib.h>
#include  <tickLib.h>
#include  <semLib.h>
#include  <sys/time.h>
#include  <syscall.h>

/* Language specific header files */
#include  <cstdlib>
#include  <cstdio>
#include  <iostream>
#include  <string>
#include  <cstring>
#include  <unistd.h>
#include  "Logger_old.h"
#include  "HMI_ASC_comms.h"

/* general macro */
#define CRITICAL_DATA_STATUS_FLAG			0xF00D
#define USER_NAME_SIZE						16
#define STACK_SERIAL_SIZE					32
#define STACK_SERIAL_NUMBER_SIZE			10
#define SHUTDOWN_EVENT_REGISTER
#define ALARM_DATA_SIZE_BITS				64
#define ALARM_ACTION_SIZE_BITS				5
#define ACT_TX_PDO_TICK						1000

/* Macro defined for VxWorks message queue length */
#define MAX_SIZE_OF_MSG_LENGTH				768
#define MSG_SIZE							512
#define	MAX_SIZE_OF_MSG_BUFF 				(MAX_SIZE_OF_MSG_LENGTH - 4 * sizeof(UINT32) /* sizeof(ID) + sizeof(len) + sizeof(rspCode) + sizeof(crc))*/)
#define READ_USB_RESP_MSG_MAX_SIZE          2048
#define READ_USB_RESP_MSG_BUFFER_MAX_SIZE   READ_USB_RESP_MSG_MAX_SIZE - 8
#define TIMESTAMP							100

/* for RTC */
#define MIN_YEAR                100
#define MAX_YEAR                199
#define DAYS_IN_YEAR             365
#define DAY_IN_WEEK              7
#define JANUARY                  1
#define FEBRUARY                 2
#define DECEMBER                 12
#define IS_LEAP_YEAR(year)      (((year % 4 == 0) && (year % 100 != 0)) \
                                || year % 400 == 0)

/* 100ms weld signature data points band used before trigger and after hold */
#define WELD_DATA_POINTS_BAND_MS			100
#define WELD_DATA_POINTS_BAND_US			400

/* Delay in ticks - seconds */
#define HALF_SEC_DELAY						(0.5 * sysClkRateGet())
#define ONE_SEC_DELAY						(1 * sysClkRateGet())
#define TWO_SEC_DELAY						(2 * sysClkRateGet())
#define FIVE_SEC_DELAY						(5 * sysClkRateGet())
#define FIFTY_MS_DELAY						((50 * sysClkRateGet()) / 1000)
#define FORTY_MS_DELAY						((40 * sysClkRateGet()) / 1000)
#define DEFAULT_TIMEINTERVAL_US				250

/* Event registers */
#define CTRL_250US							0x01
#define CTRL_1MS							VXEV01
#define	CONSOLE_EVENT						0x02
#define	DATA_TASK_EVENT						0x02
#define	DIGITAL_INPUT_TASK_EVENT			0x03

/* Task/Queue Events */
#define	DATA_TASK_QEVENT					0x04
#define	ACT_TASK_TX_EVENT					0x08
#define	ACT_TASK_RX_EVENT					0x10
#define PS_TASK_TX_EVENT					0x100
#define PS_TASK_RX_EVENT					0x200
#define PS_TASK_1MS_EVENT					0x400
#define PS_TASK_QEVENT						0x800
#define SHUTDOWN_EVENT						VXEV08

/* Macro define for type of recipe */
#define WELD_RECIPE		 					1
#define SEEK_RECIPE							2
#define POWERUP_RECIPE						3
/* L1A features */
#define SCAN_RECIPE							4
#define VERSION_INFO						5
#define TIMER_INTERVAL_RECIPE				6	
#define TEST_RECIPE							7

/* Macro defined for results */
#define WELD_RESULT							1
#define SEEK_RESULT							2
#define SCAN_RESULT							3
#define ALARM_DATA_SC						4
#define ALARM_DATA_PC						5
#define ALARM_DATA_AC						6
#define ALARM_DATA_ALARM_MGR				7
#define WELD_SIGNATURE						8

//#define DEBUG_TEST
#define TEST_TIME_LOOP						250
#define TEST_RESULT							6
/*Stub */

/*	SUBINDIXES are defined below	*/
#define OD_SUB_INDEX_ZERO_INDEX				0x0
#define OD_SUB_INDEX_FIRST_INDEX 			0x1

/* 		Slave ID Index		*/
#define SLAVE_IDX_PC 						0
#define SLAVE_IDX_AC 						1
#define MASTER_IDK_SC						2

/*
*******************************************
	Message ID and command Macro
*******************************************
*/


#define UIC_SYSINFO_READ_RES							SCBL_SYSINFO_READ_REQ
#define TO_UI_TASK_SYSINFO_READ_REQ						SCBL_SYSINFO_READ_REQ

#define UIC_USER_DETAILS_READ_RES						SCBL_USER_DETAILS_READ_REQ

#define UIC_PASSCODE_VALIDATE_RES						SCBL_PASSCODE_VALIDATE_REQ
#define TO_UI_TASK_PASSCODE_VALIDATE_REQ				SCBL_PASSCODE_VALIDATE_REQ

#define UIC_ACTIVE_RECIPE_BASIC_INFO_READ_RES			SCBL_ACTIVE_RECIPE_BASIC_INFO_READ_REQ
#define TO_UI_TASK_ACTIVE_RECIPE_BASIC_INFO_READ_REQ	SCBL_ACTIVE_RECIPE_BASIC_INFO_READ_REQ

#define UIC_WELD_RECIPE_LIST_READ_RES					SCBL_WELD_RECIPE_LIST_READ_REQ





#define ACT_HEART_BEAT_REQ					0
#define UIC_HEART_BEAT_RES					SCBL_HEART_BEAT_REQ
#define ACT_HEART_BEAT_RSP					SCBL_HEART_BEAT_REQ
#define	UIC_UW_SYSREADY_IND					1
//#define UIC_SYSCONFIG_READ_RES				3
//#define SCBL_SYSCONFIG_WRITE_REQ				4
//#define UIC_SYSCONFIG_WRITE_RES				5
//#define SCBL_WELDRECIPE_REQ_SC			    7

// new DSP
#define TO_DSP_TASK_WELD_RECIPE				TO_UI_TASK_WELD_RECIPE
#define TO_DSP_TASK_SEEK_RECIPE    			TO_UI_TASK_SEEK_RECIPE
#define TO_DSP_TASK_DOWNLOAD_RESP	   		10 // control task general response 
#define TO_DSP_TASK_WELD_RESP				13 // control task specific in-message response
#define TO_DSP_TASK_SEEK_RESP				14 // control task specific in-message response

// new AC
#define TO_ACT_SYSTEM_TASK_WELD_RECIPE		TO_UI_TASK_WELD_RECIPE

#define TO_DATA_TASK_WELD_SIGN_DATA			15
#define TO_DATA_TASK_UI_WELD_RECIPE			16 
#define TO_DATA_TASK_SCAN_SIGN_DATA			17
#define TO_DATA_TASK_UL_WELD_RESULT			18
#define TO_UI_TASK_UL_WELD_RESULT			TO_DATA_TASK_UL_WELD_RESULT
#define TO_DATA_TASK_UL_SEEK_RESULT			19
#define TO_UI_TASK_UL_SEEK_RESULT			TO_DATA_TASK_UL_SEEK_RESULT
#define TO_UI_TASK_SETUP_CMD                20
#define TO_UI_TASK_SET_NEXT_OPERATION_REQ   SCBL_SET_NEXT_OPERATION_REQ
#define TO_CTRL_TASK_SETUP_CMD				TO_UI_TASK_SETUP_CMD
#define TO_CTRL_TASK_SET_NEXT_OPERATION_REQ	TO_UI_TASK_SET_NEXT_OPERATION_REQ
#define TO_UI_TASK_WELD_CMD					21
#define TO_CTRL_TASK_WELD_CMD				TO_UI_TASK_WELD_CMD
#define TO_UI_TASK_WELD_RECIPE_PC			22
#define TO_UI_TASK_WELD_RECIPE_AC			23
#define TO_CTRL_TASK_WELD_CMD_FROM_GPIO 	24

//new DSP
#define TO_DSP_TASK_WELD_RECIPE_RELOAD			TO_UI_TASK_WELD_RECIPE_PC
//new AC
#define TO_ACT_SYSTEM_TASK_WELD_RECIPE_RELOAD	TO_UI_TASK_WELD_RECIPE_AC
#define TO_ACT_SYSTEM_TASK_WELD_RECIPE_RESP	25
#define TO_UIC_WELD_DATA_DELETE_IND			26

#define TO_DATA_TASK_READ_RECIPE			28
#define TO_UI_TASK_POWER_UP_RECIPE			29

// new DSP
#define TO_DSP_TASK_POWER_UP_RECIPE   		TO_UI_TASK_POWER_UP_RECIPE
#define TO_DSP_TASK_POWERUP_RESP			30 // control task specific in-message response


#define TO_UI_TASK_DOWNLOAD_POWERUP_RESP	TO_DSP_TASK_POWERUP_RESP
#define TO_UI_TASK_HORN_SCAN_RECIPE			31

// new DSP
#define TO_DSP_TASK_HORN_SCAN_RECIPE		TO_UI_TASK_HORN_SCAN_RECIPE
#define TO_DSP_TASK_HORN_SCAN_RESP 			32 // control task specific in-message response

#define TO_UI_TASK_HORN_SCAN_RECIPE_RESP	TO_DSP_TASK_HORN_SCAN_RESP
#define TO_UI_TASK_HORN_SCAN_CMD			33
#define TO_CTRL_TASK_HORN_SCAN_CMD			TO_UI_TASK_HORN_SCAN_CMD
#define TO_DATA_TASK_HORN_SCAN_RESULT		34
#define TO_UI_TASK_HORN_SCAN_RESULT			35
#define TO_UI_TASK_HORN_SCAN_ABORT_CMD		37
#define TO_CTRL_TASK_HORN_SCAN_ABORT_CMD	TO_UI_TASK_HORN_SCAN_ABORT_CMD
#define TO_UI_TASK_SCAN_ABORT_CMD_RESP		38

// new DSP
#define TO_DSP_TASK_ALARM_DATA_REQ 			39
#define TO_DATA_TASK_UL_ALARM_DATA_PC		40

// new AC
#define TO_ACT_SYSTEM_TASK_ALARM_DATA_REQ	41
#define TO_ACT_SYSTEM_TASK_ALARM_DATA_RESP	42

#define TO_DATA_TASK_UL_ALARM_DATA_AC		TO_ACT_SYSTEM_TASK_ALARM_DATA_RESP
#define TO_UI_TASK_VERSION_REQUEST			43

// new AC
#define TO_ACT_SYSTEM_TASK_VERSION_SERIAL_REQ  TO_UI_TASK_VERSION_REQUEST
#define TO_ACT_SYSTEM_TASK_VERSION_SERIAL_RESP	44

// new DSP
#define TO_DSP_TASK_VERSION_SERIAL_REQ		TO_UI_TASK_VERSION_REQUEST
#define TO_DSP_TASK_VERSION_SERIAL_RESP		45

#define TO_DATA_TASK_ALARM_DATA_SC			46 
#define TO_UI_TASK_SYS_CONFIG_READ_REQ		47
#define TO_UI_TASK_SYS_CONFIG_WRITE_REQ		48
#define TO_UI_TASK_RECIPE_UPDATE_STOP_REQ	49
#define TO_UI_TASK_PROGRESS_BAR_STATUS		50
#define TO_UI_TASK_SYSREADY_IND_REQ			51
#define TO_UI_TASK_ALARM_RESET_RESP			52
#define TO_UI_TASK_ALARM_CLEAR_REQ			UIC_ALARM_CLEAR_REQ
#define TO_UI_TASK_SETUP_RESP				53
#define TO_UI_TASK_SC_STATE_REQ				54
#define TO_CTRL_TASK_SC_STATE_REQ			TO_UI_TASK_SC_STATE_REQ
#define TO_UI_TASK_SC_STATE_RES				55
#define TO_DATA_TASK_NEW_RECIPE_RECEIVED	56
#define TO_UI_TASK_ACTIVE_ALARM_REQ			57
#define TO_UI_TASK_SEEK_RES					58
#define TO_UI_TASK_HORN_SCAN_RES			59
#define TO_DATA_TASK_CTRL_TEST_SIGN_DATA	60
#define TO_DATA_TASK_TEST_RESULT			61
#define TO_UI_TASK_CALIBRATION_READ_REQ		62
#define TO_UI_TASK_CALIBRATION_READ_RES		63

// new AC
#define TO_ACT_SYSTEM_TASK_CAL_READ_REQ		TO_UI_TASK_CALIBRATION_READ_REQ
#define TO_ACT_SYSTEM_TASK_CAL_READ_RESP	TO_UI_TASK_CALIBRATION_READ_RES 

#define SCBL_FACTORY_RESET_REQ 				64
#define SCBL_SEEK_RECIPE_REQ				65
#define UIC_SEEK_RECIPE_RES					66
#define SCBL_SEEK_CMD_REQ					67
#define UIC_SEEK_CMD_RES					68
#define SCBL_SETUP_CMD_REQ					69
#define UIC_SETUP_CMD_RES					70
#define UIC_ALARM_DATA_INDICATION			71
#define SCBL_ALARM_RESET_REQ				72
#define UIC_ALARM_RESET_RES					73
#define UIC_ALARM_CLEAR_REQ					74
#define SCBL_ALARM_RESET_ALL_REQ			77
#define UIC_ALARM_RESET_ALL_RES 			78 

/*BATCH SETUP */
#define TO_UI_TASK_BATCH_COUNT_EXCEED_CMD		80
#define	TO_CTRL_TASK_BATCH_COUNT_EXCEED_CMD		TO_UI_TASK_BATCH_COUNT_EXCEED_CMD
#define TO_DATA_TASK_BATCH_COUNT_EXCEED_CMD		TO_UI_TASK_BATCH_COUNT_EXCEED_CMD
#define TO_UI_TASK_BATCH_COUNT_RESET_REQ		SCBL_BATCH_COUNT_RESET_REQ
#define TO_CTRL_TASK_BATCH_COUNT_RESET_CMD_REQ	TO_UI_TASK_BATCH_COUNT_RESET_REQ
#define TO_DATA_TASK_BATCH_COUNT_RESET_REQ		TO_UI_TASK_BATCH_COUNT_RESET_REQ
#define TO_UI_TASK_BATCH_COUNT_RESET_RSP		UIC_BATCH_COUNT_RESET_RES

#define SCBL_SC_STATE_REQ					81
#define UIC_SC_STATE_RES					82
#define SCBL_ACTIVE_ALARM_REQ				83
#define UIC_ACTIVE_ALARM_RES				84
#define SCBL_FEATURERUN_READ_REQ 			85
#define UIC_FEATURERUN_READ_RES 			86
#define SCBL_IP_CONFIGURATION_READ_REQ		87
#define UIC_IP_CONFIGURATION_READ_RES		88
#define SCBL_IP_CONFIGURATION_WRITE_REQ		89
#define UIC_IP_CONFIGURATION_WRITE_RES		90

#define TO_UI_TASK_CHECK_NEW_ACTIVE_RECIPE	91					
#define SCBL_SET_NEXT_OPERATION_REQ			92
#define SCBL_TEST_RECIPE_REQ				93
#define UIC_TEST_RECIPE_RES					94
#define SCBL_TEST_CMD_REQ					95
#define UIC_TEST_CMD_RES					96
#define SCBL_TEST_ABORT_CMD_REQ				97
#define UIC_TEST_ABORT_CMD_RES				98
#define UIC_TEST_PROGRESS_IND				99
#define UIC_WELD_PROGRESS_IND				100
#define SCBL_CALIBRATION_CMD_REQ			101
#define UIC_CALIBRATION_CMD_RES				102
#define SCBL_FW_UPGRADE_REQ					104
#define UIC_FW_UPGRADE_RES					105
#define SCBL_FW_UPGRADE_CMD_REQ				106
#define UIC_FW_UPGRADE_CMD_RES				107
#define UIC_FW_UPGRADE_PROGRESS_IND			108
#define UIC_FW_UPGRADE_ETHER_IND			109
#define SCBL_FW_UPGRADE_ETHER_REQ			110

#define SCBL_SYS_DATETIME_READ_REQ			111
#define UIC_SYS_DATETIME_READ_RES			112
#define SCBL_SYS_DATETIME_WRITE_REQ			113
#define UIC_SYS_DATETIME_WRITE_RES			114
#define UIC_EMERGENCY_STOP_ACTIVE_IND		115
#define UIC_EMERGENCY_STOP_RESET_IND		116
#define SCBL_EMERGENCY_STOP_RESET_REQ		117
#define UIC_EMERGENCY_STOP_RESET_RES		118

#define SCBL_DEFAULT_ALARM_CONFIG_REQ			120
#define UIC_DEFAULT_ALARM_CONFIG_RSP			121
#define SCBL_ALARM_CONFIG_READ_REQ				122
#define UIC_ALARM_CONFIG_READ_RSP				123
#define SCBL_ALARM_CONFIG_SAVE_REQ				124
#define UIC_ALARM_CONFIG_SAVE_RSP				125
#define TO_UI_TASK_DEFAULT_ALARM_CONFIG_REQ		SCBL_DEFAULT_ALARM_CONFIG_REQ
#define TO_UI_TASK_ALARM_CONFIG_READ_REQ		SCBL_ALARM_CONFIG_READ_REQ		
#define TO_UI_TASK_ALARM_CONFIG_SAVE_REQ		SCBL_ALARM_CONFIG_SAVE_REQ
#define TO_DATA_TASK_ALARM_CONFIG_SAVE_REQ		TO_UI_TASK_ALARM_CONFIG_SAVE_REQ	
#define TO_UI_TASK_ALARM_CONFIG_SAVE_RES		UIC_ALARM_CONFIG_SAVE_RSP

#define SCBL_BATCH_COUNT_RESET_REQ				126
#define UIC_BATCH_COUNT_RESET_RES				127
#define SCBL_USERIO_READ_REQ					128
#define UIC_USERIO_READ_RES						129

/* Timer interval interface */
#define TO_UI_TASK_TMR_INTVL_DATA_PC  			131   
#define TO_UI_TASK_TMR_INTVL_RESP_PC  			132 

// new DSP
#define TO_DSP_TASK_TMR_INTVL_DATA  			131
#define TO_OSP_TASK_TMR_INTVL_RESP  			132 // control task specific in-message response

#define SCBL_MEMORY_OFFSET_RESET_REQ			133
#define UIC_MEMORY_OFFSET_RESET_RES				134

#define TO_UI_TASK_ALARM_MGR_ALARM_IND				136
#define TO_UI_TASK_ALARM_MGR_ACTIVE_ALARM_REQ 		137
#define TO_UI_TASK_ALARM_MGR_RESET_RESP				138
#define TO_ALARM_TASK_DEFAULT_ALARM_CONFIG_REQ 		139
#define TO_UI_TASK_ALARM_MGR_DEFAULT_CONFIG			140
#define TO_ALARM_TASK_ALARM_CONFIG_REQ				141
#define TO_UI_TASK_ALARM_MGR_CONFIG_REQ				142
#define TO_ALARM_TASK_ALARM_CONFIG_SAVE_REQ			143
#define TO_UI_TASK_ALARM_MGR_CONFIG_SAVE			144
#define TO_UI_TASK_ALARM_MGR_RESET_ALL_RESP			145
#define TO_ALARM_TASK_CREATE_DEFAULT_ALARM_CONFIG 	146
#define TO_ALARM_TASK_CREATE_CURRENT_ALARM_CONFIG 	147
#define SCBL_FEATURERUN_WRITE_REQ 					148
#define TO_DATA_TASK_ALARM_MGR_ALARM_DATA 			149
#define TO_CTRL_TASK_USERIO_READ_REQ				150 
#define TO_DATA_TASK_PASSWORD_OVERRIDE				151
#define TO_UI_TASK_ALARM_MGR_RESET_ALL_REQ			152
#define TO_DATA_TASK_LOG_EVENT 						153				
#define TO_DATA_TASK_LOG_EVENT_COMMENT 				154		
#define TO_CTRL_TASK_UL_WELD_SIGNATURE 				155
#define TO_CTRL_TASK_ACT_PDO_IND						156

#define SCBL_GEN_SINGLE_REPORT_REQ 					160
#define SCBL_GEN_SINGLE_REPORT_RSP 					161
#define SCBL_GEN_REPORT_ACTION_IND 					162
#define UIC_GEN_DB_REPORT_REMIND_LATER_REQ  		163
#define SCBL_GEN_REPORT_REMIND_LATER_RSP    		164

#define TO_UI_CALIBRATION_DATA_REQUEST				165
#define TO_UI_CALIBRATION_DATA_REQUEST_RESP			166
// new AC
#define TO_ACT_SYSTEM_TASK_CAL_DATA_REQ				TO_UI_CALIBRATION_DATA_REQUEST
#define TO_ACT_SYSTEM_TASK_CAL_DATA__RESP			TO_UI_CALIBRATION_DATA_REQUEST_RESP

// new AC
#define TO_ACT_PROCESS_TASK_TX_DATA					167
#define TO_ACT_PROCESS_TASK_RX_DATA					168

#define SCBL_PRIVATE_KEY_REQ						169
#define UIC_PRIVATE_KEY_RES							170
#define SCBL_PRIVATE_KEY_UPLOAD_REQ					171
#define UIC_PRIVATE_KEY_UPLOAD_RES					172

#define TO_UI_TASK_BARCODE_DATA											173		
#define UIC_BARCODE_RECIPE_RECALL_AUTHENTICATION_CHECK_REQ 				174
#define SCBL_BARCODE_RECIPE_RECALL_AUTHENTICATION_CHECK_RES				175
#define TO_UI_TASK_BARCODE_RECIPE_RECALL_AUTHENTICATION_CHECK_RES		SCBL_BARCODE_RECIPE_RECALL_AUTHENTICATION_CHECK_RES
#define TO_DATA_TASK_BARCODE_RECIPE_RECALL_REQ							176

#define TO_UI_TASK_BARCODE_RECIPE_RECALL_REQ							177
#define TO_UI_TASK_BARCODE_RECIPE_RECALL_RSP							178
#define TO_UI_TASK_BARCODE_ERROR_IND									179

/* Alarm management interface */
#define TO_DATA_TASK_ALARM_CONFIG_RW_REQ			180
#define TO_DATA_TASK_CREATE_DEFAULT_ALARM_CONFIG	181
#define UIC_FEATURERUN_WRITE_RES 					182

#define UIC_BARCODE_PART_ID_IND						183	
#define TO_UI_TASK_BARCODE_SCANNER_STATUS_IND		184
#define UIC_BARCODE_SCANNER_STATUS_IND				TO_UI_TASK_BARCODE_SCANNER_STATUS_IND
#define TO_UI_TASK_WEBSERVICE_LOGIN_IND				185
#define UIC_WEBSERVICE_LOGIN_IND					TO_UI_TASK_WEBSERVICE_LOGIN_IND

#define TO_UI_TASK_GEN_SINGLE_REPORT_REQ    		SCBL_GEN_SINGLE_REPORT_REQ
#define TO_DATA_TASK_GEN_SINGLE_REPORT_REQ			SCBL_GEN_SINGLE_REPORT_REQ
#define TO_UI_TASK_GEN_SINGLE_REPORT_RES    		SCBL_GEN_SINGLE_REPORT_RSP

#define TO_DATA_TASK_DB_CONNECTION_CLOSE_REQ		187
#define TO_DATA_TASK_DB_CONNECTION_CLOSE_RES		188
#define TO_DATA_TASK_DB_CONNECTION_OPEN_REQ			189
#define TO_DATA_TASK_DB_CONNECTION_OPEN_RES			190

#define SCBL_STACK_RECIPE_REQ               		191	
#define UIC_STACK_RECIPE_RES                		192
#define SCBL_DB_FILE_COPY_TO_USB_REQ				193
#define UIC_DB_FILE_COPY_TO_USB_RES					194
#define SCBL_DB_FILE_DELETE_FROM_USB_REQ			195
#define UIC_DB_FILE_DELETE_FROM_USB_RES				196
#define SCBL_BRANSON_KEY_REQ						197
#define UIC_BRANSON_KEY_RES							198
#define TO_UI_TASK_CLEAR_ALL						199			
#define UIC_FACTORY_RESET_RSP 						200

/* Alarm Task */
#define TO_ALARM_TASK_ALARM_EVENT					201
#define TO_ALARM_TASK_ALARM_INFO_PC					202
#define TO_ALARM_TASK_ALARM_INFO_AC					203
#define TO_ALARM_TASK_ALARM_INFO_SC					204
#define TO_ALARM_TASK_CLEAR_ALL						205
#define TO_ALARM_TASK_RESET_ALARM					206
#define TO_ALARM_TASK_ACTIVE_ALARM_REQ				207
#define TO_ALARM_TASK_ALARM_CONFIG_SAVE				208
#define TO_ALARM_TASK_ESTOP_EVENT					209
#define TO_ALARM_TASK_ESTOP_RELEASE					210
#define TO_ALARM_TASK_ESTOP_RESET					211
#define TO_ALARM_TASK_RESET_INPUT					212
#define TO_ALARM_TASK_UI_CLEAR_ALL					213
#define TO_ALARM_TASK_UI_CLEAR_ALL_REQ				214

/* maintenance Task */
#define TO_MAINTENANCE_TASK_CNTRS_INC_ACTUATIONS 	215
#define TO_MAINTENANCE_TASK_CNTRS_INC_WELDS 	 	216
#define TO_MAINTENANCE_TASK_CNTRS_INC_ALARMS 	 	217
#define TO_MAINTENANCE_TASK_CNTRS_INC_OVERLOADS	 	218

#define TO_UI_TASK_WELD_RECIPE 						219
#define TO_CTRL_TASK_SEEK_CMD						220
#define TO_UI_TASK_RESET_ALARM_CMD					221
#define TO_UI_TASK_SEEK_RECIPE						222
#define TO_UI_TASK_WELD_RECIPE_CONFIGURED   		223		
#define TO_UI_TASK_SEEK_RECIPE_CONFIGURED   		224

#define TO_CTRL_TASK_WELD_RECIPE_CONFIGURED 		TO_UI_TASK_WELD_RECIPE_CONFIGURED
#define TO_CTRL_TASK_SEEK_RECIPE_CONFIGURED 		TO_UI_TASK_SEEK_RECIPE_CONFIGURED
#define TO_UI_TASK_WELD_RECIPE_SC		    		225
#define TO_CTRL_TASK_RESET_ALARM_CMD  				226 

#define TO_UI_TASK_WELD_RECIPE_RESP_PC				227
#define TO_UI_TASK_WELD_RECIPE_RESP_AC				228
#define TO_UI_TASK_WELD_DATA_DELETE_IND				TO_UIC_WELD_DATA_DELETE_IND

#define TO_UI_TASK_VERSION_SERIAL_REQUEST_RESP_AC TO_ACT_SYSTEM_TASK_VERSION_SERIAL_RESP
#define TO_UI_TASK_VERSION_SERIAL_REQUEST_RESP_PC 229

#define SCBL_SYSINFO_WRITE_REQ						230
#define TO_UI_TASK_SYS_INFO_WRITE_REQ				SCBL_SYSINFO_WRITE_REQ
#define TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_REQ		TO_UI_TASK_SYS_INFO_WRITE_REQ
#define TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_RESP		231
#define TO_UI_TASK_SYS_INFO_WRITE_RES				TO_ACT_SYSTEM_TASK_SYS_INFO_WRITE_RESP
/* Test feature */
#define TO_UI_TASK_TEST_RECIPE_REQ 					SCBL_TEST_RECIPE_REQ
#define TO_UI_TASK_TEST_RECIPE_RES					UIC_TEST_RECIPE_RES

// new DSP
#define TO_DSP_TASK_TEST_RECIPE						TO_UI_TASK_TEST_RECIPE_REQ
#define TO_DSP_TASK_TEST_RECIPE_RESP				TO_UI_TASK_TEST_RECIPE_RES // control task specific in-message response

#define TO_UI_TASK_TEST_CMD_REQ						SCBL_TEST_CMD_REQ
#define TO_UI_TASK_TEST_PROGRESS_IND				UIC_TEST_PROGRESS_IND
#define TO_UI_TASK_TEST_CMD_RES						UIC_TEST_CMD_RES
#define TO_CTRL_TASK_TEST_CMD_REQ					TO_UI_TASK_TEST_CMD_REQ
#define TO_UI_TASK_TEST_ABORT_CMD_REQ				SCBL_TEST_ABORT_CMD_REQ
#define TO_UI_TASK_TEST_ABORT_CMD_RES				UIC_TEST_ABORT_CMD_RES
#define TO_CTRL_TASK_TEST_ABORT_CMD_REQ				TO_UI_TASK_TEST_ABORT_CMD_REQ

/* Run time feature */
#define TO_UI_TASK_FEATURERUN_READ_REQ				SCBL_FEATURERUN_READ_REQ

/* IP configuration feature */
#define TO_UI_TASK_IP_CONFIGURATION_READ_REQ 		SCBL_IP_CONFIGURATION_READ_REQ
#define TO_UI_TASK_IP_CONFIGURATION_WRITE_REQ 		SCBL_IP_CONFIGURATION_WRITE_REQ

/* Emergency stop feature */
#define TO_UI_TASK_EMERGENCY_STOP_ACTIVE_IND 		UIC_EMERGENCY_STOP_ACTIVE_IND
#define TO_UI_TASK_EMERGENCY_STOP_RESET_IND			UIC_EMERGENCY_STOP_RESET_IND
#define TO_DATA_TASK_EMERGENCY_STOP_ACTIVE_IND 		UIC_EMERGENCY_STOP_ACTIVE_IND
#define TO_DATA_TASK_EMERGENCY_STOP_RESET_IND		UIC_EMERGENCY_STOP_RESET_IND
#define TO_UI_TASK_ESTOP_RESET_REQ					SCBL_EMERGENCY_STOP_RESET_REQ
#define TO_UI_TASK_ESTOP_RESET_RES					UIC_EMERGENCY_STOP_RESET_RES

/* Progress bar indications */
#define TO_TASK_WELD_PROGRESS_IND					UIC_WELD_PROGRESS_IND

/* Force Calibration interface details */
#define TO_UI_TASK_CALIBRATION_CMD_REQ         		SCBL_CALIBRATION_CMD_REQ
#define TO_CTRL_TASK_CALIBRATION_CMD_REQ       		TO_UI_TASK_CALIBRATION_CMD_REQ
#define TO_UI_TASK_CALIBRATION_CMD_RES				UIC_CALIBRATION_CMD_RES
#define TO_DATA_TASK_CALIBRATION_ABORT_CMD_REQ		TO_UI_TASK_CALIBRATION_CMD_REQ

/* Firmware upgrade interface details */
#define TO_FWUP_TASK_FW_UPGRADE_REQ					SCBL_FW_UPGRADE_REQ
#define TO_FWUP_TASK_FW_UPGRADE_RES					UIC_FW_UPGRADE_RES
#define TO_FWUP_TASK_FW_UPGRADE_CMD_REQ				SCBL_FW_UPGRADE_CMD_REQ
#define TO_FWUP_TASK_FW_UPGRADE_CMD_RES				UIC_FW_UPGRADE_CMD_RES
#define TO_FWUP_TASK_FW_UPGRADE_PROGRESS_IND		UIC_FW_UPGRADE_PROGRESS_IND
#define SERVER_ETHRNT_FW_UPLOAD_NOTIFY 		    	UIC_FW_UPGRADE_ETHER_IND
#define TO_FWUP_TASK_FW_UPGRADE_ETHER_REQ	    	SCBL_FW_UPGRADE_ETHER_REQ
#define TO_UI_TASK_FW_UPGRADE_ETHER_IND				UIC_FW_UPGRADE_ETHER_IND

/* System date and time read and write request */
#define TO_UI_TASK_DATETIME_READ_REQ				SCBL_SYS_DATETIME_READ_REQ
#define TO_UI_TASK_DATETIME_WRITE_REQ				SCBL_SYS_DATETIME_WRITE_REQ

/*Macro defined for set the ranges of PC-Timer interval in us for the PC's ISR clock*/
#define PC_MAX_TIMER_INTERVAL						1000   	// 1ms		
#define PC_MIN_TIMER_INTERVAL						50 		// 50us			
#define PC_DEFAULT_TIMER_INTERVAL    				1000  	// 1ms		

/* Bar code interface */
#define BARCODE_DATA_SIZE							50
#define UIC_BARCODE_ERROR_IND						TO_UI_TASK_BARCODE_ERROR_IND
#define UIC_BARCODE_RECIPE_RECALL_REQ				TO_UI_TASK_BARCODE_RECIPE_RECALL_REQ
#define SCBL_BARCODE_RECIPE_RECALL_RSP				TO_UI_TASK_BARCODE_RECIPE_RECALL_RSP
#define TO_DATA_TASK_BARCODE_RECIPE_RECALL_RSP		TO_UI_TASK_BARCODE_RECIPE_RECALL_RSP
#define TO_UI_TASK_STACK_RECIPE             		SCBL_STACK_RECIPE_REQ
#define TO_UI_TASK_DB_FILE_COPY_TO_USB_REQ 			SCBL_DB_FILE_COPY_TO_USB_REQ
#define TO_UI_TASK_DB_FILE_COPY_TO_USB_RES			UIC_DB_FILE_COPY_TO_USB_RES
#define TO_UI_TASK_DB_FILE_DELETE_FROM_USB_REQ		SCBL_DB_FILE_DELETE_FROM_USB_REQ
#define TO_UI_TASK_DB_FILE_DELETE_FROM_USB_RES 		UIC_DB_FILE_DELETE_FROM_USB_RES
#define TO_DATA_TASK_DB_FILE_DELETE_FROM_USB_REQ	TO_UI_TASK_DB_FILE_DELETE_FROM_USB_REQ

/* USER I/O macros */
#define TO_UI_TASK_USERIO_READ_REQ					SCBL_USERIO_READ_REQ	
#define	TO_UI_TASK_USERIO_READ_RES					UIC_USERIO_READ_RES

/* Report Generation */
#define TO_UI_TASK_GEN_REPORT_ACTION_IND			SCBL_GEN_REPORT_ACTION_IND
#define TO_DATA_TASK_GEN_REPORT_ACTION_IND			SCBL_GEN_REPORT_ACTION_IND
#define TO_UI_TASK_GEN_SINGLE_REPORT_REQ    		SCBL_GEN_SINGLE_REPORT_REQ
#define TO_DATA_TASK_GEN_SINGLE_REPORT_REQ			SCBL_GEN_SINGLE_REPORT_REQ
#define TO_UI_TASK_GEN_SINGLE_REPORT_RES    		SCBL_GEN_SINGLE_REPORT_RSP
#define TO_UI_GEN_DB_REPORT_REMIND_LATER_REQ 		UIC_GEN_DB_REPORT_REMIND_LATER_REQ

/* BRANSON_KEY interface */	
#define TO_UI_TASK_BRANSON_KEY_REQ 					SCBL_BRANSON_KEY_REQ

#define SCBL_DEFAULT_FEATURERUN_REQ 				608
#define UIC_DEFAULT_FEATURERUN_RES 					609
#define TO_UI_TASK_FEATURERUN_WRITE_REQ 			SCBL_FEATURERUN_WRITE_REQ
#define TO_UI_TASK_FACTORY_RESET_REQ 				SCBL_FACTORY_RESET_REQ
#define TO_UI_TASK_DEFAULT_FEATURERUN_REQ			SCBL_DEFAULT_FEATURERUN_REQ
#define TO_UI_TASK_REPORT_DELETE_RSP				614
#define TO_UI_TASK_ALARM_DATA_INDICATION			UIC_ALARM_DATA_INDICATION
#define TO_DATA_TASK_MEMORY_FULL_STORAGE_CHECK		TO_UI_TASK_SYS_CONFIG_WRITE_REQ
#define TO_UI_TASK_MEMORY_OFFSET_RESET_REQ			SCBL_MEMORY_OFFSET_RESET_REQ

/* USER I/O macros */
#define TO_UI_TASK_USERIO_READ_REQ					SCBL_USERIO_READ_REQ	
#define	TO_UI_TASK_USERIO_READ_RES					UIC_USERIO_READ_RES

/* EMMC wear level */
#define TO_UI_TASK_EMMC_WEAR_LEVEL_REQ				SCBL_EMMC_WEAR_LEVEL_REQ

#define TO_CTRL_TASK_EMMC_WEAR_LEVEL_REQ			TO_UI_TASK_EMMC_WEAR_LEVEL_REQ
#define TO_UI_TASK_EMMC_WEAR_LEVEL_RESP				UIC_EMMC_WEAR_LEVEL_RESP
#define EMMC_WEAR_LEVEL_LOW							0
#define EMMC_WEAR_LEVEL_MEDUIM						50
#define EMMC_WEAR_LEVEL_ALARM						80
#define EMMC_WEAR_LEVEL_MAX							100
#define EMMC_WEAR_CYCLE_CHECK						100000

/* Database optimization */
#define TO_UI_TASK_OPTIMIZE_DATABASE_REQ			SCBL_OPTIMIZE_DATABASE_REQ
#define TO_UI_TASK_OPTIMIZE_DATABASE_RESP			UIC_OPTIMIZE_DATABASE_RESP
#define TO_CTRL_TASK_OPTIMIZE_DATABASE_REQ			TO_UI_TASK_OPTIMIZE_DATABASE_REQ

/* Macro defined to status of request from UIC */
#define RESPONSE_SUCCESS							1
#define RESPONSE_FAIL								0

#define SHUTDOWN_APPLICATION						1000
#define USER_DETAILS_MSG_LEN						100

#define TO_FWUP_TASK_WEBSERVICE_UI_VERSION_RES  	SCBL_WEBSERVICE_UI_VERSION_RES

/* Macro defined for web services */
#define USERDATA_LENGTH			 							32
#define SCBL_WEBSERVICES_LOGIN_REQ							600
#define UIC_WEBSERVICES_LOGIN_RES							601
#define SCBL_SET_HMI_LOGIN_REQ								602
#define SCBL_WEBSERVICE_UI_VERSION_RES      				603
#define UIC_WEBSERVICE_UI_VERSION_REQ       				604

#define TO_DATA_TASK_WS_USER_DETAILS						605
#define TO_WEB_SERVICES_TASK_USER_DETAILS					606
#define TO_DATA_TASK_WS_LAST_WELD_RESULTS					607
#define TO_WEB_SERVICES_TASK_LAST_WELD_RESULTS				608
#define TO_DATA_TASK_WS_EVENT_LOGIN							609
#define TO_WEB_SERVICES_TASK_WS_EVENT_LOGIN					610
#define TO_DATA_TASK_WS_NUMBER_OF_ALARMS					611
#define TO_WEB_SERVICES_TASK_NUMBER_OF_ALARMS				612
#define TO_DATA_TASK_WS_GET_PW_EXPIRY_DAYS					613
#define TO_WEB_SERVICES_TASK_GET_PW_EXPIRY_DAYS				614
#define TO_DATA_TASK_WS_EVENT_LOGOUT						615
#define TO_WEB_SERVICES_TASK_WS_EVENT_LOGOUT				616
#define TO_DATA_TASK_WS_GET_IDLE_LOGOUT_TIME				617
#define TO_WEB_SERVICES_TASK_WS_GET_IDLE_LOGOUT_TIME		618
#define TO_DATA_TASK_WS_NUMBER_OF_WELDHISTORY				619
#define TO_WEB_SERVICES_TASK_NUMBER_OF_WELDHISTORY			620
#define TO_WEB_SERVICES_TASK_AUTHORITY_CHECK_OPERATOR		621
#define TO_DATA_TASK_WS_AUTHORITY_CHECK_OPERATOR			622
#define TO_WEB_SERVICES_TASK_SET_AS_ACTIVE_RECIPE			623
#define TO_DATA_TASK_WS_SET_ACTIVE_RECIPE					624
#define TO_DATA_TASK_WS_GET_ACTIVE_RECIPE					625
#define TO_WEB_SERVICES_TASK_GET_ACTIVE_RECIPE				626
#define TO_DATA_TASK_WS_SET_ACTIVE_WELD_RECIPE				627
#define TO_DATA_TASK_WS_SET_ACTIVE_SR_RECIPE				628
#define TO_DATA_TASK_WS_GET_RECIPE_VALUE					629
#define TO_WEB_SERVICES_TASK_WS_GET_RECIPE_VALUE			630
#define TO_DATA_TASK_WS_DELETE_RECIPE						631
#define TO_WEB_SERVICES_TASK_WS_DELETE_RECIPE				632
#define TO_DATA_TASK_WS_SAVE_RECIPE							633
#define TO_WEB_SERVICES_TASK_WS_SAVE_RECIPE					634
#define TO_DATA_TASK_WS_GET_WELD_HISTORY					635
#define TO_WEB_SERVICES_TASK_WS_GET_WELD_HISTORY_NEXT		636
#define TO_WEB_SERVICES_TASK_WS_GET_WELD_HISTORY_FINISH		637
#define TO_DATA_TASK_WS_GET_ALARM_LOG						638
#define TO_WEB_SERVICES_TASK_WS_GET_ALARM_LOG_NEXT			639
#define TO_WEB_SERVICES_TASK_WS_GET_ALARM_LOG_FINISH		640
#define TO_DATA_TASK_WS_GET_GRAPH_RESULTS					641
#define TO_WEB_SERVICES_TASK_WS_GET_GRAPH_RESULTS_NEXT		642
#define TO_WEB_SERVICES_TASK_WS_GET_GRAPH_RESULTS_FINISH	643
#define TO_DATA_TASK_WS_EVENT_SET_RECIPE_VALUE				644
#define TO_WEB_SERVICES_TASK_WS_SET_RECIPE_VALUE			645
#define TO_DATA_TASK_WS_GET_RUNTIME_DETAILS					646
#define TO_WEB_SERVICES_TASK_WS_GET_RUNTIME_DETAILS			647
#define TO_DATA_TASK_WS_GET_ALL_USER_DETAILS				648
#define TO_WEB_SERVICES_TASK_GET_ALL_USER_DETAILS			649

/* Macro defined for file and path - Recipes*/
#define UPDATED_WELD_RECIPE_PATH			MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"UpdatedWeldRecipe.txt"
#define DEFAULT_WELD_RECIPE_PATH			MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"WeldRecipe.txt"
#define DEFAULT_DINPUT_RECIPE_PATH			MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"InputRecipe.txt"
#define TIMER_INTERVAL_RECIPE_PATH			MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"TimerIntervalRecipe.txt"
#define TEST_RECIPE_PATH					MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"TestRecipe.txt"
#define IO_MANAGER_LOG_PATH					MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"IOManagerLog.txt"
#define LIFETIME_COUNTERS_PATH				MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"LifetimeCounters.txt"
#define RECIPE_ZERO_PATH					MMC_EMMC_DEV_NAME PATH_SEPARATOR 	"RecipeZero.txt"
#define DEFAULT_RTC_TIME					"1900/01/01 00:00:00"
//#define	ENABLE_HISTORY_FILE

#define STATUS_CODE					"\"StatusCode\""
#define DB_QUERY_FAIL				"DBQueryFailed"
#define NUMBEROF_WELDGRAPH_PARAMETERS		11
#define NUMBEROF_WELDHISTORY_PARAMETERS		28
#define NUMBEROF_WELDRESULTS_PARAMETERS		29
#define NUMBEROF_ALARMLOG_PARAMETERS		6
#define WELDRESULT_DATETIME_INDEX			2
#define WELDRESULT_USERNAME_INDEX			21
#define WELDRESULT_PARTID_INDEX				22
#define WELDRESULT_BATCHID_INDEX			23
#define PRIVATE_KEY_SIZE			 		32

typedef enum
{
	ALARMLOG_DATETIME,
	ALARMLOG_RECIPE_NUMBER,
	ALARMLOG_RECIPE_VER_NUM,
	ALARMLOG_ALARM_ID,
	ALARMLOG_USERNAME,
	ALARMLOG_CYCLECOUNTER,
}DB_ALARMLOG_INDEXES;

/* Enums for weld graph parameter values */
typedef enum
{
	TIME_VALUES = 0,
	FREQUENCY_VALUES,
	POWER_VALUES,
	CURRENT_VALUES,
	AMPLITUDE_VALUES,
	ENERGY_VALUES,
	PHASE_VALUES,
	FORCE_VALUES,
	VELOCITY_VALUES,
	ABSDISTANCE_VALUES,
	COLDISTANCE_VALUES	
}WELDGRAPH_PARAMETERS;

enum REPTYPE
{ 
	WELD_REP	= 1,	
	SCAN_REP
};

typedef struct DeleteReport
{
	UINT8 status;
	UINT8 reportID;	
} DeleteReport;

typedef enum
{
	HMI_NOT_LOGGED_IN	= 0,
	HMI_LOGGED_IN
}HMISTATUS;

typedef enum
{
	EVENT_LOG_SUCCESS = 0,
	EVENT_LOG_FAIL
}EVENTLOG_STATUS;

/* ENUM defined for different types of WELD that supported by system */
typedef enum 
{ 
	TIMEMODE			= 1,
	ENERGYMODE,
	PEAKPOWERMODE,
	GRDDETECTMODE,
	ABSMODE,
	COLLAPSEMODE,
	CONTINUOUS,
	MULTI,
	
	MAX_MODES
}WELDMODES;

typedef enum 
{
	STANDARD,
	STANDARD_PLUS
}HDMODES; 

/* ENUM defined for different types of FREQUENCY that supported by system */
typedef enum FREQUENCY
{
	FREQ_UNKNOWN = -1,
	FREQ_20KHZ = 20,
	FREQ_30KHZ = 30,
	FREQ_40KHZ = 40,
}FREQUENCY;

typedef	enum SYSTEMTYPE
{
	SYSTEM_ADVANCED 	= 0,
	SYSTEM_FIELDBUS, 	
	SYSTEM_ADVANCED_HD, 	
	SYSTEM_FIELDBUS_HD ,	
}SYSTEMTYPE;

/* ENUM defined for different types of alarm that supported by system */
typedef enum ALARMTYPE
{
	OVERLOAD 			= 1,
	CYCLE_MODIFIED,
	WARNING,
	PROCESS_SUSPECT,
	PROCESS_REJECT,			
	NOCYCLE,
	HARDWARE_FAILURE,
	NOCYCLE_OVERLOAD,
}ALARMTYPE;

/* ENUM defined for handling bar code error status */
typedef	enum 
{ 
	RECIPE_RECALL_FAIL	= 1, 
	BARCODE_DATA_OVERFLOW, 
	RECIPE_ID_BEYOND_RANGE, 
	INVALID_PART_ID
}BARCODE_ERROR_CODES;
/********************************* Result Structures - Begin ****************************/
typedef struct TestResult
{
	UINT32  TestTime;
	UINT16  TestPeakPower;
	UINT32  ResonantFreq;
	INT16   FrequencyChange;	
}TestResult;

typedef struct ScanResult
{
	UINT16 	SecondaryParallelFrequency;
	UINT32 	MainParallelFrequency;
	UINT32 	TertiaryParallelFrequency;
	UINT32 	FirstSeriesFrequency;
	UINT32 	SecondarySeriesFrequency;
	UINT32 	TertiarySeriesFrequency;
}ScanResult;
		
typedef struct SeekResult
{
	UINT32  RecipeNumber;
	UINT32  PeakPower;
	UINT32  StartFrequency;
	INT32  FrequencyChange;
	UINT32  EndFrequency;
} SeekResult, * pSeekSequenceResult;

typedef struct WeldResult
{
	UINT32	MaxWeldForce;
	UINT32  EndHoldForce;
	UINT32	WeldAbsolute;
	UINT32	TotalAbsolute;
	UINT32  CycleCounter;
	UINT32  RecipeNumber;
	UINT32  RecipeRevNumber;
	UINT32  WeldTime;
	UINT32  CycleTime;  
	UINT32  TotalEnergy;
	UINT32  PeakPower;
	UINT32  StartFrequency;
	INT32   FrequencyChange;
	UINT32  Velocity;
	UINT32  TriggerDistance;
	INT32   WeldCollapseDistance;
	INT32   HoldCollapseDistance;
	INT32   TotalCollapseDistance;
	UINT32	TriggerTime;
	UINT32	WeldSonicTime;
	UINT32	HoldTime;
	UINT32  WeldMode;
	UINT32  StackSerialNo;
	UINT8	WeldStatus;
	UINT8 	recipeStatus;
	bool 	bAlarmflag;	
	char	UserName[USER_NAME_SIZE];
	char 	PartID[BARCODE_DATA_SIZE];
} WeldResult, * pWeldResult;		
/********************************* Result Structures - End ****************************/

/**************************** Signature Structures - Begin ****************************/
typedef struct TestSignature
{
	float	Time;
	UINT32  Frequency;			
	UINT16  Amplitude;
	UINT16  Power;
	UINT16  Current;
	float  	Phase;	
}TestSignature;

typedef struct ScanSignature
{
	UINT16  Amplitude;
	UINT16  Current;
	float  	Phase;
	UINT32  Frequency;
}ScanSignature;

typedef struct SeekSignature
{
	UINT16  Amplitude;
	UINT16  Current;
	UINT16  Power;
	INT16  	Phase;
	float	Time;
	UINT32  Frequency;
}SeekSignature;

typedef struct WeldSignature
{
	UINT32	Time;
	UINT32  Frequency;
	UINT16  Power;
	UINT16  Current;
	UINT16  Amplitude;
	INT16 	Phase;
	INT32	Energy;
	INT32   Force;
	INT32   Velocity;
	INT32   AbsoluteDistance;
	INT32   CollapseDistance;
}WeldSignature;

/*********************** Object dictionary Structures - Begin ***********************/
typedef struct FirmwareVersionACPC
{
public :
	FirmwareVersionACPC()
	{	
		lastFwVer = 0;
		presentFwVer = 0;
	}
public:
	UINT8	Entries ;
	UINT32 lastFwVer;
	UINT32 presentFwVer;
	
}FirmwareVersionACPC;

typedef struct TimerInterval
{
	INT32 TmrIntervalPC;
}TimerInterval;

typedef struct PowerUpData					
{
	UINT32 Frequency;
	UINT32 Power;
	UINT32 SystemType;
	UINT32 CheckSum;
	UINT8  SerialNo;
}PowerUpData;

typedef struct FirmwareVersion
{
	UINT16 	FwMajor;
	UINT16 	FwMinor;
	UINT16 	FwBuild;
	UINT16	FwCrc;
	UINT32 	FwInfo;	
} FirmwareVersion, * pFirmwareVersion;

typedef struct FirmWareUpgradeInfo {
	UINT16 CRC_CheckSum;
	UINT8  Upgrade_Status;
	UINT8  Progress;
	
} FirmWareUpgradeInfo;

typedef struct FirmwarePartitionInfo {
	UINT32 bootMode;
	UINT32 fwUpgrade;
	UINT32 activePart;
	UINT32 passivePart;
} FirmwarePartitionInfo;

typedef struct FirmwarePartitionInfoCRC {
	volatile    UINT32	boot_status;
	volatile    UINT32	fw_upgrade;
	volatile    UINT32	partition_a_offset;
	volatile    UINT32	partition_b_offset;	 
	volatile    UINT32	partition_a_size;
	volatile    UINT32	partition_b_size;
	volatile    UINT16	partition_a_crc;
	volatile    UINT16	partition_b_crc;
	volatile    UINT16	emmc_copy;
} FirmwarePartitionInfoCRC;

typedef struct Message
{
	UINT32	msgID;
	char	Buffer[MAX_SIZE_OF_MSG_LENGTH - sizeof(msgID)];	
}Message;

typedef struct DataReadWrite_Message
{
	UINT32	msgID;
	MSG_Q_ID task_msgQID;   // the  Message queue iD of the task.
	char	Buffer[MAX_SIZE_OF_MSG_LENGTH - sizeof(msgID)-sizeof(task_msgQID)];	
}DataReadWrite_Message;

typedef struct Client_Message
{
	UINT32	msgID;
	UINT32  msgLen;
	UINT32	rspCode;
	char	Buffer[MAX_SIZE_OF_MSG_BUFF];
	UINT32  crc32;
}Client_Message;

typedef struct
{
    int msgID;
    std::string Buffer;
}ResponseMessage;

/************************** Interface Structures - End ***************************/

typedef struct CalibrationReadings
{
	UINT32  FirstReading;
	UINT32  SecondReading;
	UINT16 tm_sec;         /* seconds after the minute     - [0, 59] */
	UINT16 tm_min;         /* minutes after the hour       - [0, 59] */
	UINT16 tm_hour;        /* hours after midnight         - [0, 23] */
	UINT16 tm_mday;        /* day of the month             - [1, 31] */
	UINT16 tm_mon;         /* months since January         - [0, 11] */
	UINT16 tm_year;        /* years since 1900     */
	UINT16 tm_wday;        /* days since Sunday            - [0, 6] */
	UINT16 tm_yday;        /* days since January 1         - [0, 365] */
	UINT16 tm_isdst;       /* Daylight Saving Time flag */
}CalibrationReadings, * pCalibrationReadings;

typedef struct USBResponseMsg
{
	INT32	msgID;
	UINT32  msglen;
	char 	Buffer[READ_USB_RESP_MSG_BUFFER_MAX_SIZE];
}USBResponseMsg;

/* EtherCAT state */
typedef enum EC_MASTER_STATE
{
    ecat_UNKNOWN  = 0,                        /*< unknown */
    ecat_INIT     = 1,                        /*< init */
    ecat_PREOP    = 2,                        /*< pre-operational */
    ecat_SAFEOP   = 4,                        /*< safe operational */
    ecat_OP       = 8,                        /*< operational */
}EC_MASTER_STATE;

/********************** User I/O Interface Structures - Begin **********************/
typedef enum	
{
	ACTUATORINPUT_NOTUSED,
    PARTPRESENT,
	TOOLING_IN,
    HOMEPOSITION_IN,
    READY_POSITION_IN
} ActuatorInput;

typedef enum 
{
	PSINPUT_NOTUSED,
    CYCLEABORT,
    US_DISABLE,
    RESET,
    HOLD_DELAY,	
	CONFIRM_REJECT,
	HORN_SEEK_IN
} PowerSupplyInput;

typedef enum 
{
	ACTUATOROUTPUT_NOTUSED,
    HOMEPOSITION_OUT,
    READY_POSITION_OUT,
    PB_RELEASE,
    TOOLING_OUT,
	SOLENOID_VALVE,
	HOLD_ACTIVE
} ActuatorOutput;

typedef enum 
{
	PSOUTPUT_NOTUSED,
    READY,
    SONICS_ACTIVE,
    GENERAL_ALARM,
    CYCLE_RUNNING,
    CYCLE_OK,
	EXTERNAL_BEEPER,
	CUSTOM_ALARM,
    REJECTPART_ALARM,
    SUSPECTPART_ALARM,
	HORN_SEEK_OUT,
	WELD_ACTIVE,
	PSHOLD_ACTIVE
} PowerSupplyOutput;

typedef enum  
{ 
	ANALOGINPUT_NOTUSED,
    AMPLITUDE_SETTING, 
    FREQUENCY_OFFSET
}AnalogInput;

typedef enum   
{
	ANALOGOUTPUT_NOTUSED,
    POWER_OUT,
    FREQUENCY_OUT
} AnalogOutput;

typedef struct 
{
	PowerSupplyInput PS_EVENT;
	bool bStatus;
}PS_INPUT;

typedef struct 
{
	PowerSupplyOutput PS_EVENT;
	bool bStatus;
}PS_OUTPUT;

typedef struct 
{
	ActuatorInput AC_EVENT;
	bool bStatus;
}AC_INPUT;

typedef struct 
{
	ActuatorOutput AC_EVENT;
	bool bStatus;
}AC_OUTPUT;

typedef struct
{
	PS_INPUT 	J116_01;
	PS_INPUT 	J116_02;
	PS_INPUT 	J116_03;
	PS_INPUT 	J116_04;
	PS_INPUT 	J116_11;
	PS_INPUT 	J116_12;
	PS_INPUT 	J116_13;
	PS_INPUT 	J116_16;
	PS_INPUT 	J116_23; 
}PS_DIGITALINPUT;

typedef struct
{
	PS_OUTPUT 	J116_07;
	PS_OUTPUT 	J116_08;
	PS_OUTPUT 	J116_09;
	PS_OUTPUT 	J116_10;
	PS_OUTPUT 	J116_19;
	PS_OUTPUT 	J116_20;
	PS_OUTPUT 	J116_21;
	PS_OUTPUT 	J116_22;
}PS_DIGITALOUTPUT;

typedef struct
{
	AnalogInput		J116_17;
	AnalogInput		J116_18;
}PS_ANALOGINPUT;

typedef struct
{
	AnalogOutput	J116_24;
	AnalogOutput	J116_25;	 
}PS_ANALOGOUTPUT;

typedef struct
{
	AC_INPUT	 	J710_01;
	AC_INPUT 		J710_02;
	AC_INPUT 		J710_03;
	AC_INPUT 		J710_04;
	AC_INPUT 		J710_05;
}AC_DIGITALINPUT;

typedef struct
{
	AC_OUTPUT 		J710_09;
	AC_OUTPUT 		J710_10;
	AC_OUTPUT 		J710_11;
	AC_OUTPUT 		J710_12;
	AC_OUTPUT 		J710_13;
}AC_DIGITALOUTPUT;

typedef struct
{
	PS_DIGITALINPUT 	PsDigitalInput;
	PS_DIGITALOUTPUT 	PsDigitalOutput;
	PS_ANALOGINPUT		PsAnalogInput;
	PS_ANALOGOUTPUT		PsAnalogOutput;
}POWERSUPPLY_USERIO;

typedef struct 
{
	AC_DIGITALINPUT		ACDigitalInput;
	AC_DIGITALOUTPUT	ACDigitalOutput;
}ACTUATOR_USERIO;

typedef struct
{
	POWERSUPPLY_USERIO PS_USERIO;
	ACTUATOR_USERIO	   AC_USERIO;
}USERIO;
/*********************** User I/O Interface Structures - End ************************/
#pragma pack(1)
typedef struct 
{
	UINT32 			   WeldResultFlag;
	RTCtimerStr 	   SysTime;
	WeldResult	   	   Results;
}ShutdownCriticalData;
#pragma pack()
#endif /* COMMON_H_ */
