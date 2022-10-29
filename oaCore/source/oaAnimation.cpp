/**
* @file oaAnimation.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#include "oaAnimation.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

Vector4f
interpolatedLocation(SPtr<AnimChannel> channel, float time)
{
  if(channel->locations.size() == 1){
    return channel->locations[0].second;
  }

  Vector4f prevKey, nextKey;
  float prevTime=0, nextTime=0;

  for(auto& keys : channel->locations){
    if(time < keys.first){
      nextKey = keys.second;
      nextTime = keys.first;
      break;
    }
    prevKey = keys.second;
    prevTime = keys.first;
  }

  return Vector4f::interpolate(
  prevKey,
  nextKey,
  (time-prevTime)/(nextTime-prevTime)
  );
}

Vector4f
interpolatedScale(SPtr<AnimChannel> channel, float time)
{
  if(channel->scales.size() == 1){
    return channel->scales[0].second;
  }

  Vector4f prevKey, nextKey;
  float prevTime=0, nextTime=0;

  for(auto& keys : channel->scales){
    if(time < keys.first){
      nextKey = keys.second;
      nextTime = keys.first;
      break;
    }
    prevKey = keys.second;
    prevTime = keys.first;
  }

  return Vector4f::interpolate(
  prevKey,
  nextKey,
  (time-prevTime)/(nextTime-prevTime)
  );
}

Quaternion
interpolatedRotation(SPtr<AnimChannel> channel, float time)
{
  if(channel->rotations.size() == 1){
    return channel->rotations[0].second;
  }

  Quaternion prevKey, nextKey;
  float prevTime=0, nextTime=0;

  for(auto& keys : channel->rotations){
    if(time < keys.first){
      nextKey = keys.second;
      nextTime = keys.first;
      break;
    }
    prevKey = keys.second;
    prevTime = keys.first;
  }

  return Quaternion::interpolate(
  prevKey,
  nextKey,
  (time-prevTime)/(nextTime-prevTime)
  );
}

Matrix4f 
Animation::getTransformOfChannelAtTime(uint32 id, float time)
{
  auto channel = m_channels[id];
  return
    Matrix4f::translateMatrix(interpolatedLocation(channel,time).xyz)*
    interpolatedRotation(channel,time).toMatrix()*
    Matrix4f::scaleMatrix(interpolatedScale(channel,time).xyz);
}

}

