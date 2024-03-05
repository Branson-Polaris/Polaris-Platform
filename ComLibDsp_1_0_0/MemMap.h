/*
 * MemMap.h
 *
 *  Created on: 01.06.2021
 *      Author: hjouini_3P13713
 */

#ifndef MEMMAP_H_
#define MEMMAP_H_


#if defined (_TMS320C6X)
#define MEM_MAP(x,l) (x)
#define MEM_UNMAP(x,l)
#endif
#if defined  (__VXWORKS__)
#if defined (_WRS_KERNEL)
#include "vxWorks.h"
#include <sysLib.h>
#include <pmapLib.h>
#ifndef _WRS_CONFIG_ARM_LPAE
#   include <arch/arm/mmuArmLib.h>
#else /* _WRS_CONFIG_ARM_LPAE */
#   include <arch/arm/mmuArmLpaeLib.h>
#endif /* !_WRS_CONFIG_ARM_LPAE */
#define MMU_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED)
#define MEM_MAP(x,l) pmapGlobalMap((PHYS_ADDR)(x), (l), MMU_ATTR);
#define MEM_UNMAP(x,l) pmapGlobalUnmap((x), (l));
#else
#endif

#endif


#endif /* MEMMAP_H_ */
