/**
 * @file oaVector3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {
/**
 * @brief tetradimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector4f
{
public:
  /**
   * @brief default constructor for the Vector4f
  */
  Vector4f() = default;

  /**
   * @brief parametrized constructor for the Vector4f
   * @param _x 
   * @param _y 
   * @param _z 
   * @param _w 
  */

  Vector4f(float _x, float _y, float _z, float _w) :
    x(_x), y(_y), z(_z), w(_w) {}

  ~Vector4f() = default;
  
  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  FORCEINLINE bool const
  operator==(const Vector4f& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }

  /**
   * @brief adds the vector v and this one
   * @param v
   * @return
  */
  FORCEINLINE Vector4f const
  operator+(const Vector4f& v) const {
    return { x + v.x , y + v.y, z + v.z, w + v.w };
  }

  /**
   * @brief adds the vector v to this one
   * @param v
  */
  FORCEINLINE Vector4f&
  operator+=(const Vector4f& v) {
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
  FORCEINLINE Vector4f const
  operator-(const Vector4f& v) const {
    return { x - v.x , y - v.y, z - v.z, w - v.w };
  }

  /**
   * @brief substract vector v from this
   * @param v
  */
  FORCEINLINE Vector4f&
  operator-=(const Vector4f& v) {
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
  FORCEINLINE Vector4f const
  operator*(float v) const {
    return { x * v , y * v , z * v, w * v };
  }

  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */
  FORCEINLINE Vector4f&
  operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
  }

  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  FORCEINLINE Vector4f const
  operator/(float v) const {
    v = 1.f / v;
    return { x * v , y * v, z * v , w * v };
  }

  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  FORCEINLINE Vector4f&
  operator/=(float v) {
    v = 1.f / v;
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
  }

  /**
   * @brief multiplies each parameter for its congruent in the other vector
   * @param v
   * @return
  */
  FORCEINLINE Vector4f const
  operator*(const Vector4f& v) const {
    return { x * v.x,y * v.y,z * v.z,w * v.w };
  }

  /**
   * @brief the lenght of the vector
   * @return
  */
  FORCEINLINE float const
  magnitud() const {
    return Math::sqrt(x * x + y * y + z * z + w * w);
  }

  /**
   * @brief the unitary form of the vector
   * @return
  */
  FORCEINLINE Vector4f const
  normalized() const {
    return *this * Math::invSqrt(x * x + y * y + z * z + w * w);
  }

  /**
  * @brief makes this vector have a magnitud of 1
  * @return
  */
  FORCEINLINE void 
  normalize() {
    *this *= Math::invSqrt(x * x + y * y + z * z + w * w);
  }

  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  FORCEINLINE Vector4f
  project(const Vector4f& v) {
    return v * (dot(*this,v) / dot(v,v));
  }

  /**
  * @brief dot product of two vectors
  * @param v1
  * @param v2
  * @return
  */
  FORCEINLINE static float
  dot(const Vector4f& v1, const Vector4f& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
  }

public:
  union {
    /**
      * @brief the x, y, and z components of the vector
    */
    Vector3f xyz;
    struct {
      /**
        * @brief the x component of the vector
      */
      float x;
      /**
       * @brief the y component of the vector
      */
      float y;
      /**
       * @brief the z component of the vector
      */
      float z;
    };

  };

  /**
   * @brief the w component of the vector
  */
  float w;

 private:
  friend class Matrix4f;
};

}
