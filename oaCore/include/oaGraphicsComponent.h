/**
* @file oaGraphicsComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaComponent.h"
#include "oaModel.h"

namespace oaEngineSDK{
/**
 * @brief the grafical part of the object
*/
class OA_CORE_EXPORT GraphicsComponent :
  public Component
{
 public:

  void
  onAttach(SPtr<Object> actor);

  COMPONENT_TYPE
  getType() override; 

 public:

  /**
   * @brief a model
  */
  SPtr<Model> model;
};

}


