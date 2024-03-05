#ifndef __TEST_DEF_H
#define __TEST_DEF_H

#include <stdio.h>
#include <string.h>
#include <customSystemCall.h>
#include "Logger.h"
/* GPIO */

#define GPIO_PIN                0xB3 /* GPIO_6_19 */

/* GPIO IRQ attribute(refer to INTR_TRIGGER/INTR_POLARITY defines of vxbIntLib.h)*/

#define GPIO_PIN_INTR_TRIG      INTR_TRIGGER_EDGE /* do not change the way of trigger */
#define GPIO_PIN_INTR_POL       INTR_POLARITY_LOW /* do not change interrupt polarity */

/* direction */

#define GPIO_DIR_INPUT          (0)
#define GPIO_DIR_OUTPUT         (1)

/* value */

#define GPIO_VALUE_LOW          (0)
#define GPIO_VALUE_HIGH         (1)
#define GPIO_VALUE_INVALID      (0xff)

/* QSPI FLASH */

#define QSPI_FLASH_DATA_OFFSET  (31 * 1024 * 1024)  /* 64MB total */
#define QSPI_FLASH_DATA_SIZE    (2 * 64 * 1024) /* 2 blocks*/

IMPORT STATUS rtc_test(void);
IMPORT STATUS gpio_test(void);
IMPORT STATUS spi_test(void);
IMPORT STATUS qspi_test(void);
IMPORT STATUS auxClk_test(void);
IMPORT STATUS logger_test(void);

IMPORT void TimerEventSc_Handler(void);
IMPORT void GpioEventSc_Handler (void);

IMPORT void test_buf_dump(UINT8 *buf, UINT32 len);

#endif /* __TEST_DEF_H */
