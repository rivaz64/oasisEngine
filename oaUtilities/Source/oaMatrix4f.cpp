/**
 * @file oaMatrix4f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */


#include "oaMatrix4f.h"
#include "oaVector3f.h"
#include "oaVector4f.h"

namespace oaEngineSDK {

Matrix4f
Matrix4f::operator+(const Matrix4f& m)
{
  return {
    m11 + m.m11,m12 + m.m12,m13 + m.m13,m14 + m.m14,
    m21 + m.m21,m22 + m.m22,m23 + m.m23,m24 + m.m24,
    m31 + m.m31,m32 + m.m32,m33 + m.m33,m34 + m.m34,
    m41 + m.m41,m42 + m.m42,m43 + m.m43,m44 + m.m44
  };
}

Matrix4f&
Matrix4f::operator+=(const Matrix4f& m)
{
  m11 += m.m11;
  m12 += m.m12;
  m13 += m.m13;
  m14 += m.m14;
  m21 += m.m21;
  m22 += m.m22;
  m23 += m.m23;
  m24 += m.m24;
  m31 += m.m31;
  m32 += m.m32;
  m33 += m.m33;
  m34 += m.m34;
  m41 += m.m41;
  m42 += m.m42;
  m43 += m.m43;
  m44 += m.m44;
  return *this;
}

Matrix4f
Matrix4f::operator-(const Matrix4f& m)
{
  return {
    m11 - m.m11,m12 - m.m12,m13 - m.m13,m14 - m.m14,
    m21 - m.m21,m22 - m.m22,m23 - m.m23,m24 - m.m24,
    m31 - m.m31,m32 - m.m32,m33 - m.m33,m34 - m.m34,
    m41 - m.m41,m42 - m.m42,m43 - m.m43,m44 - m.m44
  };
}

Matrix4f&
Matrix4f::operator-=(const Matrix4f& m)
{
  m11 -= m.m11;
  m12 -= m.m12;
  m13 -= m.m13;
  m14 -= m.m14;
  m21 -= m.m21;
  m22 -= m.m22;
  m23 -= m.m23;
  m24 -= m.m24;
  m31 -= m.m31;
  m32 -= m.m32;
  m33 -= m.m33;
  m34 -= m.m34;
  m41 -= m.m41;
  m42 -= m.m42;
  m43 -= m.m43;
  m44 -= m.m44;
  return *this;
}

Matrix4f
Matrix4f::operator*(const float m)
{
  return {
    m11 * m,m12 * m,m13 * m,m14 * m,
    m21 * m,m22 * m,m23 * m,m24 * m,
    m31 * m,m32 * m,m33 * m,m34 * m,
    m41 * m,m42 * m,m43 * m,m44 * m
  };
}

Matrix4f&
Matrix4f::operator*=(float m)
{
  m11 *= m;
  m12 *= m;
  m13 *= m;
  m14 *= m;
  m21 *= m;
  m22 *= m;
  m23 *= m;
  m24 *= m;
  m31 *= m;
  m32 *= m;
  m33 *= m;
  m34 *= m;
  m41 *= m;
  m42 *= m;
  m43 *= m;
  m44 *= m;
  return *this;
}
Vector4f
Matrix4f::operator*(const Vector4f& v)
{
  return {
  m11 * v.x + m12 * v.y + m13 * v.z + m14 * v.w,
  m21 * v.x + m22 * v.y + m23 * v.z + m24 * v.w,
  m31 * v.x + m32 * v.y + m33 * v.z + m34 * v.w,
  m41 * v.x + m42 * v.y + m43 * v.z + m44 * v.w, };
}
Matrix4f
Matrix4f::operator*(const Matrix4f& m)
{
  return {
    m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41,
    m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42,
    m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43,
    m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44,
    m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41,
    m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42,
    m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43,
    m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44,
    m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41,
    m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42,
    m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43,
    m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44,
    m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41,
    m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42,
    m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43,
    m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44,
  };
}

Matrix4f&
Matrix4f::operator*=(const Matrix4f& m)
{
  m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41;
  m12 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42;
  m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43;
  m14 = m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44;
  m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41;
  m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42;
  m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43;
  m24 = m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44;
  m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41;
  m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42;
  m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43;
  m34 = m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44;
  m41 = m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41;
  m42 = m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42;
  m43 = m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43;
  m44 = m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44;
  return *this;
}
void
Matrix4f::transpose()
{
  swap(m12, m21);
  swap(m13, m31);
  swap(m14, m41);
  swap(m23, m32);
  swap(m24, m42);
  swap(m34, m43);
}
/*
float
Matrix4f::determinant()
{
  float ans = 0;
  Matrix3f tempMatrix;
  tempMatrix = { { b.x,b.y,b.z }, { c.x,c.y,c.z }, { d.x,d.y,d.z } };
  ans -= tempMatrix.determinant() * a.w;
  tempMatrix.a = { a.x,a.y,a.z };
  ans += tempMatrix.determinant() * b.w;
  tempMatrix.b = { b.x,b.y,b.z };
  ans -= tempMatrix.determinant() * c.w;
  tempMatrix.c = { c.x,c.y,c.z };
  ans += tempMatrix.determinant() * d.w;
  return ans;
}
*/

Matrix4f
Matrix4f::inverse()
{
  float a3434 = m33 * m44 - m34 * m43;
  float a2434 = m32 * m44 - m34 * m42;
  float a2334 = m32 * m43 - m33 * m42;
  float a1434 = m31 * m44 - m34 * m41;
  float a1334 = m31 * m43 - m33 * m41;
  float a1234 = m31 * m42 - m32 * m41;
  float a3424 = m23 * m44 - m24 * m43;
  float a2424 = m22 * m44 - m24 * m42;
  float a2324 = m22 * m43 - m23 * m42;
  float a3423 = m23 * m34 - m24 * m33;
  float a2423 = m22 * m34 - m24 * m32;
  float a2323 = m22 * m33 - m23 * m32;
  float a1424 = m21 * m44 - m24 * m41;
  float a1324 = m21 * m43 - m23 * m41;
  float a1423 = m21 * m34 - m24 * m31;
  float a1323 = m21 * m33 - m23 * m31;
  float a1224 = m21 * m41 - m22 * m41;
  float a1223 = m21 * m31 - m22 * m31;

  float det = m11 * (m22 * a3434 - m23 * a2434 + m24 * a2334)
    - m12 * (m21 * a3434 - m23 * a1434 + m24 * a1334)
    + m13 * (m21 * a2434 - m22 * a1434 + m24 * a1234)
    - m14 * (m21 * a2334 - m22 * a1334 + m23 * a1234);
  float invDet = 1.f / det;

  Matrix4f inv = {
    invDet *  (m22 * a3434 - m23 * a2434 + m24 * a2334),
    invDet * -(m21 * a3434 - m23 * a1434 + m24 * a1334),
    invDet *  (m21 * a2434 - m22 * a1434 + m24 * a1234),
    invDet * -(m21 * a2334 - m22 * a1334 + m23 * a1234),
    invDet * -(m12 * a3434 - m13 * a2434 + m14 * a2334),
    invDet *  (m11 * a3434 - m13 * a1434 + m14 * a1334),
    invDet * -(m11 * a2434 - m12 * a1434 + m14 * a1234),
    invDet *  (m11 * a2334 - m12 * a1334 + m13 * a1234),
    invDet *  (m12 * a3424 - m13 * a2424 + m14 * a2324),
    invDet * -(m11 * a3424 - m13 * a1424 + m14 * a1324),
    invDet *  (m11 * a2424 - m12 * a1424 + m14 * a1224),
    invDet * -(m11 * a2324 - m12 * a1324 + m13 * a1224),
    invDet * -(m12 * a3423 - m13 * a2423 + m14 * a2323),
    invDet *  (m11 * a3423 - m13 * a1423 + m14 * a1323),
    invDet * -(m11 * a2423 - m12 * a1423 + m14 * a1223),
    invDet *  (m11 * a2323 - m12 * a1323 + m13 * a1223)
    
  };
  return inv;
}
Matrix4f 
Matrix4f::translateMatrix(const Vector3f& v)
{
  return {
    1.f,0.f,0.f,v.x,
    0.f,1.f,0.f,v.y,
    0.f,0.f,1.f,v.z,
    0.f,0.f,0.f,1.f,
  };
}
Matrix4f 
Matrix4f::scaleMatrix(const Vector3f& v)
{
  return {
    v.x,0.f,0.f,0.f,
    0.f,v.y,0.f,0.f,
    0.f,0.f,v.z,0.f,
    0.f,0.f,0.f,1.f
  };
}
Matrix4f
Matrix4f::rotationMatrixZ(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return {
    c,-s,0.f,0.f,
    s,c,0.f,0.f,
    0.f,0.f,1.f,0.f,
    0.f,0.f,0.f,1.f
  };
}
Matrix4f 
Matrix4f::rotationMatrixX(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return {
    1.f,0.f,0.f,0.f,
    0.f,c,-s,0.f,
    0.f,s,c,0.f,
    0.f,0.f,0.f,1.f
  };
}
Matrix4f 
Matrix4f::rotationMatrixY(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return {
    c,0.f,s,0.f,
    0.f,1.f,0.f,0.f,
    -s,0.f,c,0.f,
    0.f,0.f,0.f,1.f,
  };
}
Matrix4f 
Matrix4f::rotationMatrix(float r, Vector3f& v)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  float mc = 1 - c;
  float xy = v.x * v.y * mc;
  float xz = v.x * v.z * mc;
  float yz = v.y * v.z * mc;
  float sx = s * v.x;
  float sy = s * v.y;
  float sz = s * v.z;
  return  {
    c + mc * v.x * v.x,xy - sz , xz + sy,0.f,
    xz + sz ,c + mc * v.y * v.y,yz - sx,0.f ,
    xz - sy,yz + sx,c + mc * v.y * v.y,0.f  ,
    0.f,0.f,0.f,1.f                         ,
  };
}

bool OA_UTILITY_EXPORT 
operator==(const Matrix4f& m1, const Matrix4f& m2)
{
  return 
    m1.m11 == m2.m11 &&
    m1.m12 == m2.m12 &&
    m1.m13 == m2.m13 &&
    m1.m14 == m2.m14 &&
    m1.m21 == m2.m21 &&
    m1.m22 == m2.m22 &&
    m1.m23 == m2.m23 &&
    m1.m24 == m2.m24 &&
    m1.m31 == m2.m31 &&
    m1.m32 == m2.m32 &&
    m1.m33 == m2.m33 &&
    m1.m34 == m2.m34 &&
    m1.m41 == m2.m41 &&
    m1.m42 == m2.m42 &&
    m1.m43 == m2.m43 &&
    m1.m44 == m2.m44;
}
}
