/**
 * @file oaPlatformMath.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPlatformDefines.h"
#include "oaStdHeaders.h"
#include "oaForDecUtilities.h"

namespace oaEngineSDK {
/**
 * @brief math from this platform
*/
class OA_UTILITY_EXPORT PlatformMath {

 public:
  /**
   * @brief wraper of the cmath sqrtf
   * @param x
   * @return
  */
  static FORCEINLINE float 
  sqrt(float x) 
  {
    return std::sqrtf(x);
  }

  /**
   * @brief the infamous Q_rsqrt by sir John Karmak
   * @param number
   * @return 1/sqrt(x)d
  */
  static float 
  invSqrt(float number);

  /**
   * @brief cosine function in radians
   * @param r
   * @return
  */
  static FORCEINLINE float 
  cos(float r) 
  {
    return std::cosf(r);
  }

  /**
   * @brief sine function in radians
   * @param r
   * @return
  */
  static FORCEINLINE float 
  sin(float r) {
    return std::sinf(r);
  }

  /**
   * @brief tangent function in radians
   * @param r
   * @return
  */
  static FORCEINLINE float 
  tan(float r) {
    return std::tanf(r);
  }

  /**
   * @brief arc cosine function in radians
   * @param x
   * @return
  */
  static FORCEINLINE float 
  acos(float x) 
  {
    return std::acosf(x);
  }

  /**
   * @brief arc sine function in radians
   * @param x
   * @return
  */
  static FORCEINLINE float 
  asin(float x) 
  {
    return std::asinf(x);
  }

  /**
   * @brief arc tangent in radians 
   * @param x
   * @return
  */
  static FORCEINLINE float 
  atan(float x) 
  {
    return std::atanf(x);
  }

  /**
   * @brief arc tangent from y/x
   * @param x
   * @param y
   * @return
  */
  static FORCEINLINE float 
  atan2(float x, float y) {
    return std::atan2f(y, x);
  }

  /**
   * @brief absolute value of a value
   * @tparam T 
   * @param v 
   * @return 
  */
  template<class T>
  static FORCEINLINE T 
  abs(T v) 
  {
    return std::abs(v);
  }

  /**
   * @brief the maximum value between two value
   * @tparam T
   * @param v1
   * @param v2
   * @return
  */
  template<class T>
  static FORCEINLINE T 
  max(T v1,T v2) 
  {
    return std::max(v1,v2);
  }

  /**
   * @brief the minimum value between two value
   * @tparam T
   * @param v1
   * @param v2
   * @return
  */
  template<class T>
  static FORCEINLINE T 
  min(T v1, T v2) 
  {
    return std::min(v1, v2);
  }

  /**
   * @brief e to the poewr of v
   * @tparam T
   * @param v
  */
  static FORCEINLINE float 
  exp(float v) {
    return std::expf(v);
  }

  /**
   * @brief modular function for floats
   * @tparam T 
   * @param v1 
   * @param v2 
  */
  static FORCEINLINE float
  mod(float v1, float v2)
  {
    return std::fmod(v1, v2);
  }

  /**
   * @brief the first value tho the power of the second one
   * @tparam T 
   * @param v1 
   * @param v2 
   * @return 
  */
  static FORCEINLINE float
  pow(float v1, float v2)
  {
    return std::pow(v1, v2);
  }

  /**
   * @brief logaritmic function of the value
  */
  static FORCEINLINE float
  log(float v)
  {
    return std::log(v);
  }

  /**
   * @brief 1 if positive, -1 if negative, 0 if 0
   * @tparam T 
   * @param val 
   * @return 
  */
  static FORCEINLINE float
  sign(float v) {
    return float((0.f < v) - (v < 0));
  }

  /**
   * @brief a random number between 0 and 1
   * @return 
  */
  static FORCEINLINE float
  unitRandom() {
    return (float)std::rand() / RAND_MAX;
  }

  /**
   * @brief a random number between 0 and 1
   * @return
  */
  static FORCEINLINE float
  symmetricRandom() {
    return ((float)std::rand() / RAND_MAX)*2.f-1.f;
  }

  /**
   * @brief fast aproximation to sin
   * @param x 
   * @return 
  */
  static FORCEINLINE float
  fastSin(float x) 
  {
    float x2 = x * x;
    return (1.f - .16605f * x2 + .00761f*x2*x2) * x;
  }

  /**
   * @brief fast aproximate to cos
   * @param x 
   * @return 
  */
  static FORCEINLINE float
  fastCos(float x)
  {
    float x2 = x * x;
    return 1.f - .4967f * x2 + .03705f * x2 * x2;
  }

  /**
   * @brief fast aproximate to tan
   * @param x
   * @return
  */
  static FORCEINLINE float
  fastTan(float x)
  {
    float x2 = x * x;
    return (1.f + .31755f * x2 + .20330f * x2 * x2) * x;
  }

  /**
   * @brief fast aproximation to acos
   * @param x
   * @return
  */
  static FORCEINLINE float
  fastAcos(float x)
  {
    float x2 = x * x;
    return sqrt(1 - x) * 
      (1.5707288f - .2121144f * x + 0.074261f * x2 - .0187293f * x2 * x);
  }

  /**
   * @brief fast aproximation to asin
   * @param x
   * @return
  */
  static FORCEINLINE float
  fastAsin(float x)
  {
    float x2 = x * x;
    return HALF_PI - sqrt(1 - x) *
      (1.5707288f - .2121144f * x + 0.074261f * x2 - .0187293f * x2 * x);
  }

  /**
   * @brief fast aproximation to atan
   * @param x
   * @return
  */
  static FORCEINLINE float
  fastAtan(float x)
  {
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;
    return (0.9998660f - .3302995f*x2 + .180141f*x4 - .085133f*x6 + .0208351f*x6*x2) * x;
  }

  /**
   * @brief if a point is inside a sphere
   * @param _point 
   * @param _sphere 
   * @return 
  */
  static bool
  overlap(const Vector3f& _point,const Sphere& _sphere);

  /**
   * @brief if two spheres are intersecting
   * @param _sphere1 
   * @param _sphere2 
   * @return 
  */
  static bool
  overlap(const Sphere& _sphere1,const Sphere& _sphere2);

  /**
   * @brief checks if a point is inside a box
   * @param _point 
   * @param _box 
   * @return 
  */
  static bool
  overlap(const Vector3f& _point,const BoxAABB& _box);

  /**
   * @brief checks if a shpere overlaps a box
   * @param _sphere 
   * @param _box 
   * @return 
  */
  static bool
  overlap(const Sphere& _sphere,const BoxAABB& _box);

  /**
   * @brief checks if two boxes overlap
   * @param _box1 
   * @param _box2 
   * @return 
  */
  static bool
  overlap(const BoxAABB& _box1,const BoxAABB& _box2);

  /**
   * @brief checks if a point is inside a capsule
   * @param _point 
   * @param _capsule 
   * @return 
  */
  static bool
  overlap(const Vector3f& _point,const Capsule& _capsule);

  /**
   * @brief checks if a capsule and a sphere overlap
   * @param _sphere 
   * @param _capsule 
   * @return 
  */
  static bool
  overlap(const Sphere& _sphere,const Capsule& _capsule);

  /**
   * @brief 
   * @param _box 
   * @param _capsule 
   * @return 
  */
  static bool
  overlap(const BoxAABB& _box, const Capsule& _capsule);
  /**
   * @brief checks if two capsules are overlapping
   * @param _capsule1 
   * @param _capsule2 
   * @return 
  */
  static bool
  overlap(const Capsule& _capsule1,const Capsule& _capsule2);

  /**
  * @brief calculates the distance between the point p and this line
  * @param p 
  * @return 
  */
  static float 
  distance(const Line& _line, const Vector3f& _point);

  /**
   * @brief calculates the distance between two lines
   * @param _line1 
   * @param _line2 
   * @return 
  */
  static float 
  distance(const Line& _line1, const Line& _line2);

  /**
   * @brief calculates the distance between a point and a plane
   * @param _plane 
   * @param _point 
   * @return 
  */
  static float
  distance(const Plane& _plane, const Vector3f& _point);
  
  /**
   * @brief checks if a plane and a line intersect
   * @param _plane 
   * @param _line 
   * @param _point the point where the intersection ocurres
   * @return 
  */
  static bool
  intersect(const Plane& _plane, const Line& _line, Vector3f& _point);

  /**
   * @brief checks if 3 planes intersect
   * @param _plane1 
   * @param _plane2 
   * @param _plane3 
   * @param _point the point where the intersection occures
   * @return 
  */
  static bool
  intersect(const Plane& _plane1, const Plane& _plane2,const Plane& _plane3, Vector3f& _point);

  static const float PI;
  static const float HALF_PI;
  static const float TWO_PI;
  static const float INV_PI;
  static const float INV_TWO_PI;
  static const float RAD_TO_DEG;
  static const float DEG_TO_RAD;

};

}