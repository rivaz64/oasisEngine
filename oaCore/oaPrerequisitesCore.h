
#pragma once

#include "oaPrerequisitesUtilities.h"

#if OA_PLATFORM == OA_PLATFORM_WIN32
# if OA_COMPILER == OA_COMPILER_MSVC
#   if defined( OA_STATIC_lib )
#     define OA_UTILITY_EXPORT
#   else
#     if defined ( OA_CORE_EXPORT )
#       define OA_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define OA_CORE_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( OA_STATIC_LIB )
#     define OA_CORE_EXPORT
#   else
#     if defined( OA_UTILITY_EXPORTS )
#       define OA_CORE_EXPORT __attribute__ ((dllexport))
#     else
#       define OA_CORE_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define OA_UTILITY_HIDDEN
#else
# define OA_UTILITY_EXPORT __attribute__ ((visibility ("default")))
# define OA_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif
