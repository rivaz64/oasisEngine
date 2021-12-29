#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"
#include "oaCamera.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaSceneGraph.h"
#include "oaVector4f.h"
#include "oaChunk.h"
#include "oaMarchingCubes.h"

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

  void
  childsInImgui(SPtr<Object> parentObject);

 public:

   SPtr<Object> character;

   SPtr<Object> testObject;

   SPtr<Object> testObjectMC;

   SPtr<Camera> cam;

   SPtr<SamplerState> samsta;

   SPtr<RenderTarget> render;

   SPtr<RenderTarget> renderToTexture;

   SPtr<Texture> depthStencil;

   SPtr<DepthStencil> depthStencilView;

   SPtr<Texture> renTex;

   //SPtr<SceneGraph> scene; 

   SPtr<Object> actualObject;

   SPtr<Object> scene;

  SPtr<Shader> vertexShader;

  SPtr<Shader> pixelShader;

  SPtr<Texture> actualTexture;

  SPtr<Mesh> actualMesh;

  SPtr<Model> actualModel;

  bool mousePressed = false;

  SPtr<Buffer> lights;

  Vector4f color;

  Vector4f dir;

  SPtr<Chunk> chnk;

  SPtr<MarchingCubes> mc;
};

}


