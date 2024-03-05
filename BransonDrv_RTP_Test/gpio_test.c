#include "test_def.h"
#include <taskLib.h>
#include <sysLib.h>

/*
 * APIs
 * 
 * extern INT32 GpioAlloc(UINT32 id);
 * extern UINT32 GpioGetValue(UINT32 id);
 * extern INT32 GpioSetValue(UINT32 id, UINT32 value);
 * extern INT32 GpioSetDir(UINT32 id, UINT32 value);
 * extern INT32 GpioSetDebounce(UINT32 id, UINT32 value);
 * extern INT32 GpioGetDir(UINT32 id);
 * extern INT32 GpioFree(UINT32 id);
 * extern INT32 GpioIntConnect(UINT32 id, VOIDFUNCPTR pIsr, void *pArg );
 * extern INT32 GpioIntEnable(UINT32 id, VOIDFUNCPTR pIsr, void *pArg );        
 * extern INT32 GpioIntConfig(UINT32 id, INTR_TRIGER trig, INTR_POLARITY pol );
 */


STATUS gpio_test(void)
{  
    INT32   dir;
  
    dir = GpioGetDir(GPIO_PIN);
    printf("original direction: %s\n", (dir == GPIO_DIR_OUTPUT) ? "output" : "input");

    printf("trying to allocate pin 0x%x\n", GPIO_PIN);
    if(GpioAlloc(GPIO_PIN) != OK)
    {
        printf("failed to allocate pin, try to free it first\n");
        if(GpioFree(GPIO_PIN) != OK)
        {
            printf("failed to free pin\n");
            return ERROR;
        }

        if(GpioAlloc(GPIO_PIN) != OK)
        {
            printf("failed to allocate pin again\n");
            return ERROR;
        }
    }

//    if(dir == GPIO_DIR_OUTPUT)
//    {
//        printf("output value 1\n");
//        if(GpioSetValue(GPIO_PIN, GPIO_VALUE_HIGH) != OK)
//        {
//            printf("failed to output value\n");
//            goto test_exit;
//        }
//
//        printf("switching to input direction\n");
//        if(GpioSetDir(GPIO_PIN, GPIO_DIR_INPUT) != OK)
//        {
//            printf("failed to switch to input direction\n");
//            goto test_exit;
//        }
//        printf("read value: %d\n", GpioGetValue(GPIO_PIN));
//    }
//    else if(dir == GPIO_DIR_INPUT)
//    {
//        printf("read value: %d\n", GpioGetValue(GPIO_PIN));
//
//        printf("switching to output direction\n");
//        if(GpioSetDir(GPIO_PIN, GPIO_DIR_OUTPUT) != OK)
//        {
//            printf("failed to switch to output direction\n");
//            goto test_exit;
//        }
//        printf("output value 1\n");
//        if(GpioSetValue(GPIO_PIN, GPIO_VALUE_HIGH) != OK)
//        {
//            printf("failed to output value\n");
//            goto test_exit;
//        }
//    }
//    else
//    {
//        printf("unknown direction\n");
//        goto test_exit;
//    }

    printf("switching back to original direction: %s\n", (dir == GPIO_DIR_OUTPUT) ? "output" : "input");
    if(GpioSetDir(GPIO_PIN, dir) != OK)
    {
        printf("failed to switch back to original direction\n");
        goto test_exit;
    }

    if(dir == GPIO_DIR_INPUT)
    {
        printf("set debounce for input pin\n");
        if(GpioSetDebounce(GPIO_PIN, 150000) != OK)
        {
            printf("failed to set debounce for input pin\n");
            goto test_exit;
        }  	
        
        printf("configuring IRQ attribute for input pin\n");
        if(GpioIntConfig(GPIO_PIN, GPIO_PIN_INTR_TRIG, GPIO_PIN_INTR_POL) != OK)
        {
            printf("failed to configure IRQ attribute for input pin\n");
            goto test_exit;
        }

        printf("connecting ISR for input pin\n");
        if(GpioIntConnect(GPIO_PIN, NULL, NULL) != OK)
        {
            printf("failed to connect ISR for input pin\n");
            goto test_exit;
        }

        printf("enabling ISR for input pin\n");
        if(GpioIntEnable(GPIO_PIN, NULL, NULL) != OK)
        {
            printf("failed to enable ISR for input pin\n");
            goto test_exit;
        }
        printf("waiting for GPIO ISR event...\n");
//        printf("waiting 10 seconds for ISR\n");
//        for (i = 0; i < 10; i++)
//        {
//            taskDelay(sysClkRateGet() + 10);
//            printf(" %d\n", i);
//        }
        printf("\n");

    }

test_exit:
    printf("free pin\n");
    if(GpioFree(GPIO_PIN) != OK)
    {
        printf("failed to free pin\n");
        return ERROR;
    }

    return OK;
}

