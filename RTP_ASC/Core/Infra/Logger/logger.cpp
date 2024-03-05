/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/

/*
 * Revision History
 * 1. Interface definition / dummy implementation,  27 Feb 2023
 */

#include "logger.h"
#include <string>
#include <iostream>
#include <tickLib.h>


// Dummy implementation of logger entry function
int logger::add_entry(const size_t log_id, const SEVERITY severity, const uint8_t * const data, const uint8_t data_size)
{
	int return_val = -1; // default return value

	// Check if parameters are valid
	if((data!=NULL) && (data_size<buff_size_config))
	{
	// log on standard output for now
	std::string str = (char*)data;
	std::cout << "Logger:" << " T:"<< std::dec << tick64Get() << " ID:" << std::hex << log_id << " S:" << severity << " D:" << str << std::endl;
	return_val = 0;
	}
	
	return (return_val);
}

