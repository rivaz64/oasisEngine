#pragma once

#include "oaGraphicsComponent.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT SkeletalMeshComponent :
  public GraphicsComponent
{
 public:

  SkeletalMeshComponent() = default;

  SkeletalMeshComponent(WPtr<SkeletalModel> model);

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
  setModel(WPtr<SkeletalModel> model){
    m_model = model;
  }

  /**
   * @brief gets the model of this component
   * @return 
  */
  FORCEINLINE const WPtr<SkeletalModel>
  getModel(){
    return m_model;
  }

  FORCEINLINE const Vector<Matrix4f>&
  getBones(SIZE_T n)
  {
    return m_bones[n];
  }

  void
  setAtSecond(float time);

private: 

  /**
   * @brief the model of the component
  */
  WPtr<SkeletalModel> m_model;

  Vector<Vector<Matrix4f>> m_bones;

public:
  float m_actualTime;
};

}



