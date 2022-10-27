#pragma once
#include "oaGraphicsComponent.h"
#include "oaLights.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT DirectionalLightComponent :
    public GraphicsComponent
{
public:
  virtual COMPONENT_TYPE::E
  getType() override; 

  DirectionalLight m_light;
};

}


