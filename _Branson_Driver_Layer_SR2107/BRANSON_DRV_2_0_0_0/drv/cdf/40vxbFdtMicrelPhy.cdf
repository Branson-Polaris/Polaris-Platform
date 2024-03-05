/* 10mii.cdf - mii bus CDF file */

/*
 * Copyright (c) 2013-2017, 2019-2020 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
12may20,gqn  moves Ti Tda4 MCU switch driver to psl (V7NET-2751)
11may20,cya  add INCLUDE_AQUANTIA_PHY for ls2088 (VXWEXEC-49101)
20jan20,gqn  add support for Ti DA4 MCU switch (VXWPG-449)
08oct19,gqn  add dependency for miiMonitorTask to INCLUDE_END (V7NET-2603)
23aug19,hma  add INCLUDE_MV643XX_MDIO for wrSbc750(VXWPG-340)
31may19,tcw  Correct the INCLUDE_MII_FDT_SYS dependency (V7NET-2276)
20may19,gqn  added nxp enetc mdio (VXWPG-118)
31oct17,g_x  added INCLUDE_MARVELL_PHY (V7PRO-4024)
19dec16,swu  added TI DP83867IR support (F7388)
11oct16,g_x  Add INCLUDE_RTL8211PHY. (F6411)
28mar16,wap  Update component names for improved readability
15mar16,wap  Add INCLUDE_GENERICMMDPHY and INCLUDE_FSLSGMII_PHY (F1921)
13oct15,fao  add INCLUDE_RTL8169PHY (US65600)
26aug15,m_w  added INCLUDE_MII_MONITOR_TASK. (V7PRO-2370)
10oct14,y_y  add INCLUDE_BITBANG_MDIO,INCLUDE_BCM52XXPHY (US41759)
22sep14,m_w  add INCLUDE_MICREL_PHY (V7PRO-1195)
27aug14,sye  added INCLUDE_AR803X_PHY. (US44767)
22aug14,yjw  add freescale FEC MDIO (US40534)
06jun14,fao  remove DRV_QORIQMEMAC_MDIO (V7PRO-972)
12may14,l_z  add GEI support. (US33490)
25apr14,fao  correct the components INCLUDE_DUMMY_MDIO and
             INCLUDE_TSEC_MDIO.
09apr14,ylu  changed the MODULES of INCLUDE_GENERICPHY.
23jan14,ylu  fixed coverity and compling issues.
20dec13,hll  Add _CHILDREN for INCLUDE_GENERICPHY, INCLUDE_DUMMY_MDIO and
             INCLUDE_TSEC_MDIO.(VXW7-1219)
23may13,x_z  created
*/

Component   INCLUDE_FDT_MICREL_PHY {
        NAME            Branson Micrel PHY driver
        SYNOPSIS        This component implements the VxBus driver for a Micrel PHY \
                        device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbFdtMicrelPhy.o
        LINK_SYMS       fdtMicrelPhyDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

