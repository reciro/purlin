#ifndef COMMONS
#define COMMONS

#ifndef INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <ftw.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#endif

#ifndef DEFINE
#define ll long long 
#define ull unsigned long long 
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef DEFINE_ENUM
// Defines the log statement level/severity
typedef enum {
    INFO_LEVEL,
    WARNING_LEVEL,
    ERROR_LEVEL,
} PRINT_LOG_LEVEL;
#endif

#ifndef FUNCTION_DEF
void log_print(PRINT_LOG_LEVEL log_level, char* msg);
#endif

void log_print(PRINT_LOG_LEVEL log_level, char* msg) {
    switch ( log_level ) {
        case INFO_LEVEL: printf("[INFO] %s\n", msg);
        case WARNING_LEVEL: printf("[WARNING] %s\n", msg);
        case ERROR_LEVEL: printf("[ERROR] %s\n", msg);
    }
}

#endif
