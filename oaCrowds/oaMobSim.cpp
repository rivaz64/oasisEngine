#include "oaMobSim.h"
#include "oaVector2f.h"
namespace oaEngineSDK
{

float
randomFloat()
{
  return static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}

Vector<Vector2f>
scatteredPoints(SIZE_T numOfPoints,Vector2f minPoint, Vector2f maxPoint)
{
  Vector<Vector2f> ans;
  auto length = maxPoint-minPoint;
  ans.resize(numOfPoints);
  for(auto& i : ans){
    i = {randomFloat()*length.x+minPoint.x,randomFloat()*length.y+minPoint.y};
  }
  return ans;
}

vector<Vector2f>
blueNoise(vector<Vector2f> points, float radii){
  auto ans = points;
  auto numOfPoints = points.size();
  for(size_t i = 0; i<numOfPoints-1; ++i){
    for(size_t o = i+1; o<numOfPoints; ++o){
      auto d = points[i]-points[o];
      auto dis = d.magnitud();
      if(dis<radii){
        auto normal = d.normalized();
        ans[i] += normal;
        ans[o] -= normal;
      }
    }
  }
  return ans;
}

Vector<Vector2f> 
MobSim::scatter(SIZE_T numOfPoints, Vector2f& minPoint, Vector2f& maxPoint, float radii, int iterations, int seed)
{
  srand(seed);
  auto points = scatteredPoints(numOfPoints,minPoint,maxPoint);
  for(int i = 0; i<iterations; ++i){
    points = blueNoise(points,radii);
  }
  return points;
}

}

