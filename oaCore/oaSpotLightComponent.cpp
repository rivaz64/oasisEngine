#include "oaSpotLightComponent.h"

namespace oaEngineSDK
{

REGISTER_CLASS(Component,SpotLightComponent);

COMPONENT_TYPE::E 
SpotLightComponent::getType()
{
  return COMPONENT_TYPE::kSpotLight;
}

}

