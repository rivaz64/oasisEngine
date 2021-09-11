/**
 * @file oaVector3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"
#include "oaQuaternion.h"

namespace oaEngineSDK {

/**
 * @brief tridimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector3f
{
public:
  union {
    float data[3];
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

  Vector3f() = default;
  Vector3f(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}
  float&
    operator[](uint8 i);

  /**
   * @brief adds the vector v and this one
   * @param v
   * @return
  */
  Vector3f
    operator+(const Vector3f& v);
  /**
   * @brief adds the vector v to this one
   * @param v
  */
  void
    operator+=(const Vector3f& v);
  /**
   * @brief this vector minus vector v
   * @param v
   * @return
  */
  Vector3f
    operator-(const Vector3f& v);
  /**
   * @brief substract vector v from this
   * @param v
  */
  void
    operator-=(const Vector3f& v);
  /**
   * @brief calculates a vector with the same direction as this and a lenght multiplied by v
   * @param v
   * @return
  */
  Vector3f
    operator*(float v) const;
  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */
  void
    operator*=(float v);
  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  Vector3f
    operator/(float v);
  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  void
    operator/=(float v);
  /**
   * @brief dot product of two vector
   * @param v
   * @return
  */
  float
    dot(const Vector3f& v) const;
  /**
   * @brief the lenght of the vector
   * @return
  */
  float
    len();
  /**
   * @brief the unitary form of the vector
   * @return
  */
  Vector3f
    normal();
  /**
   * @brief cross product of two vectors
   * @param v
   * @return
  */
  Vector3f
    cross(const Vector3f& v);
  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  Vector3f
    project(const Vector3f& v);

  /**
   * @brief rotates the vector with the quaternion q
   * @param q
  */
  void
    rotate(Quaternion q);

  static const Vector3f RIGHT;
  static const Vector3f LEFT;
  static const Vector3f UP;
  static const Vector3f DOWN;
  static const Vector3f FRONT;
  static const Vector3f BACK;
};
bool OA_UTILITY_EXPORT
operator==(const Vector3f& v1,const Vector3f& v2);
}