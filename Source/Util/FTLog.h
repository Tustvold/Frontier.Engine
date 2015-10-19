#include <stdarg.h>

#define FTLog(format, ...) FTLogPrint("Info: ", true, format, __VA_ARGS__);

#define FTLogWarn(format, ...) FTLogPrint("Warning: ", true, format, __VA_ARGS__);

#define FTLogError(format, ...) FTLogPrint("Error: ", true, format, __VA_ARGS__);

#define FTLOG(...) FTLog(__VA_ARGS__)

void FTLogPrint(const char* prefix, bool print_new_line, const char* format, ...);
