#include "oaRandom.h"

namespace oaEngineSDK{

float
Random::noise2D(const Vector2f& point)
{
    return Math::mod(Math::sin(Vector2f::dot(point,Vector2f(12.9898,78.233))),1);
}

Vector2f
Random::vector()
{
  float value = unit()*Math::TWO_PI;
  return Vector2f(Math::cos(value),Math::sin(value));
}

Vector2f
Random::vector(const Vector2f& point)
{
  float value = noise2D(point)*Math::TWO_PI;
  return Vector2f(Math::cos(value),Math::sin(value));
}

}

