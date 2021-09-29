/**
 * @file oaQuaternion.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/11/2021
 */

#include "oaQuaternion.h"
#include "oaVector4f.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK {

bool const
Quaternion::operator==(const Quaternion& q) const
{
  return r==q.r&& i == q.i&& j == q.j&& k == q.k;
}

Quaternion 
Quaternion::operator+(const Quaternion& q) const
{
  return { r + q.r,i+q.i,j+q.j,k+q.k };
}

void 
Quaternion::operator+=(const Quaternion& q)
{
  r += q.r;
  i += q.i;
  j += q.j;
  k += q.k;
}

Quaternion 
Quaternion::operator-(const Quaternion& q) const 
{
  return { r - q.r,i - q.i,j - q.j,k - q.k };
}

void 
Quaternion::operator-=(const Quaternion& q)
{
  r -= q.r;
  i -= q.i;
  j -= q.j;
  k -= q.k;
}

Quaternion 
Quaternion::operator*(const Quaternion& q) const
{
  return { r * q.r - i * q.i - j * q.j - k * q.k,
           i * q.r + j * q.k - k * q.j + r * q.i,
           j * q.r + k * q.i + r * q.j - i * q.k,
           k * q.r + r * q.k + i * q.j - j * q.i,};
}

void 
Quaternion::operator*=(const Quaternion& q)
{
  r = r * q.r - i * q.i - j * q.j - k * q.k;
  i = i * q.r + j * q.k - k * q.j + r * q.i;
  j = j * q.r + k * q.i + r * q.j - i * q.k;
  k = k * q.r + r * q.k + i * q.j - j * q.i;
}

Quaternion 
Quaternion::conjugated() const
{
  return { r,-i,-j,-k };
}

void Quaternion::conjugate()
{
  i = -i;
  j = -j;
  k = -k;
}

Quaternion
Quaternion::inverse() const
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,-i / absVal,-j / absVal,-k / absVal };
}

void Quaternion::invert()
{
  float absValInv = 1.f / (r * r + i * i + j * j + k * k);
  r *= absValInv;
  i *= -absValInv;
  j *= -absValInv;
  k *= -absValInv;
}

Quaternion 
Quaternion::normal() const
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,i / absVal,j / absVal,k / absVal };
}

Matrix4f 
Quaternion::toMatrix() const
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
  return { 1.f - j2 + k2,ij - rk,ik + rj,0.0f,
          ij + rk,1.f - i2 + k2,jk - ri,0.0f,
          ik - rj,jk + ri,1.f - i2 + j2,0.0f,
          0.0f,0.0f,0.0f,1.0f};
}

}
