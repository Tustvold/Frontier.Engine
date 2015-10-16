#include <stdarg.h>

#define FTLog(format, ...) {FTLogPrint(false, "Info: "); \
    FTLogPrint(true, format, __VA_ARGS__);}

#define FTLogWarn(format, ...) {FTLogPrint(false, "Warning: "); \
    FTLogPrint(true, format, __VA_ARGS__);}

#define FTLogError(format, ...) {FTLogPrint(false, "Error: "); \
    FTLogPrint(true, format, __VA_ARGS__);}

#define FTLOG(...) FTLog(__VA_ARGS__)

void FTLogPrint(bool print_new_line, const char* format, ...);
