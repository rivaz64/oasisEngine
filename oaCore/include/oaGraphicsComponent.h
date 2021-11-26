#pragma once
#include "oaComponent.h"
#include "oaModel.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT GraphicsComponent :
  public Component
{
 public:

  void
  onAttach(SPtr<Object> actor);

  void
  update(SPtr<Object> actor);

  COMPONENT_TYPE
  getType() override {return COMPONENT_TYPE::GRAPHICS;}

 public:

  /**
   * @brief a model
  */
  SPtr<Model> model;
};

}


