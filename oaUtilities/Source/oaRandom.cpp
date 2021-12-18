#include "oaRandom.h"
#include "oaVector2f.h"
#include "oaVector3f.h"

namespace oaEngineSDK{

float 
Random::noise1D(const float point)
{
  return Math::mod(Math::sin(point*12.9898f+78.233f)*43758.5453123f,1);
}

float
Random::noise2D(const Vector2f& point)
{
  return Math::mod(Math::sin(Vector2f::dot(point,Vector2f(12.9898f,78.233f)))*43758.5453123f,1);
}

float
Random::noise3D(const Vector3f& point)
{
  return Math::mod(Math::sin(Vector3f::dot(point,Vector3f(12.9898f,78.233f,471.1698)))*43758.5453123f,1);
}

Vector2f
Random::vector2()
{
  float value = unit()*Math::TWO_PI;
  return Vector2f(Math::cos(value),Math::sin(value));
}

Vector2f
Random::vector2(const Vector2f& point)
{
  float value = noise2D(point)*Math::TWO_PI;
  return Vector2f(Math::cos(value),Math::sin(value));
}

float 
Random::gaussian()
{
  return Math::sqrt(-2.f*Math::log(unit()))*Math::cos(unit()*Math::TWO_PI);
}

float Random::gaussian(const float point)
{
  float u = Math::abs(noise1D(point));
  float v = Math::abs(noise1D(point+u));
  return Math::sqrt(-2.f*Math::log(u))*Math::cos(v*Math::TWO_PI);
}

Vector3f 
Random::vector3()
{
  return Vector3f(gaussian(),gaussian(),gaussian()).normalized();
}

Vector3f Random::vector3(const Vector3f& point)
{
  return Vector3f(
  gaussian(point.x),
  gaussian(point.y*2.7f),
  gaussian(point.z*7.2f)).normalized();
}

}

