/**
* @file oaVector4I.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/29/2021
*/

#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaVector3I.h"

namespace oaEngineSDK{
/**
* @brief tridimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector4I
{

 public:

  /**
  * @brief default constructor fot the Vector4I
  */
  Vector4I()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector4I(int32 _x, int32 _y, int32 _z, int32 _w) :x(_x), y(_y), z(_z), w(_w) {}

  ~Vector4I() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector4I& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }

  /**
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector4I& v) const {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector4I const
    operator+(const Vector4I& v) const {
    return { x + v.x , y + v.y, z + v.z, w + v.w };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector4I&
    operator+=(const Vector4I& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  /**
  * @brief this vector minus vector v
  * @param v
  * @return
  */
  FORCEINLINE Vector4I const
    operator-(const Vector4I& v) const {
    return { x - v.x , y - v.y,z - v.z, w - v.w };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector4I&
    operator-=(const Vector4I& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  /**
  * @brief calculates a vector with the same direction as this and a lenght multiplied by v
  * @param v
  * @return
  */
  FORCEINLINE Vector4I const
    operator*(int32 v) const {
    return { x * v , y * v, z * v, w * v };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector4I&
    operator*=(int32 v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
  }

public:

  union{

    /**
     * @brief the x and y components of the vector
    */
    Vector3I xyz;

    struct{
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
  };
  

  /**
  * @brief the w component of the vector
  */
  int32 w;

  /**
   * @brief a vector with magnitud 0
  */
  static const Vector4I ZERO;

};

}