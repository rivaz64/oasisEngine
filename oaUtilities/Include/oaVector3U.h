/**
* @file oaVector3U.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/212021
*/

#pragma once
#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{
/**
* @brief tridimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector3U
{

 public:

  /**
  * @brief default constructor fot the Vector3U
  */
  Vector3U()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector3U(uint32 _x, uint32 _y, uint32 _z) :x(_x), y(_y), z(_z) {}

  ~Vector3U() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector3U& v) const {
    return x == v.x && y == v.y && z == v.z;
  }

  /**
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector3U& v) const {
    return x != v.x || y != v.y || z != v.z;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector3U const
    operator+(const Vector3U& v) const {
    return { x + v.x , y + v.y, z + v.z };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector3U&
    operator+=(const Vector3U& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  /**
  * @brief this vector minus vector v
  * @param v
  * @return
  */
  FORCEINLINE Vector3U const
    operator-(const Vector3U& v) const {
    return { x - v.x , y - v.y,z - v.z };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector3U&
    operator-=(const Vector3U& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  /**
  * @brief calculates a vector with the same direction as this and a lenght multiplied by v
  * @param v
  * @return
  */
  FORCEINLINE Vector3U const
    operator*(uint32 v) const {
    return { x * v , y * v,y * z };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector3U&
    operator*=(uint32 v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

public:
  /**
  * @brief the x component of the vector
  */
  uint32 x;

  /**
  * @brief the y component of the vector
  */
  uint32 y;

  /**
  * @brief the z component of the vector
  */
  uint32 z;

  /**
   * @brief a vector with magnitud 0
  */
  static const Vector3U ZERO;

};

}