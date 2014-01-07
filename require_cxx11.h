#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__) 
#define clang_version (__clang__ * 10000 + __clang_minor__ * 100 \
                     + __clang_patchlevel__) 
#ifdef __MSC_VER
 #if __MSC_VER < 1700 /* Microsoft Visual Studio 2012 */
  #pragma message("ERROR: Requires C++11 vis avi Microsoft Visual Studio 2012 or later")
 #endif
#else
#if __cplusplus < 201103L
#ifdef WIN32
#pragma message("ERROR: Requires C++11")
#else
#error Requires C++11
#endif
#endif
#endif
