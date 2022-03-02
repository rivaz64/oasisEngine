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

struct ModelComponent{

  ModelComponent(SPtr<Model> _model) : model(_model){}

  ModelComponent(){}

  FORCEINLINE Matrix4f 
  getFinalTransform(){
    return transform*
           Matrix4f::translateMatrix(location)*
           Matrix4f::rotationMatrix(rotation)*
           Matrix4f::scaleMatrix(scale);
  }

  SPtr<Model> model;

  Vector3f location = Vector3f(0,0,0);

  Vector3f scale = Vector3f(1,1,1);

  Vector3f rotation = Vector3f(0,0,0);

  Matrix4f transform  = Matrix4f::IDENTITY;
};

/**
 * @brief the grafical part of the Actor
*/
class OA_CORE_EXPORT GraphicsComponent :
  public Component
{
 public:

  void
  onAttach(SPtr<Actor> actor);

  COMPONENT_TYPE::E
  getType() override; 

  /**
   * @brief attach a model componet to the actual component
   * @param component 
  */
  void
  attach(SPtr<GraphicsComponent> component);

  /**
   * @brief updates the transforms of the 
   * @param actor 
  */
  void
  update(SPtr<Actor> actor) override;

  /**
   * @brief set the model of this component
   * @param model 
  */
  FORCEINLINE void
  setModel(SPtr<Model> model){
    m_model = model;
  }

  /**
   * @brief gets the model of this component
   * @return 
  */
  FORCEINLINE const SPtr<Model>&
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
  SPtr<Model> m_model;

  /**
   * @brief the transform of the model
  */
  Transform m_transform;
};

}


