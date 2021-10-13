#pragma once
#include <assert.h>

/************************************************************************/
/**
 * Initial platform/compiler-related stuff to set.
*/
/************************************************************************/
#define OA_PLATFORM_WIN32   1                  //Windows Platform
#define OA_PLATFORM_LINUX   2                  //Linux Platform
#define OA_PLATFORM_OSX     3


#define OA_COMPILER_MSVC    1                  //Visual Studio Compiler
#define OA_COMPILER_GNUC    2                  //GCC Compiler
#define OA_COMPILER_INTEL   3                  //Intel Compiler
#define OA_COMPILER_CLANG   4                  //Clang Compiler

#define OA_ARCHITECTURE_X86_32 1               //Intel x86 32 bits
#define OA_ARCHITECTURE_X86_64 2               //Intel x86 64 bits

#define OA_ENDIAN_LITTLE  1
#define OA_ENDIAN_BIG     2

//Define the actual endian type (little endian for Windows, Linux, Apple and PS4)
#define OA_ENDIAN OA_ENDIAN_LITTLE

#define OA_VERSION_MAJOR    0                 //Engine version major
#define OA_VERSION_MINIOR   1
#define OA_VERSION_PATCH    0
#define OA_VERSION_BUILD    1

//Define if on crate a we want to report warnings on unknown symbols
#define OA_DEBUG_DETAILED_SYMBOLS   1

/************************************************************************/
/**
 * Compiler type and version
 */
 /************************************************************************/

#if defined(__clang__)
#   define OA_COMPILER OA_COMPILER_CLANG
#   define OA_COMP_VER __cland_version__
#   define OA_THREADLOCAL __thread
#   define OA_STDCALL __attribute__((stdcall))
#   define OA_CDECL __attribute__((cdecl))
#   define OA_FALLTHROUHG [[clang::fallthrough]];
#elif defined (__GNUC__) //Check after Cland, as Clang defines this too
#   define OA_COMPILER OA_COMPILER_GNUC
#   define OA_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10)+__GNUC_PATCHLEVEL__)
#   define OA_THREADLOCAL __thread
#   define OA_STDCALL __attribute__((stdcall))
#   define OA_CDECL __attribute__((cdecl))
#   define OA_FALLTHROUHG __attribute__((fallthrough));
#elif defined (__INTEL_COMPILER)
#   define OA_COMPILER OA_COMPILER_INTEL
#   define OA_COMP_VER __INTEL_COMPILER
#   define OA_STDCALL __stdcall
#   define OA_CDECL __cdecl
#   define OA_FALLTHROUHG 

/**
 * OA_THREADLOCAL define is down below because Intel compiler defines it
 * differently based on platform
 */

 //Check after Clang end Intel, we could be building with either with Vs
#elif defined (_MSC_VER)
#   define OA_COMPILER OA_COMPILER_MSVC
#   define OA_COMP_VER _MSC_VER
#   define OA_THREADLOCAL __declspec
#   define OA_STDCALL __stdcall
#   define OA_CDECL __cdecl
#   define OA_FALLTHROUHG
#   undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No know compiler found, send the error to the output (if any)
#   pragma error "No known compuler. "
#endif

/************************************************************************/
/**
 * See if we can use __forceinline or if we need to use __inline instead
 */
 /************************************************************************/
#if OA_COMPILER == OA_COMPILER_MSVC
# if OA_COMP_VER >= 1200
#   define FORCEINLINE __forceinline
#   ifndef RESTRICT 
#     define RESTRICT __restrict
#   endif
# endif
#elif defined (__MINGW32__)
# if !defined (FORCEINLINE)
#   define FORCEINLINE __inline
#   ifndef RESTRICT
#     define RESTRICT
#   endif
# endif
#else
# define FORCEINLINE __inline
# ifndef RESTRICT
#   define RESTRICT __restrict
# endif
#endif

/************************************************************************/
/**
 * Finds the current platform
 */
 /************************************************************************/
#if defined (__WIN32__) || defined (_WIN32)
# define OA_PLATFORM OA_PLATFORM_WIN32
#elif defined (__APPLE_CC__ )
# define OA_PLATFORM OA_PLATFORM_OSX
#elif defined (__ORBIS__)
# define OA_PLATFORM OA_PLATFORM_LINUX
#endif

/************************************************************************/
/**
 * Find the architecture type
 */
 /************************************************************************/
#if defined (__x86_x64__) || defined(_M_X64)    //If this is a x64 compile
# define OA_ARCH_TYPE OA_ARCHITECTURE_X86_64
#else
#  define OA_ARCH_TYPE OA_ARCHITECTURE_X86_32
#endif

/************************************************************************/
/**
 * Memory Alignment macros
 */
 /************************************************************************/
#if OA_COMPILER == OA_COMPILER_MSVC
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
# ifndef GCC_ALIGN
#   define GCC_ALIGN(n)
# endif
#elif (OA_COMPILER == OA_COMPILER_GNUC)
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__((packed, aligned(n)))
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#endif

/************************************************************************/
/**
 * For throw override (deprecated on c++11 but VS does not have handle )
 */
 /************************************************************************/
#if OA_COMPILER == OA_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif OA_COMPILER == OA_COMPILER_INTEL
# define _NOEXCEPT noexcept
#elif OA_COMPILER == OA_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if OA_PLATFORM == OA_PLATFORM_WIN32
# if OA_COMPILER == OA_COMPILER_MSVC
#   if defined( OA_STATIC_lib )
#     define OA_UTILITY_EXPORT
#   else
#     if defined ( OA_UTILITY_EXPORTS )
#       define OA_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define OA_UTILITY_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( OA_STATIC_LIB )
#     define OA_UTILITY_EXPORT
#   else
#     if defined( OA_UTILITY_EXPORTS )
#       define OA_UTILITY_EXPORT __attribute__ ((dllexport))
#     else
#       define OA_UTILITY_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define OA_UTILITY_HIDDEN
#else
# define OA_UTILITY_EXPORT __attribute__ ((visibility ("default")))
# define OA_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

 //DLL export plug ins
#if OA_PLATFORM == OA_PLATFORM_WIN32
# if OA_COMPILER == OA_COMPILER_MSVC
#   define OA_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define OA_PLUGIN_EXPORT __attribute__ ((dllexport))
# endif
#else
#  define OA_PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

/************************************************************************/
/**
 * Window specific Settings
 */
 /************************************************************************/
 //Win32
#if OA_PLATFORM == OA_PLATFORM_WIN32
# if defined(_DEBUG) || defined(DEBUG)
#   define OA_DEBUG_MODE 1
# else
#   define OA_DEBUG_MODE 0
# endif
# if OA_COMPILER == OA_COMPILER_INTEL
#   define OA_THREADLOCAL __declspec(thread)
# endif
#endif //OA_PLATFORM

/************************************************************************/
/**
 * LINUX-Apple specific Settings
 */
 /************************************************************************/

 //
#if OA_PLATFORM == OA_PLATFORM_LINUX || OA_PLATFORM == OA_PLATFORM_OSX

//if we're on debug mode
# if defined(_DEBUG) || defined(DEBUG)
#   define OA_DEBUG_MODE 1
# else
#   define OA_DEBUG_MODE 0
# endif
# if OA_COMPILER == OA_COMPILER_INTEL
#   define OA_THREADLOCAL thread
# endif
#endif //OA_PLATFORM

/************************************************************************/
/**
 * DEfinition of DEbug macros
 */
 /************************************************************************/
#if OA_DEBUG_MODE
# define OA_DEBUG_ONLY(x) x
# define OA_ASSERT(x) assert(x)
#else
# define OA_DEBUG_ONLY(x)
# define OA_ASSERT(x)
#endif

/************************************************************************/
/**
 * Disable some compiler warnings
 */
 /************************************************************************/

 //If we are compiling with VS
#if OA_COMPILER == OA_COMPILER_MSVC

# define _CRT_SECURE_NO_WARNINGS

# pragma warning(disable : 4201)

# pragma warning(disable : 4996)

# pragma warning(disable : 4251)

# pragma warning(disable : 4503)

#endif

#define OA_EXTERN extern "C"