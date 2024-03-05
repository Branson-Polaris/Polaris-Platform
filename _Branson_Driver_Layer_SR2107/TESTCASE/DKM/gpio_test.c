#include "test_def.h"
#include <sysLib.h>
#include <subsys/gpio/vxbGpioLib.h>
#include <subsys/int/vxbIntLib.h>

INT32 gpio_isr_cnt = 0;

VOID gpio_test_isr(void *arg)
{
    gpio_isr_cnt++;
}

STATUS gpio_test(void)
{  
    INT32   dir;
    INT32   i;

    dir = vxbGpioGetDir(GPIO_PIN);
    printf("original direction: %s\n", (dir == GPIO_DIR_OUTPUT) ? "output" : "input");

    printf("trying to allocate pin 0x%x\n", GPIO_PIN);
    if(vxbGpioAlloc(GPIO_PIN) != OK)
    {
        printf("failed to allocate pin, try to free it first\n");
        if(vxbGpioFree(GPIO_PIN) != OK)
        {
            printf("failed to free pin\n");
            return ERROR;
        }

        if(vxbGpioAlloc(GPIO_PIN) != OK)
        {
            printf("failed to allocate pin again\n");
            return ERROR;
        }
    }

    if(dir == GPIO_DIR_OUTPUT)
    {
        printf("output value 1\n");
        if(vxbGpioSetValue(GPIO_PIN, GPIO_VALUE_HIGH) != OK)
        {
            printf("failed to output value\n");
            goto test_exit;
        }

        printf("switching to input direction\n");
        if(vxbGpioSetDir(GPIO_PIN, GPIO_DIR_INPUT) != OK)
        {
            printf("failed to switch to input direction\n");
            goto test_exit;
        }
        printf("read value: %d\n", vxbGpioGetValue(GPIO_PIN));
    }
    else if(dir == GPIO_DIR_INPUT)
    {
        printf("read value: %d\n", vxbGpioGetValue(GPIO_PIN));

        printf("switching to output direction\n");
        if(vxbGpioSetDir(GPIO_PIN, GPIO_DIR_OUTPUT) != OK)
        {
            printf("failed to switch to output direction\n");
            goto test_exit;
        }
        printf("output value 1\n");
        if(vxbGpioSetValue(GPIO_PIN, GPIO_VALUE_HIGH) != OK)
        {
            printf("failed to output value\n");
            goto test_exit;
        }
    }
    else
    {
        printf("unknown direction\n");
        goto test_exit;
    }

    printf("switching back to original direction: %s\n", (dir == GPIO_DIR_OUTPUT) ? "output" : "input");
    if(vxbGpioSetDir(GPIO_PIN, dir) != OK)
    {
        printf("failed to switch back to original direction\n");
        goto test_exit;
    }

    if(dir == GPIO_DIR_INPUT)
    {
        printf("set debounce for input pin\n");
        if(vxbGpioSetDebounce(GPIO_PIN, 150000) != OK)
        {
            printf("failed to set debounce for input pin\n");
            goto test_exit;
        }  	
        
        printf("configuring IRQ attribute for input pin\n");
        if(vxbGpioIntConfig(GPIO_PIN, GPIO_PIN_INTR_TRIG, GPIO_PIN_INTR_POL) != OK)
        {
            printf("failed to configure IRQ attribute for input pin\n");
            goto test_exit;
        }

        printf("connecting ISR for input pin\n");
        if(vxbGpioIntConnect(GPIO_PIN, gpio_test_isr, NULL) != OK)
        {
            printf("failed to connect ISR for input pin\n");
            goto test_exit;
        }

        printf("enabling ISR for input pin\n");
        if(vxbGpioIntEnable(GPIO_PIN, gpio_test_isr, NULL) != OK)
        {
            printf("failed to enable ISR for input pin\n");
            goto test_exit;
        }

        printf("waiting 10 seconds for ISR\n");
        for (i = 0; i < 10; i++)
        {
            taskDelay(sysClkRateGet() + 10);
            printf(" %d\n", i);
        }
        printf("\n");

        printf("%d times of GPIO IRQ triggered\n",gpio_isr_cnt);
    }

test_exit:
    printf("free pin\n");
    if(vxbGpioFree(GPIO_PIN) != OK)
    {
        printf("failed to free pin\n");
        return ERROR;
    }

    return OK;
}

