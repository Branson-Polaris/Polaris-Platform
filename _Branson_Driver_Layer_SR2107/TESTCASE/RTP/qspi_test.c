#include "test_def.h"
#include <taskLib.h>
#include <stdlib.h>

/*
 * APIs
 * 
 * extern void QSPIFlashErase(uint32_t offset, uint32_t length);
 * extern STATUS QSPIFlashWrite(uint32_t offset, uint32_t length, unsigned int src);
 * extern STATUS QSPIFlashRead(uint32_t offset, uint32_t length, unsigned int dest);
 */

STATUS qspi_test(void)
{  
    int     i;
    UINT8   *wrData = NULL;
    UINT8   *rdData = NULL;
    UINT8   *origData = NULL;
    int     fail = 0;
    
    printf("offset: 0x%x size: 0x%x\n", QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE);
    wrData = (UINT8 *)calloc(1, 3 * QSPI_FLASH_DATA_SIZE);
    if(wrData == NULL)
    {
        printf("failed to allocate memory\n");
        return ERROR;
    }
    rdData      = wrData + QSPI_FLASH_DATA_SIZE;
    origData    = rdData + QSPI_FLASH_DATA_SIZE;

    printf("reading and saving original data...\n");
    if(!QSPIFlashRead(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE, (unsigned int)origData))
    {
        printf("failed to read original data\n");
        return ERROR;
    }

    printf("erasing blocks...\n");
    QSPIFlashErase(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE);

    for (i = 0; i < QSPI_FLASH_DATA_SIZE; i++)
    {
        wrData[i] = 'A' + (i % 26);
    }
    printf("writing data...\n");
    if(!QSPIFlashWrite(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE, (unsigned int)wrData))
    {
        printf("failed to write data\n");
        return ERROR;
    }
    taskDelay(20);
    printf("reading data...\n");
    if(!QSPIFlashRead(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE, (unsigned int)rdData))
    {
        printf("failed to read data\n");
        return ERROR;
    }

    printf("checking data...\n");
    for (i = 0; i < QSPI_FLASH_DATA_SIZE; i++)
    {
        if (wrData[i] != rdData[i])
        {
            printf("error @ %d\n", i);
            fail = 1;
        }
    }

    printf("erasing blocks...\n");
    QSPIFlashErase(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE);

    printf("restoring original data...\n");
    if(!QSPIFlashWrite(QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE, (unsigned int)origData))
    {
        printf("failed to write original data back\n");
        return ERROR;
    }

    if(fail == 0)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

