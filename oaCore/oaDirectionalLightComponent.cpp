#include "oaDirectionalLightComponent.h"

namespace oaEngineSDK
{

REGISTER_CLASS(Component,DirectionalLightComponent);

COMPONENT_TYPE::E 
DirectionalLightComponent::getType()
{
  return COMPONENT_TYPE::kDirectionalLight;
}

}

