/**
* @file oaAnimation.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#include "oaAnimation.h"

namespace oaEngineSDK{

void 
Animation::update(float deltaTime)
{
  float timeInTicks = ticksPerSecond * deltaTime;

  float temp = animationTime;

  animationTime =  Math::modf(animationTime+timeInTicks,duration);

  if(temp>animationTime){
    actualLocationKey = 0;
    actualScaleKey = 0;
    actualRotationKey = 0;
  }

  readNodeHeirarchy(animationTime,skeleton->skeleton,Matrix4f::IDENTITY);
}

void 
Animation::readNodeHeirarchy(const float animationTime,SPtr<SkeletalNode> skeletalNode, const Matrix4f& parentTransform)
{
  auto animNode = nodes[skeletalNode->name];

  Matrix4f globalTransform;

  if(animNode.get()){
    globalTransform =
    parentTransform*
    Matrix4f::translateMatrix(interpolatedLocation(animationTime,animNode))*
    interpolatedRotation(animationTime,animNode).toMatrix()*
    Matrix4f::scaleMatrix(interpolatedScale(animationTime,animNode));
  }
  else{
    globalTransform = parentTransform;
  }



}

Vector3f
Animation::interpolatedLocation(const float animationTime, SPtr<AnimNode> node)
{
  if(node->locations.size() == 1){
    return node->locations[0].second;
  }

  auto& actualKey = node->locations[actualLocationKey];
  auto& nextKey = node->locations[actualLocationKey+1];

  if(nextKey.first>animationTime){
    ++actualLocationKey;
    actualKey = node->locations[actualLocationKey];
    nextKey = node->locations[actualLocationKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  (animationTime-actualKey.first)/(nextKey.first - actualKey.first)
  );
}

Vector3f 
Animation::interpolatedScale(const float animationTime, SPtr<AnimNode> node)
{
  if(node->scales.size() == 1){
    return node->scales[0].second;
  }

  auto& actualKey = node->scales[actualScaleKey];
  auto& nextKey = node->scales[actualScaleKey+1];

  if(nextKey.first>animationTime){
    ++actualScaleKey;
    actualKey = node->scales[actualScaleKey];
    nextKey = node->scales[actualScaleKey+1];
  }

  return Vector3f::interpolate(
  actualKey.second,
  nextKey.second,
  (animationTime-actualKey.first)/(nextKey.first - actualKey.first)
  );
}

Quaternion
Animation::interpolatedRotation(const float animationTime, SPtr<AnimNode> node)
{
  if(node->rotations.size() == 1){
    return node->rotations[0].second;
  }

  auto& actualKey = node->rotations[actualRotationKey];
  auto& nextKey = node->rotations[actualRotationKey+1];

  if(nextKey.first>animationTime){
    ++actualRotationKey;
    actualKey = node->rotations[actualRotationKey];
    nextKey = node->rotations[actualRotationKey+1];
  }

  return Quaternion::interpolate(
  actualKey.second,
  nextKey.second,
  (animationTime-actualKey.first)/(nextKey.first - actualKey.first)
  );
}

}

