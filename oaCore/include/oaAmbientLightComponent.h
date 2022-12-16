#pragma once
#include "oaGraphicsComponent.h"
#include "oaLights.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT AmbientLightComponent :
    public GraphicsComponent
{
public:

  virtual COMPONENT_TYPE::E
  getType() override; 

  AmbientLight m_light;
};

}


