/* usrRtpAppInit.c - RTP Application Launch and Initialization Configlette */

/* Copyright 1984-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,07may04,yvp  Moved rtpLaunchFromList() rtplaunch.c.
01c,26apr04,yvp  Check return value from rtpSpawn() - SPR 94883.
01b,31mar04,yvp  Fixed compiler warnings.
01a,26feb04,yvp  written
*/

/*
DESCRIPTION
User-defined code to launch RTP applications after system boot.
*/ 
#include "vxworks.h"
#include "loadInvokeModule.h"
#include "loggerModule.h"

/******************************************************************************
*
* usrRtpAppInit - initialize the users RTP applications.
*/ 

void usrRtpAppInit (void)
{
/* TODO - add your own application launch code here */

	/* Below is an example to load a DKM if needed in the future*/
	/* Loads and starts DKM application */
	
	//	printf("\n***Kernel application loading start!***\n");
	//	if (ERROR == loadApplicationModule(KERNEL))
	//		printf("Kernel application loading error!\n");
	//	
	//	taskDelay(sysClkRateGet()*120);
			
	/* Loads and starts RTP application */
	printf("\n***User application loading start!***\n");
	if (ERROR == loadApplicationModule(USER))
		printf("User application loading error!\n");

}

