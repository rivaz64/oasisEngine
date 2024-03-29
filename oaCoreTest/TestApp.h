#pragma once

#include "oaBaseApp.h"
#include <oaEventSystem.h>
#include "oaActor.h"
#include "oaCamera.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaVector4f.h"
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

  //SubMesh
  //tetrahedron();
  //
  //SubMesh
  //octahedron();
  //
  //Mesh
  //icosahedron();
  //
  //SubMesh
  //SubDivide(Vector<Vector4f>& vertices, Vector<uint32>& indices);

  void
  vertexForEdge(Map<Pair<uint32, uint32>, uint32>& used, 
                Vector<Vector4f>& vertices, 
                uint32 index1, 
                uint32 index2);
  
  void
  genMorbiusTrip();

 public:

  WPtr<Actor> m_selectedActor;

  WPtr<Texture> m_selectedTexture;

  WPtr<Material> m_selectedMaterial;

  WPtr<StaticMesh> m_selectedMesh;

  WPtr<Model> m_selectedModel;

  WPtr<Skeleton> m_selectedSkeleton;

  WPtr<Animation> m_selectedAnimation;

  SPtr<Keyboard> m_keyboard;

  SPtr<Mouse> m_mouse;

  SPtr<StaticMesh> m_morbiusTrip;

  WPtr<Actor> m_controlledActor;

  WPtr<Camera> m_debugCamera;

  Vector<DirectionalLight> m_directionalLights;

  Vector<PointLight> m_pointLights;

  Vector<SpotLight> m_spotLights;

  Vector4f m_ssaoConfig;

  Loader* loader;

  bool isCreatingActor = false;

  bool isAddingComponent = false;

  bool isAddingSocket = false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;

  bool animInPlay=false;

  EventHandler<const Vector3f&> handler;

  SPtr<Actor> m_morbActor;
  SPtr<GraphicsComponent> m_morbComponent;
  SPtr<Model> m_morbModel;
};

}


