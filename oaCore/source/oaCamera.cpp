#include "oaCamera.h"
#include "oaGraphicAPI.h"
namespace oaEngineSDK{
Camera::Camera()
{
  view = GraphicAPI::instancePtr()->createBuffer();
  view->init(nullptr,sizeof(Matrix4f),BIND::CONSTANT);

  proyection = GraphicAPI::instancePtr()->createBuffer();
  proyection->init(nullptr,sizeof(Matrix4f),BIND::CONSTANT);

  location = {0.0f,0.0f,0.0f};

  up = {0.0f,-1.0f,0.0f};

  lookAt({0.0f,0.0f,1.0f});
}

void Camera::updateProyection()
{
  Matrix4f ans = Matrix4f::identity;
  float co = cos(angle * .5f), si = sin(angle * .5f);
  float distance = farPlane - nearPlane;

  ans.m11 = (co / si) / ratio;
  ans.m22 = co/si;
  ans.m33 = farPlane / distance;
  ans.m34 = -ans.m33*nearPlane;
  ans.m43 = 1;
  ans.m44=0;

  //ans.transpose();

  proyection->update(&ans.m11);
}

void Camera::updateView()
{
  Matrix4f ans = Matrix4f::identity;
  
  ans.m11 = axis.m11;
  ans.m12 = axis.m12;
  ans.m13 = axis.m13;

  ans.m21 = axis.m21;
  ans.m22 = axis.m22;
  ans.m23 = axis.m23;

  ans.m31 = axis.m31;
  ans.m32 = axis.m32;
  ans.m33 = axis.m33;
  
  ans.m14 = -Vector3f::dot(location,*(reinterpret_cast<Vector3f*>(&axis.m11)));
  ans.m24 = -Vector3f::dot(location,*(reinterpret_cast<Vector3f*>(&axis.m21)));
  ans.m34 = -Vector3f::dot(location,*(reinterpret_cast<Vector3f*>(&axis.m31)));

  view->update(&ans.m11);
}

void Camera::setCamera()
{

  GraphicAPI::instancePtr()->setBuffer(view,1);
  
  GraphicAPI::instancePtr()->setBuffer(proyection,2);

}

void Camera::moveCamera(const Vector3f& delta)
{
  Vector3f realDelta = axis*delta;
  location += realDelta;
  lookingAt += realDelta;
  updateView();
}

void Camera::lookAt(const Vector3f& newLocation)
{
  lookingAt = newLocation;

  *(reinterpret_cast<Vector3f*>(&axis.m31)) = 
    (lookingAt - location).normalized();

  *(reinterpret_cast<Vector3f*>(&axis.m11)) = 
    Vector3f::cross(*(reinterpret_cast<Vector3f*>(&axis.m31)),up).normalized();
    
  *(reinterpret_cast<Vector3f*>(&axis.m21)) = 
    Vector3f::cross(*(reinterpret_cast<Vector3f*>(&axis.m31)),*(reinterpret_cast<Vector3f*>(&axis.m11))).normalized();

}

}

