#include "oaObject.h"
#include "oaGraphicAPI.h"
#include "oaMatrix4f.h"
#include "oaComponent.h"

namespace oaEngineSDK{

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
  auto newNode = newSPtr<Tree<Object>>();
  newNode->data = object;
  object->subObjects = newNode;
  subObjects->childs.push_back(newNode);
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
  dirtyFlag = true;
}

void 
Object::setRotation(const Vector3f& _rotation)
{
  rotation = _rotation;
  dirtyFlag = true;
}

void 
Object::setScale(const Vector3f& _scale)
{
  scale = _scale;
  dirtyFlag = true;
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

Matrix4f 
Object::getLocalTransform()
{
  if(dirtyFlag){
    dirtyFlag = false;
    localTransform = 
      Matrix4f::translateMatrix(location)*
      Matrix4f::rotationMatrix(rotation)*
      Matrix4f::scaleMatrix(scale);
  }

  return localTransform;
  
}

Matrix4f Object::getGlobalTransform()
{
  return Matrix4f();
}

}
