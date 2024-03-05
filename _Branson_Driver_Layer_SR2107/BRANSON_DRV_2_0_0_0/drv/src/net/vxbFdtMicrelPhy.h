/* vxbFdtMicrelPhy.h - header file for micrel phy driver */

/*
 * Copyright (c) 2014-2016, 2019 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22feb19,gqn  ping lost issue fix (V7NET-2317)
28mar16,wap  Fix parameter handling
17aug15,m_w  support dynamic skew pad config of ksz9021. (V7PRO-2344)
02sep14,m_w  add support for ksz9031.(US40646)
20aug14,m_w  written (V7PRO-1195)
*/

#ifndef __INCvxbMicrelPhyh
#define __INCvxbMicrelPhyh

#ifdef __cplusplus
extern "C" {
#endif

/* PHY ID of Micrel */

#define MICREL_OUI_ID           0x00000885  /* MICREL PHY OUI ID */
#define PHY_ID_KSZ9021          0x0021      /* ksz9021 mode number */
#define PHY_ID_KSZ9031          0x0022      /* ksz9031 mode number */

#define MICREL_SKEW_NONE	    0xFFFFFFFF
#define MICREL_PHYCON1_REG      0x1e
#define MICREL_PHYCON1_LEDACT   (1U << 14)


/*-------------------------- ksz9021 --------------------------*/

#define KSZ9021_EXTREG_WRITE_FLAG               0x8000
#define KSZ9021_EXTREG_CTRL                     0x0b
#define KSZ9021_EXTREG_DATA_WRITE               0x0c
#define KSZ9021_EXTREG_DATA_READ                0x0d

/* extended skew registers */

#define KSZ9021_CLK_CTRL_PAD_SKEW               0x104
#define KSZ9021_RX_DATA_PAD_SKEW                0x105
#define KSZ9021_TX_DATA_PAD_SKEW                0x106

#define KSZ9021_RXC_PAD_SKEW_OFST               12
#define KSZ9021_RXDV_PAD_SKEW_OFST              8
#define KSZ9021_TXC_PAD_SKEW_OFST               4
#define KSZ9021_TXEN_PAD_SKEW_OFST              0

/*
 * for ksz9021, skew control options are specified in picoseconds,
 * the minimum value is 0, the maximum value is 3000, 
 * and it is incremented by 200ps steps.
 */

#define KSZ9021_PS_TO_REG                       200

/*-------------------------- ksz9031 --------------------------*/

#define KSZ9031RN_MMD_CTRL_REG                  0x0d
#define KSZ9031RN_MMD_REGDATA_REG               0x0e
#define KSZ9031_OP_DATA                         1

/* extended skew registers */

#define KSZ9031RN_CTRL_PAD_SKEW                 4
#define KSZ9031RN_RX_DATA_PAD_SKEW              5
#define KSZ9031RN_TX_DATA_PAD_SKEW              6
#define KSZ9031RN_CLK_PAD_SKEW                  8

/*
 * for ksz9031, skew control options are specified in picoseconds,
 * the minimum value is 0, and it is incremented by 60ps steps,
 * and the maximum is property-dependent,
 * these properties has the maximum value of 1860:
 *
 *  - rxc-skew-ps  : Skew control of RX clock pad
 *  - txc-skew-ps  : Skew control of TX clock pad
 *
 * these properties has the maximum value of 900:
 *
 *  - rxdv-skew-ps : Skew control of RX CTL pad
 *  - txen-skew-ps : Skew control of TX CTL pad
 *  - rxd0-skew-ps : Skew control of RX data 0 pad
 *  - rxd1-skew-ps : Skew control of RX data 1 pad
 *  - rxd2-skew-ps : Skew control of RX data 2 pad
 *  - rxd3-skew-ps : Skew control of RX data 3 pad
 *  - txd0-skew-ps : Skew control of TX data 0 pad
 *  - txd1-skew-ps : Skew control of TX data 1 pad
 *  - txd2-skew-ps : Skew control of TX data 2 pad
 *  - txd3-skew-ps : Skew control of TX data 3 pad
 */

#define KSZ9031_PS_TO_REG                       60

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbMicrelPhyh */

