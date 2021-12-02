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
Animation::readNodeHeirarchy(const float animationTime,SPtr<SkeletalNode> skeletalNode, const Matrix4f& transform)
{
  auto animNode = nodes[skeletalNode->name];

  if(animNode.get()){
    
  }
}

Vector3f Animation::interpolatedLocation(const float animationTime, SPtr<AnimNode> node)
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

  return Vector3f::inetpolate(
  actualKey.second,
  nextKey.second,
  (animationTime-actualKey.first)/(nextKey.first - actualKey.first)
  );
}

Vector3f Animation::interpolatedScale(const float animationTime, SPtr<AnimNode> node)
{
  if(node->scales.size() == 1){
    return node->scales[0].second;
  }

  auto& actualKey = node->scales[actualLocationKey];
  auto& nextKey = node->scales[actualLocationKey+1];

  if(nextKey.first>animationTime){
    ++actualLocationKey;
    actualKey = node->scales[actualLocationKey];
    nextKey = node->scales[actualLocationKey+1];
  }

  return Vector3f::inetpolate(
  actualKey.second,
  nextKey.second,
  (animationTime-actualKey.first)/(nextKey.first - actualKey.first)
  );
}

}

