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
GraphicsComponent::onAttach(SPtr<Actor> actor)
{
  //ResoureManager::instancePtr()->rendereableActors.push_back(actor);
}

COMPONENT_TYPE::E
GraphicsComponent::getType()
{
  return COMPONENT_TYPE::GRAPHICS;
}

void GraphicsComponent::update(SPtr<Actor> actor)
{ 
  
  /*for(SPtr<GraphicsComponent> component : childs){
    component->update(actor);
  }*/
  
}

void GraphicsComponent::addModel(SPtr<Model> model)
{
  m_models.insert({model->m_name,ModelComponent(model)});
}

}
