/*******************************************************************/
/* This GEL file is loaded on the command line of Code Composer    */
/* The StartUp() function is called every time you start           */
/* Code Composer.  You can customize this function to              */
/* initialize wait states or to perform other initialization.      */
/*                                                                 */
/* AM572x prcm module & clock config                               */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
#include "gel.h"
#define uint32_t                unsigned int


#define DEBUG_PRINT         (0)


/* OPP definitions */
#define     OPP_NOM         (0x0)
#define     OPP_OD          (0x1)
#define     OPP_HIGH        (0x2)

#define     SYS_CLK1        (20)

/* DEVICE_TYPE definitions */
#define     DEVICE_AM572X_GP      (0x3)

/* DPLL Definitions */
#define DPLL_TIMEOUT                            5000           // DPLL lock/unlock timeout (was 5000)
#define CM_CLKMODE_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS)
#define CM_IDLEST_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x04)
#define CM_AUTOIDLE_DPLL(DPLL_BASE_ADDRESS)     RD_MEM_32(DPLL_BASE_ADDRESS + 0x08)
#define CM_CLKSEL_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x0C)
#define CM_DIV_M2_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x10)
#define CM_DIV_M3_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x14)
#define CM_DIV_H11_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x18)
#define CM_DIV_H12_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x1C)
#define CM_DIV_H13_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x20)
#define CM_DIV_H14_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x24)
#define CM_DIV_H21_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x30)
#define CM_DIV_H22_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x34)
#define CM_DIV_H23_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x38)
#define CM_DIV_H24_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x3C)


/* Instance Base Addresses */
#define CTRL_MODULE_CORE    0x4a002000
#define CKGEN_CM_CORE_AON   0x4a005100
#define MPU_CM_CORE_AON     0x4a005300
#define DSP1_CM_CORE_AON    0x4a005400
#define IPU_CM_CORE_AON     0x4a005500
#define DSP2_CM_CORE_AON    0x4a005600
#define RTC_CM_CORE_AON     0x4a005740
#define VPE_CM_CORE_AON     0x4a005760
#define CKGEN_CM_CORE       0x4a008100
#define COREAON_CM_CORE     0x4a008600
#define CORE_CM_CORE        0x4a008700
#define IVA_CM_CORE         0x4a008f00
#define CAM_CM_CORE         0x4a009000
#define DSS_CM_CORE         0x4a009100
#define GPU_CM_CORE         0x4a009200
#define L3INIT_CM_CORE      0x4a009300
#define L4PER_CM_CORE       0x4a009700
#define CKGEN_PRM           0x4ae06100
#define WKUPAON_CM          0x4ae07800
#define EMU_CM              0x4ae07a00

/* CLKSTCTRL offsets */
#define CORE_CM_CORE__CM_L3MAIN1_CLKSTCTRL                        0x000ul
#define CORE_CM_CORE__CM_IPU2_CLKSTCTRL                           0x200ul
#define CORE_CM_CORE__CM_DMA_CLKSTCTRL                            0x300ul
#define CORE_CM_CORE__CM_EMIF_CLKSTCTRL                           0x400ul
#define CORE_CM_CORE__CM_L4CFG_CLKSTCTRL                          0x600ul
#define COREAON_CM_CORE__CM_COREAON_CLKSTCTRL                     0x00ul
#define DSP1_CM_CORE_AON__CM_DSP1_CLKSTCTRL                       0x00ul
#define DSP2_CM_CORE_AON__CM_DSP2_CLKSTCTRL                       0x00ul
#define DSS_CM_CORE__CM_DSS_CLKSTCTRL                             0x00ul
#define GPU_CM_CORE__CM_GPU_CLKSTCTRL                             0x00ul
#define IPU_CM_CORE_AON__CM_IPU1_CLKSTCTRL                        0x00ul
#define IPU_CM_CORE_AON__CM_IPU_CLKSTCTRL                         0x40ul
#define IVA_CM_CORE__CM_IVA_CLKSTCTRL                             0x00ul
#define CAM_CM_CORE__CM_CAM_CLKSTCTRL                             0x00ul
#define L3INIT_CM_CORE__CM_L3INIT_CLKSTCTRL                       0x00ul
#define L3INIT_CM_CORE__CM_PCIE_CLKSTCTRL                         0xA0ul
#define L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL                         0xC0ul
#define L4PER_CM_CORE__CM_L4PER_CLKSTCTRL                         0x000ul
#define L4PER_CM_CORE__CM_L4PER2_CLKSTCTRL                        0x1FCul
#define L4PER_CM_CORE__CM_L4PER3_CLKSTCTRL                        0x210ul
#define MPU_CM_CORE_AON__CM_MPU_CLKSTCTRL                         0x00ul
#define RTC_CM_CORE_AON__CM_RTC_CLKSTCTRL                         0x00ul
#define VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL                         0x00ul
#define WKUPAON_CM__CM_WKUPAON_CLKSTCTRL                          0x00ul

/* CLKSTCTRL modes */
#define SW_SLEEP        (0x1)
#define SW_WKUP         (0x2)
#define HW_AUTO         (0x3)

#define CLKSTCTRL_TIMEOUOT  (300)

/* CLKCTRL Offsets */
#define CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL                            0x020ul
#define CAM_CM_CORE__CM_CAM_VIP2_CLKCTRL                            0x028ul
#define CAM_CM_CORE__CM_CAM_VIP3_CLKCTRL                            0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_L3_MAIN_1_CLKCTRL                  0x020ul
#define CORE_CM_CORE__CM_L3MAIN1_GPMC_CLKCTRL                       0x028ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL                   0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_PCIESS_CLKCTRL                 0x048ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL                  0x050ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM2_CLKCTRL                  0x058ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM3_CLKCTRL                  0x060ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_ROM_CLKCTRL                   0x068ul
#define CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL                       0x070ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL                      0x078ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL                      0x080ul
#define CORE_CM_CORE__CM_IPU2_IPU2_CLKCTRL                          0x220ul
#define CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL                     0x320ul
#define CORE_CM_CORE__CM_EMIF_DMM_CLKCTRL                           0x420ul
#define CORE_CM_CORE__CM_EMIF_EMIF_OCP_FW_CLKCTRL                   0x428ul
#define CORE_CM_CORE__CM_EMIF_EMIF1_CLKCTRL                         0x430ul
#define CORE_CM_CORE__CM_EMIF_EMIF2_CLKCTRL                         0x438ul
#define CORE_CM_CORE__CM_L4CFG_L4_CFG_CLKCTRL                       0x620ul
#define CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL                     0x628ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL                     0x630ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL                     0x648ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL                     0x650ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL                     0x658ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL                     0x660ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL                     0x668ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL                     0x670ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL                     0x678ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL                     0x680ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL                    0x688ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL                    0x690ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL                    0x698ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL                    0x6A0ul
#define CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL                  0x720ul
#define DSS_CM_CORE__CM_DSS_DSS_CLKCTRL                             0x020ul
#define GPU_CM_CORE__CM_GPU_GPU_CLKCTRL                             0x020ul
#define EMU_CM__CM_EMU_MPU_EMU_DBG_CLKCTRL                          0x00Cul
#define IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL                       0x020ul
#define IPU_CM_CORE_AON__CM_IPU_MCASP1_CLKCTRL                      0x050ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL                      0x058ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL                      0x060ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER7_CLKCTRL                      0x068ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER8_CLKCTRL                      0x070ul
#define IVA_CM_CORE__CM_IVA_IVA_CLKCTRL                             0x020ul
#define IVA_CM_CORE__CM_IVA_SL2_CLKCTRL                             0x028ul
#define L3INIT_CM_CORE__CM_L3INIT_MMC1_CLKCTRL                      0x028ul
#define L3INIT_CM_CORE__CM_L3INIT_MMC2_CLKCTRL                      0x030ul
#define L3INIT_CM_CORE__CM_L3INIT_IEEE1500_2_OCP_CLKCTRL            0x078ul
#define L3INIT_CM_CORE__CM_PCIE_PCIESS1_CLKCTRL                     0x0B0ul
#define L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL                        0x0D0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP1_CLKCTRL                  0x0E0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP3_CLKCTRL                  0x0E8ul
#define L4PER_CM_CORE__CM_L4PER2_L4_PER2_CLKCTRL                    0x00Cul
#define L4PER_CM_CORE__CM_L4PER3_L4_PER3_CLKCTRL                    0x014ul
#define L4PER_CM_CORE__CM_L4PER_TIMER10_CLKCTRL                     0x028ul
#define L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL                     0x030ul
#define L4PER_CM_CORE__CM_L4PER_TIMER2_CLKCTRL                      0x038ul
#define L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL                      0x040ul
#define L4PER_CM_CORE__CM_L4PER_TIMER4_CLKCTRL                      0x048ul
#define L4PER_CM_CORE__CM_L4PER_TIMER9_CLKCTRL                      0x050ul
#define L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL                       0x060ul
#define L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL                       0x068ul
#define L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL                       0x070ul
#define L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL                       0x078ul
#define L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL                       0x080ul
#define L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL                        0x0A0ul
#define L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL                        0x0A8ul
#define L4PER_CM_CORE__CM_L4PER_I2C3_CLKCTRL                        0x0B0ul
#define L4PER_CM_CORE__CM_L4PER_I2C4_CLKCTRL                        0x0B8ul
#define L4PER_CM_CORE__CM_L4PER_L4_PER1_CLKCTRL                     0x0C0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER13_CLKCTRL                    0x0C8ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER14_CLKCTRL                    0x0D0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER15_CLKCTRL                    0x0D8ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI1_CLKCTRL                      0x0F0ul
#define L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL                       0x110ul
#define L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL                       0x118ul
#define L4PER_CM_CORE__CM_L4PER_MMC3_CLKCTRL                        0x120ul
#define L4PER_CM_CORE__CM_L4PER_MMC4_CLKCTRL                        0x128ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER16_CLKCTRL                    0x130ul
#define L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL                       0x138ul
#define L4PER_CM_CORE__CM_L4PER_UART1_CLKCTRL                       0x140ul
#define L4PER_CM_CORE__CM_L4PER_UART3_CLKCTRL                       0x150ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_CLKCTRL                         0x020ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_MPU_DBG_CLKCTRL                 0x028ul
#define VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL                         0x004ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER1_CLKCTRL                    0x028ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER2_CLKCTRL                    0x030ul
#define WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL                        0x038ul
#define WKUPAON_CM__CM_WKUPAON_TIMER1_CLKCTRL                       0x040ul
#define WKUPAON_CM__CM_WKUPAON_TIMER12_CLKCTRL                      0x048ul
#define WKUPAON_CM__CM_WKUPAON_UART10_CLKCTRL                       0x080ul

/* CLKCTRL modes */
#define MODE_DISABLED   (0x0)
#define MODE_AUTO       (0x1)
#define MODE_ENABLED    (0x2)

#define CLKCTRL_TIMEOUOT  (300)

/* Various register address definitions */
#define CM_CLKSEL_CORE              (CKGEN_CM_CORE_AON + 0x000)
#define CM_CLKSEL_ABE               (CKGEN_CM_CORE_AON + 0x008)
#define CM_DLL_CTRL                 (CKGEN_CM_CORE_AON + 0x010)
#define CM_CLKMODE_DPLL_CORE        (CKGEN_CM_CORE_AON + 0x020)
#define CM_CLKSEL_DPLL_CORE         (CKGEN_CM_CORE_AON + 0x02C)
#define CM_CLKMODE_DPLL_MPU         (CKGEN_CM_CORE_AON + 0x060)
#define CM_CLKMODE_DPLL_IVA         (CKGEN_CM_CORE_AON + 0x0A0)
#define CM_CLKMODE_DPLL_ABE         (CKGEN_CM_CORE_AON + 0x0E0)
#define CM_CLKMODE_DPLL_DDR         (CKGEN_CM_CORE_AON + 0x110)
#define CM_CLKMODE_DPLL_DSP         (CKGEN_CM_CORE_AON + 0x134)
#define CM_CLKMODE_DPLL_GMAC        (CKGEN_CM_CORE_AON + 0x1A8)
#define CM_CLKMODE_DPLL_GPU         (CKGEN_CM_CORE_AON + 0x1D8)
#define CM_CLKMODE_DPLL_PER         (CKGEN_CM_CORE     + 0x040)
#define CM_CLKMODE_DPLL_PCIE_REF    (CKGEN_CM_CORE     + 0x100)
#define CM_SYS_CLKSEL               (CKGEN_PRM         + 0x010)

#define CTRL_CORE_CONTROL_IO_2      (CTRL_MODULE_CORE  + 0x558)


void AM572x_PRCM_Clock_Config_API(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_a15_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_per_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_core_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_abe_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_iva_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_gmac_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_pcie_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_dsp_config(uint32_t OPP, uint32_t DEVICE_TYPE);
void dpll_lock_sequence(uint32_t base_address);
void dpll_unlock_sequence(uint32_t base_address);
void dpll_gpu_config(uint32_t OPP, uint32_t DEVICE_TYPE);
uint32_t dpll_get_clkout_speed_hsdiv(uint32_t base_address, uint32_t divider_val);
uint32_t dpll_get_clkout_speed(uint32_t base_address, uint32_t return_clk, uint32_t print_enable);
void prcm_set_dss_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_proc_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_ipu1_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_module_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode, uint32_t extrabits, uint32_t extrabitsMask);
void prcm_set_clkdomain_state(uint32_t module_base, uint32_t module_offset, uint32_t state);
/**********************************************************************
 *
 *  FUNCTIONS
 *
 **********************************************************************/

//menuitem "AM572x PRCM MODULE Configuration"
void AM572x_PRCM_Module_AllEnable_Config()
{
    GEL_TextOut("--->>> PRCM Configuration for all modules in progress... <<<---\n");

    /* PRCM clock domain state setting functions */
    prcm_set_clkdomain_state(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_CLKSTCTRL,        SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_CLKSTCTRL,       SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_DMA_CLKSTCTRL,         SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_IPU2_CLKSTCTRL,        SW_WKUP );
    prcm_set_clkdomain_state(COREAON_CM_CORE,   COREAON_CM_CORE__CM_COREAON_CLKSTCTRL,  SW_WKUP );
    prcm_set_clkdomain_state(DSS_CM_CORE,       DSS_CM_CORE__CM_DSS_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU1_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(RTC_CM_CORE_AON,   RTC_CM_CORE_AON__CM_RTC_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_CLKSTCTRL,       SW_WKUP );
    prcm_set_clkdomain_state(MPU_CM_CORE_AON,   MPU_CM_CORE_AON__CM_MPU_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(DSP1_CM_CORE_AON,  DSP1_CM_CORE_AON__CM_DSP1_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(DSP2_CM_CORE_AON,  DSP2_CM_CORE_AON__CM_DSP2_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(IVA_CM_CORE,       IVA_CM_CORE__CM_IVA_CLKSTCTRL,          SW_WKUP );

    /* PRCM Generic module mode setting functions */
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP2_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP3_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_DMM_CLKCTRL,              MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF1_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF2_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF_OCP_FW_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_GPMC_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_L3_MAIN_1_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_PCIESS_CLKCTRL,    MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM2_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM3_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_ROM_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  ); 
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_L4_CFG_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_MCASP1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER7_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER8_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_MMC1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_MMC2_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_L4_PER2_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_L4_PER3_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER13_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER14_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER15_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER16_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C3_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C4_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_L4_PER1_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MCSPI1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MMC3_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MMC4_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER10_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER2_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER4_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER9_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL,          MODE_ENABLED,   0x05000000, 0x07000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_UART1_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_UART3_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(MPU_CM_CORE_AON,   MPU_CM_CORE_AON__CM_MPU_MPU_CLKCTRL,            MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL,           MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_TIMER1_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_TIMER12_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_WD_TIMER1_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_WD_TIMER2_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );

    /* PRCM Specialized module mode setting functions */
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_SL2_CLKCTRL,                MODE_AUTO                   );
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_IVA_CLKCTRL,                MODE_AUTO                   );
    prcm_set_proc_mode(CORE_CM_CORE,        CORE_CM_CORE__CM_IPU2_IPU2_CLKCTRL,             MODE_AUTO                   );
    prcm_set_dss_mode(DSS_CM_CORE,          DSS_CM_CORE__CM_DSS_DSS_CLKCTRL,                MODE_ENABLED                );
    prcm_set_ipu1_mode(IPU_CM_CORE_AON,     IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL,          MODE_AUTO                   );

    GEL_TextOut("--->>> PRCM Configuration for all modules is DONE! <<<---\n");
}

void prcm_set_dss_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUOT;

    if (DEBUG_PRINT)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
    }

    /* DESHDCP Clock ENABLE for DSS */
    WR_MEM_32(CTRL_CORE_CONTROL_IO_2, RD_MEM_32(CTRL_CORE_CONTROL_IO_2) | 0x1);

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | 0x00003F00 | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    if (DEBUG_PRINT)
    {
        GEL_TextOut("\tWaiting for DSS module IDLE status....\n");
    }
    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }

    if (timeout==0)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
        GEL_TextOut("\tTIMEOUT\n");
    }
    else
    {
        if (DEBUG_PRINT)
        {
            GEL_TextOut("\tDONE\n");
        }
    }
}

void prcm_set_proc_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUOT;

    if (DEBUG_PRINT)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
    }

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) == 0x00030000) && (timeout>0))
    {
        timeout--;
    }

    if (timeout==0)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
        GEL_TextOut("\tTIMEOUT\n");
    }
    else
    {
        if (DEBUG_PRINT)
        {
            GEL_TextOut("\tDONE\n");
        }
    }
}

void prcm_set_ipu1_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUOT;

    if (DEBUG_PRINT)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
    }

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | 0x01000000 | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    if (DEBUG_PRINT)
    {
        GEL_TextOut("\tWaiting for IPU1 module IDLE status....\n");
    }
    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) == 0x00030000) && (timeout>0))
    {
        timeout--;
    }

    if (timeout==0)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
        GEL_TextOut("\tTIMEOUT\n");
    }
    else
    {
        if (DEBUG_PRINT)
        {
            GEL_TextOut("\tDONE\n");
        }
    }
}

void prcm_set_module_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode, uint32_t extrabits, uint32_t extrabitsMask)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUOT;

    if (DEBUG_PRINT)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
    }

    reg_val = RD_MEM_32(module_base + module_offset) & ~(extrabitsMask | 0x00000003);
    WR_MEM_32(module_base+module_offset, (reg_val | (extrabits & extrabitsMask) | (mode & 0x3)));

    if (DEBUG_PRINT)
    {
        GEL_TextOut("\tWaiting for module IDLE status....\n");
    }
    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }

    if (timeout==0)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
        GEL_TextOut("\tTIMEOUT\n");
    }
    else
    {
        if (DEBUG_PRINT)
        {
            GEL_TextOut("\tDONE\n");
        }
    }
}

void prcm_set_clkdomain_state(uint32_t module_base, uint32_t module_offset, uint32_t state)
{
    uint32_t reg_val;
    
    if (DEBUG_PRINT)
    {
        GEL_TextOut("module_base:   %x\n", module_base);
        GEL_TextOut("module_offset: %x\n", module_offset);
    }

    reg_val = RD_MEM_32(module_base+module_offset);
    WR_MEM_32(module_base+module_offset, ((reg_val & ~(0x3)) | (state & 0x3)));

    /*if (DEBUG_PRINT)
    {
        GEL_TextOut("\tWaiting for clock active....\n");
    }
    while( ((RD_MEM_32(module_base + module_offset) & 0x100) != 0x100) && (timeout>0) )
    {
        timeout--;
    }

    if (timeout==0)
    {
        GEL_TextOut("\tTIMEOUT\n");
    }
    else
    {
        if (DEBUG_PRINT)
        {
            GEL_TextOut("\tDONE\n");
        }
    }
    */
}

//menuitem "AM572x PRCM CLOCK Configuration"
void AM572x_PRCM_Clock_Config_OPPNOM()
{
    AM572x_PRCM_Clock_Config_API(OPP_NOM, DEVICE_AM572X_GP);
}

void AM572x_PRCM_Clock_Config_OPPOD()
{
    AM572x_PRCM_Clock_Config_API(OPP_OD, DEVICE_AM572X_GP);
}

void AM572x_PRCM_Clock_Config_OPPHIGH()
{
    AM572x_PRCM_Clock_Config_API(OPP_HIGH, DEVICE_AM572X_GP);
}

void AM572x_PRCM_Clock_Config_API(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    GEL_TextOut("--->>> PRCM Clock Configuration for OPPNOM in progress... <<<---\n");
    if(OPP_NOM != OPP)
    {
        GEL_TextOut("\t!!!Only DPLL configuration is done!!!\n\t!!!Voltage changes for non-NOMinal OPP needs to be done externally!!!\n", OPP);
    }

    /* DDR DPLL programming is NOT done here, but is called from the DDR config commands */

    // DPLL programming
    //dpll_a15_opp_config(OPP, DEVICE_TYPE);

    // IVA clock programming
    dpll_iva_opp_config(OPP, DEVICE_TYPE);

    // PER DPLL programming
    //dpll_per_opp_config(OPP, DEVICE_TYPE);

    // Core DPLL programming
    //dpll_core_opp_config(OPP, DEVICE_TYPE);

    // ABE DPLL programming
    dpll_abe_opp_config(OPP, DEVICE_TYPE);

    // GMAC DPLL programming
    //dpll_gmac_config(OPP, DEVICE_TYPE);

    // GPU DPLL programming
    dpll_gpu_config(OPP, DEVICE_TYPE);

    // DSP DPLL programming
    dpll_dsp_config(OPP, DEVICE_TYPE);
    
    // PCIE DPLL programming
    //dpll_pcie_config(OPP, DEVICE_TYPE);

    GEL_TextOut("--->>> PRCM Clock Configuration for OPP %d is DONE! <<<---\n",OPP_NOM);
}
#if 0
#endif
/******************************************************************************
* dpll_a15_opp_config() : Cortex A15 DPLL OPP configurations
******************************************************************************/
void dpll_a15_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    uint32_t dpll_m, dpll_n, divm2, dcc_en;
    dcc_en = 0;

    GEL_TextOut("\tCortex A15 DPLL OPP %d clock config is in progress...\n", OPP);

	if(OPP_HIGH == OPP)
	{
		//1500MHz at 20MHz sys_clk
		dpll_m = 600;
		dpll_n = 7;
		divm2  = 1;
		dcc_en = 1;
	}
	else if(OPP_OD == OPP)
	{
		//1176MHz at 20MHz sys_clk
		dpll_m = 294;
		dpll_n = 4;
		divm2  = 1;
	}
	else //default to OPP_NOM
	{
		//1000MHz at 20MHz sys_clk
		dpll_m = 500;
		dpll_n = 9;
		divm2  = 1;
	}

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_MPU)&0x1)
    {
        GEL_TextOut("\tCortex A15 DPLL is already locked, now unlocking...  \n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_MPU);
    }

    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_MPU) = ((dpll_m << 8) | dpll_n | (dcc_en << 22));
    WR_MEM_32(CM_CLKMODE_DPLL_MPU + 0x0C,((dpll_m << 8) | dpll_n | (dcc_en << 22)));

    // Program DPLL_CLKOUT divider (M2 = 1)
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_MPU) = divm2;
    WR_MEM_32(CM_CLKMODE_DPLL_MPU + 0x10,divm2);

    dpll_lock_sequence(CM_CLKMODE_DPLL_MPU);

    GEL_TextOut("\tCortex A15 DPLL OPP %d is DONE!\n", OPP);
}
/******************************************************************************
* dpll_per_opp_config() : PER DPLL OPP configurations
*****************************************************************************/
void dpll_per_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    GEL_TextOut("\tPER DPLL OPP %d clock config in progress...\n", OPP);

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_PER)&0x1)
    {
        GEL_TextOut("\tPER DPLL already locked, now unlocking  \n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_PER);
    }

    /* CM_CLKSEL_DPLL_PER DPLL MULT */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_PER) = 0x6004;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x0C,0x6004);

    /* CM_DIV_M2_DPLL_PER.DPLL_CLKOUT_DIV = 4*/
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_PER) = 0x4;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x10,0x4);

    /* CM_DIV_M3_DPLL_PER.DPLL_CLKOUT_DIV = 3 */
    //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_PER) = 0x1;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x14,0x1);

    /* CM_DIV_H11_DPLL_PER.HSDIVIDER_CLKOUT1_DIV  = 3 */
    //CM_DIV_H11_DPLL(CM_CLKMODE_DPLL_PER) = 0x3;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x18,0x3);

    /* CM_DIV_H12_DPLL_PER.HSDIVIDER_CLKOUT2_DIV = 4 */
    //CM_DIV_H12_DPLL(CM_CLKMODE_DPLL_PER) = 0x4;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x1C,0x4);

    /* CM_DIV_H13_DPLL_PER.HSDIVIDER_CLKOUT2_DIV = 4 : To get 192M output */
    //CM_DIV_H13_DPLL(CM_CLKMODE_DPLL_PER) = 0x04;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x20,0x04);

    /* CM_DIV_H14_DPLL_PER.HSDIVIDER_CLKOUT3_DIV = 2 */
    //CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_PER) = 0x2;
    WR_MEM_32(CM_CLKMODE_DPLL_PER + 0x24,0x2);

    dpll_lock_sequence(CM_CLKMODE_DPLL_PER);

    GEL_TextOut("\tPER DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
* dpll_core_opp_config() : CORE DPLL OPP configurations
*****************************************************************************/
void dpll_core_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    GEL_TextOut("\tCORE DPLL OPP %d clock config is in progress...\n", OPP);

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_CORE)&0x1)
    {
        GEL_TextOut("\tCORE DPLL OPP  already locked, now unlocking....  \n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_CORE);
    }

    // Program L3 & L4 dividers from CORE DPLL
    /* L3 clock = CORE CLK /2; L4 clock = L3 clock /2; CORE_CLK=CORE_X2_CLK/2 */
    WR_MEM_32(CM_CLKSEL_CORE, 0x110);

    /* Lock and code outputs ARE overriden */
    WR_MEM_32(CM_DLL_CTRL, 0x00000000);

    /* CM_CLKSEL_DPLL_CORE.PLL_MULT = 0x200 */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_CORE) = 0x10a04;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x0C,0x10a04);

    /* CM_DIV_M2_DPLL_CORE */
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_CORE) = 0x2;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x10,0x2);

    /* CM_DIV_M3_DPLL_CORE  */
    //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_CORE) = 0x1;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x14,0x1);

    /* CM_DIV_H12_DPLL_CORE  */
    //CM_DIV_H12_DPLL(CM_CLKMODE_DPLL_CORE) = 0x4;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x1C,0x4);

    /* CM_DIV_H13_DPLL_CORE */
    //CM_DIV_H13_DPLL(CM_CLKMODE_DPLL_CORE) = 0x3E;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x20,0x3E);

    /* CM_DIV_H14_DPLL_CORE */
    //CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_CORE) = 0x5;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x24,0x5);

    /* CM_DIV_H22_DPLL_CORE */
    //CM_DIV_H22_DPLL(CM_CLKMODE_DPLL_CORE) = 0x5;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x34,0x5);

    /* CM_DIV_H23_DPLL_CORE */
    //CM_DIV_H23_DPLL(CM_CLKMODE_DPLL_CORE) = 0x4;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x38,0x4);

    /* CM_DIV_H24_DPLL_CORE */                      
    //CM_DIV_H24_DPLL(CM_CLKMODE_DPLL_CORE) = 0x6;
    WR_MEM_32(CM_CLKMODE_DPLL_CORE + 0x3C,0x6);

    dpll_lock_sequence(CM_CLKMODE_DPLL_CORE);

    GEL_TextOut("\tCORE DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
 * dpll_abe_opp_config() : ABE DPLL OPP configurations
 *****************************************************************************/
void dpll_abe_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    GEL_TextOut("\tABE DPLL OPP %d clock config in progress...\n", OPP);

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_ABE)&0x1)
    {
        GEL_TextOut("\tABE DPLL OPP is already locked, now unlocking....\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_ABE);
    }

    // select sysclk as CLKINP (ABE cannot lock on CLK32K).
    WR_MEM_32(0x4AE0610C, 0x00000000);

    // Select sysclk1 (SYS_CLK2 = 22.5792) as the clock source for ABE PLL
    WR_MEM_32(0x4AE06118, 0x00000000);

    // DPLL MULT
    // Output = 451.584 MHz
    // Provides enough headroom so the McASP can evenly divide this down
    // to multiple different sampling rates as the module does not
    // contain a multiplier.
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_ABE) = 0xC809;
    WR_MEM_32(CM_CLKMODE_DPLL_ABE + 0x0C,0xC809);

    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_ABE) = 0x1;
    WR_MEM_32(CM_CLKMODE_DPLL_ABE + 0x10,0x1);
    //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_ABE) = 0x1;
    WR_MEM_32(CM_CLKMODE_DPLL_ABE + 0x14,0x1);

    dpll_lock_sequence(CM_CLKMODE_DPLL_ABE);

    GEL_TextOut("\tABE DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
 * dpll_iva_opp_config() : IVA DPLL OPP configurations
 *****************************************************************************/
void dpll_iva_opp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    uint32_t dpll_m, dpll_n, divm2;

    GEL_TextOut("\tIVA DPLL OPP %d clock config is in progress...\n", OPP);

    if(OPP_HIGH == OPP)
    {
        //532MHz at 20MHz sys_clk
        dpll_m = 266;
        dpll_n = 4;
        divm2  = 2;
    }
    else if(OPP_OD == OPP)
    {
        //430MHz at 20MHz sys_clk
        dpll_m = 172;
        dpll_n = 3;
        divm2  = 2;
    }
    else //default to OPP_NOM
    {
        //388.3MHz at 20MHz sys_clk
        dpll_m = 233;
        dpll_n = 3;
        divm2  = 3;
    }

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_IVA)&0x1)
    {
        GEL_TextOut("\tIVA DPLL already locked, now unlocking...\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_IVA);
    }

    /* CM_CLKSEL_DPLL_PER DPLL MULT */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_IVA) = ((dpll_m << 8) | dpll_n);
    WR_MEM_32(CM_CLKMODE_DPLL_IVA + 0x0C,((dpll_m << 8) | dpll_n));

    /* CM_DIV_M2_DPLL_IVA */
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_IVA) = divm2;
    WR_MEM_32(CM_CLKMODE_DPLL_IVA + 0x10,divm2);

    dpll_lock_sequence(CM_CLKMODE_DPLL_IVA);

    GEL_TextOut("\tIVA DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
 * dpll_gmac_config() : GMAC DPLL configuration
 *****************************************************************************/
void dpll_gmac_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    GEL_TextOut("\tGMAC DPLL OPP %d clock config is in progress...\n", OPP);

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_GMAC)&0x1)
    {
        GEL_TextOut("\tGMAC DPLL already locked, now unlocking....\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_GMAC);
    }

    /* CM_CLKSEL_DPLL_GMAC DPLL MULT */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_GMAC) = 0xFA04;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x0C,0xFA04);

    /* CM_DIV_M2_DPLL_GMAC */
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_GMAC) = 0x4;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x10,0x4);

    /* CM_DIV_M3_DPLL_GMAC  */
    //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_GMAC) = 0xA;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x14,0xA);

    /* CM_DIV_H11_DPLL_GMAC */
    //CM_DIV_H11_DPLL(CM_CLKMODE_DPLL_GMAC) = 0x28;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x18,0x28);

    /* CM_DIV_H12_DPLL_GMAC  */
    //CM_DIV_H12_DPLL(CM_CLKMODE_DPLL_GMAC) = 0x8;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x1C,0x8);

    /* CM_DIV_H13_DPLL_GMAC */
    //CM_DIV_H13_DPLL(CM_CLKMODE_DPLL_GMAC) = 0xA;
    WR_MEM_32(CM_CLKMODE_DPLL_GMAC + 0x20,0xA);

    dpll_lock_sequence(CM_CLKMODE_DPLL_GMAC);

    GEL_TextOut("\tGMAC DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
 * dpll_pcie_config() : PCIE DPLL configuration
 *****************************************************************************/
void dpll_pcie_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    uint32_t dpll_m, dpll_n, divm2;
    GEL_TextOut("\tPCIE_REF DPLL OPP %d clock config is in progress...\n", OPP);

    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_PCIE_REF)&0x1)
    {
        GEL_TextOut("\tPCIE_REF DPLL already locked, now unlocking....\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_PCIE_REF);
    }

    //100MHz output at 20MHz SYSCLK
    dpll_m = 750;
    dpll_n = 9;
    divm2  = 15;

    /* CM_CLKSEL_DPLL_GMAC DPLL MULT */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_PCIE_REF) = ((dpll_m << 8) | dpll_n);
    WR_MEM_32(CM_CLKMODE_DPLL_PCIE_REF + 0x0C,((dpll_m << 8) | dpll_n));

    /* CM_DIV_M2_DPLL_GMAC */
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_PCIE_REF) = divm2;
    WR_MEM_32(CM_CLKMODE_DPLL_PCIE_REF + 0x10,divm2);

    dpll_lock_sequence(CM_CLKMODE_DPLL_PCIE_REF);

    GEL_TextOut("\tPCIE_REF DPLL OPP %d is DONE!\n", OPP);
}

//menuitem "AM572x PRCM CLOCK Configuration - Common"
/******************************************************************************
 * dpll_ddr_config() : DDR DPLL OPP configurations
 *****************************************************************************/
void dpll_ddr_config_532()
{
    dpll_ddr_config(532);
}

void dpll_ddr_config_400()
{
    dpll_ddr_config(400);
}

void dpll_ddr_config(uint32_t DDR_FREQ)
{
    if (532 == DDR_FREQ)
    {
        GEL_TextOut("\tDDR DPLL clock config for %dMHz is in progress...\n", DDR_FREQ);

        if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_DDR)&0x1)
        {
            GEL_TextOut("\tDDR DPLL already locked, now unlocking....\n");
            dpll_unlock_sequence(CM_CLKMODE_DPLL_DDR);
        }
            /* CM_CLKSEL_DPLL_DDR DPLL MULT */
            //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_DDR) = 0x10A04;
            WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x0C,0x10A04);

            /* CM_DIV_M2_DPLL_DDR */
            //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_DDR) = 0x2;
            WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x10,0x2);

            /* CM_DIV_M3_DPLL_DDR  */
            //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_DDR) = 0x1;
            WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x14,0x1);

            /* CM_DIV_H11_DPLL_DDR */
            //CM_DIV_H11_DPLL(CM_CLKMODE_DPLL_DDR) = 0x8;
            WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x18,0x8);

            dpll_lock_sequence(CM_CLKMODE_DPLL_DDR);
            GEL_TextOut("\tDDR DPLL clock config for %dMHz is in DONE!\n", DDR_FREQ);
    }
    else if (400 == DDR_FREQ)
    {
        GEL_TextOut("\tDDR DPLL clock config for %dMHz is in progress...\n", DDR_FREQ);

        if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_DDR)&0x1)
        {
            GEL_TextOut("\tDDR DPLL already locked, now unlocking....\n");
            dpll_unlock_sequence(CM_CLKMODE_DPLL_DDR);
        }
            /* CM_CLKSEL_DPLL_DDR DPLL MULT */
            //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_DDR) = 0xC804; //((200 << 8) | (5-1));
        WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x0C,0xC804);

            /* CM_DIV_M2_DPLL_DDR */
            //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_DDR) = 0x2;
        WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x10,0x2);

            /* CM_DIV_M3_DPLL_DDR  */
            //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_DDR) = 0x1;
        WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x14,0x1);

            /* CM_DIV_H11_DPLL_DDR */
            //CM_DIV_H11_DPLL(CM_CLKMODE_DPLL_DDR) = 0x4;
        WR_MEM_32(CM_CLKMODE_DPLL_DDR + 0x18,0x4);

            dpll_lock_sequence(CM_CLKMODE_DPLL_DDR);

            GEL_TextOut("\tDDR DPLL clock config for %dMHz is in DONE!\n", DDR_FREQ);
    }
    else
    {
        GEL_TextOut("\tDDR DPLL frequency %dMHz not supported, nothing done.\n", DDR_FREQ);
    }
}

/******************************************************************************
 * dpll_gpu_config() : GPU DPLL OPP configurations
 *****************************************************************************/
void dpll_gpu_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    uint32_t dpll_m, dpll_n, divm2;

    GEL_TextOut("\tGPU DPLL OPP %d clock config is in progress...\n", OPP);

	if(OPP_HIGH == OPP)
	{
		//532MHz at 20MHz sys_clk
		dpll_m = 266;
		dpll_n = 4;
		divm2  = 2;
	}
	else if(OPP_OD == OPP)
	{
		//500MHz at 20MHz sys_clk
		dpll_m = 200;
		dpll_n = 3;
		divm2  = 2;
	}
	else //default to OPP_NOM
	{
		//425MHz at 20MHz sys_clk
		dpll_m = 170;
		dpll_n = 3;
		divm2  = 2;
	}


    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_GPU)&0x1)
    {
        GEL_TextOut("\tGPU DPLL already locked, now unlocking...\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_GPU);
    }

    /* CM_CLKSEL_DPLL DPLL MULT */
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_GPU) = ((dpll_m << 8) | dpll_n);
    WR_MEM_32(CM_CLKMODE_DPLL_GPU + 0x0C,((dpll_m << 8) | dpll_n));

    /* CM_DIV_M2_DPLL */
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_GPU) = divm2;
    WR_MEM_32(CM_CLKMODE_DPLL_GPU + 0x10,divm2);

    dpll_lock_sequence(CM_CLKMODE_DPLL_GPU);

    GEL_TextOut("\tGPU DPLL OPP %d is DONE!\n", OPP);
}

/******************************************************************************
 * dpll_dsp_config() : DSP DPLL OPP configurations
 *****************************************************************************/
void dpll_dsp_config(uint32_t OPP, uint32_t DEVICE_TYPE)
{
    uint32_t dpll_m, dpll_n, divm2;

    GEL_TextOut("\tDSP DPLL OPP %d clock config is in progress...\n", OPP);

	if(OPP_HIGH == OPP)
	{
		//750MHz at 20MHz sys_clk
		dpll_m = 150;
		dpll_n = 3;
		divm2  = 1;
	}
	else if(OPP_OD == OPP)
	{
		//650MHz at 20MHz sys_clk
		dpll_m = 130;
		dpll_n = 3;
		divm2  = 1;
	}
	else //default to OPP_NOM
	{
		//600MHz at 20MHz sys_clk
		dpll_m = 150;
		dpll_n = 4;
		divm2  = 1;
	}
    
    if (CM_IDLEST_DPLL(CM_CLKMODE_DPLL_DSP)&0x1)
    {
        GEL_TextOut("\tDSP DPLL already locked, now unlocking....\n");
        dpll_unlock_sequence(CM_CLKMODE_DPLL_DSP);
    }
    /* CM_CLKSEL_DPLL DPLL MULT */
    WR_MEM_32(CM_CLKMODE_DPLL_DSP + 0x0C,((dpll_m << 8) | dpll_n));
    //CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_DSP) = ((dpll_m << 8) | dpll_n);

    /* CM_DIV_M2_DPLL */
    WR_MEM_32(CM_CLKMODE_DPLL_DSP + 0x10,divm2);
    //CM_DIV_M2_DPLL(CM_CLKMODE_DPLL_DSP) = divm2;

    WR_MEM_32(CM_CLKMODE_DPLL_DSP + 0x14,0x3);
    /* CM_DIV_M3_DPLL - not used in default configuration */
    //CM_DIV_M3_DPLL(CM_CLKMODE_DPLL_DSP) = 0x3;

    dpll_lock_sequence(CM_CLKMODE_DPLL_DSP);

    GEL_TextOut("\tDSP DPLL OPP %d is DONE!\n", OPP);
}
#if 0
/******************************************************************************
 * dpll_bypass() : Put DPLL in bypass mode
 *****************************************************************************/
int32_t dpll_bypass(uint32_t base_address)
{
    uint32_t timer = DPLL_TIMEOUT;
    uint32_t clken_pll_value;

    // Put DPLL into bypass mode
    clken_pll_value = CM_CLKMODE_DPLL(base_address);
    clken_pll_value &= ~(7 << 0);
    clken_pll_value |= (4 << 0);
    CM_CLKMODE_DPLL(base_address) = clken_pll_value;

    // Wait for DPLL to be unlocked
    while ( ((CM_IDLEST_DPLL(base_address) & 0x1) == 0x1) && (timer--) );

    if (timer > 0)
    {
       return -1;
    }
    else
    {
        return 0;
    }
}
#endif
/******************************************************************************
 * dpll_lock_sequence() : DPLL lock sequence
 *****************************************************************************/
void dpll_lock_sequence(uint32_t base_address)
{
    int32_t timer = DPLL_TIMEOUT;

    // Put DPLL into lock mode
    //CM_CLKMODE_DPLL(base_address) = 7;
    WR_MEM_32(base_address,7);
    // Wait for DPLL to be locked
    while( ((CM_IDLEST_DPLL(base_address) & 0x1) != 0x1) && (timer--) );

    if (timer <= 0)
    {
        GEL_TextOut("\tERROR: timeout while locking DPLL \n");
    }
}

/******************************************************************************
 * dpll_unlock_sequence() : DPLL unlock sequence
 *****************************************************************************/
void dpll_unlock_sequence(uint32_t base_address)
{
    // Take DPLL out of lock mode
    //CM_CLKMODE_DPLL(base_address) &= ~0x1;
    UINT32 value = RD_MEM_32(base_address);
    WR_MEM_32(base_address,value & ~0x1);
}


#define GENERIC_DPLL_FDPLL           0x1000
#define GENERIC_DPLL_CLKOUT_M2       0x1001
#define GENERIC_DPLL_CLKOUTX2_M2     0x1002
#define GENERIC_DPLL_CLKOUTX2_M3     0x1003

void AM572x_PRCM_Clock_GetConfig ()
{
    uint32_t temp, ipu_clksel, core_fdpll, ipu1_clk, ipu2_clk;
    uint32_t gpu_core_clk, gpu_hyd_clk;

    GEL_TextOut("--->>> Reading DPLL configurations...<<<---\n");
    GEL_TextOut("       Frequency values are as per M/N/etc...\n");

    GEL_TextOut("\tMPU:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_MPU, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tCORE:\n");
    core_fdpll = dpll_get_clkout_speed(CM_CLKMODE_DPLL_CORE, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tABE:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_ABE, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tIVA:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_IVA, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tDDR:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_DDR, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tDSP:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_DSP, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tGMAC:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_GMAC, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tGPU:\n");
    gpu_core_clk = dpll_get_clkout_speed(CM_CLKMODE_DPLL_GPU, GENERIC_DPLL_FDPLL, 1);
    gpu_hyd_clk = dpll_get_clkout_speed(CM_CLKMODE_DPLL_GPU, GENERIC_DPLL_FDPLL, 0);

    GEL_TextOut("\tPER:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_PER, GENERIC_DPLL_FDPLL, 1);

    GEL_TextOut("\tPCIE:\n");
    dpll_get_clkout_speed(CM_CLKMODE_DPLL_PCIE_REF, GENERIC_DPLL_FDPLL, 1);


    GEL_TextOut("\tClock inputs to different modules:\n");
    temp = RD_MEM_32(IPU_CM_CORE_AON+IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL);
    ipu_clksel = (temp >> 24) & 0x1;
    if(ipu_clksel == 0)
    {
        ipu1_clk = dpll_get_clkout_speed(CM_CLKMODE_DPLL_ABE, GENERIC_DPLL_CLKOUTX2_M2, 1);
        GEL_TextOut("\t\tIPU1 functional clock is CLKOUTX2_M2 from ABE DPLL.\n");
    }
    else
    {
        GEL_TextOut("\t\tIPU1 functional clock is from CORE DPLL (CLKOUTX2_H22).\n");
        ipu1_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_CORE, CM_DIV_H22_DPLL(CM_CLKMODE_DPLL_CORE));
    }
    GEL_TextOut("\t\tIPU1 CPU speed is %d MHz\n\n", ipu1_clk/2);

    GEL_TextOut("\t\tIPU2 functional clock is from CORE DPLL (CLKOUTX2_H22).\n");
    ipu2_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_CORE, CM_DIV_H22_DPLL(CM_CLKMODE_DPLL_CORE));
    GEL_TextOut("\t\tIPU2 CPU speed is %d MHz\n\n", ipu2_clk/2);

    if(0x00000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x03000000))
    {
        gpu_core_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_CORE, CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_CORE));
        GEL_TextOut("\t\tGPU CORE clock is from CORE DPLL (CLKOUTX2_H14).\n");
    }
    if(0x01000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x03000000))
    {
        gpu_core_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_PER, CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_PER));
        GEL_TextOut("\t\tGPU CORE clock is from PER DPLL (CLKOUTX2_H14).\n");
    }
    if(0x02000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x03000000))
    {
        GEL_TextOut("\t\tGPU CORE clock is from GPU DPLL.\n");
    }
    GEL_TextOut("\t\tGPU CORE clock speed is %d MHz\n", gpu_core_clk);

    if(0x00000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x0C000000))
    {
        gpu_hyd_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_CORE, CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_CORE));
        GEL_TextOut("\t\tGPU HYD clock is from CORE DPLL (CLKOUTX2_H14).\n");
    }
    if(0x04000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x0C000000))
    {
        gpu_hyd_clk = dpll_get_clkout_speed_hsdiv(CM_CLKMODE_DPLL_PER, CM_DIV_H14_DPLL(CM_CLKMODE_DPLL_PER));
        GEL_TextOut("\t\tGPU HYD clock is from PER DPLL (CLKOUTX2_H14).\n");
    }
    if(0x08000000 == (RD_MEM_32(GPU_CM_CORE + GPU_CM_CORE__CM_GPU_GPU_CLKCTRL) & 0x0C000000))
    {
        GEL_TextOut("\t\tGPU HYD clock is from GPU DPLL.\n");
    }
    GEL_TextOut("\t\tGPU HYD clock speed is %d MHz\n", gpu_hyd_clk);

    GEL_TextOut("--->>> Reading DPLL configurations...done<<<---\n");
}

uint32_t dpll_get_clkout_speed(uint32_t base_address, uint32_t return_clk, uint32_t print_enable)
{
    uint32_t temp, dpll_div_n, dpll_div_m, dpll_div_m2, f_dpll;
    uint32_t clkst_clkout_M2, clkst_clkoutX2_M2, clkout_M2, clkoutX2_M2;
    uint32_t dpll_div_m3, clkst_clkoutX2_M3, clkoutX2_M3;
    temp = CM_CLKSEL_DPLL(base_address);
    dpll_div_n = temp & 0x7F;
    dpll_div_m = (temp >> 8) & 0x7FF;
    f_dpll = (SYS_CLK1*dpll_div_m)/(dpll_div_n+1);

    temp = CM_DIV_M2_DPLL(base_address);
    dpll_div_m2 = temp & 0x1F;
    clkst_clkout_M2 = (temp >> 9) & 0x1;
    clkst_clkoutX2_M2 = (temp >> 11) & 0x1;

    temp = CM_DIV_M3_DPLL(base_address);
    dpll_div_m3 = temp & 0x1F;
    clkst_clkoutX2_M3 = (temp >> 9) & 0x1;

    f_dpll = (2*SYS_CLK1*dpll_div_m)/(dpll_div_n+1);

    if(CM_CLKMODE_DPLL_ABE == base_address)
    {
        temp = CM_CLKMODE_DPLL(CM_CLKMODE_DPLL_ABE);
        temp = ((temp >> 11) & 0x1); /* DPLL_REGM4XEN */
        if(temp)
        {
            f_dpll = f_dpll*4;
        }
    }

    if(CM_CLKMODE_DPLL_MPU == base_address)
    {
        temp = CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_MPU);
        temp = ((temp >> 22) & 0x1); /* DCC_EN */
        if(temp)
        {
            f_dpll = f_dpll/2;
        }
    }

    clkout_M2 = f_dpll/(dpll_div_m2*2);
    if(CM_CLKMODE_DPLL_MPU == base_address)
    {
        temp = CM_CLKSEL_DPLL(CM_CLKMODE_DPLL_MPU);
        temp = ((temp >> 22) & 0x1); /* DCC_EN */
        if(temp)
        {
            clkout_M2 = f_dpll/(dpll_div_m2);
        }
    }

    clkoutX2_M2 = f_dpll/dpll_div_m2;

    if(0 == dpll_div_m3)
    {
        clkoutX2_M3 = 0;
    }
    else
    {
        clkoutX2_M3 = f_dpll/dpll_div_m3;
    }

    temp = CM_CLKMODE_DPLL(base_address);
    temp = temp & 0x7;
    if(print_enable)
    {
        if (0x5 == temp)
        {
            GEL_TextOut("\t\tDPLL in IDLE_BYPASS_LOW_POWER mode\n");
        }
        if (0x6 == temp)
        {
            GEL_TextOut("\t\tDPLL in IDLE_BYPASS_FAST_RELOCK mode\n");
        }
        if (0x7 == temp)
        {
            GEL_TextOut("\t\tDPLL in LOCK_MODE mode\n");
        }
    }

    if(print_enable)
    {
        GEL_TextOut("\t\tDPLL CLKOUT_M2 speed is %d MHz\n", clkout_M2);
        if(0 == clkst_clkout_M2)
        {
            GEL_TextOut("\t\tDPLL CLKOUT_M2 is GATED\n\n");
            clkout_M2 = 0;
        }
        else
        {
            GEL_TextOut("\t\tDPLL CLKOUT_M2 is ACTIVE\n\n");
        }


        //GEL_TextOut("\t\tDPLL CLKOUTX2_M2 speed is %d MHz\n", clkoutX2_M2);
        if(0 == clkst_clkoutX2_M2)
        {
            //GEL_TextOut("\t\tDPLL CLKOUTX2_M2 is GATED\n\n",);
            clkoutX2_M2 = 0;
        }
        else
        {
            //GEL_TextOut("\t\tDPLL CLKOUTX2_M2 is ACTIVE\n\n",);
        }

        //GEL_TextOut("\t\tDPLL CLKOUTX2_M3 speed is %d MHz\n", clkoutX2_M3);
        if(0 == clkst_clkoutX2_M3)
        {
            //GEL_TextOut("\t\tDPLL CLKOUTX2_M3 is GATED\n\n",);
            clkoutX2_M3 = 0;
        }
        else
        {
            //GEL_TextOut("\t\tDPLL CLKOUTX2_M3 is ACTIVE\n\n",);
        }
    }

    if(GENERIC_DPLL_CLKOUTX2_M3 == return_clk)
    {
        return clkoutX2_M3;
    }
    else if(GENERIC_DPLL_CLKOUTX2_M2 == return_clk)
    {
        return clkoutX2_M2;
    }
    else if(GENERIC_DPLL_CLKOUT_M2 == return_clk)
    {
        return clkout_M2;
    }
    else
    {
        return f_dpll;
    }
}

uint32_t dpll_get_clkout_speed_hsdiv(uint32_t base_address, uint32_t divider_val)
{
    uint32_t divhs, clkst, f_dpll, f_divhs;
    f_dpll = dpll_get_clkout_speed(base_address, GENERIC_DPLL_FDPLL, 0);
    divhs = divider_val & 0x3F;
    clkst = (divider_val >> 9) & 0x1;
    if(clkst)
    {
        f_divhs = f_dpll/(divhs);
    }
    else
    {
        f_divhs = 0;
    }
    return f_divhs;
}
#if 0
float convertTemp(float device_temp)
{
    float temperature = 0.0;
    int temp = 0;
    if (device_temp - 833 > 0)
    {
        temperature = 0.40470 * (device_temp - 833) + 80.6;
    }
    else if (device_temp - 735.721 > 0)
    {
        temperature = 0.41196 * (device_temp - 735.721) + 40.6;
    }
    else if (device_temp - 639.875 > 0)
    {
        temperature = 0.41820 * (device_temp - 639.875) + 0.6;
    }
    else
    {
        temperature = 0.41820 * (device_temp - 639.875) + 0.6;
    }

    return temperature;
}

//menuitem "Temperature Sensor Readings"
void Readout_Temperatures()
{
    float device_temp;
    float temperature;
    float factor=10;

    device_temp = (RD_MEM_32(0x4A00232C) & 0x03FF);
    temperature = convertTemp(device_temp);
    GEL_TextOut("MPU Temperature:    %f degC\n",temperature);

    device_temp = (RD_MEM_32(0x4A002330) & 0x03FF);
    temperature = convertTemp(device_temp);
    GEL_TextOut("GPU Temperature:    %f degC\n",temperature);

    device_temp = (RD_MEM_32(0x4A002334) & 0x03FF);
    temperature = convertTemp(device_temp);
    GEL_TextOut("CORE Temperature:   %f degC\n",temperature);

    device_temp = (RD_MEM_32(0x4A002578) & 0x03FF);
    temperature = convertTemp(device_temp);
    GEL_TextOut("IVA Temperature:    %f degC\n",temperature);
}
#endif