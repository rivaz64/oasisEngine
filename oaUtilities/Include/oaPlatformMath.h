/**
 * @file oaMath.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */
#pragma once
#include "oaPlatformDefines.h"
#include<cmath>
namespace oaEngineSDK {
class OA_UTILITY_EXPORT PlatformMath {
public:
  static const float pi;
  static const float radiansToDegrees;
  static const float degreesToRadians;
  /**
   * @brief wraper of the cmath sqrtf
   * @param x
   * @return
  */
  static FORCEINLINE float sqrt(float x) {
    return std::sqrtf(x);
  }
  /**
   * @brief the infamous Q_rsqrt by sir John Karmak
   * @param number
   * @return 1/sqrt(x)d
  */
  static float invSqrt(float number);
  /**
   * @brief wraper of the cmath cos
   * @param x
   * @return
  */
  static FORCEINLINE float cos(float x) {
    return std::cos(x);
  }
  /**
   * @brief wraper of the cmath sin
   * @param x
   * @return
  */
  static FORCEINLINE float sin(float x) {
    return std::sin(x);
  }
  /**
   * @brief wraper of the cmath tan
   * @param x
   * @return
  */
  static FORCEINLINE float tan(float x) {
    return std::tan(x);
  }
  /**
   * @brief wraper of the cmath acos
   * @param x
   * @return
  */
  static FORCEINLINE float acos(float x) {
    return std::acos(x);
  }
  /**
   * @brief wraper of the cmath asin
   * @param x
   * @return
  */
  static FORCEINLINE float asin(float x) {
    return std::asin(x);
  }
  /**
   * @brief wraper of the cmath atan
   * @param x
   * @return
  */
  static FORCEINLINE float atan(float x) {
    return std::atan(x);
  }
  /**
   * @brief wraper of the cmath atan2
   * @param x
   * @return
  */
  static FORCEINLINE float atan2(float x, float y) {
    return std::atan2(y, x);
  }

  template<class T>
  static FORCEINLINE T abs(T v) {
    return std::abs(v);
  }
};


}
