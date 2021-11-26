#pragma once
#include "oaComponent.h"
#include "oaModel.h"

namespace oaEngineSDK{

class oaGraphicsComponent :
  public Component
{
 public:

  void
  onAttach(SPtr<Object> actor);

  void
  update(SPtr<Object> actor);

 private:

  /**
   * @brief a model
  */
  SPtr<Model> model;
};

}


