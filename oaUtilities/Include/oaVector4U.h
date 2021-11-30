/**
* @file oaVector4U.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/29/2021
*/

#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaVector3U.h"

namespace oaEngineSDK{
/**
* @brief tridimencional vector of ints
*/
class OA_UTILITY_EXPORT Vector4U
{

 public:

  /**
  * @brief default constructor fot the Vector4U
  */
  Vector4U()=default;

  /**
  * @brief constructor with parameters
  * @param _x
  * @param _y
  */
  Vector4U(int32 _x, int32 _y, int32 _z, int32 _w) :x(_x), y(_y), z(_z), w(_w) {}

  ~Vector4U() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector4U& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }

  /**
  * @brief compares if two vectors are not equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator!=(const Vector4U& v) const {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  /**
  * @brief adds the vector v and this one
  * @param v
  * @return
  */
  FORCEINLINE Vector4U const
    operator+(const Vector4U& v) const {
    return { x + v.x , y + v.y, z + v.z, w + v.w };
  }

  /**
  * @brief adds the vector v to this one
  * @param v
  */
  FORCEINLINE Vector4U&
    operator+=(const Vector4U& v) {
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
  FORCEINLINE Vector4U const
    operator-(const Vector4U& v) const {
    return { x - v.x , y - v.y,z - v.z, w - v.w };
  }

  /**
  * @brief substract vector v from this
  * @param v
  */
  FORCEINLINE Vector4U&
    operator-=(const Vector4U& v) {
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
  FORCEINLINE Vector4U const
    operator*(int32 v) const {
    return { x * v , y * v, z * v, w * v };
  }

  /**
  * @brief multiply the length vector the vector by v
  * @param v
  */

  FORCEINLINE Vector4U&
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
    Vector3U xyz;

    struct{
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
    };
  };
  

  /**
  * @brief the w component of the vector
  */
  uint32 w;

  /**
   * @brief a vector with magnitud 0
  */
  static const Vector4U ZERO;

};

}