#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdexcept>
#include <glm/glm.hpp>

#ifdef WIN32
#include <Windows.h>

#define USE_VS_CONSOLE

static inline void FTLogPrint(const char* prefix, const char* format, va_list args) {
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

static inline void FTLog(const char* format, ...) {
	va_list args;
	va_start(args, format);

	FTLogPrint("Info: ", format, args);

	va_end(args);
}

static inline void FTLogWarn(const char* format, ...) {
	va_list args;
	va_start(args, format);

	FTLogPrint("Warning: ", format, args);

	va_end(args);
}

static inline void FTLogError(const char* format, ...) {
	va_list args;
	va_start(args, format);

	FTLogPrint("Error: ", format, args);

	va_end(args);
}


static inline void FTAssert(bool value, const char* format, ...) {
	if (value)
		return;
	va_list args;
	va_start(args, format);
	FTLogPrint("Fatal: ", format, args);

	va_end(args);
	throw std::exception();
}

#endif

//#define u(string) (char16_t*)TEXT(string)

#define FTMAX(a, b) ( (a > b) ? a : b )
#define FTMIN(a, b) ( (a < b) ? a : b )

#define FTLOG(...) FTLog(__VA_ARGS__)

#define INT_TO_FVECTOR(a,b,c) (irr::f32)(a),(irr::f32)(b),(irr::f32)(c)

#define MAX(a, b) (((a)>(b)) ? (a) : (b))

/* absolute value of a */
#define ABS(a) (((a)<0) ? -(a) : (a))

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)


// Maths utility functions
#define RAD2DEG 0.01745329251f
#define DEG2RAD 57.2957795131f

static inline float fastabs(float f) {
	int i = ((*(int*)&f) & 0x7fffffff);
	return (*(float*)&i);
}

static inline float fastneg(float f) {
	int i = ((*(int*)&f) ^ 0x80000000);
	return (*(float*)&i);
}

static inline int fastsgn(float f) {
	return 1 + (((*(int*)&f) >> 31) << 1);
}

// Roughly 2 times faster than the built in approach
static inline glm::vec4 fastabsvec4(const glm::vec4& vec) {
	return glm::vec4(fastabs(vec.x), fastabs(vec.y), fastabs(vec.z), fastabs(vec.w));
}

static inline glm::vec4 fastnegvec4(const glm::vec4& vec) {
	return glm::vec4(fastneg(vec.x), fastneg(vec.y), fastneg(vec.z), fastneg(vec.w));
}


static inline glm::vec3 vec3xor(const glm::vec3& av, const glm::vec3& bv) {
	int x = (*(int*)&(av.x)) ^ (*(int*)&(bv.x));
	int y = (*(int*)&(av.y)) ^ (*(int*)&(bv.y));
	int z = (*(int*)&(av.z)) ^ (*(int*)&(bv.z));
	return glm::vec3((*(float*)&x), (*(float*)&y), (*(float*)&z));
}
