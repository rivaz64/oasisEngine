/**
* @file oaVector3I.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/10/2021
*/

#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaVector2I.h"
#include "oaVector3U.h"

namespace oaEngineSDK{
/**
* @brief tridimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector3I
{

 public:

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
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector3I& v) const {
    return x != v.x || y != v.y || z != v.z;
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
    return { x * v , y * v, z * v };
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

  static const Vector3I RIGHT;
  static const Vector3I LEFT;
  static const Vector3I UP;
  static const Vector3I DOWN;
  static const Vector3I FRONT;
  static const Vector3I BACK;

  union{

    /**
     * @brief the x and y components of the vector
    */
    Vector2I xy;

    struct{
      /**
      * @brief the x component of the vector
      */
      int32 x;

      /**
      * @brief the y component of the vector
      */
      int32 y;
    };
  };
  

  /**
  * @brief the z component of the vector
  */
  int32 z;

  /**
   * @brief a vector with magnitud 0
  */
  static const Vector3I ZERO;

};

}
