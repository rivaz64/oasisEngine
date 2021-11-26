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

void Object::attachComponent(SPtr<Component> component)
{
  component->onAttach(shared_from_this());
}

void Object::update()
{
  for(auto component:components){
    component->update(shared_from_this());
  }
}

Matrix4f 
Object::getLocalTransform()
{
  return 
  Matrix4f::translateMatrix(location)*
  Matrix4f::rotationMatrix(rotation)*
  Matrix4f::scaleMatrix(scale);
}

Matrix4f Object::getGlobalTransform()
{
  return Matrix4f();
}

}
