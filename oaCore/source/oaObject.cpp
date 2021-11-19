#include "oaObject.h"
#include "oaGraphicAPI.h"
#include "oaMatrix4f.h"

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
Object::update()
{
  auto transform = Matrix4f::translateMatrix(location)*Matrix4f::rotationMatrix(rotation)*Matrix4f::scaleMatrix(scale);

  transformB->update(&transform);
}

void 
Object::attach(SPtr<Object> object)
{
  auto newNode = newSPtr<Tree<Object>>();
  newNode->data = object;
  object->subObjects = newNode;
  subObjects->childs.push_back(newNode);
}

Matrix4f 
Object::getTransform()
{
  return Matrix4f::translateMatrix(location)*Matrix4f::rotationMatrixX(rotation.x)*Matrix4f::rotationMatrixY(rotation.y)*Matrix4f::rotationMatrixZ(rotation.z)*Matrix4f::scaleMatrix(scale);
}

}
