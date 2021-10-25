#include "oaObject.h"
#include "oaGraphicAPI.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

Object::Object()
{
  location = {0.f,0.f,0.f};
  //locationB = GraphicAPI::instancePtr()->createBuffer();
  //locationB->init(nullptr,sizeof(Matrix4f),BUFFER_FLAGS::CONSTANT);
}

void 
Object::update()
{
  //auto transform = Matrix4f::translateMatrix(location);
  //locationB->update(&transform,sizeof(Matrix4f));
}

}
