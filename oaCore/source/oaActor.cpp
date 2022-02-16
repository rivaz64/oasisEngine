/**
* @file oaActor.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaActor.h"
#include "oaGraphicAPI.h"
#include "oaMatrix4f.h"
#include "oaComponent.h"
#include "oaBuffer.h"
#include "oaComponent.h"

namespace oaEngineSDK{

/*
enum FLAGS{
  LOCAL=1,
  GLOBAL=2,
  ALL=3
};*/

void 
Actor::attach(SPtr<Actor> Actor)
{
  m_subActors.push_back(Actor);
  Actor->m_parent = shared_from_this();
}

void 
Actor::attachComponent(SPtr<Component> component)
{
  component->onAttach(shared_from_this());
  m_components.insert({component->getType(),component});
  m_components[component->getType()] = component;
}

void 
Actor::update()
{
  for(auto component : m_components){
    if(component.second.get())
    component.second->update(shared_from_this());
  }
}

const Vector<SPtr<Actor>>& 
Actor::getChilds()
{
  return m_subActors;
}

Matrix4f
Actor::getGlobalTransform()
{
  if(true /*dirtyFlag & FLAGS::GLOBAL*/){
    
    if(m_parent.get()){
      m_globalTransform = m_parent->getGlobalTransform()*m_localTransform.getMatrix();
    }
    else{
      m_globalTransform = Matrix4f::IDENTITY;
    }
  }
  return m_globalTransform;
}

}
