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
  postShutDown() override;

  void
  preInit();

  void 
  postInit() override;

  void
  update() override;

  void
  draw() override;

  void
  initImGui();

  void
  newImGuiFrame();

  void
  renderImGui();

  void
  drawImGui();

 private:

   //SPtr<Object> triangle;
   SPtr<Object> character;

   SPtr<Camera> cam;

   SPtr<Buffer> camBuf;
};

}


