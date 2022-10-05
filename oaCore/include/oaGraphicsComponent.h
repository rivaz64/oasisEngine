/**
* @file oaGraphicsComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaTransform.h"
#include "oaComponent.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

/**
 * @brief the grafical part of the Actor
*/
class OA_CORE_EXPORT GraphicsComponent :
  public Component
{
 public:
  

  virtual COMPONENT_TYPE::E
  getType() override; 

  /**
   * @brief updates the transforms of the 
   * @param actor 
  */
  void
  update(WPtr<Actor> actor) override;

  void
  onAttach(WPtr<Actor> actor) override;

  FORCEINLINE Transform&
  getTransform(){
    return m_transform;
  }

  void 
  postUpdate();

  FORCEINLINE bool
  hasChanged()
  {
    return m_transform.m_changed;
  }

 private:

  /**
   * @brief the transform of the component
  */
  Transform m_transform;
};

}


