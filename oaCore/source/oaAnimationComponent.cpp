#include "oaAnimationComponent.h"
#include "oaAnimation.h"
#include "oaSkeletalComponent.h"
#include "oaObject.h"
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
AnimationComponent::update(SPtr<Object> actor)
{
  OA_ASSERT(actor->getComponent<SkeletalComponent>().get());

  if(!animation){
    return;
  }

  auto skeleton = actor->getComponent<SkeletalComponent>()->skeleton;

  auto model = actor->getComponent<GraphicsComponent>()->model;

  animTimeInSecs += Time::instancePtr()->getDelta();

  //float timeInTicks = animation->ticksPerSecond * Time::instancePtr()->getDelta();

  float temp = animationTime;

  animationTime = Math::modf(animTimeInSecs/animation->ticksPerSecond,animation->duration);

  if(temp>animationTime){
    actualLocationKey = 0;
    actualScaleKey = 0;
    actualRotationKey = 0;
  }

  readNodeHeirarchy(skeleton->skeleton,Matrix4f::IDENTITY,skeleton,model);
}


void 
AnimationComponent::readNodeHeirarchy(
  SPtr<SkeletalNode> skeletalNode, 
  const Matrix4f& parentTransform,
  SPtr<Skeleton> skeleton,
  SPtr<Model> model
  )
{
  auto animNode = animation->nodes[skeletalNode->name];

  Matrix4f globalTransform;

  Matrix4f nodeTransform = Matrix4f::IDENTITY;

  if(animNode.get()){
    nodeTransform =
    Matrix4f::translateMatrix(interpolatedLocation(animNode))*
    interpolatedRotation(animNode).toMatrix()*
    Matrix4f::scaleMatrix(interpolatedScale(animNode));
  }

  globalTransform = parentTransform*nodeTransform;

  for(auto mesh : model->meshes){
    if(mesh->boneMaping.find(skeletalNode->name) != mesh->boneMaping.end()){
      uint32 boneIndex = mesh->boneMaping[skeletalNode->name];
      mesh->ofset[boneIndex] = skeleton->globalInverse*globalTransform*mesh->bones[boneIndex];
    }
  }
  /*skeleton->boneMaping[skeletalNode->name] = 
    skeleton->globalInverse*globalTransform;*/

  for(auto child : skeletalNode->childs){
    readNodeHeirarchy(child,globalTransform,skeleton,model);
  }

}

Vector3f
AnimationComponent::interpolatedLocation(SPtr<AnimNode> node)
{
  if(node->locations.size() == 1){
    return node->locations[0].second;
  }

  auto& actualKey = node->locations[actualLocationKey];
  auto& nextKey = node->locations[actualLocationKey+1];

  if(nextKey.first<animationTime){
    ++actualLocationKey;
    actualKey = node->locations[actualLocationKey];
    nextKey = node->locations[actualLocationKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  Math::modf(animationTime,1.f)
  );
}

Vector3f 
AnimationComponent::interpolatedScale(SPtr<AnimNode> node)
{
  if(node->scales.size() == 1){
    return node->scales[0].second;
  }

  auto& actualKey = node->scales[actualScaleKey];
  auto& nextKey = node->scales[actualScaleKey+1];

  if(nextKey.first<animationTime){
    ++actualScaleKey;
    actualKey = node->scales[actualScaleKey];
    nextKey = node->scales[actualScaleKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  Math::modf(animationTime,1.f)
  );
}

Quaternion
AnimationComponent::interpolatedRotation(SPtr<AnimNode> node)
{
  //return node->rotations[0].second;
  if(node->rotations.size() == 1){
    return node->rotations[0].second;
  }

  auto& actualKey = node->rotations[actualRotationKey];
  auto& nextKey = node->rotations[actualRotationKey+1];

  if(nextKey.first<animationTime){
    ++actualRotationKey;
    actualKey = node->rotations[actualRotationKey];
    nextKey = node->rotations[actualRotationKey+1];
  }
  //return actualKey.second;
  return Quaternion::interpolate(
  actualKey.second,
  nextKey.second,
  Math::modf(animationTime,1.f)
  );
}


}

