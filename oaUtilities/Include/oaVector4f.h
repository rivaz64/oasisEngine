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
   * @brief adds the vector v and this one
   * @param v
   * @return
  */
  Vector4f
  operator+(const Vector4f& v);

  /**
   * @brief adds the vector v to this one
   * @param v
  */
  Vector4f&
  operator+=(const Vector4f& v);

  /**
   * @brief this vector minus vector v
   * @param v
   * @return
  */
  Vector4f
  operator-(const Vector4f& v);

  /**
   * @brief substract vector v from this
   * @param v
  */
  Vector4f&
  operator-=(const Vector4f& v);

  /**
   * @brief calculates a vector with the same direction as this and a lenght multiplied by v
   * @param v
   * @return
  */
  Vector4f
  operator*(float v) const;

  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */
  Vector4f&
  operator*=(float v);

  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  Vector4f
  operator/(float v);

  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  Vector4f&
  operator/=(float v);

  /**
   * @brief multiplies each parameter for its congruent in the other vector
   * @param v
   * @return
  */
  Vector4f
    operator*(const Vector4f& v);

  /**
   * @brief dot product of to vector
   * @param v
   * @return
  */
  float
  dot(const Vector4f& v) const;

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
  Vector4f
  normal();

  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  Vector4f
  project(const Vector4f& v);

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
bool OA_UTILITY_EXPORT
operator==(const Vector4f& v1, const Vector4f& v2);
}
