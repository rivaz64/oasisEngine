/**
* @file oaAnimationComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#include "oaAnimationComponent.h"
#include "oaAnimation.h"
#include "oaSkeletalComponent.h"
#include "oaActor.h"
#include "oaGraphicsComponent.h"
#include "oaTime.h"
#include "oaSkeleton.h"
#include "oaMesh.h"
#include "oaModel.h"

namespace oaEngineSDK{

COMPONENT_TYPE::E oaEngineSDK::AnimationComponent::getType()
{
  return COMPONENT_TYPE::ANIMATION;
}

void 
AnimationComponent::update(SPtr<Actor> actor)
{
  OA_ASSERT(actor->getComponent<SkeletalComponent>().get());

  if(!m_animation){
    return;
  }

  //m_animTimeInSecs += Time::instancePtr()->getDelta();

  //float timeInTicks = animation->ticksPerSecond * Time::instancePtr()->getDelta();

  float temp = m_animationTime;

  m_animationTime = Math::modf(m_animTimeInSecs/m_animation->m_ticksPerSecond,
                               m_animation->m_duration);

  if(temp>m_animationTime){
    m_actualLocationKey = 0;
    m_actualScaleKey = 0;
    m_actualRotationKey = 0;
  }
  if(m_skeleton)
  readNodeHeirarchy(m_skeleton->m_skeleton,Matrix4f::IDENTITY);
}


void 
AnimationComponent::readNodeHeirarchy(
  SPtr<SkeletalNode> skeletalNode, 
  const Matrix4f& parentTransform
  )
{
  auto animNode = m_animation->m_nodes[skeletalNode->name];

  Matrix4f globalTransform;

  Matrix4f nodeTransform = Matrix4f::IDENTITY;

  if(animNode.get()){
    nodeTransform =
    Matrix4f::translateMatrix(interpolatedLocation(animNode))*
    interpolatedRotation(animNode).toMatrix()*
    Matrix4f::scaleMatrix(interpolatedScale(animNode));
  }

  globalTransform = parentTransform*nodeTransform;

  for(auto mesh : m_model->m_meshes){
    if(mesh->m_boneMaping.find(skeletalNode->name) != mesh->m_boneMaping.end()){
      uint32 boneIndex = mesh->m_boneMaping[skeletalNode->name];

      mesh->m_ofset[boneIndex] = m_skeleton->m_globalInverse*
                                 globalTransform*
                                 mesh->m_bones[boneIndex];

      m_skeleton->m_finalMatrix[skeletalNode->name] = globalTransform;
    }
  }

  for(auto child : skeletalNode->childs){
    readNodeHeirarchy(child,globalTransform);
  }

}

Vector3f
AnimationComponent::interpolatedLocation(SPtr<AnimNode> node)
{
  if(node->locations.size() == 1){
    return node->locations[0].second;
  }

  auto& actualKey = node->locations[m_actualLocationKey];
  auto& nextKey = node->locations[m_actualLocationKey+1];

  if(nextKey.first < m_animationTime){
    ++m_actualLocationKey;
    actualKey = node->locations[m_actualLocationKey];
    nextKey = node->locations[m_actualLocationKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  Math::modf(m_animationTime,1.f)
  );
}

Vector3f 
AnimationComponent::interpolatedScale(SPtr<AnimNode> node)
{
  if(node->scales.size() == 1){
    return node->scales[0].second;
  }

  auto& actualKey = node->scales[m_actualScaleKey];
  auto& nextKey = node->scales[m_actualScaleKey+1];

  if(nextKey.first<m_animationTime){
    ++m_actualScaleKey;
    actualKey = node->scales[m_actualScaleKey];
    nextKey = node->scales[m_actualScaleKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  Math::modf(m_animationTime,1.f)
  );
}

Quaternion
AnimationComponent::interpolatedRotation(SPtr<AnimNode> node)
{
  //return node->rotations[0].second;
  if(node->rotations.size() == 1){
    return node->rotations[0].second;
  }

  auto& actualKey = node->rotations[m_actualRotationKey];
  auto& nextKey = node->rotations[m_actualRotationKey+1];

  if(nextKey.first<m_animationTime){
    ++m_actualRotationKey;
    actualKey = node->rotations[m_actualRotationKey];
    nextKey = node->rotations[m_actualRotationKey+1];
  }
  //return actualKey.second;
  return Quaternion::interpolate(
                                actualKey.second,
                                nextKey.second,
                                Math::modf(m_animationTime,1.f)
                                );
}


}

