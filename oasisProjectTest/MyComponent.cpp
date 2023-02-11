#include "MyComponent.h"
#include "include\MyComponent.h"
#include "oaFactory.h"

namespace oaEngineSDK
{
REGISTER_CLASS(Component,MyComponent);
}


oaEngineSDK::COMPONENT_TYPE::E MyComponent::getType()
{
  return oaEngineSDK::COMPONENT_TYPE::E(8);
}
