#include "oaAmbientLightComponent.h"

namespace oaEngineSDK
{

REGISTER_CLASS(Component,AmbientLightComponent);

COMPONENT_TYPE::E 
AmbientLightComponent::getType()
{
  return COMPONENT_TYPE::kAmbientLight;
}

}

