/**
 * @file oaMatrix3f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */


#include "oaMatrix3f.h"
#include"oaVector2f.h"
#include"oaVector3f.h"

namespace oaEngineSDK {

Matrix3f
Matrix3f::operator+(const Matrix3f& m)
{
  return {
    m11 + m.m11,m12 + m.m12,m13 + m.m13,
    m21 + m.m21,m22 + m.m22,m23 + m.m23,
    m31 + m.m31,m32 + m.m32,m33 + m.m33
  };
}

Matrix3f&
Matrix3f::operator+=(const Matrix3f& m)
{
  m11 += m.m11;
  m12 += m.m12;
  m13 += m.m13;
  m21 += m.m21;
  m22 += m.m22;
  m23 += m.m23;
  m31 += m.m31;
  m32 += m.m32;
  m33 += m.m33;
  return *this;
}

Matrix3f
Matrix3f::operator-(const Matrix3f& m)
{
  return {
    m11 - m.m11,m12 - m.m12,m13 - m.m13,
    m21 - m.m21,m22 - m.m22,m23 - m.m23,
    m31 - m.m31,m32 - m.m32,m33 - m.m33
  };
}

Matrix3f&
Matrix3f::operator-=(const Matrix3f& m)
{
  m11 -= m.m11;
  m12 -= m.m12;
  m13 -= m.m13;
  m21 -= m.m21;
  m22 -= m.m22;
  m23 -= m.m23;
  m31 -= m.m31;
  m32 -= m.m32;
  m33 -= m.m33;
  return *this;
}

Matrix3f
Matrix3f::operator*(float m)
{
  return {
    m11* m,m12* m,m13* m,
    m21* m,m22* m,m23* m,
    m31* m,m32* m,m33* m
  };
}

Matrix3f&
Matrix3f::operator*=(float m)
{
  m11 *= m;
  m12 *= m;
  m13 *= m;
  m21 *= m;
  m22 *= m;
  m23 *= m;
  m31 *= m;
  m32 *= m;
  m33 *= m;
  return *this;
}

Vector3f
Matrix3f::operator*(const Vector3f& v)
{
  return { 
  m11 * v.x + m12 * v.y + m13 * v.z,
  m21 * v.x + m22 * v.y + m23 * v.z, 
  m31 * v.x + m32 * v.y + m33 * v.z, };
}

Matrix3f
Matrix3f::operator*(const Matrix3f& m)
{
  return {
    m11* m.m11 + m12 * m.m21 + m13 * m.m31,
    m11* m.m12 + m12 * m.m22 + m13 * m.m32,
    m11* m.m13 + m12 * m.m23 + m13 * m.m33,
    m21* m.m11 + m22 * m.m21 + m23 * m.m31,
    m21* m.m12 + m22 * m.m22 + m23 * m.m32,
    m21* m.m13 + m22 * m.m23 + m23 * m.m33,
    m31* m.m11 + m32 * m.m21 + m33 * m.m31,
    m31* m.m12 + m32 * m.m22 + m33 * m.m32,
    m31* m.m13 + m32 * m.m23 + m33 * m.m33,
  };
}

Matrix3f&
Matrix3f::operator*=(const Matrix3f& m)
{
  m11 = m11* m.m11 + m12 * m.m21 + m13 * m.m31;
  m12 = m11* m.m12 + m12 * m.m22 + m13 * m.m32;
  m13 = m11* m.m13 + m12 * m.m23 + m13 * m.m33;
  m21 = m21* m.m11 + m22 * m.m21 + m23 * m.m31;
  m22 = m21* m.m12 + m22 * m.m22 + m23 * m.m32;
  m23 = m21* m.m13 + m22 * m.m23 + m23 * m.m33;
  m31 = m31* m.m11 + m32 * m.m21 + m33 * m.m31;
  m32 = m31* m.m12 + m32 * m.m22 + m33 * m.m32;
  m33 = m31* m.m13 + m32 * m.m23 + m33 * m.m33;
  return *this;
}
void
Matrix3f::transpose()
{
  swap(m12, m21);
  swap(m13, m31);
  swap(m23, m32);
}
float
Matrix3f::determinant()
{
  return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32
    - m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
}



Matrix3f
Matrix3f::inverse()
{
  Vector3f a = { m11,m12,m13 };
  Vector3f b = { m21,m22,m23 };
  Vector3f c = { m31,m32,m33 };
  Vector3f r0 = b.cross(c);
  Vector3f r1 = c.cross(a);
  Vector3f r2 = a.cross(b);
  float invDet = 1.f / c.dot(r2);
  return {
    r0.x * invDet,r1.x * invDet,r2.x * invDet,
    r0.y * invDet,r1.y * invDet,r2.y * invDet,
    r0.z * invDet,r1.z * invDet,r2.z * invDet };
}

Matrix3f
Matrix3f::translateMatrix(const Vector2f& v)
{
  return { 1.f,0.f,v.x ,
           0.f,1.f,v.y ,
           0.f,0.f,1.f };
}

Matrix3f
Matrix3f::scaleMatrix(const Vector2f& v)
{
  return { v.x,0.f,0.f ,
           0.f,v.y,0.f ,
           0.f,0.f,1.f };
}

Matrix3f
Matrix3f::rotationMatrix(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return{ c,-s,0.f ,
          s, -c, 0.f ,
          0.f,0.f,1.f };
}

bool
OA_UTILITY_EXPORT operator==(const Matrix3f& m1, const Matrix3f& m2)
{
  return
    m1.m11 == m2.m11 &&
    m1.m12 == m2.m12 &&
    m1.m13 == m2.m13 &&
    m1.m21 == m2.m21 &&
    m1.m22 == m2.m22 &&
    m1.m23 == m2.m23 &&
    m1.m31 == m2.m31 &&
    m1.m32 == m2.m32 &&
    m1.m33 == m2.m33;
}
}

