/* includes */

#include <ctype.h>
#include "test_def.h"
#include <taskLib.h>

typedef struct tagTEST_CASE {
    char    *name;
    FUNCPTR func;
    UINT8   level;
} TEST_CASE;

LOCAL STATUS timestamp_test(void);
LOCAL STATUS run_test(char *name);

LOCAL TEST_CASE test_func_list[] = {
    {"TimeStamp/MsDelay test",  timestamp_test, 0},
    {"I2C RTC test",            rtc_test,       0},
    {"McSPI test",              spi_test,       0}, 
    {"QSPI FLASH test",         qspi_test,      0},
	{"Aux Clk test",            auxClk_test,    0},
    {"GPIO test",               gpio_test,      0},
	{"Log Function test",       logger_test,    0},
    {NULL,                      NULL,           0}
};

TASK_ID auxTaskId, gpioTaskId;

INT32 Aux_isr_cnt = 0, gpio_isr_cnt = 0;

void TimerEventSc_Handler(void)
{
	_Vx_event_t event = 0;
	while(TRUE)
	{
		if(eventReceive(VXEV01, EVENTS_WAIT_ANY, WAIT_FOREVER, &event) != OK)
		{
            printf("failed to obtain aux ISR event\n");
            perror("AUX ISR event");
		}
		else
		{
			Aux_isr_cnt++;
			printf("\nAux isr Triggered: %d\n\n",Aux_isr_cnt);
		}
		
		AuxClkEnable();
	}
}



//vmTranslate(NULL, isr, &physAddr);

void GpioEventSc_Handler (void)
{
    _Vx_event_t event = 0;
    while(TRUE)
    {
        
        if(eventReceive(VXEV05, EVENTS_WAIT_ANY, WAIT_FOREVER, &event) != OK)
        {
            printf("failed to obtain GPIO ISR event\n");
            perror("GPIO ISR event");
        }
        else
        {
        	gpio_isr_cnt++;
            printf("GPIO ISR event received: %d\n", gpio_isr_cnt);
        }
        printf("waiting for GPIO ISR event...\n");
    }
}


int main 
	(
    int	   argc,	/* number of arguments */
    char * argv[]	/* array of arguments */
    ) 
	{
    EST_LIFE emmc_est_life = {0};

    if(EmmcExtCsdDecode(&emmc_est_life) == SUCCESS)
    {
        printf("EmmcExtCsdDecode: LifeTimeEstA = 0x%x LifeTimeEstB = 0x%x PreEOLInfo = 0x%x\n", 
            emmc_est_life.LifeTimeEstA, emmc_est_life.LifeTimeEstB, emmc_est_life.PreEOLInfo);
    }
    else
    {
        printf("EmmcExtCsdDecode: failed\n");
    }

	auxTaskId = taskOpen("/TimerEventSc", 100, 0, OM_CREATE, NULL, 0x1000, 0, (FUNCPTR)TimerEventSc_Handler,0,0,0,0,0,0,0,0,0,0);	
//	auxTaskId = taskSpawn ("tAuxTest", 51, 0, 0x50000, (FUNCPTR)auxTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	if(auxTaskId == TASK_ID_ERROR)
		printf("Failed to create task for TimerEventSc\n");
	else
		printf("/TimerEventSc = %x\n",auxTaskId);
	
	gpioTaskId = taskOpen("/GpioEventSc", 100, 0, OM_CREATE, NULL, 0x1000, NULL, (FUNCPTR)GpioEventSc_Handler, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    
	if(gpioTaskId == NULL)
    {
        perror("gpio_test taskOpen");
    }
    else
    {
        printf("GPIO taskId (RTP): 0x%x\n", gpioTaskId);
    }    
    
    
    (void)run_test(NULL);
//	(void)run_test("Log Function test");
	
    printf("\n\n Now Waiting for GPIO INT & AUX INT Trigger\n");
    while(TRUE)
    {
    	MsDelay(1000);
    	printf("*\n");
    }
    return 0;
	}

LOCAL STATUS run_test(char *name)
    {
    TEST_CASE   *p;
    FUNCPTR     func;
    int         i;

    if(name == NULL)
    {
        printf("\n==============starting to run all test cases...==============\n");
        for (i = 0; i <= 255; i++)
        {
            for (p = (TEST_CASE*)test_func_list; p->name != NULL; p++)
            {
                if (p->level == i)
                {
                    printf("\n#############starting to run %s...#############\n", p->name);
                    func = p->func;
                    if (OK == func())
                    {
                        printf("\n+++++++++succeeded to run %s\n", p->name);
                    }
                    else
                    {
                        printf("\n---------failed to run %s\n", p->name);
                    }
                }
            }
            printf("\n==============finished to run all test cases==============\n");
            return OK;
        }
    }
    else
    {
        for (p = (TEST_CASE*)test_func_list; p->name != NULL; p++)
        {
            if (strcmp(name, p->name) == 0)
            {
                printf("#############starting to run %s...#############\n", p->name);
                func = p->func;
                if (OK == func())
                {
                    printf("+++++++++succeeded to run %s\n", p->name);
                }
                else
                {
                    printf("---------failed to run %s\n", p->name);
                }
                return OK;
                }
            }
    }
    printf("no matched test case for %s\n", name);
    return ERROR;
}

/*
 * APIs
 * 
 * extern void MsDelay(INT32 delayTime);
 * extern float TimeStamp(); 
*/

LOCAL STATUS timestamp_test(void)
{
    int     i;
    float   time1;
    float   time2;

    time1 = (float)TimeStamp() / 1000;
    printf ("time1: %f\n", time1);
    printf ("delay 10 seconds\n");
    for (i = 0; i < 10; i++)
    {
        MsDelay(1000);
        printf(" %d", i);
    }
    printf("\n");
    time2 = (float)TimeStamp() / 1000;
    printf ("time2: %f\n", time2);
    if((time2 - time1) < 10.0)
    {
        printf("wrong timestamp or delay\n");
        return ERROR;
    }
    return OK;
}

void test_buf_dump(UINT8 *buf, UINT32 len)
{
    UINT32  i;
    UINT32  j;
    int     retLen;
    int     unalign;

    unalign = len & 0xF;
    retLen  = len - unalign;
    for(i = 0; i < retLen; i += 16)
    {
        printf("    %03u:", i);
        for(j = 0; j < 16; j++)
        {
            printf(" %02x", buf[i + j]);
        }
        printf("    | ");
        for(j = 0; j < 16; j++)
        {
            if(isprint(buf[i + j]))
            {
                printf("%c", buf[i + j]);
            }
            else
            {
                printf(".");
            }
        }
        printf(" |\n");
    }

    if(unalign == 0)
    {
        return;
    }

    printf("    %03u:", i);
    for(j = 0; j < unalign; j++)
    {
        printf(" %02x", buf[i + j]);
    }
    for(j = unalign; j < 16; j++)
    {
        printf("   ");
    }
    printf("    | ");
    for(j = 0; j < unalign; j++)
    {
        if(isprint(buf[i + j]))
        {
            printf("%c", buf[i + j]);
        }
        else
        {
            printf(".");
        }
    }
    for(j = unalign; j < 16; j++)
    {
        printf(".");
    }

    printf(" |\n");
}
