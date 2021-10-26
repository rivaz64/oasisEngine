#include "oaCamera.h"
#include "oaGraphicAPI.h"
namespace oaEngineSDK{
Camera::Camera()
{
  buffer = GraphicAPI::instancePtr()->createBuffer();
  buffer->init(nullptr,sizeof(Matrix4f),BUFFER_FLAGS::CONSTANT);
}
void Camera::setCamera()
{
  Matrix4f ans(1);
  float co = cos(angle * .5f), si = sin(angle * .5f);
  float distance = farPlane - nearPlane;

  ans.m11 = (co / si) / ratio;
  ans.m22 = co/si;
  ans.m33 = farPlane / distance;
  ans.m34 = -ans.m33*nearPlane;
  ans.m43 = 1;
  ans.m44=0;

  buffer->update(&ans.m11,sizeof(Matrix4f));

  GraphicAPI::instancePtr()->setBuffer(buffer,1);

  
}

}

