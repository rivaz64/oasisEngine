#pragma once
#include"oaPrerequisitesUtilities.h"
namespace oaEngineSDK {
class OA_UTILITY_EXPORT Quaternion
{
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
  Quaternion() = default;
  Quaternion(float _r, float _i, float _j, float _k) :r(_r), i(_i), j(_j), k(_k) {}
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
};
}


