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
#include <CrowdSimulator.h>
#include "imgui_internal.h"
namespace oaEngineSDK{

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
  updateImGui();

  void
  ImGuiBehind();

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
  initMeshScene();
  
  void
  generateCube();

  void 
  initMaterialScene();

  void 
  initModelScene();

  void 
  components();
  //void
  //genMorbiusTrip();

 public:

  /**
   * @brief the scene of the world
  */
  SPtr<Actor> m_worldScene;

  /**
   * @brief the scene for inspecting meshes
  */
  SPtr<Actor> m_meshScene;

  /**
   * @brief the scene for inspecting materials
  */
  SPtr<Actor> m_materialScene;

  /**
   * @brief the scene for inspecting models
  */
  SPtr<Actor> m_modelScene;

  /**
   * @brief the model for the mesh inspector
  */
  SPtr<Model> m_meshModel;

  /**
   * @brief the model for the material inspector
  */
  SPtr<Model> m_materialModel;

  /**
   * @brief the material for the model of the mesh inspector
  */
  SPtr<Material> m_meshMaterial;

  //WPtr<Resourse> m_selected
  WPtr<Actor> m_selectedActor;
  
  WPtr<Texture> m_selectedTexture;
  
  WPtr<Material> m_selectedMaterial;
  
  WPtr<StaticMesh> m_selectedMesh;
  
  WPtr<SkeletalMesh> m_selectedSkeletalMesh;
  
  WPtr<Model> m_selectedModel;

  WPtr<SkeletalModel> m_selectedSkeletalModel;
  
  WPtr<Skeleton> m_selectedSkeleton;
  
  WPtr<Animation> m_selectedAnimation;

  SPtr<Keyboard> m_keyboard;

  SPtr<Mouse> m_mouse;

  SPtr<StaticMesh> m_morbiusTrip;

  WPtr<Actor> m_controlledActor;

  WPtr<Camera> m_debugCamera;

  SPtr<StaticMesh> cube;

  Vector<String> m_actors;

  Vector<WPtr<Actor>> agents;


  Vector4f m_ssaoConfig;

  Loader* loader;

  //bool play = flase;

  bool isCreatingActor = false;

  bool isAddingActor = false;

  bool isAddingComponent = false;

  bool isAddingSocket = false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;

  bool animInPlay=false;

  Path m_projectPath;

  bool textureInspector = false;

  bool m_hasGrid=true;

  ImGuiContext* m_imguiState1;
  ImGuiContext *m_imguiState2;

  int numOfAgents = 6;
  SPtr<Actor> agent;
  cwSDKtoolkit::SPtr<cwSDKtoolkit::CrowdSimulator> cw;

  EventHandler<const Vector3f&> handler;

  /**
   * @brief if a project is currently open in the engine
  */
  bool isProjectOpen = false;

  SPtr<Actor> m_morbActor;
  SPtr<GraphicsComponent> m_morbComponent;
  SPtr<Model> m_morbModel;
};

}


