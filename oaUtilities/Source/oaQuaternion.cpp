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
Quaternion::operator-() const
{
  return {-r,-i,-j,-k};
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
  float i2 = 2.f *i * i;
  float j2 = 2.f * j * j;
  float k2 = 2.f * k * k;
  float ij = 2.f * i * j;
  float jk = 2.f * j * k;
  float ik = 2.f * i * k;
  float ri = 2.f * r * i;
  float rj = 2.f * r * j;
  float rk = 2.f * r * k;
  return {1.f - j2 - k2 ,ij - rk       ,ik + rj       ,0.0f,
          ij + rk       ,1.f - i2 - k2 ,jk - ri       ,0.0f,
          ik - rj       ,jk + ri       ,1.f - i2 - j2 ,0.0f,
          0.0f          ,0.0f          ,0.0f          ,1.0f};
}

void 
Quaternion::fromEulerAngles(const Vector3f& eulerAngles)
{
  float c1 = Math::cos(eulerAngles.y * .5f);
  float s1 = Math::sin(eulerAngles.y * .5f);
  float c2 = Math::cos(eulerAngles.z * .5f);
  float s2 = Math::sin(eulerAngles.z * .5f);
  float c3 = Math::cos(eulerAngles.x * .5f);
  float s3 = Math::sin(eulerAngles.x * .5f);
  float c1c2 = c1 * c2;
  float s1s2 = s1 * s2;
  r =c1c2 * c3 - s1s2 * s3;
  i =c1c2 * s3 + s1s2 * c3;
  j =s1 * c2 * c3 + c1 * s2 * s3;
  k =c1 * s2 * c3 - s1 * c2 * s3;
}

Vector3f Quaternion::toEulerAngles() const
{
  Vector3f ans;
  float sqr = r*r;
  float sqi = i*i;
  float sqj = j*j;
  float sqk = k*k;
  float unit = i + j + k + r; 
  float test = i*j + k*r;
  if (test > 0.499*unit) { 
    ans.y = 2.f * Math::atan2(r,i);
    ans.z = Math::HALF_PI;
    ans.x = 0.f;
    return ans;
  }
  if (test < -0.499*unit) { 
    ans.y = -2.f * atan2(r,i);
    ans.z = -Math::HALF_PI;
    ans.x = 0.f;
    return ans;
  }
  ans.y = Math::atan2(sqi - sqj - sqk + sqr,2.f*j*r-2*i*k);
  ans.z = Math::asin(2.f*test/unit);
  ans.x = Math::atan2(-sqi + sqj - sqk + sqr,2*i*r-2*j*k);
  return ans;
}



Quaternion Quaternion::interpolate(Quaternion a, Quaternion b, const float t)
{
  float cosom = a.r*b.r+a.i*b.i+a.j*b.j+a.k*b.k;

  if(cosom < 0.0f){
    cosom = -cosom;
    b = -b;
  }

  float sclp, sclq;

  if( 1.0 - cosom > 0.0001){
    float omega, sinom;
    omega = Math::acos(cosom);
    sinom = Math::sin(omega);
    sclp  = Math::sin( (1.0 - t) * omega) / sinom;
    sclq  = Math::sin( t * omega) / sinom;
  }
  else{
    sclp = 1.0 - t;
    sclq = t;
  }

  return {
  sclp * a.r + sclq * b.r,
  sclp * a.i + sclq * b.i,
  sclp * a.j + sclq * b.j,
  sclp * a.k + sclq * b.k,
  };
}

}
