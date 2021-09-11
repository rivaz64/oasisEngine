#include "oaVector3f.h"
namespace oaEngineSDK {
const Vector3f Vector3f::RIGHT = Vector3f(1, 0, 0);
const Vector3f Vector3f::LEFT = Vector3f(-1, 0, 0);
const Vector3f Vector3f::UP = Vector3f(0, 1, 0);
const Vector3f Vector3f::DOWN = Vector3f(0, -1, 0);
const Vector3f Vector3f::FRONT = Vector3f(0, 0, 1);
const Vector3f Vector3f::BACK = Vector3f(0, 0, -1);

float&
Vector3f::operator[](uint8 i) {
  return ((&x)[i]);
}
Vector3f
Vector3f::operator+(Vector3f& v)
{
  return { x + v.x , y + v.y, z + v.z };
}
void
Vector3f::operator+=(Vector3f& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
}
Vector3f
Vector3f::operator-(Vector3f& v)
{
  return { x - v.x , y - v.y, z - v.z };
}

void
Vector3f::operator-=(Vector3f& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

Vector3f
Vector3f::operator*(float v)
{
  return { x * v , y * v , z * v };
}

void
Vector3f::operator*=(float v)
{
  x *= v;
  y *= v;
  z *= v;
}

Vector3f
Vector3f::operator/(float v)
{
  v = 1.f / v;
  return { x * v , y * v, z * v };
}

void
Vector3f::operator/=(float v)
{
  v = 1.f / v;
  x *= v;
  y *= v;
  z *= v;
}

float
Vector3f::dot(Vector3f& v)
{
  return x * v.x + y * v.y + z * v.z;
}

float
Vector3f::len()
{
  return Math::Sqrt(x * x + y * y + z * z);
}

Vector3f
Vector3f::normal()
{
  return *this * Math::InvSqrt(x * x + y * y + z * z);
}

Vector3f
Vector3f::cross(Vector3f& v)
{
  return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3f
Vector3f::project(Vector3f& v)
{
  return v * (dot(v) / v.dot(v));
}


bool
operator==(Vector3f v1, Vector3f v2)
{
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

}


