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
struct AnimNode{
  
  /**
   * @brief the name of this node
  */
  String name;

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
class Animation :
  public Resourse
{

 public:
  
  String m_name;

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kAnimation;
  }
  
 private:

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
  Map<String,SPtr<AnimNode>> m_nodes;

  friend class Model;
  friend class AnimationComponent;
  friend class Loader;
};

}


