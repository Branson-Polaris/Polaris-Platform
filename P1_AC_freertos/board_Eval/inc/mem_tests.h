/*
 * @brief    Generic memory tests
 *           Various memory tests for testing external memory integrity. Includes
 *           inverse address, walking bit, and pattern tests.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
#ifdef PRODUCTION
#else

#ifndef __MEM_TESTS_H_
#define __MEM_TESTS_H_

#include "../../chip/inc/lpc_types.h"

/** @defgroup BOARD_Memory_Tests BOARD: Various RAM memory tests
 * @ingroup BOARD_Common
 * @{
 */

/**
 * @brief Memory test address/size and result structure
 */
typedef struct {
	uint32_t *start_addr;	/*!< Starting address for memory test */
	uint32_t bytes;			/*!< Size in bytes for memory test */
	uint32_t *fail_addr;	/*!< Failed address of test (returned only if failed) */
	uint32_t is_val;		/*!< Failed value of test (returned only if failed) */
	uint32_t ex_val;		/*!< Expected value of test (returned only if failed) */
} MEM_TEST_SETUP_T;

/**
 * @brief	Walking 0 memory test
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @return	true if the test passed, or false on failure
 * @note	Writes a shifting 0 bit pattern to the entire memory range and
 * verifies the result after all memory locations are written
 */
bool mem_test_walking0(MEM_TEST_SETUP_T *pMemSetup);

/**
 * @brief	Walking 1 memory test
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @return	true if the test passed, or false on failure
 * @note	Writes a shifting 1 bit pattern to the entire memory range and
 * verifies the result after all memory locations are written
 */
bool mem_test_walking1(MEM_TEST_SETUP_T *pMemSetup);

/**
 * @brief	Address memory test
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @return	true if the test passed, or false on failure
 * @note	Writes the address to each memory location and verifies the
 * result after all memory locations are written
 */
bool mem_test_address(MEM_TEST_SETUP_T *pMemSetup);

/**
 * @brief	Inverse address memory test
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @return	true if the test passed, or false on failure
 * @note	Writes the inverse address to each memory location and verifies the
 * result after all memory locations are written
 */
bool mem_test_invaddress(MEM_TEST_SETUP_T *pMemSetup);

/**
 * @brief	Pattern memory test
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @return	true if the test passed, or false on failure
 * @note	Writes the an alternating 0x55/0xAA pattern to each memory location
 * and verifies the result after all memory locations are written
 */
bool mem_test_pattern(MEM_TEST_SETUP_T *pMemSetup);

/**
 * @brief	Pattern memory test with seed and increment value
 * @param	pMemSetup	: Memory test setup (and returned results)
 * @param	seed		: Initial seed value for test
 * @param	incr		: Increment value for each memory location
 * @return	true if the test passed, or false on failure
 * @note	Writes the an alternating pattern to each memory location based on a
 * passed seed and increment value and verifies the result after all
 * memory locations are written
 */
bool mem_test_pattern_seed(MEM_TEST_SETUP_T *pMemSetup, uint32_t seed, uint32_t incr);

/**
 * @}
 */

#endif /* __MEM_TESTS_H_ */
#endif /*PRODUCTION*/
