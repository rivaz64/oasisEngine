#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"
#include "oaCamera.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaSceneGraph.h"

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
  update(float delta) override;

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

 public:

   SPtr<Object> character;

   SPtr<Object> testObject;

   SPtr<Camera> cam;

   SPtr<Buffer> camBuf;

   SPtr<SamplerState> samsta;

   SPtr<RenderTarget> render;

   SPtr<RenderTarget> renderToTexture;

   SPtr<Texture> depthStencil;

   SPtr<DepthStencil> depthStencilView;

   SPtr<Texture> renTex;

   SPtr<SceneGraph> scene; 

   SPtr<Object> actualObject;

  SPtr<Shader> vertexShader;

  SPtr<Shader> pixelShader;

  
};

}


