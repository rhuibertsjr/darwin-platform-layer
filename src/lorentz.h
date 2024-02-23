#ifndef LRTZ_H
#define LRTZ_H

/* =============================================================================
 * Dependencies 
 ============================================================================ */
#define TARGET_OS_IPHONE 0 
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
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef float    f32;
typedef double   f64;

typedef uint32_t b32; 
typedef uint64_t b64; 

#define true  1
#define false 0

typedef const char* string;

typedef union vector2 {
    struct {
        u32 x, y;
    };

    u32 v[2];
    
} vector2;

typedef union vector3 {

    struct {
        u32 x, y, z;
    };

    u32 v[3];
    
} vector3;

typedef union vector4 {

    struct {
        u32 x, y, z, w;
    };

    u32 v[4];
    
} vector4;

/* =============================================================================
 * Helpers 
 ============================================================================ */
#define clamp(a, x, b) ((x) < (a) ? (a) : (x) > (b) ? (b) : (x))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define stringify_(S) #S
#define stringify(S) stringify_(S)
#define concat_(A, B) A##B
#define concat(A, B) concat_(A, B)

#define statement(S) \
    do { S } while(0)

/* =============================================================================
 * Syntax and attributes 
 ============================================================================ */
#ifndef internal
#define internal static
#endif

#define UNUSED __attribute__((unused))

/* =============================================================================
 * Logging 
 ============================================================================ */
typedef enum lrtz_log_type_table {
    NONE = 0x00,
    ERROR,
    WARNING,
    INFO,
    TEST
} lrtz_log_type_table;

typedef enum lrtz_log_tag_table {
    TAG_NONE    = 0x00,
    TAG_LORENTZ,
    TAG_ASSERT,
    TAG_PLATFORM,
    TAG_WINDOW
} lrtz_log_tag_table;

internal string _lrtz_log_type_table[] = {"", "ERROR", "WARNING", "INFO"};
internal string _lrtz_log_tag_table[] =
{
    "",
    "Lorentz",
    "Assert",
    "Platform",
    "Window"
}; 

inline internal void
_lrtz_log(
    lrtz_log_type_table type, lrtz_log_tag_table tag, string format, ...)
{
    va_list args_list;
    char message[1024];

    va_start(args_list, format);
    vsnprintf(message, 1024, format, args_list);
    va_end(args_list);
    
    printf(
       "[DEBUG][%s] (%s) %s\n",
       _lrtz_log_type_table[type], _lrtz_log_tag_table[tag], message);
}

#define lrtz_log(type, tag, format, ...)                        \
    statement(_lrtz_log(type, tag, "\t" format, ##__VA_ARGS__);)

#ifdef NDEBUG
#define lrtz_debug(format, ...)
#else
#define lrtz_debug(format, ...)                                      \
    statement(_lrtz_log(NONE, TAG_NONE, format, ##__VA_ARGS__);)
#endif

/* =============================================================================
 * Assertion 
 ============================================================================ */
#if NDEBUG
#define lrtz_assert(expression)
#else
#define lrtz_assert(expression)                                          \
    statement(                                                           \
        if (!(expression)) {                                             \
            lrtz_log(                                                    \
                ERROR, TAG_ASSERT, "/ " stringify(expression) " / \n "); \
            __builtin_trap();                                            \
    }) 
#endif

#endif // LRTZ_H
