/**
* @file oaAnimation.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaQuaternion.h"
#include "oaResourse.h"

namespace oaEngineSDK{

/**
 * @brief an animation channel
*/
struct OA_CORE_EXPORT AnimChannel{

  /**
   * @brief the keyframes of the locations
  */
  Vector<Pair<float,Vector4f>> locations;

  /**
   * @brief the keyframes of the scales
  */
  Vector<Pair<float,Vector4f>> scales;

  /**
   * @brief the keyframes of the rotations
  */
  Vector<Pair<float,Quaternion>> rotations;

};

/**
 * @brief a class to store animations
*/
class OA_CORE_EXPORT Animation :
  public Resourse
{

 public:

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kAnimation;
  }
  
  FORCEINLINE void
  setDuration(float duration)
  {
    m_duration = duration;
  }

  FORCEINLINE void
  setTicksPerSecond(float ticksPerSecond)
  {
    m_ticksPerSecond = ticksPerSecond;
  }

  FORCEINLINE void
  addChannel(uint32 id, SPtr<AnimChannel> node)
  {
    m_channels.insert({id,node});
  }

  FORCEINLINE float
  getTicksPerSecond()
  {
    return m_ticksPerSecond;
  }

  FORCEINLINE float
  getDuration()
  {
    return m_duration;
  }

  FORCEINLINE bool 
  hasChannel(uint32 id)
  {
    return m_channels.find(id) != m_channels.end();
  }

  FORCEINLINE Matrix4f
  getTransformOfChannelAtTime(uint32 id, float time);

 public:

  /**
   * @brief the ticks this animation has 
  */
  float m_duration;

  /**
   * @brief how many tiks have to be executed each second
  */
  float m_ticksPerSecond;

  /**
   * @brief the keyFrames of the animation
  */
  Map<uint32,SPtr<AnimChannel>> m_channels;

  friend class Loader;
};

}


