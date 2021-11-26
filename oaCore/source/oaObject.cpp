#include "oaObject.h"
#include "oaGraphicAPI.h"
#include "oaMatrix4f.h"
#include "oaComponent.h"

namespace oaEngineSDK{

enum FLAGS{
  LOCAL=1,
  GLOBAL=2,
  ALL=3
};

Object::Object()
{
  location = {0.f,0.f,0.f};
  scale = {1.f,1.f,1.f};
  rotation =  {0.f,0.f,0.f};
  transformB = GraphicAPI::instancePtr()->createBuffer();
  transformB->init(nullptr,sizeof(Matrix4f),BIND::CONSTANT);
}

void 
Object::attach(SPtr<Object> object)
{
  subObjects.push_back(object);
  object->parent = shared_from_this();
}

void 
Object::attachComponent(SPtr<Component> component)
{
  component->onAttach(shared_from_this());
}

void 
Object::update()
{
  for(auto component:components){
    component->update(shared_from_this());
  }
}

void 
Object::setLocation(const Vector3f& _location)
{
  location = _location;
  dirtyFlag = FLAGS::ALL;
}

void 
Object::setRotation(const Vector3f& _rotation)
{
  rotation = _rotation;
  dirtyFlag |= FLAGS::ALL;
}

void 
Object::setScale(const Vector3f& _scale)
{
  scale = _scale;
  dirtyFlag |= FLAGS::ALL;
}

const Vector3f&
Object::getLocation()
{
  return location;
}

const Vector3f& 
Object::getRotation()
{
  return rotation;
}

const Vector3f& 
Object::getScale()
{
  return scale;
}

const Vector<SPtr<Object>>& 
Object::getChilds()
{
  return subObjects;
}

Matrix4f 
Object::getLocalTransform()
{
  if(dirtyFlag & FLAGS::LOCAL){

    dirtyFlag &= FLAGS::GLOBAL;

    localTransform = 
      Matrix4f::translateMatrix(location)*
      Matrix4f::rotationMatrix(rotation)*
      Matrix4f::scaleMatrix(scale);
  }

  return localTransform;
  
}

Matrix4f
Object::getGlobalTransform()
{
  if(dirtyFlag & FLAGS::GLOBAL){
    
    dirtyFlag &= FLAGS::LOCAL;

    if(parent.get()){
      globalTransform = parent->getGlobalTransform()*getLocalTransform();
    }
    else{
      globalTransform = Matrix4f::IDENTITY;
    }
  }
  return globalTransform;
}

}
