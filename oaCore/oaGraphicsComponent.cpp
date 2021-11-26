#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"

void oaEngineSDK::oaGraphicsComponent::onAttach(SPtr<Object> actor)
{
  ResoureManager::instancePtr()->rendereableObjects.push_back(actor);
}

void oaEngineSDK::oaGraphicsComponent::update(SPtr<Object> actor)
{
  
}
