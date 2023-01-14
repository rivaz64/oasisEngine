/**
* @file oaGraphicsComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaGraphicsComponent.h"
#include "oaResoureManager.h"
#include "oaModel.h"
#include "oaActor.h"


namespace oaEngineSDK{

REGISTER_CLASS(Component,GraphicsComponent);

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

void 
GraphicsComponent::onAttach(WPtr<Actor> wActor)
{
  if(wActor.expired()) return;
  auto actor = wActor.lock();
  actor->addGraphicComponent(cast<GraphicsComponent>(shared_from_this()));
}

void 
GraphicsComponent::postUpdate()
{
  m_transform.m_changed = false;
}


}
