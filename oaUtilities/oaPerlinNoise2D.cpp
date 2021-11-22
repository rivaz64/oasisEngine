#include "oaPerlinNoise2D.h"
#include "oaVector2I.h"

namespace oaEngineSDK{

float PerlinNoise2D::valueAt(const Vector2f& point)
{
  Vector2I pointI = point.floor();
  Vector2f pointf = point.fraction();
  return 0.0f;
}

}

