#include "test_def.h"
#include <taskLib.h>
#include <sysLib.h>



STATUS logger_test(void)
{  
	printf("\nlogger_test start\n");
	MsDelay(1000);
	printf("\nlogger_test LOGCRIT\n");
	LOGCRIT("\n\n This is LOGCRIT Test!\n",0,1,0);
	MsDelay(1000);
	LOGERR("\n\n This is LOGERR Test! %d\n",1,2,3);
	MsDelay(1000);
	LOGWARN("\n\n This is LOGWARN Test! %d %d\n",1,2,3);
	MsDelay(1000);
	LOGINFO("\n\n This is LOGDBG Test! %d %d %d\n",1,2,3);
	
	return OK;
}
