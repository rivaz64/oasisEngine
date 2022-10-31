#pragma once
#include "oaGraphicsComponent.h"
#include "oaLights.h"
namespace oaEngineSDK
{

class OA_CORE_EXPORT PointLightComponent :
  public GraphicsComponent
{
 public:
  virtual COMPONENT_TYPE::E
  getType() override; 

  PointLight m_light;
};

}



