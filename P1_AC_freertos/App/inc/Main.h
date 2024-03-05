/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

Module name: Main

Filename:    Mainr.h

--------------------------- TECHNICAL NOTES -------------------------------

 * Main.h
 *
 *  Created on: Apr 23, 2021
 *      Author: E1356301
*/

#ifndef INC_MAIN_H_
#define INC_MAIN_H_
#include "global.h"
#include "../../../_Branson_User_Common/Commons/Commons.h"



#define PRNT_DBG							0
#define SPLIT_RECV							0
#define USE_TIMER0							0

#define LINK_READY							1
#define LINK_CONNECTED						2

#if PRNT_DBG

#define RECV_BUFFER_SIZE					40

#endif


extern TxPDO_AC txpdoac;
extern RxPDO_AC rxpdoac;
extern BOOL SocketCommStatus;

#endif /* INC_MAIN_H_ */
