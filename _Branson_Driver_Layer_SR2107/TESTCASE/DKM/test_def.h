#ifndef __TEST_DEF_H
#define __TEST_DEF_H

#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */

#include <vxWorks.h>
#include <stdio.h>
#include <sioLib.h>
#include <string.h>
#include <taskLib.h>

/* CPSW MAC / PHY */

#define CPSW_MAC0_DEV_NAME          "cpsw0"
#define CPSW_MAC1_DEV_NAME          "cpsw1"

/* USB Mass Storage */

#define USB_DISK_DEV_NAME           "/bd0a"
#define USB_DISK_FILE_SIZE          0x100000

/* GPIO */

#define GPIO_PIN                    0xB3 /* GPIO_6_19 */

/* GPIO IRQ attribute(refer to INTR_TRIGGER/INTR_POLARITY defines of vxbIntLib.h)*/

#define GPIO_PIN_INTR_TRIG          INTR_TRIGGER_EDGE /* do not change the way of trigger */
#define GPIO_PIN_INTR_POL           INTR_POLARITY_LOW /* do not change interrupt polarity */

/* MMC1/SD Storage */

#define MMC1_SD_DEV_NAME            "/sd0a"
#define MMC1_SD_FILE_SIZE           0x100000

/* EEPROM */

#define EEPROM_DEV_NAME             "/eeprom/0"
#define EEPROM_DATA_START_ADDR      0
#define EEPROM_DATA_SIZE            256

/* McSPI */

/* QSPI FLASH */

#define QSPI_FLASH_DATA_OFFSET      (31 * 1024 * 1024)  /* must be aligned with block size */
#define QSPI_FLASH_DATA_BLK_CNT     2 /* block count */
#define QSPI_FLASH_DATA_BLK_SIZE    (64 * 1024) /* block size */
#define QSPI_FLASH_DATA_SIZE        (QSPI_FLASH_DATA_BLK_CNT * QSPI_FLASH_DATA_BLK_SIZE) /* total siz */

/* MMC2/eMMC Storage */

#define MMC2_EMMC_DEV_NAME          "/mmc1"
#define MMC2_EMMC_FILE_SIZE         0x100000

IMPORT STATUS edma_test(void);
IMPORT STATUS usb_test(void);
IMPORT STATUS gpio_test(void);
IMPORT STATUS mmc1_sd_test(void);
IMPORT STATUS eeprom_test(void);
IMPORT STATUS rtc_test(void);
IMPORT STATUS spi2_test(void);
IMPORT STATUS spi4_test(void);
IMPORT STATUS qspi_test(void);
IMPORT STATUS mmc2_emmc_test(void);

IMPORT void test_buf_dump(UINT8 *buf, UINT32 len);

#endif /* __TEST_DEF_H */
