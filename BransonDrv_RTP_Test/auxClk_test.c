#include "test_def.h"
#include <taskLib.h>
#include <sysLib.h>


/*
 * APIs
 * 
 * extern INT32 AuxClkConnect(INT32 task_id);
 * extern void AuxClkEnable(void);
 * extern void AuxClkDisable(void);
 * extern INT32 AuxClkRateGet(void);
 * extern INT32 AuxClkRateSet(INT32 ticksPerSecond);
 */

extern TASK_ID auxTaskId;



STATUS auxClk_test(void)
{

	int status = 0;
	
	printf("\nAuxClk original Rate = %d\n",AuxClkRateGet());
	
	MsDelay(100);
	
	status = AuxClkRateSet(1);
	
	if(status == OK)
		printf("\nAuxClk set Rate = %d\n",AuxClkRateGet());
	else
		printf("\nAuxClk set Rate failed!\n");
	
	if(AuxClkConnect(auxTaskId) != OK)
	{
		printf("Failed to connect Aux ISR\n");
	}
	
	AuxClkEnable();
	
	MsDelay(1000);
	
	return OK;
}

