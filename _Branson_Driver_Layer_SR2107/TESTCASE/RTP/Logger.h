#ifndef LOGGER_H_
#define LOGGER_H_

#include <customSystemCall.h>


#define LOG_LEVEL  	4
#define LOGFILE 	1

#define LOGCRIT(str,arg1, arg2, arg3) logCRIT(str, __LINE__,  __FILE__, LOG_LEVEL, LOGFILE, arg1, arg2, arg3)
#define LOGERR(str,arg1, arg2, arg3)  logERR(str, __LINE__,  __FILE__, LOG_LEVEL, LOGFILE,  arg1, arg2, arg3)
#define LOGWARN(str,arg1, arg2, arg3) logWARN(str, __LINE__,  __FILE__, LOG_LEVEL, LOGFILE, arg1, arg2, arg3)
#define LOGDBG(str,arg1, arg2, arg3)  logDBG(str, __LINE__,  __FILE__, LOG_LEVEL, LOGFILE,  arg1, arg2, arg3)

#endif /* LOGGER_H_ */
