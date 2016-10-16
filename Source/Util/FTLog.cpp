#include "FTLog.h"
#include <stdio.h>


#include <mutex>

// This is to prevent corruption when printing from multiple threads
static std::mutex log_mutex;

#ifdef _MSC_VER
#include <Windows.h>
#define LOG_BUFFER_SIZE 1024
static char log_buffer[LOG_BUFFER_SIZE];
#endif



void FTLogPrint(const char* prefix, bool print_new_line, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_mutex.lock();
#if defined(_MSC_VER)
    _vsnprintf_s(log_buffer, sizeof(log_buffer), LOG_BUFFER_SIZE, format, args);

    OutputDebugStringA(prefix);
    OutputDebugStringA(log_buffer);
    if (print_new_line)
        OutputDebugStringA("\n");

#else
    printf("%s", prefix);
	vprintf(format, args);
    if (print_new_line)
	    printf("\n");
#endif
    log_mutex.unlock();
    va_end(args);
}
