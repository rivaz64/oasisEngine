#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"

namespace oaEngineSDK{

void 
GraphicsComponent::onAttach(SPtr<Object> actor)
{
  ResoureManager::instancePtr()->rendereableObjects.push_back(actor);
}

}
