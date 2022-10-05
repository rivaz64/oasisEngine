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
#include "oaGraphicsComponent.h"

namespace oaEngineSDK{

/*
enum FLAGS{
  LOCAL=1,
  GLOBAL=2,
  ALL=3
};*/

void 
Actor::save(Serializer& serializer)
{
  serializer.encodeString(getName());
  auto& transform = GetActorTransform();
  serializer.file.write(reinterpret_cast<const char*>(&transform),sizeof(Vector3f)*3);
  SIZE_T num = getNumOfComponents();
  serializer.encodeSize(num);
  for(auto& components : m_components){
    for(auto& component : components.second){
      serializer.encodeNumber(components.first);
      component->save(serializer);
    }
    
  }
  serializer.encodeSize(m_subActors.size());
  for(auto& child : m_subActors){
    child->save(serializer);
  }
}

void 
Actor::load(Serializer& serializer)
{
  setName(serializer.decodeString());
  auto& transform = GetActorTransform();
  serializer.file.read(reinterpret_cast<char*>(&transform),sizeof(Vector3f)*3);
  SIZE_T num = serializer.decodeSize();
  for(SIZE_T n = 0; n<num; ++n){
    auto componentType = serializer.decodeNumber();
    if(componentType == COMPONENT_TYPE::kGrpahics){
      auto component = makeSPtr<GraphicsComponent>();
      attachComponent(component);
      component->load(serializer);
    }
  }
  SIZE_T numOfChilds = serializer.decodeSize();
  for(SIZE_T i = 0; i<numOfChilds; ++i){
    auto newActor = makeSPtr<Actor>();
    attach(newActor);
    newActor->load(serializer);
  }
}

void
Actor::attach(SPtr<Actor> actor)
{
  //if(wActor.expired()){
  //  return;
  //}
  //auto actor = wActor.lock();
  m_subActors.push_back(actor);
  actor->m_parent = cast<Actor>(shared_from_this());
}

void
Actor::unattach(WPtr<Actor> wChild)
{
  auto child = wChild.lock();
  auto found = find(m_subActors.begin(),m_subActors.end(),child);
  if(found != m_subActors.end()){
    m_subActors.erase(found);
  }
}

void 
Actor::attachComponent(SPtr<Component> component)
{
  component->onAttach(cast<Actor>(shared_from_this()));
  auto type = component->getType();
  if(m_components.find(type) == m_components.end()){
    m_components.insert({component->getType(),{}});
  }
  m_components[type].push_back(component);
  
}

void 
Actor::update()
{
  for(auto& componentList : m_components){
    for(auto& component : componentList.second){
      component->update(cast<Actor>(shared_from_this()));
    }
  }
}

void
Actor::postUpdate()
{
  m_localTransform.m_changed = false;
  for(auto& child : m_subActors){
    child->postUpdate();
  }
  auto components = getComponents<GraphicsComponent>();
  for(auto& component : components){
    cast<GraphicsComponent>(component)->postUpdate();
  }
}

const Vector<SPtr<Actor>>& 
Actor::getChilds()
{
  return m_subActors;
}

void
Actor::setActorLocation(const Vector3f& v)
{
  if(m_localTransform.getLocation() != v){
    m_localTransform.setLocation(v);
    m_localTransform.calculate();
  }
  
}

void 
Actor::setActorScale(const Vector3f& v)
{
  if(m_localTransform.getScale() != v){
    m_localTransform.setScale(v);
    m_localTransform.calculate();
  }
  
}

void 
Actor::setActorRotation(const Vector3f& v)
{
  if(m_localTransform.getRotation() != v){
    m_localTransform.setRotation(v);
    m_localTransform.calculate();
  }
  
}

Matrix4f
Actor::getGlobalTransform()
{
  if(true /*dirtyFlag & FLAGS::GLOBAL*/){
    
    if(!m_parent.expired()){
      auto parent = m_parent.lock();
      m_globalTransform = m_localTransform.getMatrix()*parent->getGlobalTransform();
    }
    else{
      m_globalTransform = m_localTransform.getMatrix();
    }
  }
  return m_globalTransform;
}

Vector3f
Actor::getGlobalLocation()
{
  auto transform = getGlobalTransform();
  auto ans = transform  *  Vector4f(0,0,0,1);
  return (ans).xyz;
}

Vector3f 
Actor::getGlobalScale()
{
  auto transform = getGlobalTransform();
  auto ans = transform  *  Vector4f(1,1,1,0);
  return (ans).xyz;
}

Vector3f
Actor::getGlobalRotation()
{
  auto transform = getGlobalTransform();
  Vector3f ans(Math::atan2(transform.row3.z,transform.row3.y),
               Math::atan2(Math::sqrt(transform.row3.y*transform.row3.y+transform.row3.z*transform.row3.z),-transform.row3.x),
               Math::atan2(transform.row1.x,transform.row2.x));
  return ans;
}

Vector3f
Actor::getLocalLocation()
{
  return m_localTransform.getLocation();
}

Vector3f
Actor::getLocalScale()
{
  return m_localTransform.getScale();
}

Vector3f
Actor::getLocalRotation()
{
  return m_localTransform.getRotation();
}

SIZE_T
Actor::getNumOfComponents()
{
  SIZE_T ans = 0;
  for(auto& type : m_components){
    ans += type.second.size();
  }
  return ans;
}

}
