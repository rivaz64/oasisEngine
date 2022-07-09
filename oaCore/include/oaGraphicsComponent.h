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

  //void
  //onAttach(SPtr<Actor> actor);

  COMPONENT_TYPE::E
  getType() override; 

  /**
   * @brief updates the transforms of the 
   * @param actor 
  */
  void
  update(WPtr<Actor> actor) override;

  /**
   * @brief set the model of this component
   * @param model 
  */
  FORCEINLINE void
  setModel(WPtr<Model> model){
    m_model = model;
  }

  /**
   * @brief gets the model of this component
   * @return 
  */
  FORCEINLINE const WPtr<Model>&
  getModel(){
    return m_model;
  }

  FORCEINLINE Transform&
  getTransform(){
    return m_transform;
  }

 private:

  /**
   * @brief the model of the component
  */
  WPtr<Model> m_model;

  /**
   * @brief the transform of the model
  */
  Transform m_transform;
};

}


