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

void 
GraphicsComponent::save(Serializer& serializer)
{
  serializer.encodeString(m_model.lock()->getName());
}

void 
GraphicsComponent::load(Serializer& serializer)
{
  auto modelName = serializer.decodeString();
  setModel(cast<Model>(ResoureManager::instance().getResourse(modelName)));
}

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
GraphicsComponent::postUpdate()
{
  m_transform.m_changed = false;
}


}
