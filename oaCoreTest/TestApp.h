#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"

namespace oaEngineSDK{

class TestApp :
  public BaseApp
{
public:

  void
  run() override;

  void 
  postInit() override;

  void
  update() override;

  void
  draw() override;

 private:

   SPtr<Object> triangle;
};

}


