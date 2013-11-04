#ifndef __dbg_h__
#define __dbg_h__

/**
  * Adapted from Zed's Awesome Debug Macros:
  * http://c.learncodethehardway.org/book/ex20.html
  * Compile with -DNLOG_SUFFIX where
  * SUFFIX is the type of log to be supressed: DEBUG, INFO, WARN, ERR
  * Compile with -DNLOG_ALL to supress all log types
  * Compile with -DNTIME to suppress time
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef NLOG_ALL
/* This smells bad... */
#include <time.h>

static char buffer[27];

static char* get_time() {
#ifdef NTIME
	buffer[0] = '\0';
#else
	time_t timer;
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 27, "[%Y:%m:%d %H:%M:%S]", tm_info);
#endif
	return buffer;
}
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR]%s (%s:%d: errno: %s) " M "\n", get_time(), __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN]%s (%s:%d: errno: %s) " M "\n", get_time(), __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO]%s (%s:%d) " M "\n", get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

#define log_debug(M, ...) fprintf(stderr, "[DEBUG]%s (%s:%d) " M "\n", get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#ifdef NLOG_ERR
	#undef log_err
	#define log_err(M, ...)
#endif
#ifdef NLOG_WARN
	#undef log_warn
	#define log_warn(M, ...)
#endif
#ifdef NLOG_INFO
	#undef log_info
	#define log_info(M, ...)
#endif
#ifdef NLOG_DEBUG
	#undef log_debug
	#define log_debug(M, ...)
#endif

#ifdef NLOG_ALL
	#undef log_err
	#undef log_warn
	#undef log_info
	#undef log_debug
	#define log_err(M, ...)
	#define log_warn(M, ...)
	#define log_info(M, ...)
	#define log_debug(M, ...)
#endif

#endif

