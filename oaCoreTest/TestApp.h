#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"
#include "oaCamera.h"

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

   //SPtr<Object> triangle;
   SPtr<Object> character;

   SPtr<Camera> cam;

   SPtr<Buffer> camBuf;
};

}


