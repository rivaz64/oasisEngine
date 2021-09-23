/**
 * @file oaVector3f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#include "oaVector2f.h"
#include "oaVector3f.h"


namespace oaEngineSDK {
const Vector3f Vector3f::RIGHT = Vector3f(1, 0, 0);
const Vector3f Vector3f::LEFT = Vector3f(-1, 0, 0);
const Vector3f Vector3f::UP = Vector3f(0, 1, 0);
const Vector3f Vector3f::DOWN = Vector3f(0, -1, 0);
const Vector3f Vector3f::FRONT = Vector3f(0, 0, 1);
const Vector3f Vector3f::BACK = Vector3f(0, 0, -1);

Vector3f
Vector3f::operator+(const Vector3f& v)
{
  return { x + v.x , y + v.y, z + v.z };
}

Vector3f&
Vector3f::operator+=(const Vector3f& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vector3f
Vector3f::operator-(const Vector3f& v)
{
  return { x - v.x , y - v.y, z - v.z };
}

Vector3f&
Vector3f::operator-=(const Vector3f& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector3f
Vector3f::operator*(float v) const
{
  return { x * v , y * v , z * v };
}

Vector3f&
Vector3f::operator*=(float v)
{
  x *= v;
  y *= v;
  z *= v;
  return *this;
}

Vector3f
Vector3f::operator/(float v)
{
  v = 1.f / v;
  return { x * v , y * v, z * v };
}

Vector3f&
Vector3f::operator/=(float v)
{
  v = 1.f / v;
  x *= v;
  y *= v;
  z *= v;
  return *this;
}

Vector3f Vector3f::operator*(const Vector3f& v)
{
    return { x * v.x,y * v.y,z * v.z };
}

float
Vector3f::dot(const Vector3f& v) const
{
  return x * v.x + y * v.y + z * v.z;
}

float
Vector3f::len()
{
  return Math::sqrt(x * x + y * y + z * z);
}

Vector3f
Vector3f::normal()
{
  return *this * Math::invSqrt(x * x + y * y + z * z);
}

Vector3f
Vector3f::cross(const Vector3f& v)
{
  return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3f
Vector3f::project(const Vector3f& v)
{
  return v * (dot(v) / v.dot(v));
}

void Vector3f::rotate(Quaternion q)
{
  q = q.normal();
  Vector3f b = { q.i,q.j,q.k };
  float b2 = b.x * b.x + b.y * b.y + b.z * b.z;
  float thisdot = dot(b);
  *this = (*this * (q.r * q.r - b2) + b * (dot(b) * 2.0f)+ cross(b) * (q.r * 2.0f));
}

bool
operator==(const Vector3f& v1, const Vector3f& v2)
{
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}


}


