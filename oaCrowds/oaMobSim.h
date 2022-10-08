#pragma once
#include "oaCrowdSim.h"
namespace oaEngineSDK
{

class MobSim :
  public CrowdSim
{
  Vector<Vector2f> 
  scatter(
    SIZE_T numOfPoints,
    Vector2f& minPoint, 
    Vector2f& maxPoint,
    float radii,
    int iterations,
    int seed) override;
};

}


