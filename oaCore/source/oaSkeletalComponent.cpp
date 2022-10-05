/**
* @file oaSkeletalComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaSkeletalComponent.h"
#include "oaGraphicsComponent.h"
#include "oaActor.h"
#include "oaSkeleton.h"
#include "oaModel.h"

namespace oaEngineSDK{

COMPONENT_TYPE::E
SkeletalComponent::getType()
{
  //return COMPONENT_TYPE::kSkeleton;
  return COMPONENT_TYPE::E();
}

void SkeletalComponent::update(WPtr<Actor> actor)
{
  //if(m_skeleton)
  //for(auto it= m_sockets.begin(); it!=m_sockets.end(); ++it){
  //  actor->getComponent<GraphicsComponent>()->m_models[it->first->m_name].transform = 
  //  m_skeleton->m_finalMatrix[it->second];
  //  
  //}

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

bool 
SkeletalComponent::attachToBone(WPtr<Model> model, String bone)
{
  if(m_skeleton.expired()) return false;

  auto skeleton = m_skeleton.lock();

  if(skeleton->m_boneMaping.find(bone)==skeleton->m_boneMaping.end()){
    return false;
  }
  
  //m_sockets.insert({model,bone});
  
  return true;
}

}
