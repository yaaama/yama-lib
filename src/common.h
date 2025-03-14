#ifndef COMMON_H_
#define COMMON_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

#define true 1
#define false 0

#define u32_max 4294967295

#define YAMA_ASSERT assert
#define YAMA_UNUSED(value) (void) (value)
#define YAMA_ARRAY_LENGTH(a) (sizeof((a)) / sizeof(((a)[0])))
#define YAMA_ARRAY_GET(array, index)                        \
    (YAMA_ASSERT((size_t) (index) < YAMA_ARRAY_LEN(array)), \
     (array)[(size_t) (index)])

#ifdef NDEBUG
    #define YAMA_TODO(message) ((void) 0)
    #define YAMA_UNREACHABLE(message) ((void) 0)
#else
    /* If stdio is not included then lets define it */
    #if !defined(_STDIO_H_) && !defined(_STDIO_H)
int printf(const char *restrict format, ...);
int fprintf(int *restrict stream, const char *restrict format, ...);
    #endif

    /* Define our debugging macros */
    #define YAMA_TODO(message)                                                 \
        do {                                                                   \
            fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, message); \
            abort();                                                           \
        } while (0)
    #define YAMA_UNREACHABLE(message)                                       \
        do {                                                                \
            fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, \
                    message);                                               \
            abort();                                                        \
        } while (0)

#endif

#endif  // COMMON_H_
