/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
 /*--------------------------- MODULE DESCRIPTION ---------------------------
 // This is the unit testing include file.  All these macros expand to no code in application build, and to executable
code during unit testing.
 Module name: TestMacros
 File name: TestMacros.h
 -------------------------- TECHNICAL NOTES --------------------------------*/


#ifndef TESTMACROS_H_
#define TESTMACROS_H_

#include <stdio.h>


#define UNIT_TESTING 0

// All these macros expand to no code in application build, and to executable
// code during unit testing.

// This macro defines a variable that will be only used for unit testing code.
#define UT_VARIABLE(x) x;

// Print a checkpoint number if the variable is non-zero. Macro is used to run
// multiple function tests in same module without having to compile different
// code for every function. do-while executes once, and it does not confuse
// Eclipse CDT syntax highlighter and formatter.
#define CHECKPOINT(var,number) \
		if (var) { \
			DiagCheckpoint(number); \
		}

// Print the function name (which is part of the format) and function
// parameters using given format, but only if the variable is non-zero. Macro
// is used for diagnostics output when a specific function is being tested
// separately before being included in higher level test.
#define FUNCTION(var,format,...) \
		if (var) { \
			printf(format, __VA_ARGS__); \
		}

// Same as FUNCTION, but for functions with no parameters.
#define FUNCTION1(var,format) \
		if (var) { \
			PrintfEnabled = true; \
			printf(format); \
			PrintfEnabled = false; \
		}

// Insert a fault if variable reaches zero.
#define FAULT(var,code) \
		if (var >= 0) { \
			if (var-- == 0) { \
				code \
			} \
		}

#endif
