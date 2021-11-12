#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"
#include "oaCamera.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"

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

   SPtr<SamplerState> samsta;

   SPtr<RenderTarget> render;

   SPtr<Texture> depthStencil;

   SPtr<DepthStencil> depthStencilView;
};

}


