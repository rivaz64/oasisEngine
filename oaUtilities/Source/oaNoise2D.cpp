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

void oaEngineSDK::Noise2D::redistribute(Grid2D<float>& grid, float power, float minValue)
{
  const Vector2U& size = grid.getSize();
  Vector2U position;
  float inverseMin = 1.f/(1.f-minValue);
  for(position.x = 0;position.x< size.y; ++position.x){
    for(position.y = 0;position.y< size.x; ++position.y){
      float actualValue = grid.getAt(position);
      actualValue-=minValue;
      if(actualValue<0){
        actualValue = 0;
      }
      else{
        actualValue*=inverseMin;
      }
      actualValue = Math::pow(actualValue*1.2f,power);
      grid.setAt(position,actualValue);
    }
  }
}
