#pragma once

#include "oaGraphicsComponent.h"
#include "oaLights.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT SpotLightComponent :
    public GraphicsComponent
{
 public:
  virtual COMPONENT_TYPE::E
  getType() override; 

  SpotLight m_light;
};

}


