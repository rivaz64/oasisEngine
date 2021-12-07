/**
* @file oaSkeletalComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaSkeletalComponent.h"
#include "oaGraphicsComponent.h"
#include "oaObject.h"
#include "oaSkeleton.h"

namespace oaEngineSDK{

COMPONENT_TYPE::E
SkeletalComponent::getType()
{
  return COMPONENT_TYPE::SKELETON;
}

void SkeletalComponent::update(SPtr<Object> actor)
{
  /*OA_ASSERT(actor->getComponent<GraphicsComponent>().get());

  auto model = actor->getComponent<GraphicsComponent>()->model;

  Vector<Matrix4f> finalMatrix;

  for(auto mesh: model->meshes){

    finalMatrix.clear();

    finalMatrix.resize(mesh->bones.size());

    for(uint32 i = 0; i<mesh->bones.size(); ++i){
      finalMatrix[i] = skeleton->boneMaping[mesh->boneNames[i]] * mesh->bones[i];
    }

    mesh->bonesB->update(finalMatrix.data());
  }*/

}

}
