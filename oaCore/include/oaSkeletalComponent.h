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
  update(SPtr<Object> actor) override;

  SPtr<Skeleton> skeleton;
};

}


