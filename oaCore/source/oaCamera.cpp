/**
* @file oaCamera.h
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
Camera::init(float viewAngle,
             float nearPlaneDistance,
             float farPlaneDistance)
{
  m_viewAngle = viewAngle;
  m_nearPlaneDistance = nearPlaneDistance;
  m_farPlaneDistance = farPlaneDistance;

  auto& api = GraphicAPI::instance();

  m_ratio = static_cast<float>(api.m_windowWidth) / 
            static_cast<float>(api.m_windowHeight);

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

  m_projectionMatrix.m11 = (co / si) / m_ratio;
  m_projectionMatrix.m22 = co/si;
  m_projectionMatrix.m33 = m_farPlaneDistance / distance;
  m_projectionMatrix.m34 = -m_projectionMatrix.m33*m_nearPlaneDistance;
  m_projectionMatrix.m43 = 1.f;
  m_projectionMatrix.m44= 0.f;

  //ans.transpose();
}

void 
Camera::updateView()
{
  if(!dirtyFlags){
    return;
  }

  m_viewMatrix.m11 = m_axis.m11;
  m_viewMatrix.m12 = m_axis.m12;
  m_viewMatrix.m13 = m_axis.m13;

  m_viewMatrix.m21 = m_axis.m21;
  m_viewMatrix.m22 = m_axis.m22;
  m_viewMatrix.m23 = m_axis.m23;

  m_viewMatrix.m31 = m_axis.m31;
  m_viewMatrix.m32 = m_axis.m32;
  m_viewMatrix.m33 = m_axis.m33;
  
  m_viewMatrix.m14 = -Vector3f::dot(m_location,m_axisX);
  m_viewMatrix.m24 = -Vector3f::dot(m_location,m_axisY);
  m_viewMatrix.m34 = -Vector3f::dot(m_location,m_axisZ);

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

void
Camera::seeActors(SPtr<Actor> scene,Vector<SPtr<Actor>>& seenActors)
{
  auto& childs = scene->getChilds();

  for(auto Actor : childs){

    auto component = Actor->getComponent<GraphicsComponent>();

    if(component && component->m_models.size()!=0){
      seenActors.push_back(Actor);
    }

    seeActors(Actor,seenActors);

  }
}

}

