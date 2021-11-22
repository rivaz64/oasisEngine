/**
* @file oaVector2U.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/21/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{
/**
 * @brief bidimencional vector of unsigned ints
*/
class OA_UTILITY_EXPORT Vector2U
{

 public:

  /**
   * @brief default constructor fot the Vector2U
  */
  Vector2U()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector2U(uint32 _x, uint32 _y) :x(_x), y(_y) {}

  ~Vector2U() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector2U& v) const {
    return x == v.x && y == v.y;
  }

  /**
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector2U& v) const {
    return x != v.x || y != v.y;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector2U const
  operator+(const Vector2U& v) const {
    return { x + v.x , y + v.y };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector2U&
  operator+=(const Vector2U& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  /**
  * @brief this vector minus vector v
  * @param v
  * @return
  */
  FORCEINLINE Vector2U const
  operator-(const Vector2U& v) const {
    return { x - v.x , y - v.y };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector2U&
  operator-=(const Vector2U& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  /**
  * @brief calculates a vector with the same direction as this and a lenght multiplied by v
  * @param v
  * @return
  */
  FORCEINLINE Vector2U const
  operator*(uint32 v) const {
    return { x * v , y * v };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector2U&
  operator*=(uint32 v) {
    x *= v;
    y *= v;
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
   * @brief a vector with magnitud 0
  */
  static const Vector2U ZERO;

};

}

