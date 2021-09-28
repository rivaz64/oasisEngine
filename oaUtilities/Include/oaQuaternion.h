/**
 * @file oaQuaternion.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/11/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief a class for quaternion numbers
*/
class OA_UTILITY_EXPORT Quaternion
{
public:
  /**
   * @brief default constructor for the Quaternions
  */
  Quaternion() = default;
  /**
   * @brief parametrized constructor for the Quaternion
   * @param _r 
   * @param _i 
   * @param _j 
   * @param _k 
  */
  Quaternion(float _r, float _i, float _j, float _k) :
    r(_r), i(_i), j(_j), k(_k) {}

  ~Quaternion() = default;

  /**
   * @brief compares if two quaternions are the same
   * @param q
   * @return 
  */
  bool 
  operator==(Quaternion q);

  /**
   * @brief adds the quaternion q and this one
   * @param q
   * @return
  */
  Quaternion
  operator+(Quaternion& q);

  /**
   * @brief adds the quaternion q to this one
   * @param q
  */
  void
  operator+=(Quaternion& q);

  /**
   * @brief this quaternion minus vector q
   * @param q
   * @return
  */
  Quaternion
  operator-(Quaternion& q);

  /**
   * @brief substract the quaternion q from this
   * @param q
  */
  void
  operator-=(Quaternion& q);

  /**
   * @brief quaternion multiplication
   * @param q 
   * @return 
  */
  Quaternion
  operator*(Quaternion& q);

  /**
   * @brief multiply q to this quaternion
   * @param q
  */
  void
  operator*=(Quaternion& q);

  /**
   * @brief gives the conjugate of this quaternion
   * @return r-i-j-k
  */
  Quaternion
  conjugate();

  /**
   * @brief gives the inverse of this quaternion
   * @return 
  */
  Quaternion
  inverse();

  /**
   * @brief gives this quaternion in its unitary form
   * @return
  */
  Quaternion 
  normal();

  /**
   * @brief gives the rotation matrix of this quaternion
   * @return
  */
  Matrix4f 
  toMatrix();

 public:
  /**
   * @brief real part of the quaternion
  */
  float r;
  /**
   * @brief the i component of the quaternion
  */
  float i;
  /**
   * @brief the j component of the quaternion
  */
  float j;
  /**
   * @brief the k component of the quaternion
  */
  float k;
};

}


