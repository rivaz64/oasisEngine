/**
* @file oaVector2I.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{
/**
 * @brief bidimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector2I
{

 public:

  /**
   * @brief default constructor fot the Vector2I
  */
  Vector2I()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector2I(int32 _x, int32 _y) :x(_x), y(_y) {}

  ~Vector2I() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector2I& v) const {
    return x == v.x && y == v.y;
  }

  /**
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector2I& v) const {
    return x != v.x || y != v.y;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector2I const
  operator+(const Vector2I& v) const {
    return { x + v.x , y + v.y };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector2I&
  operator+=(const Vector2I& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  /**
  * @brief this vector minus vector v
  * @param v
  * @return
  */
  FORCEINLINE Vector2I const
  operator-(const Vector2I& v) const {
    return { x - v.x , y - v.y };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector2I&
  operator-=(const Vector2I& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector2I
  operator-() {
    return { -x, -y};
  }


  /**
  * @brief calculates a vector with the same direction as this and a lenght multiplied by v
  * @param v
  * @return
  */
  FORCEINLINE Vector2I const
  operator*(int32 v) const {
    return { x * v , y * v };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector2I&
  operator*=(int32 v) {
    x *= v;
    y *= v;
    return *this;
  }

  /**
  * @brief calculates a vector with the same direction as this and a lenght divided by v
  * @param v
  * @return
  */
  FORCEINLINE Vector2I const
  operator/(int32 v) const {
    return { x / v , y / v };
  }

  FORCEINLINE Vector2I&
  operator/=(int32 v) {
    x /= v;
    y /= v;
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
   * @brief a vector with magnitud 0
  */
  static const Vector2I ZERO;

};

}


