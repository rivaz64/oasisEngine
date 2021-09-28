/**
 * @file oaMath.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPlatformDefines.h"
#include "oaPlatformMath.h"

namespace oaEngineSDK {
#if OA_PLATFORM == OA_PLATFORM_LINUX || OA_PLATFORM == OA_PLATFORM_WIN32 || OA_PLATFORM == OA_PLATFORM_OSX
using Math = PlatformMath;
#else
using Math = PlatformMath;
#endif
}