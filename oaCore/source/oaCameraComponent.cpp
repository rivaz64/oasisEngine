#include "oaCameraComponent.h"
#include <oaTransform.h>
#include "oaCamera.h"
#include "oaActor.h"

namespace oaEngineSDK{

void 
CameraComponent::update(SPtr<Actor> actor)
{
  m_camera->setLocation(actor->GetActorTransform().getLocation());
}

}

