/*
 * Lock.c
 *
 *  Created on: 30.05.2021
 *      Author: hjouini_3P13713
 */
#include <stdint.h>
#include "MemMap.h"
#if defined (_TMS320C6X)
#include <ti/csl/csl_spinlock.h>
#endif
#if defined (_WRS_KERNEL)
#include "spinlock.h"
#else if defined  (__VXWORKS__)
#include "spinlock.h"
#include  <sdLib.h>
#include <errno.h>
#endif

#define SPINLOCK_MEM       (0x4a0f6000U)
#define SPINLOCK_MEM_SIZE  (0x880U)

static uint32_t spinLockBaseaddr = 0;
void Icl_init()
{
#if defined (_WRS_KERNEL)
    spinLockBaseaddr = (uint32_t)MEM_MAP(SPINLOCK_MEM, SPINLOCK_MEM_SIZE);
#else if defined  (__VXWORKS__)
    SD_ID sd;
    char memName[32];
    snprintf(memName, 32, "/ComData_%x", SPINLOCK_MEM);
    uint32_t err = 0;
    /* Create the R/W shared buffer */
    if ((sd = sdOpen(memName, 0, OM_CREATE, SPINLOCK_MEM_SIZE, SPINLOCK_MEM, SD_ATTR_RW | SD_CACHE_OFF, (void **)&spinLockBaseaddr)) == SD_ID_NULL)
    {
        err = errno;
        printf("MEM_MAP failed. 0x%x\n", err);
    }
#endif
#if defined  (_TMS320C6X)
    SPINLOCKModuleReset(spinLockBaseaddr);
#endif
}
void Icl_deinit(void)
{
    if(spinLockBaseaddr != 0)
    {
#if defined (_WRS_KERNEL)
    	MEM_UNMAP((void*)spinLockBaseaddr, SPINLOCK_MEM_SIZE);
#endif
        spinLockBaseaddr = 0;
    }
}
void Icl_lock(uint32_t lock)
{
    uint32_t status = 1;
    if(spinLockBaseaddr != 0)
    {
        while(status != 0)
        {
            status = SPINLOCKLockStatusSet(spinLockBaseaddr, lock);
        }
    }
}
void Icl_unlock(uint32_t lock)
{
    if(spinLockBaseaddr != 0)
    {
        SPINLOCKLockStatusFree(spinLockBaseaddr, lock);
    }
}
