#include "oaVector2f.h"
namespace oaEngineSDK {
float&
Vector2f::operator[](const uint8 i) {
  return ((&x)[i]);
}
Vector2f
Vector2f::operator+(const Vector2f& v)
{
  return { x + v.x , y + v.y };
}
void
Vector2f::operator+=(const Vector2f& v)
{
  x += v.x;
  y += v.y;
}
Vector2f
Vector2f::operator-(const Vector2f& v)
{
  return { x - v.x , y - v.y };
}

void
Vector2f::operator-=(const Vector2f& v)
{
  x -= v.x;
  y -= v.y;
}

Vector2f
Vector2f::operator*(const float v) const
{
  return { x * v , y * v };
}

void
Vector2f::operator*=(const float v)
{
  x *= v;
  y *= v;
}

Vector2f Vector2f::operator/(float v)
{
  v = 1.f / v;
  return { x * v , y * v };
}

void
Vector2f::operator/=(float v)
{
  v = 1.f / v;
  x *= v;
  y *= v;
}

float
Vector2f::dot(const Vector2f& v) const
{
  return x * v.x + y * v.y;
}

float
Vector2f::len()
{
  return Math::sqrt(x * x + y * y);
}

Vector2f
Vector2f::normal()
{
  return *this * Math::invSqrt(x * x + y * y);
}

Vector2f
Vector2f::project(const Vector2f& v)
{
  return v * (dot(v) / v.dot(v));
}

float
Vector2f::getDirection()
{

  return Math::atan2(x, y);
}

void
Vector2f::setDirection(const float r)
{
  float l = len();
  x = l * Math::cos(r);
  y = l * Math::sin(r);
}



bool OA_UTILITY_EXPORT operator==(const Vector2f& v1, const Vector2f& v2)
{
  return v1.x == v2.x && v1.y == v2.y;
}

}

