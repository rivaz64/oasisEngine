#pragma once
#include "oaPrerequisitesCore.h"
#include "oaComponent.h"

using oaEngineSDK::Component;
class MyComponent :
  public Component
{
public:
  virtual oaEngineSDK::COMPONENT_TYPE::E
  getType() override; 
};

