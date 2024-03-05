/*
 * gel.c
 *
 *  Created on: Jun 7, 2021
 *      Author: hjouini_3P13713
 */

#include "gel.h"
#include <pmapLib.h>
#ifndef _WRS_CONFIG_ARM_LPAE
#   include <arch/arm/mmuArmLib.h>
#else /* _WRS_CONFIG_ARM_LPAE */
#   include <arch/arm/mmuArmLpaeLib.h>
#endif /* !_WRS_CONFIG_ARM_LPAE */
#include <sysLib.h>
#include "cacheLib.h"
#include <taskLib.h>

#define MMU_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED)

#define L4_CFG_TARG                  0x4A000000
#define L4_CFG_TARG_SIZE             0x1000000
#define L3_INST                      0x54000000
#define L3_INST_SIZE                 0x800000
#define DSP1_MEM                     0x40800000
#define DSP1_MEM_SIZE                0x800000
#define L4_PER3_MEM                  0x48800000
#define L4_PER3_MEM_SIZE             0x800000

static UINT32      l4MemMap;
static UINT32      l3InstMemMap;
static UINT32      l4Per3MemMap;
static UINT32      dsp1MemMap;
void Gel_init()
{
    l4MemMap = (UINT32)pmapGlobalMap((PHYS_ADDR)L4_CFG_TARG, L4_CFG_TARG_SIZE, MMU_ATTR);
    l3InstMemMap = (UINT32)pmapGlobalMap((PHYS_ADDR)L3_INST, L3_INST_SIZE, MMU_ATTR);
    l4Per3MemMap = (UINT32)pmapGlobalMap((PHYS_ADDR)L4_PER3_MEM, L4_PER3_MEM_SIZE, MMU_ATTR);
    dsp1MemMap = (UINT32)pmapGlobalMap((PHYS_ADDR)DSP1_MEM, DSP1_MEM_SIZE, MMU_ATTR);
}
void Gel_deinit()
{
    pmapGlobalUnmap((void*)l4MemMap, L4_CFG_TARG_SIZE);
    pmapGlobalUnmap((void*)l3InstMemMap, L3_INST_SIZE);
    pmapGlobalUnmap((void*)l4Per3MemMap, L4_PER3_MEM_SIZE);
    pmapGlobalUnmap((void*)dsp1MemMap, DSP1_MEM_SIZE);
}
void Gel_flushDspMem()
{
    cacheFlush(DATA_CACHE, (void*)dsp1MemMap, 64);
}
void Gel_sysWrite32(UINT32 addr, UINT32 data)
{
    if(L4_CFG_TARG <= addr && addr < (L4_CFG_TARG + L4_CFG_TARG_SIZE))
    {
        *(UINT32*)(l4MemMap + (addr - L4_CFG_TARG)) = data;
    }
    else if(L3_INST <= addr && addr < (L3_INST + L3_INST_SIZE))
    {
        *(UINT32*)(l3InstMemMap + (addr - L3_INST)) = data;
    }
    else if(DSP1_MEM <= addr && addr < (DSP1_MEM + DSP1_MEM_SIZE))
    {
        *(UINT32*)(dsp1MemMap + (addr - DSP1_MEM)) = data;
    }
    else if(L4_PER3_MEM <= addr && addr < (L4_PER3_MEM + L4_PER3_MEM_SIZE))
    {
        *(UINT32*)(l4Per3MemMap + (addr - L4_PER3_MEM)) = data;
    }
    else
    {
        printf("ERROR: mySysWrite32 - address range not supported %.8X\n", addr);
    }
}
UINT32 Gel_sysRead32(UINT32 addr)
{
    UINT32 result = 0;
    if(L4_CFG_TARG <= addr && addr < (L4_CFG_TARG + L4_CFG_TARG_SIZE))
    {
        result = *(UINT32*)(l4MemMap + (addr - L4_CFG_TARG));
    }
    else if(L3_INST <= addr && addr < (L3_INST + L3_INST_SIZE))
    {
        result = *(UINT32*)(l3InstMemMap + (addr - L3_INST));
    }
    else if(DSP1_MEM <= addr && addr < (DSP1_MEM + DSP1_MEM_SIZE))
    {
        result = *(UINT32*)(dsp1MemMap + (addr - DSP1_MEM));
    }
    else if(L4_PER3_MEM <= addr && addr < (L4_PER3_MEM + L4_PER3_MEM_SIZE))
    {
        result = *(UINT32*)(l4Per3MemMap + (addr - L4_PER3_MEM));
    }
    else
    {
        printf("ERROR: mySysRead32 - address range not supported %.8X\n", addr);
    }
    return result;
}
void Gel_usDelay(uint32_t delay)
{
    taskDelay((int)((delay)* sysClkRateGet()) / 1000000);
}
