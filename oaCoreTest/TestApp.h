#pragma once

#include "oaBaseApp.h"
#include "oaObject.h"
#include "oaCamera.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaVector4f.h"
#include "oaChunk.h"
#include "oaMarchingCubes.h"
#include "oaProceduralTerrain.h"
#include "oaNoise2D.h"
#include "oaLoader.h"

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
  postUpdate(float delta) override;

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

  SubMesh
  tetrahedron();

  SubMesh
  octahedron();

  SubMesh
  icosahedron();

  SubMesh
  SubDivide(const SubMesh& data);

  

 public:

   SPtr<Object> character;

   SPtr<Object> testObject1;

   SPtr<Object> testObject2;

   SPtr<Object> testObjectMC;

   SPtr<Camera> cam;

   SPtr<SamplerState> samsta;


   SPtr<RenderTarget> renderToTexture;


   SPtr<Texture> renTex;

   //SPtr<SceneGraph> scene; 

   SPtr<Object> actualObject;

  SPtr<Shader> vertexShader;

  SPtr<Shader> pixelShader;

  SPtr<Texture> actualTexture;

  SPtr<Mesh> actualMesh;

  SPtr<Model> actualModel;

  SPtr<Skeleton> actualSkeleton;

  SPtr<Animation> actualAnimation;

  bool mousePressed = false;

  SPtr<Buffer> lights;

  Vector4f color;

  Vector4f dir;

  SPtr<Chunk> chnk;

  SPtr<MarchingCubes> mc;

  SPtr<ProceduralTerrain> pt1;
  SPtr<ProceduralTerrain> pt2;

  SPtr<Noise2D> noise1;

  SPtr<Noise2D> noise2;

  Loader* loader;

  bool isCreatingObject=false;

  bool isAddingComponent=false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;
};

}


