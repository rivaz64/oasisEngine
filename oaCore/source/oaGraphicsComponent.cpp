#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"

void oaEngineSDK::GraphicsComponent::onAttach(SPtr<Object> actor)
{
  ResoureManager::instancePtr()->rendereableObjects.push_back(actor);
}

void oaEngineSDK::GraphicsComponent::update(SPtr<Object> actor)
{
  
}
