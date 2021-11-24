#include "oaPerlinNoise2D.h"
#include "oaVector2I.h"
#include "oaRandom.h"

namespace oaEngineSDK{

float 
PerlinNoise2D::valueAt(const Vector2f& point)
{
  Vector2I pointI = point.floor();
  Vector2f pointf = point.fraction();

  Vector2f a = Random::vector(pointI);
  Vector2f b = Random::vector(pointI+Vector2I(1,0));
  Vector2f c = Random::vector(pointI+Vector2I(0,1));
  Vector2f d = Random::vector(pointI+Vector2I(1,1));

  float e = Vector2f::dot(pointf,a);
  float f = Vector2f::dot(pointf-Vector2f(1,0),b);
  float g = Vector2f::dot(pointf-Vector2f(0,1),c);
  float h = Vector2f::dot(pointf-Vector2f(1,1),d);

  return Math::interpolate(
                           Math::interpolate(e,f,pointf.x),
                           Math::interpolate(g,h,pointf.x),
                           pointf.y);
}

void 
PerlinNoise2D::fillGrid(Grid2D<float>& grid, float scale)
{
  const Vector2U& size = grid.getSize();
  Vector2U position;
  for(position.x = 0;position.x< size.y; ++position.x){
    for(position.y = 0;position.y< size.x; ++position.y){
      grid.setAt(position,valueAt(Vector2f(position)/scale));
    }
  }
}

}

