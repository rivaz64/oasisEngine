/**
 * @file oaVector4f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#include "oaVector4f.h"

namespace oaEngineSDK {
float&
Vector4f::operator[](uint8 i) {
  return ((&x)[i]);
}
Vector4f
Vector4f::operator+(const Vector4f& v)
{
  return { x + v.x , y + v.y, z + v.z, w + v.w };
}
void
Vector4f::operator+=(const Vector4f& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;

}
Vector4f
Vector4f::operator-(const Vector4f& v)
{
  return { x - v.x , y - v.y, z - v.z, w - v.w };
}

void
Vector4f::operator-=(const Vector4f& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
}

Vector4f
Vector4f::operator*(float v) const
{
  return { x * v , y * v , z * v, w * v };
}

void
Vector4f::operator*=(float v)
{
  x *= v;
  y *= v;
  z *= v;
  w *= v;
}

Vector4f
Vector4f::operator/(float v)
{
  v = 1.f / v;
  return { x * v , y * v, z * v , w * v };
}

void
Vector4f::operator/=(float v)
{
  v = 1.f / v;
  x *= v;
  y *= v;
  z *= v;
  w *= v;
}

float
Vector4f::dot(const Vector4f& v) const
{
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

float
Vector4f::len()
{
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

Vector4f
Vector4f::normal()
{
  return *this * Math::invSqrt(x * x + y * y + z * z + w * w);
}

Vector4f
Vector4f::project(const Vector4f& v)
{
  return v * (dot(v) / v.dot(v));
}


bool
operator==(const Vector4f& v1, const Vector4f& v2)
{
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

}


