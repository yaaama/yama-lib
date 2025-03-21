#ifndef YAMA_COMMON_H_
#define YAMA_COMMON_H_

/* Determine compiler */
#if defined(_MSC_VER)
#if defined(__clang__)
#define ENV_COMPILER_CLANG
#define ENV_COMPILER_CLANG_WITH_MSVC
#else
#define ENV_COMPILER_MSVC
#endif
#elif defined(__GNUC__)
#if defined(__clang__)
#define ENV_COMPILER_CLANG
#define ENV_COMPILER_CLANG_WITH_GCC
#else
#define ENV_COMPILER_GCC
#endif
#elif defined(__clang__)
#define ENV_COMPILER_CLANG
#else
#error Compiler not supported
#endif

#include <stdio.h>

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

/* Maths */
#define KiB(x) ((x) * 1024ULL)
#define MiB(x) (KiB(x) * 1024ULL)
#define GiB(x) (MiB(x) * 1024ULL)
#define TiB(x) (GiB(x) * 1024ULL)

#define HUNDRED 100L
#define THOUSAND 1000L
#define MILLION 1000000L
#define BILLION 1000000000L

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* Memory management and  */

/* Likely/unlikely for better branch prediction */
#if defined(ENV_COMPILER_MSVC)
#define likely(x) (x)
#define unlikely(x) (x)
#elif defined(ENV_COMPILER_CLANG) || defined(ENV_COMPILER_GCC)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

/* Development debugging and other useful things */

#define YAMA_ASSERT assert

#define ya_die(msg)                                                            \
  do {                                                                         \
    fprintf(stderr, "__FILE__:__LINE__:__func__ %s\n", (msg));                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0);

#define YA_SIZE_T_OVERFLOW(a, b)                                               \
  do {                                                                         \
    if ((a) > (SIZE_MAX - (b))) {                                              \
      ya_die("Overflow detected!");                                            \
    }                                                                          \
  } while (0);

#define YAMA_UNUSED(value) (void)(value)
#define YAMA_ARRAY_LENGTH(a) (sizeof((a)) / sizeof(((a)[0])))
#define YAMA_ARRAY_GET(array, index)                                           \
  (YAMA_ASSERT((size_t)(index) < YAMA_ARRAY_LEN(array)),                       \
   (array)[(size_t)(index)])

#ifdef NDEBUG
#define YAMA_TODO(message) ((void)0)
#define YAMA_UNREACHABLE(message) ((void)0)
#else
/* If stdio is not included then lets define it */
#if !defined(_STDIO_H_) && !defined(_STDIO_H)
int printf(const char *restrict format, ...);
int fprintf(int *restrict stream, const char *restrict format, ...);
#endif

/* Define our debugging macros */
#define YAMA_TODO(message)                                                     \
  do {                                                                         \
    fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, (message));       \
    abort();                                                                   \
  } while (0)
#define YAMA_UNREACHABLE(message)                                              \
  do {                                                                         \
    fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__,            \
            (message));                                                        \
    abort();                                                                   \
  } while (0)

#endif

/* Disable all warnings in headers */
#define disable_warnings()                                                     \
  pragma_clang("clang diagnostic push");                                       \
  pragma_clang("clang diagnostic ignored \"-Weverything\"");                   \
  pragma_msvc("warning ( push , 0 )")
#define enable_warnings()                                                      \
  pragma_clang("clang diagnostic pop");                                        \
  pragma_msvc("warning ( pop )")

#if defined(BUILD_INTERNAL)
#if defined(ENV_OS_WINDOWS)
#define breakpoint() __debugbreak()
#elif defined(ENV_OS_LINUX)
#if defined(ENV_ARCH_X86) || defined(ENV_ARCH_X64)
#if defined(ENV_COMPILER_GCC) || defined(ENV_COMPILER_CLANG)
#define breakpoint() __asm__ volatile("int $0x03")
#endif // !GCC && !Clang
#endif // !x86 && !x64
#endif // !window && !linux
#else
#define breakpoint()                                                           \
  do {                                                                         \
  } while (0)
#endif

#define debugBreak() breakpoint()
#define debugAssert(...)                                                       \
  do {                                                                         \
    if (!(__VA_ARGS__)) {                                                      \
      debugBreak();                                                            \
    }                                                                          \
  } while (0)

#if defined(BUILD_INTERNAL)
global_immutable Bool debug_unreachable_code_executed = false;
#define debugUnreachable() debugAssert(debug_unreachable_code_executed == true)
#else
#if defined(ENV_COMPILER_MSVC)
#define debugUnreachable() __assume(false)
#elif defined(ENV_COMPILER_GCC) || defined(ENV_COMPILER_CLANG)
#define debugUnreachable() __builtin_unreachable()
#endif
#endif

/* Bit operations */

#define bitToBytes(b) (((b) + (CHAR_BIT - 1)) / (CHAR_BIT))

#define bit_ValInBuf(array, index) ((index) / (CHAR_BIT * sizeof(*(array))))
#define bit_BitInVal(array, index) ((index) % (CHAR_BIT * sizeof(*(array))))
#define bitSet(array, index)                                                   \
  ((array)[bit_ValInBuf(array, index)] |= (1LLU << bit_BitInVal(array, index)))
#define bitReset(array, index)                                                 \
  ((array)[bit_ValInBuf(array, index)] &= ~(1LLU << bit_BitInVal(array, index)))
#define bitToggle(array, index)                                                \
  ((array)[bit_ValInBuf(array, index)] ^= ~(1LLU << bit_BitInVal(array, index)))
#define bitTest(array, index)                                                  \
  ((array)[bit_ValInBuf(array, index)] & (1LLU << bit_BitInVal(array, index)))

#endif // YAMA_COMMON_H_
