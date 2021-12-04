/**
* @file oaAnimation.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaQuaternion.h"
#include "oaSkeleton.h"

namespace oaEngineSDK{

struct AnimNode{
  
  /**
   * @brief the name of this node
  */
  String name;

  /**
   * @brief the keyframes of the locations
  */
  Vector<Pair<uint32,Vector3f>> locations;

  /**
   * @brief the keyframes of the scales
  */
  Vector<Pair<uint32,Vector3f>> scales;

  /**
   * @brief the keyframes of the rotations
  */
  Vector<Pair<uint32,Quaternion>> rotations;

};

class Animation
{

 private:

  /**
   * @brief the ticks this animation has 
  */
  float duration;

  /**
   * @brief how many tiks have to be executed each second
  */
  float ticksPerSecond;

  /**
   * @brief the keyFrames of the animation
  */
  Map<String,SPtr<AnimNode>> nodes;

  

  friend class Model;
  friend class AnimationComponent;
};

}


