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
  SIZE_T num = m_components.size();
  serializer.encodeSize(num);
  for(auto component : m_components){
    serializer.encodeNumber(component.first);
    component.second[0]->save(serializer);
  }
}

void 
Actor::load(Serializer& serializer)
{
  setName(serializer.decodeString());
  auto& transform = GetActorTransform();
  serializer.file.read(reinterpret_cast<char*>(&transform),sizeof(Vector3f)*3);
  SIZE_T num = serializer.decodeNumber();
  for(SIZE_T n = 0; n<num; ++n){
    auto componentType = serializer.decodeNumber();
    if(componentType == COMPONENT_TYPE::kGrpahics){
      auto component = makeSPtr<GraphicsComponent>();
      attachComponent(component);
      component->load(serializer);
    }
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
  actor->m_parent = shared_from_this();
}

void 
Actor::attachComponent(SPtr<Component> component)
{
  component->onAttach(shared_from_this());
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
      component->update(shared_from_this());
    }
    
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

}
