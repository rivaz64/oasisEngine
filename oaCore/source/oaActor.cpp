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

Actor::Actor()
{
  m_location = {0.f,0.f,0.f};
  m_scale = {1.f,1.f,1.f};
  m_rotation =  {0.f,0.f,0.f};
  m_transformB = GraphicAPI::instancePtr()->createBuffer();
  m_transformB->init(sizeof(Matrix4f));
}

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

void 
Actor::setLocation(const Vector3f& _location)
{
  m_location = _location;
  //dirtyFlag = FLAGS::ALL;
}

void 
Actor::setRotation(const Vector3f& _rotation)
{
  m_rotation = _rotation;
  //dirtyFlag |= FLAGS::ALL;
}

void 
Actor::setScale(const Vector3f& _scale)
{
  m_scale = _scale;
  //dirtyFlag |= FLAGS::ALL;
}

const Vector3f&
Actor::getLocation()
{
  return m_location;
}

const Vector3f& 
Actor::getRotation()
{
  return m_rotation;
}

const Vector3f& 
Actor::getScale()
{
  return m_scale;
}

const Vector<SPtr<Actor>>& 
Actor::getChilds()
{
  return m_subActors;
}

Matrix4f 
Actor::getLocalTransform()
{
  if(true/*dirtyFlag & FLAGS::LOCAL*/){

    //dirtyFlag &= FLAGS::GLOBAL;

    m_localTransform = 
      Matrix4f::translateMatrix(m_location)*
      Matrix4f::rotationMatrix(m_rotation)*
      Matrix4f::scaleMatrix(m_scale);
  }

  return m_localTransform;
  
}

Matrix4f
Actor::getGlobalTransform()
{
  if(true /*dirtyFlag & FLAGS::GLOBAL*/){
    
    //dirtyFlag &= FLAGS::LOCAL;

    if(m_parent.get()){
      m_globalTransform = m_parent->getGlobalTransform()*getLocalTransform();
    }
    else{
      m_globalTransform = Matrix4f::IDENTITY;
    }
  }
  return m_globalTransform;
}

}
