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
  
  

  //void
  //genMorbiusTrip();

 public:

  /**
   * @brief the scene of the world
  */
  SPtr<Scene> m_worldScene;

  /**
   * @brief the scene for inspecting meshes
  */
  SPtr<Scene> m_meshScene;

  /**
   * @brief the model for the mesh inspector
  */
  SPtr<Model> m_meshModel;

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

  Vector<DirectionalLight> m_directionalLights;

  Vector<PointLight> m_pointLights;

  Vector<SpotLight> m_spotLights;

  Vector<WPtr<Actor>> agents;

  Vector4f m_ssaoConfig;

  Loader* loader;

  //bool play = flase;

  bool isCreatingActor = false;

  bool isAddingComponent = false;

  bool isAddingSocket = false;

  char imguiString[64];

  LOADERFLAGS::E loadflags;

  uint32 loadflags0 = 0;

  uint8 loaderFlagsActive;

  bool animInPlay=false;

  Path m_projectPath;

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


