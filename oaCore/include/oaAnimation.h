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
  readNodeHeirarchy(const float animationTime,SPtr<SkeletalNode> node, const Matrix4f& transform);
  
  /**
   * @brief calculates the interpolation of the location
   * @param animationTime 
   * @param node 
   * @return 
  */
  Vector3f
  interpolatedLocation(const float animationTime,SPtr<AnimNode> node);

  /**
   * @brief calculates the interpolation of the scale
   * @param animationTime 
   * @param node 
   * @return 
  */
  Vector3f
  interpolatedScale(const float animationTime,SPtr<AnimNode> node);

  /**
   * @brief calculates the interpolation of the rotation
   * @param animationTime 
   * @param node 
   * @return 
  */
  Quaternion
  interpolatedRotation(const float animationTime,SPtr<AnimNode> node);

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

  /**
   * @brief the skeleton this animation uses
  */
  SPtr<Skeleton> skeleton;

  /**
   * @brief the time where the animation is at;
  */
  float animationTime = 0;

  /**
   * @brief the actual key frame of the location
  */
  uint32 actualLocationKey = 0;

  /**
   * @brief the actual key frame of the scale
  */
  uint32 actualScaleKey = 0;

  /**
   * @brief the actual key frame of the rotation
  */
  uint32 actualRotationKey = 0;

  friend class Model;
};

}


