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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

// Definition of severity for logger
typedef enum{
	LOG_DEBUG = 1,     // use for debug purpose, lowest severity
	LOG_GENERAL_INFO,  // use this for general information, Low severity
	LOG_NOTIFICATION,  // use this for notifications, medium severity
	LOG_EVENT,         // use this for important events in the system, high severity
	LOG_ALARM          // use this for alarms or errors generated in the system, highest severity
}SEVERITY;

// Static configuration for buffer size used for logging
constexpr uint8_t buff_size_config = 16;

// Definition of Logger entry object
typedef struct{
	size_t log_id;      // identifier for log entry
	SEVERITY severity;  // severity of the entry
	uint64_t timestamp; // time-stamp of the entry (in nsec)
	uint8_t buffer[buff_size_config];  // buffer for storing log information
}entry;

// Definition of logger class interface
class logger{
public:
	// user needs to enroll to use logging functionality. "enroll" returns the unique ID based on class type.
	template <typename T>
	static std::size_t enroll(const T *class_type);

	// use "add_entry" function to add new entry to log, requires unique id received during "enroll"
	static int add_entry(const size_t log_id, const SEVERITY severity, const uint8_t * const data, const uint8_t data_size);
};

// Dummy implementation of logger enroll function
template <typename T>
std::size_t logger::enroll(const T *class_type)
{
	// get hash code of the caller's object, we will use this to uniquely identify caller's object. 
	std::size_t hash_code = typeid(*class_type).hash_code();

	// print on standard output for now
	std::cout << "Logger: Enroll: " << typeid(*class_type).name() << ":" << std::hex << hash_code << std::endl;

	return (hash_code);
}

#endif /* LOGGER_H_ */
