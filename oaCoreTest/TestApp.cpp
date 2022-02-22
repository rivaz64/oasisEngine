#include "TestApp.h"
#include <oaVector3f.h>
#include <oaGraphicAPI.h>
#include <oaModel.h>
#include <oaSamplerState.h>
#include <oaShader.h>
#include <oaInputManager.h>
#include <oaGrid2D.h>
#include <oaPerlinNoise2D.h>
#include <oaPerlinNoise3D.h>
#include <oaMaterial.h>
#include <oaGraphicsComponent.h>
#include <oaSkeletalComponent.h>
#include <oaAnimationComponent.h>
#include <oaDepthStencil.h>
#include <oaTexture.h>
#include <oaMesh.h>
#include <oaSimplexNoise.h>
#include <oaOctavesNoise.h>
#include <oaPath.h>
#include <oaSkeleton.h>
#include <oaAnimation.h>
#include <oaVertexBuffer.h>
#include <oaIndexBuffer.h>
#include <oaBuffer.h>
#include <oaActor.h>
#include <oaTime.h>
#include <oaLogger.h>
#include <oaResoureManager.h>
#include <oaScene.h>
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <oaSerializer.h>




extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

oaEngineSDK::TestApp* g_app = nullptr;

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;
  if(ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;

  switch( message )
  {
  case WM_PAINT:
    hdc = BeginPaint( hWnd, &ps );
    EndPaint( hWnd, &ps );
    break;

  case WM_QUIT:
    g_app->m_isRunning = false;
    break;

  case WM_DESTROY:
    g_app->m_isRunning = false;
    PostQuitMessage( 0 );
    break;

  case WM_SIZE:
    g_app->resizeWindow();
    break;
  

  case WM_KEYDOWN:
    g_app->processInputs(wParam);
    break;
    
  default:
    
    return DefWindowProc( hWnd, message, wParam, lParam );
  }

  return 0;
}



namespace oaEngineSDK {

void 
TestApp::preShutDown()
{
  auto& api = GraphicAPI::instance();
  if (api.m_actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
  }

  if (api.m_actualGraphicAPI == GRAPHIC_API::OPENGL) {
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
  }

  ImGui::DestroyContext();
}

void
TestApp::preInit()
{
  g_app = this;

  auto& api = GraphicAPI::instance();

  api.eventsFunction = WindowProc;
  
}

void 
TestApp::postInit()
{
  InputManager::instancePtr()->addInput(VK_RBUTTON);

  SamplerDesc sampDesc;
  ZeroMemory( &sampDesc, sizeof(sampDesc) );
  sampDesc.filter = FILTER::kMinMagMipLinear;
  sampDesc.addressU = TEXTURE_ADDRESS_MODE::kWrap;
  sampDesc.addressV = TEXTURE_ADDRESS_MODE::kWrap;
  sampDesc.addressW = TEXTURE_ADDRESS_MODE::kWrap;
  sampDesc.comparison = COMPARISON_FUNC::kNever;
  sampDesc.minLOD = 0.0f;
  sampDesc.maxLOD = Math::MAX_FLOAT;

  auto& graphicAPI = GraphicAPI::instance();
  
  m_samplerState = graphicAPI.createSamplerState(sampDesc);

  lights = graphicAPI.createBuffer();

  lights->init(sizeof(Vector4f));

  m_viewLocationBuffer = graphicAPI.createBuffer();

  m_viewLocationBuffer->init(sizeof(Vector4f));

  IMGUI_CHECKVERSION();

  initImGui();

  graphicAPI.setBackgroundColor(Color::OCEAN);

  //ResoureManager::instancePtr()->loadTexture(Path("textures/wall.jpg"));

  m_actualScene = newSPtr<Scene>();

  m_actualScene->m_root = newSPtr<Actor>();

  m_selectedActor = m_actualScene->m_root;

  m_globalTransformBuffer = graphicAPI.createBuffer();
  m_globalTransformBuffer->init(sizeof(Matrix4f));

  m_viewBuffer = graphicAPI.createBuffer();
  m_viewBuffer->init(sizeof(Matrix4f));

  m_projectionBuffer = graphicAPI.createBuffer();
  m_projectionBuffer->init(sizeof(Matrix4f));
}


void 
TestApp::postUpdate(float delta)
{ 
  auto& inputManager = InputManager::instance();
  if (inputManager.getInput(VK_RBUTTON))
  {
    m_camera->rotateWithMouse(inputManager.getMouseDelta());
  }

  m_camera->update();
}

void 
TestApp::draw()
{
  auto& graphicsAPI = GraphicAPI::instance();

  graphicsAPI.setRenderTargetAndDepthStencil(m_finalRender,m_finalDepthStencil);


  graphicsAPI.clearRenderTarget(m_finalRender);
  graphicsAPI.clearDepthStencil(m_finalDepthStencil);

  
  m_viewBuffer->write(&m_camera->getViewMatrix().m11);
  graphicsAPI.setVSBuffer(m_viewBuffer,1);

  m_projectionBuffer->write(&m_camera->getProjectionMatrix().m11);
  graphicsAPI.setVSBuffer(m_projectionBuffer,2);
   
  graphicsAPI.setSamplerState(m_samplerState);
  
  //m_camera->setCamera();

  Vector<SPtr<Actor>> seenActors;
  m_camera->seeActors(m_actualScene->m_root,seenActors);

  lights->write(&dir.x);
  graphicsAPI.setVSBuffer(lights,3);
  graphicsAPI.setPSBuffer(lights,0);

  m_viewLocationBuffer->write(&m_camera->getLocation().x);
  graphicsAPI.setVSBuffer(m_viewLocationBuffer,4);

  Matrix4f finalTransform;

  Matrix4f globalActorTransform;

  for(auto Actor : seenActors){
    
    globalActorTransform = Actor->getGlobalTransform();

    for(auto& modelPair : Actor->getComponent<GraphicsComponent>()->m_models){

      auto& model = modelPair.second.model;

      for(uint32 i = 0;i<model->m_meshes.size();++i){
      
        if(model->m_materials.size()>i && model->m_materials[i]){
          model->m_materials[i]->set();
        }

        finalTransform = globalActorTransform * modelPair.second.getFinalTransform();

        m_globalTransformBuffer->write(&finalTransform);

        graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

        auto& actualMesh = model->m_meshes[i];

        actualMesh->set();
       
        graphicsAPI.draw(actualMesh->getIndexNum());
      }
    }
  }
   
  newImGuiFrame();
  drawImGui();
  renderImGui();

}

void 
TestApp::initImGui()
{
  auto& api = GraphicAPI::instance();
  if (api.m_actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
  }
  
  if (api.m_actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplWin32_Init(api.getWindow());
    ImGui_ImplDX11_Init(
      (ID3D11Device*)api.getDevice(), 
      (ID3D11DeviceContext*)api.getContext());
  }
  if (api.m_actualGraphicAPI == GRAPHIC_API::OPENGL) {
    //ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)api.getWindow(), true);
    //ImGui_ImplOpenGL3_Init("#version 130");
  }
  

}

void 
TestApp::newImGuiFrame()
{
  auto& api = GraphicAPI::instance();
  if (api.m_actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
  }

  if (api.m_actualGraphicAPI == GRAPHIC_API::OPENGL) {
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
  }
  
  if (api.m_actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::NewFrame();
  }
  
}

void TestApp::renderImGui()
{
  auto& api = GraphicAPI::instance();
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize.x = static_cast<float>(api.m_windowWidth);
  io.DisplaySize.y = static_cast<float>(api.m_windowHeight);
  
  if (api.m_actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::Render();
  }

  if (api.m_actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

  if (api.m_actualGraphicAPI == GRAPHIC_API::OPENGL) {
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

}

void oaEngineSDK::TestApp::drawImGui()
{
  auto& resourceManager = ResoureManager::instance();
  /*if (api.actualGraphicAPI == GRAPHIC_API::NONE) {
    return;
  }
  ImGui::Begin("Actors");
  if(ImGui::Button("character")){
    actualActor = character;
  }
  if(ImGui::Button("test Actor")){
    actualActor = testActor;
  }
  ImGui::End();
  */

  ImGui::Begin("Actor atributes");
  if(m_selectedActor){
    if(ImGui::Button("Add Component")){
      isAddingComponent = true;
    }

    if (ImGui::CollapsingHeader("transform")){
      
      if(m_selectedActor.get()){
        auto& transform = m_selectedActor->GetActorTransform();
        Vector3f vec = transform.getLocation();
        if(ImGui::DragFloat3("location", &vec.x, .01f)){
          transform.setLocation(vec);
        }
        vec = transform.getScale();
        if(ImGui::DragFloat3("scale", &vec.x, .01f)){
          transform.setScale(vec);
        }
        vec = transform.getRotation();
        if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
          transform.setRotation(vec);
        };
      }
    }

    SPtr<Component> component;
    component = m_selectedActor->getComponent<GraphicsComponent>();
    if (component && ImGui::CollapsingHeader("models")){
      
      if(ImGui::Button("select model") && m_selectedModel.get()){
        cast<GraphicsComponent>(component)->addModel(m_selectedModel);
      }
      for(auto& model : cast<GraphicsComponent>(component)->m_models){
        if(ImGui::Button(model.second.model->m_name.c_str())){
          m_selectedModelComponent = &model.second;
        }
      }
      if(m_selectedModelComponent){
        ImGui::DragFloat3("location Model",&m_selectedModelComponent->location.x);
        ImGui::DragFloat3("scale Model",&m_selectedModelComponent->scale.x);
        ImGui::DragFloat3("rotation Model",&m_selectedModelComponent->rotation.x);
      }

    }

    component = m_selectedActor->getComponent<SkeletalComponent>();

    if (component && ImGui::CollapsingHeader("skeleton")){
      
      if(ImGui::Button("select Skeleton")){
        cast<SkeletalComponent>(component)->m_skeleton = m_selectedSkeleton;
      }
      if(cast<SkeletalComponent>(component)->m_skeleton){
        if(ImGui::Button("add socket")){
          isAddingSocket = true;
        }
      }

    }

    component = m_selectedActor->getComponent<AnimationComponent>();


    if (component && ImGui::CollapsingHeader("animation")){
      auto animComponent = cast<AnimationComponent>(component);
      if(ImGui::Button("select Animation")){
        animComponent->m_animation = m_selectedAnimation;
        animComponent->m_model = m_selectedModel;
        animComponent->m_skeleton = m_selectedSkeleton;
      }
      if(animComponent->m_animation){
        ImGui::DragFloat("m_selectedTime",&animComponent->m_animTimeInSecs);
      }
      ImGui::Checkbox("play",&animInPlay);
      if(animInPlay){
        animComponent->m_animTimeInSecs += Time::instance().getDelta();
      }
    }

  }
  ImGui::End();

  ImGui::Begin("resources");
  
  if (ImGui::CollapsingHeader("textures")){
    if(ImGui::Button("load Texture")){
      Path path;
      if(path.searchForPath()){
        loader = new Loader;
        loader->loadTexture(path);
        //loadflags = loader->checkForLoad(path);
        delete loader;
        loader = 0;
      }
    }
    for(auto texture : resourceManager.m_textures){
      if(ImGui::ImageButton(texture.second->getId(),ImVec2(100,100))){
        m_selectedTexture = texture.second;
      }
    }
  }
  
  if (ImGui::CollapsingHeader("materials")){
    for(auto material : resourceManager.m_materials){
      if(ImGui::Button(material.first.c_str(),ImVec2(100,100))){
        m_selectedMaterial = material.second;
      }
    }
  }

  if (ImGui::CollapsingHeader("meshes")){
    for(auto mesh : resourceManager.m_meshes){
      if(ImGui::Button(mesh.first.c_str(),ImVec2(100,100))){
        m_selectedMesh = mesh.second;
      }
    }
  }
  
  if (ImGui::CollapsingHeader("models")){
    if(ImGui::Button("Load From File")){
      Path path;
      if(path.searchForPath()){
        loader = new Loader;
        loader->checkForLoad(path);
        //loadflags = loader->checkForLoad(path);
        delete loader;
        loader = 0;
      }
    }

    for(auto model : resourceManager.m_models){
      if(ImGui::Button(model.second->m_name.c_str(),ImVec2(100,100))){
        m_selectedModel = model.second;
      }
    }
  }

  if (ImGui::CollapsingHeader("skeletons")){
    for(auto skeleton : resourceManager.m_skeletons){
      if(ImGui::Button(skeleton.second->m_name.c_str(),ImVec2(100,100))){
        print("working");
        m_selectedSkeleton = skeleton.second;
      }
    }
  }

  if (ImGui::CollapsingHeader("animations")){
    for(auto animation : resourceManager.m_animations){
      if(ImGui::Button(animation.second->m_name.c_str(),ImVec2(100,100))){
        m_selectedAnimation = animation.second;
      }
    }
  }

  ImGui::End();

  ImGui::Begin("Actors");
  if(ImGui::Button("new Actor")){
    isCreatingActor = true;
  }
  if(ImGui::Button("scene")){
    m_selectedActor = m_actualScene->m_root;
  }
  childsInImgui(m_actualScene->m_root);
  ImGui::End();

  ImGui::Begin("lights");
  ImGui::DragFloat3("direction",&dir.x,.01f,-1.0f,1.0f);
  ImGui::DragFloat("paralax",&dir.w,1.0f);
  ImGui::End();

  if(isCreatingActor){
    ImGui::Begin("new Actor");
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("create")){
      auto actor = newSPtr<Actor>();
      actor->m_name = imguiString;
      m_selectedActor->attach(actor);
      isCreatingActor = false;
    }
    ImGui::End();
  }

  if(isAddingComponent){
    ImGui::Begin("add component");
    if(ImGui::Button("Graphics")){
      m_selectedActor->attachComponent(newSPtr<GraphicsComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Skeletal")){
      m_selectedActor->attachComponent(newSPtr<SkeletalComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Animation")){
      m_selectedActor->attachComponent(newSPtr<AnimationComponent>());
      isAddingComponent = false;
    }

    ImGui::End();
  }

  if(loader){
    ImGui::Begin("load");
    if(loadflags & LOADERFLAGS::kMesh){
      ImGui::CheckboxFlags("mesh",&loadflags0,LOADERFLAGS::kMesh);
    }
    if(loadflags & LOADERFLAGS::kTexture){
      ImGui::CheckboxFlags("texture",&loadflags0,LOADERFLAGS::kTexture);
    }
    if(loadflags & LOADERFLAGS::kSkeleton){
      ImGui::CheckboxFlags("skeleton",&loadflags0,LOADERFLAGS::kSkeleton);
    }
    if(loadflags & LOADERFLAGS::kAnimation){
      ImGui::CheckboxFlags("animation",&loadflags0,LOADERFLAGS::kAnimation);
    }
    if(ImGui::Button("OK")){
      if(loadflags0 & LOADERFLAGS::kMesh){
        ImGui::CheckboxFlags("mesh",&loadflags0,LOADERFLAGS::kMesh);
      }
      if(loadflags0 & LOADERFLAGS::kTexture){
        ImGui::CheckboxFlags("texture",&loadflags0,LOADERFLAGS::kTexture);
      }
      if(loadflags0 & LOADERFLAGS::kSkeleton){
        ImGui::CheckboxFlags("skeleton",&loadflags0,LOADERFLAGS::kSkeleton);
      }
      if(loadflags0 & LOADERFLAGS::kAnimation){
        ImGui::CheckboxFlags("animation",&loadflags0,LOADERFLAGS::kAnimation);
      }
      loader->load(static_cast<LOADERFLAGS::E>(loadflags0));
      delete loader;
      loader = nullptr;
    }
    
    ImGui::End();
  }

  if(isAddingSocket){
    ImGui::InputText("bone name",imguiString,64);
    if(ImGui::Button("ok")){
      m_selectedActor->getComponent<SkeletalComponent>()->attachToBone(m_selectedModel,imguiString);
      isAddingSocket = false;
    }
  }

  ImGui::Begin("file");
  if(ImGui::Button("save all")){
    Serializer serializer;
    Path path;
    if(path.searchForPath()){
      serializer.init(path);
      for(auto& model: ResoureManager::instance().m_models){
        serializer.encodeModel(model.second);
      }
      
    }
  }
  ImGui::End();

  ImGui::Begin("material editor");
  if(m_selectedMaterial){
    if(ImGui::Button("select difusse")){
      m_selectedMaterial->m_diffuse = m_selectedTexture;
    }

    if(ImGui::Button("select normal map")){
      m_selectedMaterial->m_normalMap = m_selectedTexture;
    }

    if(ImGui::Button("select specular")){
      m_selectedMaterial->m_specular = m_selectedTexture;
    }

    if(ImGui::Button("select depth map")){
      m_selectedMaterial->m_depthMap = m_selectedTexture;
    }
  }
  ImGui::End();

  ImGui::Begin("Model Editor");
  if(m_selectedModel){
    if(ImGui::Button("select material")){
      m_selectedModel->addMaterial(m_selectedMaterial);
    }
  }
  ImGui::End();

  
}

void oaEngineSDK::TestApp::childsInImgui(SPtr<Actor> parentActor)
{
  auto& childs = parentActor->getChilds();
  for(SPtr<Actor> Actor : childs){
    if(ImGui::Button(Actor->m_name.c_str())){
      m_selectedActor = Actor;
    }
    if(Actor->getChilds().size()>0){
      if(ImGui::CollapsingHeader("childs")){
        childsInImgui(Actor);
      }
    }
  }
}

SubMesh
oaEngineSDK::TestApp::tetrahedron()
{
  SubMesh ans;
  float sq2 = Math::sqrt(2.0f);
  float sq3 = Math::sqrt(3.0f);
  ans.points = {
    {0.0f,0.0f,1.0f,0.0f},
    {2.0f*sq2/3.0f,0.0f,-1.0f/3.0f,0.0f},
    {-sq2/3.0f,sq2/sq3,-1.0f/3.0f,0.0f},
    {-sq2/3.0f,-sq2/sq3,-1.0f/3.0f,0.0f},
  };

  ans.indices = {0,1,2,0,2,3,0,3,1,1,3,2};

  return ans;
}

SubMesh
oaEngineSDK::TestApp::octahedron()
{
  SubMesh ans;
  ans.points = {
    {0.0f,0.0f, 1.0f,0.0f},
    {0.0f,0.0f,-1.0f,0.0f},
    {0.0f, 1.0f,0.0f,0.0f},
    {0.0f,-1.0f,0.0f,0.0f},
    { 1.0f,0.0f,0.0f,0.0f},
    {-1.0f,0.0f,0.0f,0.0f},
  };
  ans.indices = {0,4,2,0,3,4,0,5,3,0,2,5,1,2,4,1,4,3,1,3,5,1,5,2};

  return ans;
}

SubMesh
oaEngineSDK::TestApp::icosahedron()
{
  float phi = (Math::sqrt(5)+1.0f)/2.0f;
  Vector2f v{1.0f,phi};
  v.normalize();

  SubMesh ans;

  ans.points = {
    {-v.x, v.y,0.0f,0.0f},
    { v.x, v.y,0.0f,0.0f},
    {-v.x,-v.y,0.0f,0.0f},
    { v.x,-v.y,0.0f,0.0f},

    {0.0f,-v.x, v.y,0.0f},
    {0.0f, v.x, v.y,0.0f},
    {0.0f,-v.x,-v.y,0.0f},
    {0.0f, v.x,-v.y,0.0f},
    
    { v.y,0.0f,-v.x,0.0f},
    { v.y,0.0f, v.x,0.0f},
    {-v.y,0.0f,-v.x,0.0f},
    {-v.y,0.0f, v.x,0.0f},
    
  };

  ans.indices = {0,11,5,0,5,1,0,1,7,0,7,10,0,10,11,1,5,9,5,11,4,11,10,2,10,7,6,
                 7,1,8,3,9,4,3,4,2,3,2,6,3,6,8,3,8,9,4,9,5,2,4,11,6,2,10,8,6,7,
                 9,8,1};

  return ans;
}

SubMesh 
oaEngineSDK::TestApp::SubDivide(const SubMesh& data)
{
  uint32 size = static_cast<uint32>(data.indices.size());

  SubMesh ans;

  for(uint32 i = 0; i < size; i+=3){
    Vector3f oldPoints[3]={
      data.points[data.indices[i]].xyz,
      data.points[data.indices[i+1]].xyz,
      data.points[data.indices[i+2]].xyz,
    };
    Vector3f newPoints[3]={
    Vector3f::interpolate(oldPoints[1],oldPoints[2],.5f).normalized(),
    Vector3f::interpolate(oldPoints[0],oldPoints[2],.5f).normalized(),
    Vector3f::interpolate(oldPoints[0],oldPoints[1],.5f).normalized()
    };

    uint32 actual = static_cast<uint32>(ans.points.size());

    ans.points.push_back(Vector4f(oldPoints[0],0.0f));
    ans.points.push_back(Vector4f(oldPoints[1],0.0f));
    ans.points.push_back(Vector4f(oldPoints[2],0.0f));
    ans.points.push_back(Vector4f(newPoints[0],0.0f));
    ans.points.push_back(Vector4f(newPoints[1],0.0f));
    ans.points.push_back(Vector4f(newPoints[2],0.0f));

    

    ans.indices.push_back(actual);
    ans.indices.push_back(actual+5);
    ans.indices.push_back(actual+4);

    ans.indices.push_back(actual+1);
    ans.indices.push_back(actual+3);
    ans.indices.push_back(actual+5);

    ans.indices.push_back(actual+2);
    ans.indices.push_back(actual+4);
    ans.indices.push_back(actual+3);

    ans.indices.push_back(actual+3);
    ans.indices.push_back(actual+4);
    ans.indices.push_back(actual+5);

  }
  return ans;
}

}




