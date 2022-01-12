#include "oaPerlinNoise3D.h"
#include "oaVector3I.h"
#include "oaVector3f.h"
#include "oaRandom.h"

namespace oaEngineSDK{

Vector<Vector3f> GRADIENTS = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
                              {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}, {1, 1, 0}, {0, -1, 1}, {-1, 1, 0}, {0, -1, -1}};

float PerlinNoise3D::valueAt(const Vector3f& point)
{
  Vector3I pointI = point.floor();
  Vector3f pointf = point.fraction();
  Vector<float> ans;
  for(int8 a = 0;a<2;++a){
    for(int8 e = 0;e<2;++e){
      for(int8 i = 0;i<2;++i){
        auto vec = Vector3I(a,e,i);
        auto actualVec = GRADIENTS[int(Math::abs(Random::noise3D(pointI+vec))*16)];
        ans.push_back(Vector3f::dot(actualVec,pointf-vec));
      }
    }
  }
  return Math::interpolate(
    Math::interpolate(
      Math::interpolate(ans[0],ans[1],pointf.z),
      Math::interpolate(ans[2],ans[3],pointf.z),
      pointf.y),
    Math::interpolate(
      Math::interpolate(ans[4],ans[5],pointf.z),
      Math::interpolate(ans[6],ans[7],pointf.z),
      pointf.y),
    pointf.x);
}

void PerlinNoise3D::fillGrid(Grid3D<float>& grid, float scale)
{
  const Vector3U& size = grid.getSize();
  Vector3I position;
  for(position.x = 0;position.x< size.y; ++position.x){
    for(position.y = 0;position.y< size.x; ++position.y){
      for(position.z = 0;position.z< size.z; ++position.z){
        grid.setAt(position,valueAt(Vector3f(position)/scale+Vector3f(.1,.2,.3)));
      }
    }
  }
}


}
