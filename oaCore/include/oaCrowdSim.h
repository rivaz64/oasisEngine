#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>
#include <oaSkeletalComponent.h>
#include <oaVector2f.h>
namespace oaEngineSDK
{

class OA_CORE_EXPORT CrowdSim :
  public Module<CrowdSim>
{
public:
  virtual Vector<Vector2f> 
  scatter(
    SIZE_T numOfPoints,
    Vector2f& minPoint, 
    Vector2f& maxPoint,
    float radii,
    int iterations,
    int seed){ return {};}


};

}


