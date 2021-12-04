/**
* @file oaAnimationComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaComponent.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT AnimationComponent :
  public Component
{
 public:

  COMPONENT_TYPE
  getType() override;

  void
  update(SPtr<Object> actor) override;

  /**
   * @brief reads each node to update it to the right time
   * @param animationTime 
   * @param parentTransform the transform of the parent node
  */
  void
  readNodeHeirarchy(
    const float animationTime,
     SPtr<SkeletalNode> node, 
     const Matrix4f& parentTransform,
     SPtr<Skeleton> skeleton,
     SPtr<Model> model);
  
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
   * @brief the time where the animation is at;
  */
  float animationTime = 0;

  float animTimeInSecs = 0;

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

  SPtr<Animation> animation;
};

}


