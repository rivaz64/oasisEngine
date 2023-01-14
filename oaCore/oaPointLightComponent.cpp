#include "oaPointLightComponent.h"

namespace oaEngineSDK
{

REGISTER_CLASS(Component,PointLightComponent);

COMPONENT_TYPE::E 
PointLightComponent::getType()
{
  return COMPONENT_TYPE::kPointLight;
}

}

