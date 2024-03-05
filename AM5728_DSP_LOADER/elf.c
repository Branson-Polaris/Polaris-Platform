/*
 * elf.c
 *
 *  Created on: May 7, 2021
 *      Author: hjouini_3P13713
 */
#include "vxWorks.h"
#include "elf.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pmapLib.h>
#include <sysLib.h>
#ifndef _WRS_CONFIG_ARM_LPAE
#   include <arch/arm/mmuArmLib.h>
#else /* _WRS_CONFIG_ARM_LPAE */
#   include <arch/arm/mmuArmLpaeLib.h>
#endif /* !_WRS_CONFIG_ARM_LPAE */
#include "cacheLib.h"

#define MMU_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED)

int rproc_elf32_sanity_check(ulong addr, ulong size)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)addr;
    char class;

    if (!IS_ELF(*ehdr)) {
        printf("## No elf image at address 0x%08lx\n", addr);
        return -EINVAL;
    }

    class = ehdr->e_ident[EI_CLASS];
    if (class != ELFCLASS32) {
        printf("Unsupported ELF class: %d\n", class);
        return -EINVAL;
    }

    /* We assume the firmware has the same endianness as the host */
# ifdef __LITTLE_ENDIAN
    if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB) {
# else /* BIG ENDIAN */
    if (ehdr->e_ident[EI_DATA] != ELFDATA2MSB) {
# endif
        printf("Unsupported firmware endianness\n");
        return -EINVAL;
    }

    if (size < ehdr->e_shoff + sizeof(Elf32_Shdr)) {
        printf("Image is too small\n");
        return -EINVAL;
    }

    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG)) {
        printf("Image is corrupted (bad magic)\n");
        return -EINVAL;
    }

    if (ehdr->e_phnum == 0) {
        printf("No loadable segments\n");
        return -EINVAL;
    }

    if (ehdr->e_phoff > size) {
        printf("Firmware size is too small\n");
        return -EINVAL;
    }

    return 0;
}

UINT32 rproc_elf32_load_segments(ulong addr, ulong size)
{
    UINT32 da, memsz, filesz, offset;
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    UINT32 ret = 0;
    int i = 0;
    void *ptr;

    printf("%s: addr = 0x%lx size = 0x%lx\n", __func__, addr, size);

    if (rproc_elf32_sanity_check(addr, size))
        return -EINVAL;

    ehdr = (Elf32_Ehdr *)addr;
    phdr = (Elf32_Phdr *)(addr + ehdr->e_phoff);
    ret = ehdr->e_entry;
    /* go through the available ELF segments */
    for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
        da = phdr->p_paddr;
        memsz = phdr->p_memsz;
        filesz = phdr->p_filesz;
        offset = phdr->p_offset;

        if (phdr->p_type != PT_LOAD)
            continue;


        if (filesz > memsz) {
            printf("bad phdr filesz 0x%x memsz 0x%x\n",
                filesz, memsz);
            ret = -EINVAL;
            break;
        }

        if (offset + filesz > size) {
            printf("truncated fw: need 0x%x avail 0x%lx\n",
                offset + filesz, size);
            ret = -EINVAL;
            break;
        }

        /* get the cpu address for this device address */
        
        if (!ptr) {
            printf("bad phdr da 0x%x mem 0x%x\n", da, memsz);
            ret = -EINVAL;
            break;
        }
        if (filesz)
        {
            UINT32 mapSize = ((filesz / PAGE_SIZE) + 1) * PAGE_SIZE;
            ptr = pmapGlobalMap((PHYS_ADDR)da, mapSize, MMU_ATTR);
            memcpy(ptr, (void *)addr + offset, filesz);
            STATUS status = cacheFlush(DATA_CACHE, ptr, mapSize);
            if(status != 0)
            {
                printf("cache flush failed %d\n", status);
            }
            pmapGlobalUnmap(ptr, mapSize);
        }
        if (filesz != memsz)
        {
            UINT32 mapSize = (((memsz - filesz) / PAGE_SIZE) + 1) * PAGE_SIZE;
            ptr = pmapGlobalMap((PHYS_ADDR)da, mapSize, MMU_ATTR);
            memset(ptr + filesz, 0x00, memsz - filesz);
            STATUS status = cacheFlush(DATA_CACHE, ptr, mapSize);
            if(status != 0)
            {
                printf("cache flush failed %d\n", status);
            }
            pmapGlobalUnmap(ptr, mapSize);
            
        }
        
    }

    return ret;
}

