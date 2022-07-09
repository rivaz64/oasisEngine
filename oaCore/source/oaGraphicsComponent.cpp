/**
* @file oaGraphicsComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"
#include "oaModel.h"
#include "oaGraphicsComponent.h"

namespace oaEngineSDK{

COMPONENT_TYPE::E
GraphicsComponent::getType()
{
  return COMPONENT_TYPE::kGrpahics;
}

void 
GraphicsComponent::update(WPtr<Actor> actor)
{ 
  
  /*for(SPtr<GraphicsComponent> component : childs){
    component->update(actor);
  }*/
  
}


}
