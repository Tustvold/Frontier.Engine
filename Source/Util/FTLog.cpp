#include "FTLog.h"
#include <stdio.h>

#ifdef WIN32
#include <Windows.h>

#define USE_VS_CONSOLE

void FTLogPrint(const char* prefix, const char* format, va_list args) {
#ifdef USE_VS_CONSOLE
    char buff[1024];

    _vsnprintf_s(buff, sizeof(buff), 1024, format, args);

    OutputDebugStringA(prefix);
    OutputDebugStringA(buff);
    OutputDebugStringA("\n");

#else
	printf(prefix);
	vprintf(format, args);
	printf("\n");
#endif
}
#endif
