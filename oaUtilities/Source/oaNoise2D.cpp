#include "oaNoise2D.h"
#include "oaVector2f.h"
void oaEngineSDK::Noise2D::fillGrid(Grid2D<float>& grid, float scale)
{
  const Vector2U& size = grid.getSize();
  Vector2U position;
  for(position.x = 0;position.x< size.y; ++position.x){
    for(position.y = 0;position.y< size.x; ++position.y){
      grid.setAt(position,valueAt(Vector2f(position)/scale));
    }
  }
}
