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
  Vector<Pair<float,Vector3f>> locations;

  /**
   * @brief the keyframes of the scales
  */
  Vector<Pair<float,Vector3f>> scales;

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
    m_secondsPerTick = 1.f/ticksPerSecond;
  }

  FORCEINLINE void
  addChannel(const String& name, SPtr<AnimChannel> node)
  {
    m_channels.insert({name,node});
  }

  FORCEINLINE float
  getSecondPerTicks()
  {
    return m_secondsPerTick;
  }

  FORCEINLINE bool 
  hasChannel(const String& name)
  {
    return m_channels.find(name) != m_channels.end();
  }

  FORCEINLINE Matrix4f
  getTransformOfChannelAtTime(const String& name, float time);

 public:

  /**
   * @brief the ticks this animation has 
  */
  float m_duration;

  /**
   * @brief how many tiks have to be executed each second
  */
  float m_secondsPerTick;

  /**
   * @brief the keyFrames of the animation
  */
  Map<String,SPtr<AnimChannel>> m_channels;

  friend class Loader;
};

}


