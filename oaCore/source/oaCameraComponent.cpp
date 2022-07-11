#include "oaCameraComponent.h"
#include <oaTransform.h>
#include "oaCamera.h"
#include "oaActor.h"

namespace oaEngineSDK{

void 
CameraComponent::update(WPtr<Actor> actor)
{
  //m_camera->setLocation(actor->GetActorTransform().getLocation());
}

COMPONENT_TYPE::E 
CameraComponent::getType()
{
  return COMPONENT_TYPE::E();
}

}

