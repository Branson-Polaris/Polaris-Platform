/* vxbMcSpiLib.c - vxBus McSpi function interfaces file */


/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semLib.h>
#include <vxFdtLib.h>
#include <hwif/vxBus.h>
#include <vxbMcSpiLib.h>
#include <hwif/buslib/vxbSpiLib.h>
#include <hwif/buslib/vxbFdtLib.h>

/* locals */
#if 0
LOCAL struct vxbMcSpiHandle mcspiHandle;

/*****************************************************************************
*
* mcspiRegister - register McSpi set/get routine to VxBus mcspi subsystem.
*
* This function register McSpi routine to VxBus interrupt subsystem.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void mcspiRegister
    (
    VXB_DEV_ID pDev,
    VXB_MC_SPI_FUNC * mcspi,
    char    name[32]
    )
    {
    kprintf("\t\t\t%s\n",__FUNCTION__);
    
    char    * channel0  = "mcspi0";
    char    * channel1  = "mcspi1";
    char    * channel2  = "mcspi2";
    char    * channel3  = "mcspi3";
    char    * channel4  = "mcspi4";
    
    int       strLen    = strlen(name);
    
    if(strncmp(name, channel0, strLen) == 0)
    {
        kprintf("name %s Channel0 %s\n",name,channel0);
        mcspiHandle.pInst0 = pDev;
    }
    
    if(strncmp(name, channel1, strLen) == 0)
    {
        kprintf("name %s Channel1 %s\n",name,channel1);
        mcspiHandle.pInst1 = pDev;
    }
    
    if(strncmp(name, channel2, strLen) == 0)
    {
        kprintf("name %s Channel2 %s\n",name,channel2);
        mcspiHandle.pInst2 = pDev;
    }
    
    if(strncmp(name, channel3, strLen) == 0)
    {
        kprintf("name %s Channel3 %s\n",name,channel3);
        mcspiHandle.pInst3 = pDev;
    }
    
    if(strncmp(name, channel4, strLen) == 0)
    {
        kprintf("name %s Channel4 %s\n",name,channel4);
        mcspiHandle.pInst4 = pDev;
    }
    
    
    
    kprintf("\t\t\t%s\n",__FUNCTION__);
    mcspiHandle.pMcSpiFunc = mcspi;
    kprintf("\t\t\t%s\n",__FUNCTION__);
    }
#else

#define VXB_MSCPI_MAX_CHANNEL 	4

LOCAL int       vxbMcSpiCtrlDevOffset[VXB_MSCPI_MAX_CHANNEL] = {0};
LOCAL SEM_ID    vxbMcSpiCtrlDevSem[VXB_MSCPI_MAX_CHANNEL] = {SEM_ID_NULL};

VXB_DEV_ID vxbMcSpiCtrlFind(int channel)
{
    char 	    *path = NULL;
    VXB_DEV_ID  dev = NULL;

    if(vxbMcSpiCtrlDevOffset[channel] == 0)
    {
        switch(channel + 1)
        {
            case 1:
                path = "/soc/mcspi1@48098000";
                break;
            case 2:
                path = "/soc/mcspi2@4809A000";
                break;
            case 4:
                path = "/soc/mcspi4@480BA000";
                break;
            default:
                return NULL;
        }

        vxbMcSpiCtrlDevOffset[channel] = vxFdtPathOffset(path);
        if(vxbMcSpiCtrlDevOffset[channel] <= 0)
        {
            vxbMcSpiCtrlDevOffset[channel] = 0;
            return NULL;
        }

        vxbMcSpiCtrlDevSem[channel] =
            semMCreate (SEM_Q_PRIORITY | SEM_INVERSION_SAFE | SEM_DELETE_SAFE);
        if(vxbMcSpiCtrlDevSem[channel] == SEM_ID_NULL)
        {
            return NULL;
        }
    }

    if(semTake(vxbMcSpiCtrlDevSem[channel], WAIT_FOREVER) != OK)
    {
        return NULL;
    }
    dev = vxbFdtDevAcquireByOffset(vxbMcSpiCtrlDevOffset[channel]);
    if(dev == NULL)
    {
        (void)semGive(vxbMcSpiCtrlDevSem[channel]);
        return NULL;
    }
    else
    {
        return dev;
    }
}
#endif
/*******************************************************************************
*
* vxbMcSpiTrans - Spi Transfer Function
*
* This routine is used to perform one transmission. It is the interface which
* can be called by SPI device driver to send and receive data via the SPI
* controller.
*
* RETURNS: OK, or ERROR.
*
* ERRNO: N/A
*/

STATUS vxbMcSpiTrans
    (
        SPI_HARDWARE *  devInfo,        /* device info */
        SPI_TRANSFER *  pPkg,            /* transfer data info */
        int				channel
    )
    {
#if 0
    if (channel == 0)
        {
        if (mcspiHandle.pInst0 == NULL)
            return ERROR;
    
        return mcspiHandle.pMcSpiFunc->mcspiTrans(mcspiHandle.pInst0, devInfo, pPkg);
        }
    else if (channel == 1)
    {
    if (mcspiHandle.pInst1 == NULL)
        return ERROR;

    return mcspiHandle.pMcSpiFunc->mcspiTrans(mcspiHandle.pInst1, devInfo, pPkg);
    }
    else 	if (channel == 2)
    {
    if (mcspiHandle.pInst2 == NULL)
        return ERROR;

    return mcspiHandle.pMcSpiFunc->mcspiTrans(mcspiHandle.pInst2, devInfo, pPkg);
    }
    else 	if (channel == 3)
    {
    if (mcspiHandle.pInst3 == NULL)
        return ERROR;

    return mcspiHandle.pMcSpiFunc->mcspiTrans(mcspiHandle.pInst3, devInfo, pPkg);
    }
    else 	if (channel == 4)
    {
    if (mcspiHandle.pInst4 == NULL)
        return ERROR;

    return mcspiHandle.pMcSpiFunc->mcspiTrans(mcspiHandle.pInst4, devInfo, pPkg);
    }
#else
    VXB_DEV_ID 	pDev = vxbMcSpiCtrlFind(channel - 1);
    STATUS 		ret;

    if(pDev == NULL)
    {
        return ERROR;
    }

    ret = VXB_SPI_XFER(pDev, devInfo, pPkg);
    (void)vxbDevRelease(pDev);
    (void)semGive(vxbMcSpiCtrlDevSem[channel - 1]);
    return ret;
#endif
    return OK;
    }
