/**
* @file oaCapsule.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Capsule
{
 public:
  /**
  * @brief default constructor for the Sphere
  */
  Capsule() = default;

  /**
  * @brief parametrized construcrtor for the Capsule
  * @param _center 
  * @param _radius 
  */
  Capsule(const Vector3f& _base, float _radius,float _height) :base(_base), radius(_radius),height(_height) {}

  ~Capsule() = default;

  /**
   * @brief getter for the base point
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getBase() const {
    return base;
  }

  /**
  * @brief getter for the radius
  * @return 
  */
  FORCEINLINE float const 
  getRadius() const {
    return radius;
  }

  /**
  * @brief getter for the height
  * @return 
  */
  FORCEINLINE float const 
  getHeight() const {
    return height;
  }

  /**
  * @brief setter for the base
  * @param _center 
  */
  FORCEINLINE void 
  setBase(const Vector3f& _base) {
    base = _base;
  }

  /**
  * @brief setter for the radius
  * @param _radius 
  */
  FORCEINLINE void 
  setRadius(float _radius) {
    radius = _radius;
  }

  /**
  * @brief setter for the height
  * @param _radius 
  */
  FORCEINLINE void 
  setHeight(float _height) {
    height = _height;
  }
 private:

  /**
  * @brief the lowest point of the capsule
  */
  Vector3f base;

  /**
  * @brief the radius of the capsule
  */
  float radius;

  /**
  * @brief the height of the capsule
  */
  float height;

  friend class PlatformMath;
};

}

