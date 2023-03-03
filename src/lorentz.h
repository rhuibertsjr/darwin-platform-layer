#ifndef LRTZ_H
#define LRTZ_H

/* =============================================================================
 * Dependencies 
 ============================================================================ */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/* =============================================================================
 * Context and platform 
 ============================================================================ */
#if defined(_WIN64) || defined(_WIN32)
#   define LRTZ_PLATFORM_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#   define LRTZ_PLATFORM_DARWIN 1
#elif defined(__gnu_linux__)
#   define LRTZ_PLATFORM_GNU_LINUX 1
#else
#   error "Couldn't get the operating system from compiler context."
#endif

#if !defined(_WIN64) && !defined(_WIN32)
#   define LRTZ_PLATFORM_WINDOWS 0
#endif
#if !defined(__APPLE__) && !defined(__MACH__)
#   define LRTZ_PLATFORM_DARWIN 0
#endif
#if !defined(__gnu_linux__)
#   define LRTZ_PLATFORM_GNU_LINUX 0
#endif

/* =============================================================================
 * Types and compounds 
 ============================================================================ */
typedef uint8_t   U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t    S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;

typedef float    F32;
typedef double   F64;

typedef uint32_t B32; 
typedef uint64_t B64; 

#define true  1
#define false 0

typedef const char* String;

typedef union Vector2 {
    struct {
        U32 x, y;
    };

    U32 v[2];
    
} Vector2;

typedef union Vector3 {

    struct {
        U32 x, y, z;
    };

    U32 v[3];
    
} Vector3;

typedef union Vector4 {

    struct {
        U32 x, y, z, w;
    };

    U32 v[4];
    
} Vector4;

/* =============================================================================
 * Helpers 
 ============================================================================ */
#define Clamp(a, x, b) ((x) < (a) ? (a) : (x) > (b) ? (b) : (x))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Concat_(A, B) A##B
#define Concat(A, B) Concat_(A, B)

/* =============================================================================
 * Syntax and attributes 
 ============================================================================ */
#define LrtzInternal  static
#define LrtzGlobal    static
#define LrtzLocal     static

#define UNUSED __attribute__((unused))

/* =============================================================================
 * Logging 
 ============================================================================ */
enum LrtzLoggingTypeTable {
    ERROR    = 0x00,
    WARNING,
    INFO,
    TEST
};

enum LrtzLoggingTagTable {
    TAG_NONE    = 0x00,
    TAG_PLATFORM,
    TAG_WINDOW
};

LrtzInternal String _LrtzLoggingTypeTable[] = {"ERROR", "WARNING", "INFO"};
LrtzInternal String _LrtzLoggingTagTable[] =
{
    "",
    "Platform",
    "Window"
}; 

inline LrtzInternal void
_LrtzLog(enum LrtzLoggingTypeTable type,
         enum LrtzLoggingTagTable tag, String format, ...)
{
    va_list args_list;
    char message[1024];

    va_start(args_list, format);
    vsnprintf(message, 1024, format, args_list);
    va_end(args_list);
    
    printf(
       "[DEBUG][%s] (%s) %s\n",
       _LrtzLoggingTypeTable[type], _LrtzLoggingTagTable[tag], message);
}

#define Log(type, tag, format) _LrtzLog(type, tag, format)
#define DEBUG(tag, format) _LrtzLog(TEST, tag, format)

#endif 
