/**
* @file oaAnimation.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaQuaternion.h"

namespace oaEngineSDK{

struct AnimNode{
  
  /**
   * @brief the name of this node
  */
  String name;

  /**
   * @brief the locations of this node
  */
  Vector<Vector3f> locations;

  /**
   * @brief the scales of this node
  */
  Vector<Vector3f> scales;

  /**
   * @brief the rotations of this node
  */
  Vector<Quaternion> rotations;

};

class Animation
{
 public:
  
  /**
   * @brief updates the animation to be in the right position
   * @param deltaTime 
  */
  void
  update(float deltaTime);

 private:

  /**
   * @brief reads each node to update it to the right time
   * @param animationTime 
   * @param transform the transform of the parent node
  */
  void
  readNodeHeirarchy(float animationTime,const AnimNode& node, const Matrix4f& transform);
  
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
};

}


