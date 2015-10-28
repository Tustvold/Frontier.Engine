#include <stdarg.h>

#define FTLog(...) FTLogPrint("Info: ", true, __VA_ARGS__);

#define FTLogWarn(...) FTLogPrint("Warning: ", true, __VA_ARGS__);

#define FTLogError(...) FTLogPrint("Error: ", true, __VA_ARGS__);

#define FTLOG(...) FTLog(__VA_ARGS__)

void FTLogPrint(const char* prefix, bool print_new_line, const char* format, ...);
