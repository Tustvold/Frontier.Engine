#include "FTLog.h"
#include <stdio.h>

#define USE_VS_CONSOLE
#define LOG_BUFFER_SIZE 1024

#ifdef WIN32
#include <Windows.h>
#include <mutex>

// This is to prevent corruption when printing from multiple threads
static std::mutex log_mutex;
static char log_buffer[LOG_BUFFER_SIZE];

void FTLogPrint(bool print_new_line, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_mutex.lock();
#ifdef USE_VS_CONSOLE


    _vsnprintf_s(log_buffer, sizeof(log_buffer), LOG_BUFFER_SIZE, format, args);

    OutputDebugStringA(log_buffer);
    if (print_new_line)
        OutputDebugStringA("\n");

#else
	vprintf(format, args);
    if (print_new_line)
	    printf("\n");
#endif
    log_mutex.unlock();
    va_end(args);
}
#endif
