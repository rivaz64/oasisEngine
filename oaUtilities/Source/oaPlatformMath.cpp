#include "oaPlatformMath.h"
const float oaEngineSDK::PlatformMath::pi = 3.1415926535897932384626433832795f;
const float oaEngineSDK::PlatformMath::radiansToDegrees = 180.f / pi;
const float oaEngineSDK::PlatformMath::degreesToRadians = pi / 180.f;
float OA_UTILITY_EXPORT oaEngineSDK::PlatformMath::invSqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  return y;
}
