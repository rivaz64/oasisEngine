/**
 * @file oaVector3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaVector2f.h"
#include "oaQuaternion.h"

namespace oaEngineSDK {

/**
 * @brief tridimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector3f
{
public:
  /**
   * @brief defaault constructor for the Vector3f
  */
  Vector3f() = default;

  /**
   * @brief parametrized constructor for the Vector3f
   * @param _x 
   * @param _y 
   * @param _z 
  */
  Vector3f(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

  /**
   * @brief constructor from a vector2 for members x and y
   * @param _xy 
   * @param _z
  */
  Vector3f(const Vector2f& _xy, float _z):xy(_xy),z(_z){}

  ~Vector3f() = default;

  /**
  * @brief compares if two vectors are equal
  * @param v 
  * @return 
  */
  bool const
  operator==(const Vector3f& v) const
  {
    return x == v.x && y == v.y && z == v.z;
  }

  /**
   * @brief adds the vector v and this one
   * @param v
   * @return
  */
  FORCEINLINE Vector3f const 
  operator+(const Vector3f& v) const
  {
    return { x + v.x , y + v.y, z + v.z };
  }

  /**
   * @brief adds the vector v to this one
   * @param v
  */
  FORCEINLINE Vector3f&
  operator+=(const Vector3f& v)
  {
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
  FORCEINLINE Vector3f const
  operator-(const Vector3f& v) const
  {
    return { x - v.x , y - v.y, z - v.z };
  }

  /**
   * @brief substract vector v from this
   * @param v
  */
  FORCEINLINE Vector3f&
  operator-=(const Vector3f& v)
  {
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
  FORCEINLINE Vector3f const
  operator*(float v) const
  {
    return { x * v , y * v , z * v };
  }

  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */
  FORCEINLINE Vector3f&
  operator*=(float v)
  {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  FORCEINLINE Vector3f const 
  operator/(float v) const
  {
    v = 1.f / v;
    return { x * v , y * v, z * v };
  }

  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  FORCEINLINE Vector3f&
  operator/=(float v)
  {
    v = 1.f / v;
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  /**
   * @brief multiplies each parameter for its congruent in the other vector
   * @param v
   * @return
  */
  FORCEINLINE Vector3f const
  operator*(const Vector3f& v) const
  {
    return { x * v.x,y * v.y,z * v.z };
  }

  

  /**
   * @brief the lenght of the vector
   * @return
  */
  FORCEINLINE float const
  magnitud() const
  {
    return Math::sqrt(x * x + y * y + z * z);
  }

  /**
   * @brief the unitary form of the vector
   * @return
  */
  FORCEINLINE Vector3f const
  normalized() const
  {
    return *this * Math::invSqrt(x * x + y * y + z * z);
  }

  /**
  * @brief makes this vector have a magnitud of 1
  * @return
  */
  FORCEINLINE void 
    normalize()
  {
    *this *= Math::invSqrt(x * x + y * y + z * z);
  }

  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  FORCEINLINE Vector3f const
  project(const Vector3f& v) const
  {
    return v * (dot(*this,v) / dot(v,v));
  }

  /**
   * @brief rotates the vector with the quaternion q
   * @param q
  */
  FORCEINLINE void 
  rotate(const Quaternion& q);

  /**
   * @brief dot product of two vectors
   * @param v1
   * @param v2
   * @return
  */
  FORCEINLINE static float
  dot(const Vector3f& v1, const Vector3f& v2)
  {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  /**
  * @brief cross product of two vectors
  * @param v1
  * @param v2
  * @return
  */
  FORCEINLINE static Vector3f
  cross(const Vector3f& v1, const Vector3f& v2)
  {
    return Vector3f(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
  }
 public:
  static const Vector3f RIGHT;
  static const Vector3f LEFT;
  static const Vector3f UP;
  static const Vector3f DOWN;
  static const Vector3f FRONT;
  static const Vector3f BACK;

  union {
    /**
     * @brief the x and y components of the vector
    */
    Vector2f xy;
    struct {
      /**
       * @brief the x component of the vector
      */
      float x;
      /**
       * @brief the y component of the vector
      */
      float y;

    };
  };
  /**
    * @brief the z component of the vector
  */
  float z;

};

}
