/**
* @file oaCamera.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#include "oaCamera.h"
#include "oaGraphicAPI.h"
#include "oaGraphicsComponent.h"
#include "oaBuffer.h"
#include "oaActor.h"
#include <iostream>



namespace oaEngineSDK{

Camera::Camera()
{

  m_viewMatrix = Matrix4f::IDENTITY;

  m_location = {0.0f,0.0f,0.0f};

  m_up = {0.0f,-1.0f,0.0f};

  lookAt({0.0f,0.0f,1.0f});
}

void
Camera::init(const float ratio,
             const float viewAngle,
             const float nearPlaneDistance,
             const float farPlaneDistance)
{
  m_viewAngle = viewAngle;
  m_nearPlaneDistance = nearPlaneDistance;
  m_farPlaneDistance = farPlaneDistance;
  m_ratio = ratio;
  update();
}

void 
Camera::update(){
  updateProyection();
  updateView();
}

void 
Camera::updateProyection()
{
  m_projectionMatrix = Matrix4f::IDENTITY;
  float co = cos(m_viewAngle * .5f), si = sin(m_viewAngle * .5f);
  float distance = m_farPlaneDistance - m_nearPlaneDistance;

  m_projectionMatrix.row1.x = (co / si) / m_ratio;
  m_projectionMatrix.row2.y = co/si;
  m_projectionMatrix.row3.z = m_farPlaneDistance / distance;
  m_projectionMatrix.row3.w = -m_projectionMatrix.row3.z*m_nearPlaneDistance;
  m_projectionMatrix.row4.z = 1.f;
  m_projectionMatrix.row4.w= 0.f;

  //ans.transpose();
}

void 
Camera::updateView()
{
  if(!dirtyFlags){
    return;
  }

  m_viewMatrix = Matrix4f(m_axis);
  
  m_viewMatrix.row1.w = -Vector3f::dot(m_location,m_axisX);
  m_viewMatrix.row2.w = -Vector3f::dot(m_location,m_axisY);
  m_viewMatrix.row3.w = -Vector3f::dot(m_location,m_axisZ);

  //createFrustrum();

  //view->write(&viewMatrix.m11);

  dirtyFlags = false;
}

void 
Camera::moveCamera(const Vector3f& delta)
{
  m_axis.transpose();
  Vector3f realDelta = m_axis*delta;
  m_axis.transpose();
  m_location += realDelta;
  lookAt(m_lookingAt+realDelta);
  dirtyFlags = true;
}

void 
Camera::lookAt(const Vector3f& newLocation)
{
  m_lookingAt = newLocation;

  m_axisZ = (m_lookingAt - m_location).normalized();

  m_axisX = Vector3f::cross(m_axisZ,m_up).normalized();
    
  m_axisY = Vector3f::cross(m_axisZ,m_axisX).normalized();

}

void 
Camera::rotateWithMouse(const Vector2f& delta)
{
  if(delta.magnitud()<=0){
    return;
  }
  lookAt(
    (m_axisZ + m_axisX * delta.x * .003f - m_axisY * delta.y * .003f).normalized()+
    m_location
  );

  dirtyFlags = true;
}
/*
bool 
Camera::isInFrustrum(const Vector3f& _location)
{
  //print(Math::distance(nearP,_location));
  return 
    Math::distance(nearP,_location)>0 &&
    Math::distance(farP,_location)>0 &&
    Math::distance(topP,_location)>0 &&
    Math::distance(bottomP,_location)>0 &&
    Math::distance(rightP,_location)>0 && 
    Math::distance(leftP,_location)>0;

}*/

//void
//Camera::seeActors(SPtr<Actor> scene,Vector<SPtr<Actor>>& seenActors)
//{
//  auto& childs = scene->getChilds();
//
//  for(auto Actor : childs){
//
//    auto component = Actor->getComponent<GraphicsComponent>();
//    seenActors.push_back(Actor);
//    //if(component && component->m_models.size()!=0){
//    //  seenActors.push_back(Actor);
//    //}
//
//    seeActors(Actor,seenActors);
//
//  }
//}

void 
Camera::setLocation(const Vector3f& newLocation)
{
  auto pastLocation = m_location;
  m_location = newLocation;
  lookAt(m_lookingAt+newLocation-pastLocation);
  dirtyFlags = true;
}


}

