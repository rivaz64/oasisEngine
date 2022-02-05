#pragma once

#include "oaBaseApp.h"
#include "oaActor.h"
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

struct ModelComponent;

class TestApp :
  public BaseApp
{
public:

  void
  preInit();

  void 
  postInit() override;

  void
  postUpdate(float delta) override;

  void
  preShutDown() override;

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
  childsInImgui(SPtr<Actor> parentActor);

  SubMesh
  tetrahedron();

  SubMesh
  octahedron();

  SubMesh
  icosahedron();

  SubMesh
  SubDivide(const SubMesh& data);

  

 public:

   SPtr<Actor> character;

   SPtr<Actor> testActor1;

   SPtr<Actor> testActor2;

   SPtr<Actor> testActorMC;

   SPtr<Camera> cam;

   SPtr<SamplerState> samsta;


   SPtr<RenderTarget> renderToTexture;

   //SPtr<SceneGraph> scene; 

   SPtr<Actor> actualActor;

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

  bool isCreatingActor = false;

  bool isAddingComponent = false;

  bool isAddingSocket = false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;

  ModelComponent* actualModelComponent = nullptr;

  bool animInPlay=false;
};

}


