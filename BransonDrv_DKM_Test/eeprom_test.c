#include "test_def.h"
#include <ioLib.h>

/*******************************************************************************
 * eepromIoRead - read EEPROM
 *
 * The function reads 'length' bytes into 'pRdBuf' from 'devName', starting from 'startAddr'.
 *
 * RETURN - OK or ERROR
 *
 * ERRNO - NA
 */

LOCAL ssize_t eepromIoRead(char *devName, UINT32 startAddr, UINT32 length, void *pRdBuf)
{
    int fd = 0;
    ssize_t ret = ERROR;
    UINT32 curAddr = 0;
    UINT32 curAddr2 = 0;

    /* open the EEPROM */

    if ((fd = open(devName, O_RDONLY, 0)) == ERROR)
    {
        perror("open");
        return (ERROR);
    }

    /* redirection */

    if (ioctl(fd, FIOSEEK, startAddr) == ERROR)
    {
        perror("FIOSEEK\n");
        goto Exit;
    }

    /*get current position before read*/

    curAddr = ioctl(fd, FIOWHERE, 0);
    printf("location before read: 0x%x\n", curAddr);

    /* read the data */

    if ((ret = read(fd, pRdBuf, length)) == ERROR)
    {
        perror("read");
        goto Exit;
    }

    curAddr2 = ioctl(fd, FIOWHERE, 0);
    printf("location after read: 0x%x\n", curAddr2);
    ret = OK;

Exit:
    (void) close(fd);
    return (ret);
}

/*******************************************************************************
 * eepromIoWrite - write EEPROM
 *
 * The function writes 'length' bytes, saved in 'pWrBuf', into 'devName', starting from 'startAddr'.
 *
 * RETURN - OK or ERROR
 *
 * ERRNO - NA
 */

LOCAL ssize_t eepromIoWrite(char *devName, UINT32 startAddr, UINT32 length, void *pWrBuf)
{
    int fd = 0;
    ssize_t ret = ERROR;
    UINT32 curAddr = 0;
    UINT32 curAddr2 = 0;

    /* open the EEPROM */

    if ((fd = open(devName, O_WRONLY, 0)) == ERROR)
    {
        perror("open");
        return (ERROR);
    }

    /* redirection */

    if (ioctl(fd, FIOSEEK, startAddr) == ERROR)
    {
        perror("FIOSEEK");
        goto Exit;
    }

    curAddr = ioctl(fd, FIOWHERE, 0);
    printf("location before write: 0x%x\n", curAddr);

    /* write data */

    if ((ret = write(fd, pWrBuf, length)) == ERROR)
    {
        perror("write");
        goto Exit;
    }

    /*get current position after write*/

    curAddr2 = ioctl(fd, FIOWHERE, 0);
    printf("location after write: 0x%x\n", curAddr2);
    ret = OK;

Exit:
    (void) close(fd);
    return (ret);
}

STATUS eeprom_test(void )
{
    int     i;
    UINT8   *wrData = NULL;
    UINT8   *rdData = NULL;
    UINT8   *origData = NULL;
    int     fail = 0;

    printf("device name: %s\n", EEPROM_DEV_NAME);
    printf("data size: %d\n", EEPROM_DATA_SIZE);
    wrData = (UINT8 *)calloc(1, 3 * EEPROM_DATA_SIZE);
    if(wrData == NULL)
    {
        printf("failed to allocate memory\n");
        return ERROR;
    }
    rdData      = wrData + EEPROM_DATA_SIZE;
    origData    = rdData + EEPROM_DATA_SIZE;

    printf("reading and saving original data...\n");
    if(eepromIoRead(EEPROM_DEV_NAME, EEPROM_DATA_START_ADDR, EEPROM_DATA_SIZE, (void *)origData) != OK)
    {
        printf("failed to read original data\n");
        return ERROR;
    }
    printf("original data:\n");
    test_buf_dump(origData, EEPROM_DATA_SIZE);

    for (i = 0; i < EEPROM_DATA_SIZE; i++)
    {
        wrData[i] = 'A' + (i % 26);
    }
    printf("writing data...\n");
    test_buf_dump(wrData, EEPROM_DATA_SIZE);
    if(eepromIoWrite(EEPROM_DEV_NAME, EEPROM_DATA_START_ADDR, EEPROM_DATA_SIZE, (void *)wrData) != OK)
    {
        printf("failed to write data\n");
        return ERROR;
    }
    taskDelay(20);
    printf("reading data...\n");
    if(eepromIoRead(EEPROM_DEV_NAME, EEPROM_DATA_START_ADDR, EEPROM_DATA_SIZE, (void *)rdData) != OK)
    {
        printf("failed to read data\n");
        return ERROR;
    }
    test_buf_dump(rdData, EEPROM_DATA_SIZE);
    printf("checking data...\n");
    for (i = 0; i < EEPROM_DATA_SIZE; i++)
    {
        if (wrData[i] != rdData[i])
        {
            printf("error @ %d\n", i);
            fail = 1;
        }
    }
    printf("restoring original data...\n");
    if(eepromIoWrite(EEPROM_DEV_NAME, EEPROM_DATA_START_ADDR, EEPROM_DATA_SIZE, (void *)origData))
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

