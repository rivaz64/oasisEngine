/**
* @file oaGraphicsComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"
#include "oaModel.h"

namespace oaEngineSDK{

void 
GraphicsComponent::onAttach(SPtr<Object> actor)
{
  ResoureManager::instancePtr()->rendereableObjects.push_back(actor);
}

COMPONENT_TYPE::E
GraphicsComponent::getType()
{
  return COMPONENT_TYPE::GRAPHICS;
}

}
