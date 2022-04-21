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
#include "oaLights.h"
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

  Mesh
  icosahedron();

  SubMesh
  SubDivide(Vector<Vector4f>& vertices, Vector<uint32>& indices);

  void
  vertexForEdge(Map<Pair<uint32, uint32>, uint32>& used, 
                Vector<Vector4f>& vertices, 
                uint32 index1, 
                uint32 index2);

  void
  onKeyBoardInput(char input);

 public:

  SPtr<Actor> m_selectedActor;

  SPtr<Texture> m_selectedTexture;

  SPtr<Material> m_selectedMaterial;

  SPtr<Mesh> m_selectedMesh;

  SPtr<Model> m_selectedModel;

  SPtr<Skeleton> m_selectedSkeleton;

  SPtr<Animation> m_selectedAnimation;

  SPtr<ShaderProgram> m_program; 

  //SPtr<Buffer> lights;

  SPtr<Actor> m_controlledActor;

  SPtr<Camera> m_debugCamera;

  Vector<DirectionalLight> m_directionalLights;

  Vector<PointLight> m_pointLights;

  Vector4f m_ssaoConfig;

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


