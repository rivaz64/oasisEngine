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
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>



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
  
  InputManager::instancePtr()->addInput('W');
  InputManager::instancePtr()->addInput('S');
  InputManager::instancePtr()->addInput('A');
  InputManager::instancePtr()->addInput('D');
  InputManager::instancePtr()->addInput('E');
  InputManager::instancePtr()->addInput('Q');
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

  auto& api = GraphicAPI::instance();
  
  samsta = api.createSamplerState(sampDesc);

  vertexShader = api.createVertexShader();

  pixelShader = api.createPixelShader();

  lights = api.createBuffer();

  lights->init(sizeof(Vector4f));

  IMGUI_CHECKVERSION();

  initImGui();

  api.setBackgroundColor(Color::OCEAN);

  //ResoureManager::instancePtr()->loadTexture(Path("textures/wall.jpg"));

  m_actualScene = newSPtr<Actor>();

  actualActor = m_actualScene;

  cam = newSPtr<Camera>();

  cam->m_angle = 0.785398163f;
  cam->m_ratio = (float)api.m_windowWidth / (float)api.m_windowHeight;
  cam->m_nearPlane = 1.0f;
  cam->m_farPlane = 100.0f;

  cam->updateView();

  cam->updateProyection();

  
}


void 
TestApp::postUpdate(float delta)
{

  Vector3f camdelta = {0.0f,0.0f,0.0f};

  if (InputManager::instancePtr()->getInput('A'))
  {
    camdelta.x = -delta;
  }
  if (InputManager::instancePtr()->getInput('D'))
  {
    camdelta.x = delta;
  }
  if (InputManager::instancePtr()->getInput('W'))
  {
    camdelta.z = delta;
  }
  if (InputManager::instancePtr()->getInput('S'))
  {
    camdelta.z = -delta;
  }
  if (InputManager::instancePtr()->getInput('Q'))
  {
    camdelta.y = delta;
  }
  if (InputManager::instancePtr()->getInput('E'))
  {
    camdelta.y = -delta;
  }
  if (InputManager::instancePtr()->getInput(VK_RBUTTON) && 
      InputManager::instancePtr()->getMouseDelta() != Vector2I::ZERO)
  {
    cam->rotateWithMouse(InputManager::instancePtr()->getMouseDelta());
  }
  else{
    mousePressed;
  }

  if(camdelta.magnitud()>0){
    cam->moveCamera(camdelta);
  }

  cam->updateView();

  //character->update();

  //lights->update(&color.x);
}

void 
TestApp::draw()
{
  auto& api = GraphicAPI::instance();

  api.setRenderTargetAndDepthStencil(m_finalRender,m_finalDepthStencil);


  api.clearRenderTarget(m_finalRender);
  api.clearDepthStencil(m_finalDepthStencil);

   

  api.setSamplerState(samsta);
  
  cam->setCamera();

  Vector<SPtr<Actor>> seenActors;
  cam->seeActors(m_actualScene,seenActors);

  lights->update(&dir.x);
  api.setPSBuffer(lights,0);

  for(auto Actor : seenActors){
    
    auto mat = Actor->getGlobalTransform();

    for(auto& modelPair : Actor->getComponent<GraphicsComponent>()->m_models){
      auto model = modelPair.second.model;
      for(uint32 i = 0;i<model->m_meshes.size();++i){
      
        if(model->m_materials.size()>i && model->m_materials[i]){
          model->m_materials[i]->set();
        }

        auto finalMat = mat * modelPair.second.getFinalTransform();

        Actor->m_transformB->update(&finalMat);

        api.setVSBuffer(Actor->m_transformB, 0);

        auto actualMesh = model->m_meshes[i];

        actualMesh->set();

        if(actualMesh->m_hasBones){

          actualMesh->m_bonesB->update(actualMesh->m_ofset.data());

          api.setVSBuffer( actualMesh->m_bonesB,3);
        }
       
        api.draw(static_cast<uint32>(actualMesh->m_indexNumber));
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
  if(actualActor){
    if(ImGui::Button("Add Component")){
      isAddingComponent = true;
    }

    if (ImGui::CollapsingHeader("transform")){
      
      if(actualActor.get()){
        Vector3f vec = actualActor->getLocation();
        if(ImGui::DragFloat3("location", &vec.x, .01f)){
          actualActor->setLocation(vec);
        }
        vec = actualActor->getScale();
        if(ImGui::DragFloat3("scale", &vec.x, .01f)){
          actualActor->setScale(vec);
        }
        vec = actualActor->getRotation();
        if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
          actualActor->setRotation(vec);
        };
      }
    }

    SPtr<Component> component;
    component = actualActor->getComponent<GraphicsComponent>();
    if (component && ImGui::CollapsingHeader("models")){
      
      if(ImGui::Button("select model") && actualModel.get()){
        cast<GraphicsComponent>(component)->addModel(actualModel);
      }
      for(auto& model : cast<GraphicsComponent>(component)->m_models){
        if(ImGui::Button(model.second.model->m_name.c_str())){
          actualModelComponent = &model.second;
        }
      }
      if(actualModelComponent){
        ImGui::DragFloat3("location Model",&actualModelComponent->location.x);
        ImGui::DragFloat3("scale Model",&actualModelComponent->scale.x);
        ImGui::DragFloat3("rotation Model",&actualModelComponent->rotation.x);
      }

    }

    component = actualActor->getComponent<SkeletalComponent>();

    if (component && ImGui::CollapsingHeader("skeleton")){
      
      if(ImGui::Button("select Skeleton")){
        cast<SkeletalComponent>(component)->m_skeleton = actualSkeleton;
      }
      if(cast<SkeletalComponent>(component)->m_skeleton){
        if(ImGui::Button("add socket")){
          isAddingSocket = true;
        }
      }

    }

    component = actualActor->getComponent<AnimationComponent>();


    if (component && ImGui::CollapsingHeader("animation")){
      auto animComponent = cast<AnimationComponent>(component);
      if(ImGui::Button("select Animation")){
        animComponent->m_animation = actualAnimation;
        animComponent->m_model = actualModel;
        animComponent->m_skeleton = actualSkeleton;
      }
      if(animComponent->m_animation){
        ImGui::DragFloat("actualTime",&animComponent->m_animTimeInSecs);
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
    for(auto texture : resourceManager.textures){
      if(ImGui::ImageButton(texture.second->getId(),ImVec2(100,100))){
        actualTexture = texture.second;
      }
    }
  }
  
  if (ImGui::CollapsingHeader("materials")){
    for(auto material : resourceManager.materials){
      if(ImGui::Button(material.first.c_str(),ImVec2(100,100))){
        material.second->m_textures[0] = actualTexture;
      }
    }
  }

  if (ImGui::CollapsingHeader("meshes")){
    for(auto mesh : resourceManager.meshes){
      if(ImGui::Button(mesh.first.c_str(),ImVec2(100,100))){
        actualMesh = mesh.second;
      }
    }
  }
  
  if (ImGui::CollapsingHeader("models")){
    if(ImGui::Button("Load From File")){
      Path path;
      if(path.searchForPath()){
        loader = new Loader;
        loadflags = loader->checkForLoad(path);
        loadflags0 = 0;
      }
    }

    for(auto model : resourceManager.models){
      if(ImGui::Button(model.second->m_name.c_str(),ImVec2(100,100))){
        actualModel = model.second;
      }
    }
  }

  if (ImGui::CollapsingHeader("skeletons")){
    for(auto skeleton : resourceManager.skeletons){
      if(ImGui::Button(skeleton.second->m_name.c_str(),ImVec2(100,100))){
        print("working");
        actualSkeleton = skeleton.second;
      }
    }
  }

  if (ImGui::CollapsingHeader("animations")){
    for(auto animation : resourceManager.animations){
      if(ImGui::Button(animation.second->m_name.c_str(),ImVec2(100,100))){
        actualAnimation = animation.second;
      }
    }
  }


  ImGui::End();

  
  

  ImGui::Begin("Actors");
  if(ImGui::Button("new Actor")){
    isCreatingActor = true;
  }
  if(ImGui::Button("scene")){
    actualActor = m_actualScene;
  }
  childsInImgui(m_actualScene);
  ImGui::End();

  ImGui::Begin("lighs");
  ImGui::DragFloat3("direction",&dir.x,.01f,-1.0f,1.0f);
  ImGui::End();

  if(isCreatingActor){
    ImGui::Begin("new Actor");
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("create")){
      auto actor = newSPtr<Actor>();
      actor->m_name = imguiString;
      actualActor->attach(actor);
      isCreatingActor = false;
    }
    ImGui::End();
  }

  if(isAddingComponent){
    ImGui::Begin("add component");
    if(ImGui::Button("Graphics")){
      actualActor->attachComponent(newSPtr<GraphicsComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Skeletal")){
      actualActor->attachComponent(newSPtr<SkeletalComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Animation")){
      actualActor->attachComponent(newSPtr<AnimationComponent>());
      isAddingComponent = false;
    }

    ImGui::End();
  }

  if(loader){
    ImGui::Begin("load");
    ImGui::DragFloat("scale",&loader->m_importScale);
    if(loadflags & LOADERFLAGS::MESH){
      ImGui::CheckboxFlags("mesh",&loadflags0,LOADERFLAGS::MESH);
    }
    if(loadflags & LOADERFLAGS::TEXTURE){
      ImGui::CheckboxFlags("texture",&loadflags0,LOADERFLAGS::TEXTURE);
    }
    if(loadflags & LOADERFLAGS::SKELETON){
      ImGui::CheckboxFlags("skeleton",&loadflags0,LOADERFLAGS::SKELETON);
    }
    if(loadflags & LOADERFLAGS::ANIMATION){
      ImGui::CheckboxFlags("animation",&loadflags0,LOADERFLAGS::ANIMATION);
    }
    if(ImGui::Button("OK")){
      if(loadflags0 & LOADERFLAGS::MESH){
        ImGui::CheckboxFlags("mesh",&loadflags0,LOADERFLAGS::MESH);
      }
      if(loadflags0 & LOADERFLAGS::TEXTURE){
        ImGui::CheckboxFlags("texture",&loadflags0,LOADERFLAGS::TEXTURE);
      }
      if(loadflags0 & LOADERFLAGS::SKELETON){
        ImGui::CheckboxFlags("skeleton",&loadflags0,LOADERFLAGS::SKELETON);
      }
      if(loadflags0 & LOADERFLAGS::ANIMATION){
        ImGui::CheckboxFlags("animation",&loadflags0,LOADERFLAGS::ANIMATION);
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
      actualActor->getComponent<SkeletalComponent>()->attachToBone(actualModel,imguiString);
      isAddingSocket = false;
    }
  }

}

void oaEngineSDK::TestApp::childsInImgui(SPtr<Actor> parentActor)
{
  auto& childs = parentActor->getChilds();
  for(SPtr<Actor> Actor : childs){
    if(ImGui::Button(Actor->m_name.c_str())){
      actualActor = Actor;
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




