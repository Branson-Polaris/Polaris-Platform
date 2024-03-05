#include "test_def.h"
#include <ctype.h>

typedef struct tagTEST_CASE {
    char        *name;
    FUNCPTR     func;
    int         level;
} TEST_CASE;

LOCAL TEST_CASE test_func_list[] = {
    {"EDMA test",           edma_test,      0},
    {"USB test",            usb_test,       0},
    {"MMC1/SD test",        mmc1_sd_test,   0},
    {"I2C EEPROM test",     eeprom_test,    0},
    {"I2C RTC test",        rtc_test,       0},
    {"McSPI2 test",         spi2_test,      0},
    {"McSPI4 test",         spi4_test,      0},
    {"QSPI/Flash test",     qspi_test,      0},
    {"GPIO test",           gpio_test,      0},
    {"MMC2/eMMC test",      mmc2_emmc_test, 0},
    {NULL,                  NULL,           0}
};

int run_test_task_cnt = 0;
int run_test_task_err = 0;
void run_test_task(void *arg)
{
    TEST_CASE   *p = (TEST_CASE *)arg;

    printf("############# DKM: run_test_task: starting to run %s...#############\n", p->name);
    if (OK == p->func())
    {
        printf("+++++++++  DKM: run_test_task: succeeded to run %s\n", p->name);
    }
    else
    {
        printf("--------- DKM: run_test_task: failed to run %s\n", p->name);
        run_test_task_err = 1;
    }

    run_test_task_cnt++;
}

STATUS run_test(char *name, int parallel)
    {
    TEST_CASE   *p;
    FUNCPTR     func;
    int         task_cnt = 0;

    if(name == NULL)
    {
        run_test_task_cnt = 0;
        run_test_task_err = 0;
        printf("============== DKM: run_test: starting to run all test cases...==============\n");
        for(p = (TEST_CASE*)test_func_list; p->name != NULL; p++)
        {
            if(p->func == NULL)
            {
                continue;
            }

            if(parallel != 0)
            {
                if(taskSpawn (p->name, 51, 0, 0x50000,
                    (FUNCPTR)run_test_task, (_Vx_usr_arg_t)p, 0, 0, 0, 0, 0, 0, 0, 0, 0) == TASK_ID_ERROR)
                {
                    printf("DKM: run_test: failed to create task for %s\n", p->name);
                }
                else
                {
                    task_cnt++;
                    taskDelay(1);
                }
            }
            else
            {
                printf("############# DKM: run_test: starting to run %s...#############\n", p->name);
                func = p->func;
                if (OK == func())
                {
                    printf("+++++++++ DKM: run_test: succeeded to run %s\n", p->name);
                }
                else
                {
                    printf("---------DKM: run_test: failed to run %s\n", p->name);
                }
            }
        }

        while(run_test_task_cnt < task_cnt)
        {
            taskDelay(1);
        }

        if(run_test_task_err != 0)
        {
            printf("============== DKM: run_test: finished to run all test cases with error==============\n");
        }
        else
        {
            printf("============== DKM: run_test: finished to run all test cases==============\n");
        }

        return OK;
    }
    else
    {
        for(p = (TEST_CASE*)test_func_list; p->name != NULL; p++)
        {
            if (strcmp(name, p->name) == 0)
            {
                if(p->func == NULL)
                {
                    continue;
                }

                printf("############# DKM: run_test: starting to run %s...#############\n", p->name);
                func = p->func;
                if (OK == func())
                {
                    printf("+++++++++DKM: run_test: succeeded to run %s\n", p->name);
                }
                else
                {
                    printf("---------DKM: run_test: failed to run %s\n", p->name);
                }
                return OK;
            }
        }
    }
    printf("no matched test case for %s\n", name);
    return ERROR;
}

void start_test(void)
{
    taskSpawn ((char *)"start_test", 51, 0, 0x50000,
        (FUNCPTR)run_test, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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

