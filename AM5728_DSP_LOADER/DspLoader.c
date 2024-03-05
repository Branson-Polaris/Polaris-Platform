/*
 * dsp.c
 *
 *  Created on: May 18, 2021
 *      Author: hjouini_3P13713
 */
#include "vxWorks.h"
#include <taskLib.h>
#include "cacheLib.h"
#include "elf.h"
#include "AM572x_init/gel.h"
#include <pmapLib.h>
#ifndef _WRS_CONFIG_ARM_LPAE
#   include <arch/arm/mmuArmLib.h>
#else /* _WRS_CONFIG_ARM_LPAE */
#   include <arch/arm/mmuArmLpaeLib.h>
#endif /* !_WRS_CONFIG_ARM_LPAE */
#include <private/vxCpuLibP.h>
#include <sysLib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Com.h"
#include <subsys/gpio/vxbGpioLib.h>

#define MMU_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED)


#define DSP1_MEM                     0x40800000
#define DSP1_MEM_SIZE                0x800000

#define DSP1_FIRMWARE_MEM            0xB0000000
#define DSP1_FIRMWARE_SIZE           0x2000000

#define OCMC_RAM2                    0x40400000

#define DATA_SHM  OCMC_RAM2

void DspLoader_init()
{
    Gel_init();
}
void DspLoader_deinit()
{
    Gel_deinit();
}

void DspLoader_startCore()
{
    ComConfig 	config;
    UINT32   	entryPoint;
    UINT32 		comObjsize = Com_getShmSize();
    
    UINT32 dsp1Firmware = (UINT32)pmapGlobalMap((PHYS_ADDR)DSP1_FIRMWARE_MEM, DSP1_FIRMWARE_SIZE, MMU_ATTR);
    UINT32 dspSharedMemory = (UINT32)pmapGlobalMap((PHYS_ADDR)DATA_SHM, comObjsize, MMU_ATTR);
    config.ShmBaseAddress = dspSharedMemory;
    
    Com_init(&config);
    
    //Setting dsp up
    AM572x_PRCM_Clock_Config_OPPNOM();        
    AM572x_PRCM_Module_AllEnable_Config();
    entryPoint = rproc_elf32_load_segments((ulong)dsp1Firmware, DSP1_FIRMWARE_SIZE);
    AM572x_MULTICORE_EnableAllCores(entryPoint);
    
    bool success = Com_armWaitForDsp(5000);
    if(success)
    {
        printf("DSP started successfully\n");
    }
    else
    {
        printf("ERROR: DSP not started within 5 seconds. Failed\n");
    }
    if(dsp1Firmware != 0)
    {
        pmapGlobalUnmap((void*)dsp1Firmware, DSP1_FIRMWARE_SIZE);
    }
    if(dspSharedMemory != 0)
    {
        pmapGlobalUnmap((void*)dspSharedMemory, comObjsize);
    }
    Com_deinit();
#if(0)    
    DspRealTimeData dspData;
    printf("Enter readerTask\n");

    
    while(1)
    {
        Com_delayUs(1000000);
        //Com_sendCommand(command, 8);
        bool result = Com_dspDataRead(&dspData);
        if(result)
        {
            DspRealTimeDataDetailed* dspDataDetailed = (DspRealTimeDataDetailed*)&dspData.Entries;
            printf("DSP Data Entries: %d, %d, %d, %d, %d, %d, %d\n", 
                    dspDataDetailed->Entry0, 
                    dspDataDetailed->Entry1, 
                    dspDataDetailed->Entry2, 
                    dspDataDetailed->Entry3, 
                    dspDataDetailed->Entry4, 
                    dspDataDetailed->Entry5, 
                    dspDataDetailed->Entry6);
            
        }
        else
        {
            printf("ERROR: DSP data invalid. \n");
        }
    }
#endif
}


