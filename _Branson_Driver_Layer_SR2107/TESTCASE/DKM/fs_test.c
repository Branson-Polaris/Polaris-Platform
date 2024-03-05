#include "test_def.h"

STATUS fs_test (char *name, int size)
    {
    FILE    *fd;
    char    *wrData;
    char    *rdData;
    int     i;
    int     fail = 0;

    printf("file name: %s file size: 0x%x\n", name, size);
    wrData = (char *)calloc(1, size * 2);
    if(wrData == NULL)
    {
        printf ("failed to allocate data buffers\n");
        return ERROR;
    }
    rdData = wrData + size;

    if((fd = fopen(name, "w")) == NULL)
    {
        printf ("failed to open file\n");
        free(wrData);
        return ERROR;
    }
    printf("fd: %p\n", fd);

    for (i = 0; i < size; i++)
    {
        wrData[i] = 'A' + (i % 26);
    }

    printf("writing data to file...\n");
    if (fwrite(wrData, 1, size, fd) != size)
    {
        printf("failed to write data\n");
        free(wrData);
        fclose(fd);
        return ERROR;
    }
    fclose (fd);

    if((fd = fopen (name, "r")) == NULL)
    {
        printf ("failed to open file\n");
        free(wrData);
        return ERROR;
    }

    printf("reading data from file...\n");
    if (fread(rdData, 1, size, fd) != size)
    {
        printf("failed to read data\n");
        free(wrData);
        fclose(fd);
        return ERROR;
    }
    fclose (fd);

    printf("checking data...\n");
    for (i = 0; i < size; i++)
    {
        if (wrData[i] != rdData[i])
        {
            printf("error @ %d\n", i);
            fail = 1;
        }
    }

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

STATUS usb_test(void)
{
    char    name[256];
    int     len = snprintf(name, 256, "%s/usb_test.txt", USB_DISK_DEV_NAME);

    name[len] = 0;
    return fs_test(name, USB_DISK_FILE_SIZE);
}

STATUS mmc1_sd_test(void)
{
    char    name[256];
    int     len = snprintf(name, 256, "%s/sd_test.txt", MMC1_SD_DEV_NAME);

    name[len] = 0;
    return fs_test(name, MMC1_SD_FILE_SIZE);
}

STATUS mmc2_emmc_test(void)
{
    char    name[256];
    int     len = snprintf(name, 256, "%s/emmc_test.txt", MMC2_EMMC_DEV_NAME);

    name[len] = 0;
    return fs_test(name, MMC2_EMMC_FILE_SIZE);
}

