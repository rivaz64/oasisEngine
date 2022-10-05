#pragma once

#include "oaGraphicsComponent.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT StaticMeshComponent :
  public GraphicsComponent
{
 public:

  virtual COMPONENT_TYPE::E
  getType() override; 

  void
  save(Serializer& serializer) override;

  void
  load(Serializer& serializer) override;

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
  FORCEINLINE const WPtr<Model>
  getModel(){
    return m_model;
  }

private: 

  /**
   * @brief the model of the component
  */
  WPtr<Model> m_model;
};

}


