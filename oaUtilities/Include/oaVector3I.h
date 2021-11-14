/**
* @file oaVector3I.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/10/2021
*/

#pragma once
#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{
/**
* @brief tridimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector3I
{
  /**
  * @brief default constructor fot the Vector3I
  */
  Vector3I()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector3I(int32 _x, int32 _y, int32 _z) :x(_x), y(_y), z(_z) {}

  ~Vector3I() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector3I& v) const {
    return x == v.x && y == v.y && z == v.z;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector3I const
    operator+(const Vector3I& v) const {
    return { x + v.x , y + v.y, z + v.z };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector3I&
    operator+=(const Vector3I& v) {
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
  FORCEINLINE Vector3I const
    operator-(const Vector3I& v) const {
    return { x - v.x , y - v.y,z - v.z };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector3I&
    operator-=(const Vector3I& v) {
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
  FORCEINLINE Vector3I const
    operator*(int32 v) const {
    return { x * v , y * v,y * z };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector3I&
    operator*=(int32 v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

public:
  /**
  * @brief the x component of the vector
  */
  int32 x;

  /**
  * @brief the y component of the vector
  */
  int32 y;

  /**
  * @brief the z component of the vector
  */
  int32 z;

};

}
