/**
 * @file oaVector2f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK {

/**
 * @brief bidimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector2f
{
 public:
  /**
   * @brief default constructor for the vector2f
  */
  Vector2f() = default;

  /**
   * @brief constructor with parameters
   * @param _x 
   * @param _y 
  */
  Vector2f(float _x, float _y) :x(_x), y(_y) {}
  
  ~Vector2f() = default;

  /**
  * @brief adds the vector v and this one
   * @param v
   * @return
  */

  Vector2f
  operator+(const Vector2f& v);
  /**
   * @brief adds the vector v to this one
   * @param v
  */

  Vector2f&
  operator+=(const Vector2f& v);
  /**
   * @brief this vector minus vector v
   * @param v
   * @return
  */

  Vector2f
  operator-(const Vector2f& v);
  /**
   * @brief substract vector v from this
   * @param v
  */

  Vector2f&
  operator-=(const Vector2f& v);
  /**
   * @brief calculates a vector with the same direction as this and a lenght multiplied by v
   * @param v
   * @return
  */

  Vector2f
  operator*(float v) const;
  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */

  Vector2f&
  operator*=(float v);

  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  Vector2f
  operator/(float v);

  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  Vector2f&
  operator/=(float v);

  /**
   * @brief multiplies each parameter for its congruent in the other vector
   * @param v 
   * @return 
  */
  Vector2f
  operator*(const Vector2f& v);

  /**
   * @brief dot product of to vector
   * @param v
   * @return
  */
  float
  dot (const Vector2f& v) const;

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
  Vector2f
  normal();

  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  Vector2f
  project(const Vector2f& v);

  /**
   * @brief the direction in radians of the vector
   * @return
  */
  float
  getDirection();

  /**
   * @brief changes the direction of the vector to r in radians and the lenght stays the same
   * @return
  */
  void
  setDirection(float r);

 public:
  /**
   * @brief the x component of the vector
  */
  float x;

  /**
   * @brief the y component of the vector
  */
  float y;

};

bool OA_UTILITY_EXPORT
operator==(const Vector2f& v1, const  Vector2f& v2);
}