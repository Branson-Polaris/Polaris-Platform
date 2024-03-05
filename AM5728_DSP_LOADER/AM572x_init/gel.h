#ifndef GEL_H
#define GEL_H
#include <stdint.h>
#include <stdio.h>
#define hotmenu void
#define GEL_TextOut printf

void Gel_init();
void Gel_deinit();
void Gel_sysWrite32(UINT32 addr, UINT32 data);
UINT32 Gel_sysRead32(UINT32 addr);
void Gel_usDelay(uint32_t delay);
void Gel_flushDspMem();

#define WR_MEM_32(addr, data)   Gel_sysWrite32(addr, data)
#define RD_MEM_32(addr)         Gel_sysRead32(addr)

void AM572x_PRCM_Module_AllEnable_Config();
void AM572x_PRCM_Clock_Config_OPPNOM();
void AM572x_DDR3_532MHz_Config();
void AM572x_MULTICORE_EnableAllCores();
void AM572x_show_device_info();
void dpll_ddr_config(uint32_t DDR_FREQ);

#endif
