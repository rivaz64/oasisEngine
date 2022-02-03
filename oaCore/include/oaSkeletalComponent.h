/**
* @file oaSkeletalComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaComponent.h"


namespace oaEngineSDK{

/**
 * @brief the component for the skeleton
*/
class OA_CORE_EXPORT SkeletalComponent :
  public Component
{
 public:

  COMPONENT_TYPE::E
  getType() override; 

  void
  update(SPtr<Actor> actor) override;

  /**
   * @brief attach a model to a bone 
   * @param model the model to be attached
   * @param bone the bone the model is going to be attached
   * @return if the model was attached
  */
  bool
  attachToBone(SPtr<Model> model,String bone);

  /**
   * @brief the skeleton this component is using
  */
  SPtr<Skeleton> m_skeleton;

  /**
   * @brief the model this component is using
  */
  SPtr<Model> m_model;

  /**
   * @brief the sockets this skeleton has
  */
  Map<SPtr<Model>,String> m_sockets;
};

}


