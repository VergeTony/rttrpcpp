#pragma once
#include <cstdio>
#include <cstring>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#if defined(RTTRPCPP_LOG_FILENAME)

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if RTTRPCPP_LOG_LEVEL == 0
#  define log_debug(fmt, ...) ((void)0)
#  define log_info(fmt, ...) ((void)0)
#elif RTTRPCPP_LOG_LEVEL == 1
#  define log_debug(fmt, ...) ((void)0)
#  define log_info(fmt, ...) printf(ANSI_COLOR_BLUE "INFO [%s:%i] " ANSI_COLOR_RESET fmt "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#elif RTTRPCPP_LOG_LEVEL == 2
#  define log_debug(fmt, ...) printf(ANSI_COLOR_MAGENTA "DBG [%s:%i] " ANSI_COLOR_RESET fmt "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#  define log_info(fmt, ...) printf(ANSI_COLOR_BLUE "INFO [%s:%i] " ANSI_COLOR_RESET fmt "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#endif

#else

#if RTTRPCPP_LOG_LEVEL == 0
#  define log_debug(fmt, ...) ((void)0)
#  define log_info(fmt, ...) ((void)0)
#elif RTTRPCPP_LOG_LEVEL == 1
#  define log_debug(fmt, ...) ((void)0)
#  define log_info(fmt, ...) printf(ANSI_COLOR_BLUE "INFO " ANSI_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#elif RTTRPCPP_LOG_LEVEL == 2
#  define log_debug(fmt, ...) printf(ANSI_COLOR_MAGENTA "DBG " ANSI_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#  define log_info(fmt, ...) printf(ANSI_COLOR_BLUE "INFO " ANSI_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#endif

#endif