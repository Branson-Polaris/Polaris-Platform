/*******************************************************************/
/* This GEL file is loaded on the command line of Code Composer    */
/* The StartUp() function is called every time you start           */
/* Code Composer.  You can customize this function to              */
/* initialize wait states or to perform other initialization.      */
/*                                                                 */
/* AM572x multicore reset config                                   */
/* Revision history                                                */
/* ================================================================*/
/* Version   Date      Change from previous version                */
/* ================================================================*/
/* 0.2       20160314  Add Mapping TIMER suspend sources to        */
/*                     default cores                               */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
#include "gel.h"

#define DEBUG_PRINT            1

/*******************************************************************************
        AM572x Registers Map Defines: CortexA15_CPU1 view
*******************************************************************************/
#define GPMC_TARG                    0x00000000
#define MPU_RAM                      0x402F0000
#define OCMC_RAM1_TARG               0x40300000
#define OCMC_RAM2_TARG               0x40400000
#define OCMC_RAM3_TARG               0x40500000
#define DSP1_L2_SRAM_TARG            0x40800000
#define DSP1_SYSTEM_TARG             0x40D00000
#define DSP1_MMU0CFG_TARG            0x40D01000
#define DSP1_MMU1CFG_TARG            0x40D02000
#define DSP1_FW0CFG_TARG             0x40D03000
#define DSP1_FW1CFG_TARG             0x40D04000
#define DSP1_EDMA_TC0_TARG           0x40D05000
#define DSP1_EDMA_TC1_TARG           0x40D06000
#define DSP1_NoC_TARG                0x40D07000
#define DSP1_EDMA_CC_TARG            0x40D10000
#define DSP1_L1P_SRAM_TARG           0x40E00000
#define DSP1_L1D_SRAM_TARG           0x40F00000
#define DSP2_L2_SRAM_TARG            0x41000000
#define DSP2_SYSTEM_TARG             0x41500000
#define DSP2_MMU0CFG_TARG            0x41501000
#define DSP2_MMU1CFG_TARG            0x41502000
#define DSP2_FW0CFG_TARG             0x41503000
#define DSP2_FW1CFG_TARG             0x41504000
#define DSP2_EDMA_TC0_TARG           0x41505000
#define DSP2_EDMA_TC1_TARG           0x41506000
#define DSP2_NoC_TARG                0x41507000
#define DSP2_EDMA_CC_TARG            0x41510000
#define DSP2_L1P_SRAM_TARG           0x41600000
#define DSP2_L1D_SRAM_TARG           0x41700000
#define OCMC_RAM1_CBUF_TARG          0x41800000
#define EDMA_TPCC_TARG               0x43300000
#define EDMA_TC0_TARG                0x43400000
#define EDMA_TC1_TARG                0x43500000
#define OCMC_ROM_TARG                0x43A00000
#define SN_L3_MAIN_TARG              0x44000000
#define McASP1_TARG                  0x45800000
#define McASP2_TARG                  0x45C00000
#define McASP3_TARG                  0x46000000
#define L4_PER1_TARG                 0x48000000
#define MPU_MA                       0x482AF000
#define L4_PER2_TARG                 0x48400000
#define L4_PER3_TARG                 0x48800000
#define OCMC_RAM2_CBUF_TARG          0x49000000
#define OCMC_RAM3_CBUF_TARG          0x49800000
#define L4_CFG_TARG                  0x4A000000
#define L4_WKUP_TARG                 0x4AE00000
#define QSPI_ADDRSP0_TARG            0x4B300000
#define EMIF1_CONF_REGS              0x4C000000
#define EMIF2_CONF_REGS              0x4D000000
#define DMM_CONF_REGS_TARG           0x4E000000
#define GPMC_CONF_REGS_TARG          0x50000000
#define IPU2_TARGET_TARG             0x55000000
#define GPU_TARG                     0x56000000
#define DSS_TARG                     0x58000000
#define IPU1_TARGET_TARG             0x58800000
#define BB2D_TARG                    0x59000000
#define IVA_CONFIG_TARG              0x5A000000
#define IVA_SL2IF_TARG               0x5B000000
#define QSPI_ADDRSP1_TARG            0x5C000000
#define TILER                        0x60000000
#define EMIF1_SDRAM_CS0              0x80000000
#define EMIF2_SDRAM_CS0              0xC0000000

/*******************************************************************************
        L4_CFG Registers Map Defines: CortexA15_CPU1 view
*******************************************************************************/
#define CTRL_MODULE_CORE             (L4_CFG_TARG + 0x2000)
#define CM_CORE_AON                  (L4_CFG_TARG + 0x5000)
#define CM_CORE                      (L4_CFG_TARG + 0x8000)

/*******************************************************************************
        L4_WKUP Registers Map Defines: CortexA15_CPU1 view
*******************************************************************************/
#define PRM                          (L4_WKUP_TARG + 0x6000)

/*******************************************************************************
        PRCM Registers Map Defines: CortexA15_CPU1 view
*******************************************************************************/
#define IPU_CM_CORE_AON              (CM_CORE_AON + 0x500)
#define DSP1_CM_CORE_AON             (CM_CORE_AON + 0x400)
#define DSP2_CM_CORE_AON             (CM_CORE_AON + 0x600)
#define CORE_CM_CORE                 (CM_CORE + 0x700)
#define IVA_CM_CORE                  (CM_CORE + 0xF00)
#define DSP1_PRM                     (PRM + 0x400)
#define IPU_PRM                      (PRM + 0x500)
#define CORE_PRM                     (PRM + 0x700)
#define IVA_PRM                      (PRM + 0xF00)
#define DSP2_PRM                     (PRM + 0x1B00)

/*******************************************************************************
        IPU1 Address Map defines: CortexA15_CPU1 view
*******************************************************************************/
#define RM_IPU1_RSTCTRL              (IPU_PRM + 0x10)
#define RM_IPU1_RSTST                (IPU_PRM + 0x14)
#define CM_IPU1_CLKSTCTRL            (IPU_CM_CORE_AON + 0x0)
#define CM_IPU1_IPU1_CLKCTRL         (IPU_CM_CORE_AON + 0x20)

#define IPU1_BASE_ADDR               (IPU1_TARGET_TARG + 0x20000)
#define IPU1_MMU_CFG                 (IPU1_TARGET_TARG + 0x80000)

/*******************************************************************************
        IPU2 Address Map defines: CortexA15_CPU1 view
*******************************************************************************/
#define RM_IPU2_RSTCTRL              (CORE_PRM + 0x210)
#define RM_IPU2_RSTST                (CORE_PRM + 0x214)
#define CM_IPU2_CLKSTCTRL            (CORE_CM_CORE + 0x200)
#define CM_IPU2_IPU2_CLKCTRL         (CORE_CM_CORE + 0x220)

#define IPU2_BASE_ADDR               (IPU2_TARGET_TARG + 0x20000)
#define IPU2_MMU_CFG                 (IPU2_TARGET_TARG + 0x80000)

/*******************************************************************************
            IPU CPU Independent defines
*******************************************************************************/
#define RM_IPU_RSTCTRL               ((cpu_num == 1) ? (RM_IPU1_RSTCTRL) : (RM_IPU2_RSTCTRL))
#define RM_IPU_RSTST                 ((cpu_num == 1) ? (RM_IPU1_RSTST) : (RM_IPU2_RSTST))

#define IPU_BASE_ADDR                ((cpu_num == 1) ? (IPU1_BASE_ADDR) : (IPU2_BASE_ADDR))
#define IPU_MMU_CFG                  ((cpu_num == 1) ? (IPU1_MMU_CFG) : (IPU2_MMU_CFG))

/*******************************************************************************
        DSPSS1 Address Map defines: CortexA15_CPU1 view
*******************************************************************************/
#define CM_DSP1_CLKSTCTRL            (DSP1_CM_CORE_AON + 0x0)
#define CM_DSP1_DSP1_CLKCTRL         (DSP1_CM_CORE_AON + 0x20)
#define RM_DSP1_RSTCTRL              (DSP1_PRM + 0x10)
#define RM_DSP1_RSTST                (DSP1_PRM + 0x14)

#define DSPSS1BOOTADDR               (CTRL_MODULE_CORE + 0x55C)
#define DSPSS1BOOTADDRVALUE          (DSP1_L2_SRAM_TARG - 0x40000000)

/*******************************************************************************
        DSPSS2 Address Map defines: CortexA15_CPU1 view
*******************************************************************************/
#define CM_DSP2_CLKSTCTRL            (DSP2_CM_CORE_AON + 0x0)
#define CM_DSP2_DSP2_CLKCTRL         (DSP2_CM_CORE_AON + 0x20)
#define RM_DSP2_RSTCTRL              (DSP2_PRM + 0x10)
#define RM_DSP2_RSTST                (DSP2_PRM + 0x14)

#define DSPSS2BOOTADDR               (CTRL_MODULE_CORE + 0x560)
#define DSPSS2BOOTADDRVALUE          (DSP2_L2_SRAM_TARG - 0x40800000)

/*******************************************************************************
            DSPSS CPU Independent defines
*******************************************************************************/
#define CM_DSP_CLKSTCTRL             ((cpu_num == 1) ? (CM_DSP1_CLKSTCTRL) : (CM_DSP2_CLKSTCTRL))
#define CM_DSP_DSP_CLKCTRL           ((cpu_num == 1) ? (CM_DSP1_DSP1_CLKCTRL) : (CM_DSP2_DSP2_CLKCTRL))
#define RM_DSP_RSTCTRL               ((cpu_num == 1) ? (RM_DSP1_RSTCTRL) : (RM_DSP2_RSTCTRL))
#define RM_DSP_RSTST                 ((cpu_num == 1) ? (RM_DSP1_RSTST) : (RM_DSP2_RSTST))

#define DSPSSBOOTADDR                ((cpu_num == 1) ? (DSPSS1BOOTADDR) : (DSPSS2BOOTADDR))
#define DSPSSBOOTADDRVALUE           ((cpu_num == 1) ? (DSPSS1BOOTADDRVALUE) : (DSPSS2BOOTADDRVALUE))

#define DSP_L2_SRAM_TARG             ((cpu_num == 1) ? (DSP1_L2_SRAM_TARG) : (DSP2_L2_SRAM_TARG))

/*******************************************************************************
        IVASS Address Map defines: CortexA15_CPU1 view
*******************************************************************************/
#define CM_IVA_CLKSTCTRL             (IVA_CM_CORE + 0x0)
#define CM_IVA_IVA_CLKCTRL           (IVA_CM_CORE + 0x20)
#define CM_IVA_SL2_CLKCTRL           (IVA_CM_CORE + 0x28)
#define RM_IVA_RSTCTRL               (IVA_PRM + 0x10)
#define RM_IVA_RSTST                 (IVA_PRM + 0x14)

#define ICONT1_ITCM                  (IVA_CONFIG_TARG + 0x08000)
#define ICONT2_ITCM                  (IVA_CONFIG_TARG + 0x18000)

#define L3_CLK_EN (0x4A008E28)

#define DRM_SUSPEND_CTRL                         0x54160200
#define DRM_SUSPEND_CTRL_TIMER1                  (DRM_SUSPEND_CTRL + 0x00000040)
#define DRM_SUSPEND_CTRL_TIMER2                  (DRM_SUSPEND_CTRL + 0x00000044)
#define DRM_SUSPEND_CTRL_TIMER3                  (DRM_SUSPEND_CTRL + 0x00000048)
#define DRM_SUSPEND_CTRL_TIMER4                  (DRM_SUSPEND_CTRL + 0x0000004C)
#define DRM_SUSPEND_CTRL_TIMER5                  (DRM_SUSPEND_CTRL + 0x00000014)
#define DRM_SUSPEND_CTRL_TIMER6                  (DRM_SUSPEND_CTRL + 0x00000018)
#define DRM_SUSPEND_CTRL_TIMER7                  (DRM_SUSPEND_CTRL + 0x0000001C)
#define DRM_SUSPEND_CTRL_TIMER8                  (DRM_SUSPEND_CTRL + 0x00000020)
#define DRM_SUSPEND_CTRL_TIMER9                  (DRM_SUSPEND_CTRL + 0x00000050)
#define DRM_SUSPEND_CTRL_TIMER10                 (DRM_SUSPEND_CTRL + 0x00000054)
#define DRM_SUSPEND_CTRL_TIMER11                 (DRM_SUSPEND_CTRL + 0x00000058)
#define DRM_SUSPEND_CTRL_TIMER12                 (DRM_SUSPEND_CTRL + 0x0000005C)
#define DRM_SUSPEND_CTRL_TIMER13                 (DRM_SUSPEND_CTRL + 0x00000028)
#define DRM_SUSPEND_CTRL_TIMER14                 (DRM_SUSPEND_CTRL + 0x00000030)
#define DRM_SUSPEND_CTRL_TIMER15                 (DRM_SUSPEND_CTRL + 0x00000060)
#define DRM_SUSPEND_CTRL_TIMER16                 (DRM_SUSPEND_CTRL + 0x00000074)

#define DRM_SUSPEND_SRC_DSP1    (0x0)
#define DRM_SUSPEND_SRC_IVA1    (0x1)
#define DRM_SUSPEND_SRC_IVA2    (0x2)
#define DRM_SUSPEND_SRC_IPU1_C0 (0x3)
#define DRM_SUSPEND_SRC_IPU1_C1 (0x4)
#define DRM_SUSPEND_SRC_MPU_C0  (0x5)
#define DRM_SUSPEND_SRC_MPU_C1  (0x6)
#define DRM_SUSPEND_SRC_DSP2    (0x7)

void PRUSS_1_2_ClkEnable();

/************ Enable the IPU1 Clocks ***************/
void IPU1SSClkEnable_API();

/************ Enable the IPU2 Clocks ***************/
void IPU2SSClkEnable_API();

/************ Enable the DSP1 Clocks ***************/
void DSP1SSClkEnable_API(uint32_t entryPoint);

/************ Enable the DSP2 Clocks ***************/
void DSP2SSClkEnable_API(uint32_t entryPoint);

/************ Enable the IVA Clocks ***************/
void IVAHDSSClkEnable_API();
//menuitem "AM572x MULTICORE Initialization"
void IPUSSClkEnable(uint32_t cpu_num);
void DSPSSClkEnable(uint32_t cpu_num, uint32_t entryPoint);
void IVAHDSSClkEnable();
/************ Enable all slave cores ***************/
void AM572x_MULTICORE_EnableAllCores(uint32_t entryPoint)
{

    GEL_TextOut("--->>> Mapping TIMER suspend sources to default cores <<<<<<----\n");

    /*   --------------------------------------------
     *  | Target       | Default availMask           |
     *   --------------------------------------------
     *  | A15          | 0x0202 (GPTimer 2 & 10)     |
     *  | DSP          | 0x0030 (GPTimer 5 & 6)      |
     *  | IPU(Dual-M4) | 0x050C (GPTimer 3,4,9 & 11) |
     *   --------------------------------------------
     */
    //WR_MEM_32(DRM_SUSPEND_CTRL_TIMER2,  (DRM_SUSPEND_SRC_MPU_C0 << 4)  | 0x1);
    //WR_MEM_32(DRM_SUSPEND_CTRL_TIMER10, (DRM_SUSPEND_SRC_MPU_C1 << 4)  | 0x1);
    WR_MEM_32(DRM_SUSPEND_CTRL_TIMER5,  (DRM_SUSPEND_SRC_DSP1 << 4)    | 0x1);
    WR_MEM_32(DRM_SUSPEND_CTRL_TIMER6,  (DRM_SUSPEND_SRC_DSP1 << 4)    | 0x1);
    //WR_MEM_32(DRM_SUSPEND_CTRL_TIMER3,  (DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1);
    //WR_MEM_32(DRM_SUSPEND_CTRL_TIMER4,  (DRM_SUSPEND_SRC_IPU1_C1 << 4) | 0x1);

    //IPU1SSClkEnable_API();
	//IPU2SSClkEnable_API(); //IPU2 subsystem is dedicated to IVA support and is not available for other processing

    DSP1SSClkEnable_API(entryPoint);
    //DSP2SSClkEnable_API(0);  

    //IVAHDSSClkEnable_API();

    //PRUSS_1_2_ClkEnable();
}

/************ Enable the PRUSS Clocks **************/
void PRUSS_1_2_ClkEnable()
{
    GEL_TextOut("--->>> PRUSS 1 and 2 Initialization is in progress ... <<<---\n");
    WR_MEM_32(0x4a009718, 0x0); //PRUSS_1_CLKCTRL
    WR_MEM_32(0x4a009720, 0x0); //PRUSS_2_CLKCTRL

    WR_MEM_32(0x4a009718, 0x2); //PRUSS_1_CLKCTRL
    WR_MEM_32(0x4a009720, 0x2); //PRUSS_2_CLKCTRL
    while ((RD_MEM_32(0x4a0098FC) & 0x100) != 0x100); //L4PER2 - ICSS_CLKACTIVITY
    GEL_TextOut("--->>> PRUSS 1 and 2 Initialization is in complete ... <<<---\n");
}

/************ Enable the IPU1 Clocks ***************/
void IPU1SSClkEnable_API()
{
    IPUSSClkEnable(1);
}

/************ Enable the IPU2 Clocks ***************/
void IPU2SSClkEnable_API()
{
    IPUSSClkEnable(2);
}

/************ Enable the DSP1 Clocks ***************/
void DSP1SSClkEnable_API(uint32_t entryPoint)
{
    DSPSSClkEnable(1, entryPoint);
}

/************ Enable the DSP2 Clocks ***************/
void DSP2SSClkEnable_API(uint32_t entryPoint)
{
    DSPSSClkEnable(2, entryPoint);
}

/************ Enable the IVA Clocks ***************/
void IVAHDSSClkEnable_API()
{
    IVAHDSSClkEnable();
}

void IPUSSClkEnable(uint32_t cpu_num)
{
    uint32_t regAddr;

    GEL_TextOut("--->>> IPU%dSS Initialization is in progress ... <<<---\n", cpu_num);
    /* Reset asserted for IPU CPU0, CPU1, Unicache and MMU */
    WR_MEM_32(RM_IPU_RSTCTRL, 0x7);

    /* Reset deassertion for IPU Unicache/MMU */
    WR_MEM_32(RM_IPU_RSTST, 0x7);
    WR_MEM_32(RM_IPU_RSTCTRL, 0x3);
    do{
    }while ((RD_MEM_32(RM_IPU_RSTST) & 0x4) != 0x4);

        /*---------------- Setup the UNICACHE MMU -----------------*/
        /*Large Page Translations */
        /* Logical Address */
        regAddr = IPU_MMU_CFG;
        regAddr += 0x800;
        WR_MEM_32(regAddr,         0x40000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x80000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0xA0000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x60000000); regAddr += 0x4;

        /* Physical Address */
        regAddr = IPU_MMU_CFG;
        regAddr += 0x820;
        WR_MEM_32(regAddr,         0x40000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x80000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0xA0000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x40000000); regAddr += 0x4;

        /* Policy Register */
        regAddr = IPU_MMU_CFG;
        regAddr += 0x840;
        WR_MEM_32(regAddr,         0x00000007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x000B0007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00020007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00000007); regAddr += 0x4;

        /*Medium Page*/
        regAddr = IPU_MMU_CFG;
        regAddr += 0x860;
        WR_MEM_32(regAddr,         0x00300000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00400000); regAddr += 0x4;

        regAddr = IPU_MMU_CFG;
        regAddr += 0x8A0;
        WR_MEM_32(regAddr,         0x40300000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x40400000); regAddr += 0x4;

        regAddr = IPU_MMU_CFG;
        regAddr += 0x8E0;
        WR_MEM_32(regAddr,         0x00000007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00020007); regAddr += 0x4;

        /*Small Page*/
        regAddr = IPU_MMU_CFG;
        regAddr += 0x920;
        WR_MEM_32(regAddr,         0x00000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x40000000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00004000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00008000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x20000000); regAddr += 0x4;

        regAddr = IPU_MMU_CFG;
        regAddr += 0x9A0;
        WR_MEM_32(regAddr,         0x55020000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x55080000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x55024000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x55028000); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x55020000); regAddr += 0x4;

        regAddr = IPU_MMU_CFG;
        regAddr += 0xA20;
        WR_MEM_32(regAddr,         0x0001000B); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x0000000B); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00010007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00000007); regAddr += 0x4;
        WR_MEM_32(regAddr,         0x00000007); regAddr += 0x4;
    
    /*---------------- Write IPU IRAM Boot Image ---------------*/
    /* This puts the cores into dummy loops to prevent them from running bad code */
    WR_MEM_32(IPU_BASE_ADDR, 0x10000);
    WR_MEM_32(IPU_BASE_ADDR + 0x4, 0x9);
    WR_MEM_32(IPU_BASE_ADDR + 0x8, 0xE7FEE7FE);
    while (RD_MEM_32(IPU_BASE_ADDR) != 0x10000);
    while (RD_MEM_32(IPU_BASE_ADDR + 0x4) != 0x9);
    while (RD_MEM_32(IPU_BASE_ADDR + 0x8) != 0xE7FEE7FE);


    /* Reset deassertion for IPU CPU0, CPU1 */
    WR_MEM_32(RM_IPU_RSTCTRL, 0x0);

    /* Check the reset state: IPU CPU0, CPU1, Unicache and MMU are out of reset */
    while ((RD_MEM_32(RM_IPU_RSTST) & 0x3) != 0x3);
    WR_MEM_32(RM_IPU_RSTST, 0x7);


    GEL_TextOut("--->>> IPU%dSS Initialization is DONE! <<<---\n",cpu_num);
}

void DSPSSClkEnable(uint32_t cpu_num, uint32_t entryPoint)
{
    uint32_t i = 0;
    UINT32 instruction = 0;
    GEL_TextOut("--->>> DSP%dSS Initialization is in progress ... <<<---\n",cpu_num);

    /* DSPSS Boot Address */
    WR_MEM_32(DSPSSBOOTADDR, (DSPSSBOOTADDRVALUE >> 10));

    /* Ware reset asserted for DSP_LRST, DSP Cache and Slave */
    WR_MEM_32(RM_DSP_RSTCTRL, 0x3);

    /* Start a SW force wakeup for DSPSS */
    WR_MEM_32(CM_DSP_CLKSTCTRL, 0x2);
    /* Enable DSPSS clock */
    WR_MEM_32(CM_DSP_DSP_CLKCTRL, 0x1);

    /* Check whether GFCLK is gated or not */
    while ((RD_MEM_32(CM_DSP_CLKSTCTRL) & 0x100) != 0x100);
    if (DEBUG_PRINT)
    {
        GEL_TextOut("DEBUG: Clock is active ... \n");
    }

    /* Reset de-assertion for DSPSS */
    WR_MEM_32(RM_DSP_RSTCTRL, 0x1);
    /* Check the reset state: DSPSS */
    while ((RD_MEM_32(RM_DSP_RSTST) & 0x2) != 0x2);
    if(entryPoint != 0)
    {
    instruction = 0x0200002A; // MVK with side B selected using B4
    instruction |= (entryPoint & 0xFFFF) << 7; // insert the lower 16 bits of the entry point address
    WR_MEM_32(DSP_L2_SRAM_TARG, instruction); //Write the instruction

    instruction = 0x0200006A; // MVKH with side B selected using B4
    instruction |= ((entryPoint >> 16) & 0xFFFF) << 7; // insert the higher 16 bits of the entry point address
    WR_MEM_32(DSP_L2_SRAM_TARG + 4, instruction); //Write the instruction
    
    instruction = 0x00100362; //Branch instruction to the address contained in B4
    WR_MEM_32(DSP_L2_SRAM_TARG + 8, instruction); //Write the instruction
    
    for (i = 3; i < 16; i++)
    {
        WR_MEM_32((DSP_L2_SRAM_TARG + (i << 2)), 0x12345678);
    }
    }
    else
    {
        WR_MEM_32(DSP_L2_SRAM_TARG, 0x0000A120); //Self branch loop for DSP
    }
    Gel_flushDspMem();
    /* Reset de-assertion for DSP CPUs */
    WR_MEM_32(RM_DSP_RSTCTRL, 0x0);
    /* Check the reset state: DSPSS Core, Cache and Slave interface */
    while ((RD_MEM_32(RM_DSP_RSTST) & 0x3) != 0x3);
    /* Check module mode */
    while ((RD_MEM_32(CM_DSP_DSP_CLKCTRL) & 0x30000) != 0x0);

//    if (DEBUG_PRINT)
//    {
//        GEL_TextOut("DEBUG: Checking for data integrity in DSPSS L2RAM ... \n");
//    }
    
//    for (i = 1; i < 16; i++)
//    {
//        if (RD_MEM_32(DSP_L2_SRAM_TARG + (i << 2)) != 0x12345678)
//        {
//            fail++;
//            break;
//        }
//    }
//
//    if (fail)
//    {
//        GEL_TextOut("ERROR: Data integrity check in GEM L2RAM has failed! \n");
//    }
//    else
//    {
//        if (DEBUG_PRINT)
//        {
//            GEL_TextOut("DEBUG: Data integrity check in GEM L2RAM is sucessful! \n");
//        }
//    }


    GEL_TextOut("--->>> DSP%dSS Initialization is DONE! <<<---\n",cpu_num);
}

void IVAHDSSClkEnable()
{
    GEL_TextOut("--->>> IVAHD Initialization is in progress ... <<<---\n");

    /* Start a SW force wakeup for IVASS */
    WR_MEM_32(CM_IVA_CLKSTCTRL, 0x2);
    /* Enable IVASS clock */
    WR_MEM_32(CM_IVA_IVA_CLKCTRL, 0x1);
    /* Enable IVA SL2 clock */
    WR_MEM_32(CM_IVA_SL2_CLKCTRL, 0x1);

    /* Check whether GFCLK is gated or not */
    while ((RD_MEM_32(CM_IVA_CLKSTCTRL) & 0x100) != 0x100);
    if (DEBUG_PRINT)
    {
        GEL_TextOut("DEBUG: Clock is active ... \n");
    }

    /* Warm reset asserted for CPU1, CPU2, IVA Logic */
    WR_MEM_32(RM_IVA_RSTCTRL, 0x7);
    WR_MEM_32(RM_IVA_RSTST, 0x7);

    /* Warm reset asserted for CPU1, CPU2 */
    WR_MEM_32(RM_IVA_RSTCTRL, 0x3);

    /* Check the reset state: IVA Logic */
    while ((RD_MEM_32(RM_IVA_RSTST) & 0x4) != 0x4);

    /* Self branch instruction */
    WR_MEM_32(ICONT1_ITCM, 0xEAFFFFFE);
    WR_MEM_32(ICONT2_ITCM, 0xEAFFFFFE);

    /* Reset de-assertion for CPU1, CPU2 */
    WR_MEM_32(RM_IVA_RSTCTRL, 0x1);
    while ((RD_MEM_32(RM_IVA_RSTST) & 0x6) != 0x6);
    WR_MEM_32(RM_IVA_RSTCTRL, 0x0);
    while ((RD_MEM_32(RM_IVA_RSTST) & 0x7) != 0x7);

    WR_MEM_32(RM_IVA_RSTST, 0x7);

    GEL_TextOut("--->>> IVAHD Initialization is DONE! ... <<<---\n");
}
