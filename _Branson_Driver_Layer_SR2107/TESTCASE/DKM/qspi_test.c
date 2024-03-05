#include "test_def.h"
#include <vxbSp25QspiFlash.h>

STATUS qspi_test(void)
{  
    S25FL_Handle        flashHandle;
    S25FL_Transaction   flashTransaction;
    UINT32              blkAddr;
    UINT8               *wrData = NULL;
    UINT8               *rdData = NULL;
    UINT8               *origData = NULL;
    int                 i;
    int                 fail = 0;

    printf("offset: 0x%x size: 0x%x\n", QSPI_FLASH_DATA_OFFSET, QSPI_FLASH_DATA_SIZE);
    wrData = (UINT8 *)calloc(1, 3 * QSPI_FLASH_DATA_SIZE);
    if(wrData == NULL)
    {
        printf("failed to allocate memory\n");
        return ERROR;
    }
    rdData      = wrData + QSPI_FLASH_DATA_SIZE;
    origData    = rdData + QSPI_FLASH_DATA_SIZE;

    flashHandle = vxbQspiLibSF25FLOpen();
    printf("flashHandle: %p\n", flashHandle);

    flashTransaction.address    = QSPI_FLASH_DATA_OFFSET;
    flashTransaction.dataSize   = QSPI_FLASH_DATA_SIZE;

    printf("reading and saving original data...\n");
    flashTransaction.data = (void *)origData;
    if(!vxbQspiLibSF25FLBufferRead(flashHandle, &flashTransaction))
    {
        printf("failed to read original data\n");
        vxbQspiLibSF25FLClose(flashHandle);
        free(wrData);
        return ERROR;
    }

    printf("erasing blocks...\n");
    blkAddr = QSPI_FLASH_DATA_OFFSET / QSPI_FLASH_DATA_BLK_SIZE;
    for(i = 0; i < QSPI_FLASH_DATA_BLK_CNT; i++)
    {
        if(!vxbQspiLibS25FLFlashBlockErase(flashHandle, blkAddr + i))
        {
            printf("failed to erase block %d\n", blkAddr + i);
            vxbQspiLibSF25FLClose(flashHandle);
            free(wrData);
            return ERROR;
        }
    }

    printf("writing data...\n");
    flashTransaction.data = (void *)wrData;
    for (i = 0; i < QSPI_FLASH_DATA_SIZE; i++)
    {
        wrData[i] = 'A' + (i % 26);
    }
    if(!vxbQspiLibSF25FLBufferWrite(flashHandle, &flashTransaction))
    {
        printf("failed to write data\n");
        vxbQspiLibSF25FLClose(flashHandle);
        free(wrData);
        return ERROR;
    }
    taskDelay(20);


    printf("reading data...\n");
    flashTransaction.data = (void *)rdData;
    if(!vxbQspiLibSF25FLBufferRead(flashHandle, &flashTransaction))
    {
        printf("failed to read data\n");
        vxbQspiLibSF25FLClose(flashHandle);
        free(wrData);
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
    for(i = 0; i < QSPI_FLASH_DATA_BLK_CNT; i++)
    {
        if(!vxbQspiLibS25FLFlashBlockErase(flashHandle, blkAddr + i))
        {
            printf("failed to erase block %d\n", blkAddr + i);
            vxbQspiLibSF25FLClose(flashHandle);
            free(wrData);
            return ERROR;
        }
    }

    printf("restoring original data...\n");
    flashTransaction.data = (void *)origData;
    if(!vxbQspiLibSF25FLBufferWrite(flashHandle, &flashTransaction))
    {
        printf("failed to write original data back\n");
        vxbQspiLibSF25FLClose(flashHandle);
        free(wrData);
        return ERROR;
    }

    vxbQspiLibSF25FLClose(flashHandle);
    free(wrData);
    if(fail == 0)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

