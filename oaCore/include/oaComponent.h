/**
* @file oaComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"


namespace oaEngineSDK{

namespace COMPONENT_TYPE{
enum E{
  NONE = 0,
  GRAPHICS,
  SKELETON,
  ANIMATION
};
}

/**
 * @brief a component an object can have
*/
class OA_CORE_EXPORT Component
{
 public:
  
  /**
   * @brief this executes when this is attached to an actor
   * @param actor 
  */
  virtual void
  onAttach(SPtr<Object> actor) {};

  /**
   * @brief updates this component
   * @param actor the actor that has this component
  */
  virtual void
  update(SPtr<Object> actor) {}

  /**
   * @brief get what is the type of this component
  */
  virtual COMPONENT_TYPE::E
  getType() {return COMPONENT_TYPE::NONE;}
};

}


