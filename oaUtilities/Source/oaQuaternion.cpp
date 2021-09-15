/**
 * @file oaQuaternion.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/11/2021
 */

#include "oaQuaternion.h"
#include "oaVector4f.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK {
Quaternion oaEngineSDK::Quaternion::operator+(Quaternion& q)
{
  return { r + q.r,i+q.i,j+q.j,k+q.k };
}
void Quaternion::operator+=(Quaternion& q)
{
  r += q.r;
  i += q.i;
  j += q.j;
  k += q.k;
}
Quaternion Quaternion::operator-(Quaternion& q)
{
  return { r - q.r,i - q.i,j - q.j,k - q.k };
}
void Quaternion::operator-=(Quaternion& q)
{
  r -= q.r;
  i -= q.i;
  j -= q.j;
  k -= q.k;
}
Quaternion Quaternion::operator*(Quaternion& q)
{
  return { r * q.r - i * q.i - j * q.j - k * q.k,
           i * q.r + j * q.k - k * q.j + r * q.i,
           j * q.r + k * q.i + r * q.j - i * q.k,
           k * q.r + r * q.k + i * q.j - j * q.i,};
}
void Quaternion::operator*=(Quaternion& q)
{
  r = r * q.r - i * q.i - j * q.j - k * q.k;
  i = i * q.r + j * q.k - k * q.j + r * q.i;
  j = j * q.r + k * q.i + r * q.j - i * q.k;
  k = k * q.r + r * q.k + i * q.j - j * q.i;
}
Quaternion Quaternion::conjugate()
{
  return { r,-i,-j,-k };
}
Quaternion Quaternion::inverse()
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,-i / absVal,-j / absVal,-k / absVal };
}
Quaternion Quaternion::normal()
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,i / absVal,j / absVal,k / absVal };
}
Matrix4f Quaternion::toMatrix()
{
  float i2 = 2*i * i;
  float j2 = 2 * j * j;
  float k2 = 2 * k * k;
  float ij = 2 * i * j;
  float jk = 2 * j * k;
  float ik = 2 * i * k;
  float ri = 2 * r * i;
  float rj = 2 * r * j;
  float rk = 2 * r * k;
  return { {1.f - j2 + k2,ij - rk,ik + rj,0.0f},
          {ij + rk,1.f - i2 + k2,jk - ri,0.0f},
          {ik - rj,jk + ri,1.f - i2 + j2,0.0f},
          {0.0f,0.0f,0.0f,1.0f} };
}
bool OA_UTILITY_EXPORT operator==(Quaternion q1, Quaternion q2)
{
  return q1.r==q2.r&& q1.i == q2.i&& q1.j == q2.j&& q1.k == q2.k;
}
}

