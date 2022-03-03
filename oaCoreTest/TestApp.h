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
  onInit() override;

  void 
  postInit() override;

  void
  onUpdate(float delta) override;

  void
  onDestroy() override;

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

  void
  onKeyBoardInput(char input);

 public:

  SPtr<SamplerState> m_samplerState; 

  SPtr<Actor> m_selectedActor;

  SPtr<Texture> m_selectedTexture;

  SPtr<Material> m_selectedMaterial;

  SPtr<Mesh> m_selectedMesh;

  SPtr<Model> m_selectedModel;

  SPtr<Skeleton> m_selectedSkeleton;

  SPtr<Animation> m_selectedAnimation;

  SPtr<ShaderProgram> m_program; 

  SPtr<Renderer> m_renderer;

  SPtr<Buffer> lights;

  SPtr<Actor> m_controlledActor;

  SPtr<Camera> m_debugCamera;

  Vector4f dir;

  Loader* loader;

  bool isCreatingActor = false;

  bool isAddingComponent = false;

  bool isAddingSocket = false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;

  ModelComponent* m_selectedModelComponent = nullptr;

  bool animInPlay=false;
};

}


