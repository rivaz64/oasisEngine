#include "oaCamera.h"
#include "oaGraphicAPI.h"
#include <iostream>
namespace oaEngineSDK{
Camera::Camera()
{
  view = GraphicAPI::instancePtr()->createBuffer();
  view->init(nullptr,sizeof(Matrix4f),BIND::CONSTANT);

  proyection = GraphicAPI::instancePtr()->createBuffer();
  proyection->init(nullptr,sizeof(Matrix4f),BIND::CONSTANT);

  viewMatrix = Matrix4f::IDENTITY;

  location = {0.0f,0.0f,0.0f};

  up = {0.0f,-1.0f,0.0f};

  lookAt({0.0f,0.0f,1.0f});
}

void Camera::updateProyection()
{
  Matrix4f ans = Matrix4f::IDENTITY;
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
  
  viewMatrix.m11 = axis.m11;
  viewMatrix.m12 = axis.m12;
  viewMatrix.m13 = axis.m13;

  viewMatrix.m21 = axis.m21;
  viewMatrix.m22 = axis.m22;
  viewMatrix.m23 = axis.m23;

  viewMatrix.m31 = axis.m31;
  viewMatrix.m32 = axis.m32;
  viewMatrix.m33 = axis.m33;
  
  viewMatrix.m14 = -Vector3f::dot(location,axisX);
  viewMatrix.m24 = -Vector3f::dot(location,axisY);
  viewMatrix.m34 = -Vector3f::dot(location,axisZ);

  createFrustrum();

  view->update(&viewMatrix.m11);
}

void Camera::setCamera()
{

  GraphicAPI::instancePtr()->setBuffer(view,1);
  
  GraphicAPI::instancePtr()->setBuffer(proyection,2);

}

void Camera::moveCamera(const Vector3f& delta)
{
  axis.transpose();
  Vector3f realDelta = axis*delta;
  axis.transpose();
  location += realDelta;
  lookingAt += realDelta;
  updateView();
}

void Camera::lookAt(const Vector3f& newLocation)
{
  lookingAt = newLocation;

  axisZ = (lookingAt - location).normalized();

  axisX = Vector3f::cross(axisZ,up).normalized();
    
  axisY = Vector3f::cross(axisZ,axisX).normalized();

}

void Camera::rotateWithMouse(const Vector2f& delta)
{
  //std::cout<<delta.x<<" "<<delta.y<<std::endl;
  //std::cout<<lookingAt.x<<" "<<lookingAt.y<<" "<<lookingAt.z<<std::endl;
  lookingAt = axisZ + axisX * delta.x * .003f - axisY * delta.y * .003f;

  lookingAt.normalize();

  lookingAt += location;

  //std::cout<<lookingAt.x<<" "<<lookingAt.y<<" "<<lookingAt.z<<std::endl<<std::endl;
  lookAt(lookingAt);
  updateView();

}

bool Camera::isInFrustrum(const Vector3f& _location)
{
  //std::cout<<Math::distance(nearP,_location)<<std::endl;
  return 
    Math::distance(nearP,_location)>0 &&
    Math::distance(farP,_location)>0 &&
    Math::distance(topP,_location)>0 &&
    Math::distance(bottomP,_location)>0 &&
    Math::distance(rightP,_location)>0 && 
    Math::distance(leftP,_location)>0;

}

void Camera::createFrustrum()
{
  nearP = Plane(location+axisZ*nearPlane,axisZ);
  farP = Plane(location+axisZ*farPlane,-axisZ);
  float temp = Math::tan(angle/2.f);
  float nh = Math::tan(angle/2.f)*nearPlane;
  float nw = nh*ratio;
  float fh = Math::tan(angle/2.f)*farPlane;
  float fw = fh*ratio;

  Vector3f nnw = location+axis*Vector3f(-nw,nh,nearPlane);
  Vector3f nne = location+axis*Vector3f(nw,nh,nearPlane);
  Vector3f fne = location+axis*Vector3f(fw,fh,farPlane);

  topP = Plane(nnw,nne,fne);

  Vector3f nsw = location+axis*Vector3f(-nw,-nh,nearPlane);
  Vector3f nse = location+axis*Vector3f(nw,-nh,nearPlane);
  Vector3f fse = location+axis*Vector3f(fw,-fh,farPlane);
  Vector3f fsw = location+axis*Vector3f(-fw,-fh,farPlane);

  bottomP = Plane(nsw,fse,nse);

  rightP = Plane(nne,fse,fne);

  leftP = Plane(nnw,fsw,nsw);

}

}

