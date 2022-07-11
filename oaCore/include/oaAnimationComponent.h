/**
* @file oaAnimationComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaComponent.h"

namespace oaEngineSDK{

/**
 * @brief a conponent that handles the animation
*/
class OA_CORE_EXPORT AnimationComponent :
  public Component
{
 public:

  COMPONENT_TYPE::E
  getType() override;

  /**
   * @brief updates the animation
   * @param actor 
  */
  void
  update(WPtr<Actor> actor) override;

  /**
   * @brief reads each node to update it to the right time
   * @param animationTime 
   * @param parentTransform the transform of the parent node
  */
  void
  readNodeHeirarchy(WPtr<SkeletalNode> wNode, const Matrix4f& parentTransform);
  
  /**
   * @brief calculates the interpolation of the location
   * @param animationTime 
   * @param node 
   * @return 
  */
  Vector3f
  interpolatedLocation(WPtr<AnimNode> wNode);

  /**
   * @brief calculates the interpolation of the scale
   * @param animationTime 
   * @param node 
   * @return 
  */
  Vector3f
  interpolatedScale(WPtr<AnimNode> wNode);

  /**
   * @brief calculates the interpolation of the rotation
   * @param animationTime 
   * @param node 
   * @return 
  */
  Quaternion
  interpolatedRotation(WPtr<AnimNode> wNode);

  

 private:
  /**
   * @brief the time where the animation is at in animation time
  */
  float m_animationTime = 0;

  /**
   * @brief the time where the animation is at in seconds
  */
  float m_animTimeInSecs = 0;

  /**
   * @brief the actual key frame of the location
  */
  uint32 m_actualLocationKey = 0;

  /**
   * @brief the actual key frame of the scale
  */
  uint32 m_actualScaleKey = 0;

  /**
   * @brief the actual key frame of the rotation
  */
  uint32 m_actualRotationKey = 0;

  /**
   * @brief the animation this component uses
  */
  WPtr<Animation> m_animation;

  /**
   * @brief the model using the animation
  */
  WPtr<Model> m_model;

  /**
   * @brief the skeleton using the animation
  */
  WPtr<Skeleton> m_skeleton;
};

}


