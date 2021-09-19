#include "oaPlatformMath.h"
const float oaEngineSDK::PlatformMath::PI = 3.1415926535897932384626433832795f;
const float oaEngineSDK::PlatformMath::HALF_PI = 1.57079632679489661923132169163975f;
const float oaEngineSDK::PlatformMath::TWO_PI = 6.283185307179586476925286766559f;
const float oaEngineSDK::PlatformMath::INV_PI = 0.318309886183790671537767526745f;
const float oaEngineSDK::PlatformMath::INV_TWO_PI = 0.159154943091895335768883763372f;
const float oaEngineSDK::PlatformMath::RAD_TO_DEG = 57.2957795130823208767981548141f;
const float oaEngineSDK::PlatformMath::DEG_TO_RAD = 0.01745329251994329576923690768f;
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
