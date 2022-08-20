#include "TestApp.h"
#include <oaVector3f.h>
#include <oaGraphicAPI.h>
#include <oaModel.h>
#include <oaSamplerState.h>
#include <oaShader.h>
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
#include <oaSkeleton.h>
#include <oaAnimation.h>
#include <oaVertexBuffer.h>
#include <oaIndexBuffer.h>
#include <oaBuffer.h>
#include <oaActor.h>
#include <oaTime.h>
#include <oaLogger.h>
#include <oaShaderProgram.h>
#include <oaResoureManager.h>
#include <oaScene.h>
#include <oaRasterizerState.h>
#include <oaRenderer.h>
#include <oaCameraComponent.h>
#include <oaInputAPI.h>
#include <oaKeyboard.h>
#include <oaMouse.h>
#include <oaAudioAPI.h>
#include <oaSound.h>
#include <oaEventSystem.h>
#include <oaTransform.h>
#include <oaMesh.h>
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <oaSerializer.h>
#include "ImGuiFileDialog.h"
extern "C" {
#include <lua\lua.h>
#include <lua\lualib.h>
#include <lua/lauxlib.h>
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace oaEngineSDK {

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;

  BaseApp* app = reinterpret_cast<BaseApp*>(GetWindowLongPtr(hWnd, 0));

  if(ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;

  app->processInputs({hWnd,message,wParam,lParam});

  switch( message )
  {
  case WM_PAINT:
    hdc = BeginPaint( hWnd, &ps );
    EndPaint( hWnd, &ps );
    break;

  case WM_QUIT:
    app->m_isRunning = false;
    break;

  case WM_DESTROY:
    app->m_isRunning = false;
    PostQuitMessage( 0 );
    break;

  case WM_SIZE:
    app->resizeWindow();
    break;
  

  case WM_KEYDOWN:
   
    break;
    
  //case WM_NCCREATE:
    
    //break;

  default:
    
    return DefWindowProc( hWnd, message, wParam, lParam );
  }

  return 0;
}

void
TestApp::genMorbiusTrip(){
  auto& grapgicApi = GraphicAPI::instance();
  m_morbiusTrip = makeSPtr<StaticMesh>();
  m_morbModel = makeSPtr<Model>();
  m_morbComponent = makeSPtr<GraphicsComponent>();
  m_morbActor = makeSPtr<Actor>();
  m_morbComponent->setModel(m_morbModel);
  m_morbActor->attachComponent(m_morbComponent);
  m_morbActor->GetActorTransform().setScale({1.f,1.f,1.f});
  
  m_morbModel->addMesh(m_morbiusTrip);
  m_morbiusTrip->setControlPoints({
	{ 1.0f, -0.5f, 0.0f, 0.0f },
	{ 1.0f, -0.5f, 0.5f, 0.0f },
	{ 0.5f, -0.3536f, 1.354f, 0.0f },
	{ 0.0f, -0.3536f, 1.354f, 0.0f },
	{ 1.0f, -0.1667f, 0.0f, 0.0f },
	{ 1.0f, -0.1667f, 0.5f, 0.0f },
	{ 0.5f, -0.1179f, 1.118f, 0.0f },
	{ 0.0f, -0.1179f, 1.118f, 0.0f },
	{ 1.0f, 0.1667f, 0.0f, 0.0f },
	{ 1.0f, 0.1667f, 0.5f, 0.0f },
	{ 0.5f, 0.1179f, 0.8821f, 0.0f },
	{ 0.0f, 0.1179f, 0.8821f, 0.0f },
	{ 1.0f, 0.5f, 0.0f, 0.0f },
	{ 1.0f, 0.5f, 0.5f, 0.0f },
	{ 0.5f, 0.3536f, 0.6464f, 0.0f },
	{ 0.0f, 0.3536f, 0.6464f, 0.0f },
	{ 0.0f, -0.3536f, 1.354f, 0.0f },
	{ -0.5f, -0.3536f, 1.354f, 0.0f },
	{ -1.5f, 0.0f, 0.5f, 0.0f },
	{ -1.5f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, -0.1179f, 1.118f, 0.0f },
	{ -0.5f, -0.1179f, 1.118f , 0.0f},
	{ -1.167f, 0.0f, 0.5f , 0.0f},
	{ -1.167f, 0.0f, 0.0f , 0.0f},
	{ 0.0f, 0.1179f, 0.8821f , 0.0f},
	{ -0.5f, 0.1179f, 0.8821f , 0.0f},
	{ -0.8333f, 0.0f, 0.5f , 0.0f},
	{ -0.8333f, 0.0f, 0.0f , 0.0f},
	{ 0.0f, 0.3536f, 0.6464f , 0.0f},
	{ -0.5f, 0.3536f, 0.6464f , 0.0f},
	{ -0.5f, 0.0f, 0.5f , 0.0f},
	{ -0.5f, 0.0f, 0.0f , 0.0f},
	{ -1.5f, 0.0f, 0.0f , 0.0f},
	{ -1.5f, 0.0f, -0.5f , 0.0f},
	{ -0.5f, 0.3536f, -1.354f , 0.0f},
	{ 0.0f, 0.3536f, -1.354f , 0.0f},
	{ -1.167f, 0.0f, 0.0f , 0.0f},
	{ -1.167f, 0.0f, -0.5f , 0.0f},
	{ -0.5f, 0.1179f, -1.118f , 0.0f},
	{ 0.0f, 0.1179f, -1.118f , 0.0f},
	{ -0.8333f, 0.0f, 0.0f , 0.0f},
	{ -0.8333f, 0.0f, -0.5f , 0.0f},
	{ -0.5f, -0.1179f, -0.8821f , 0.0f},
	{ 0.0f, -0.1179f, -0.8821f , 0.0f},
	{ -0.5f, 0.0f, 0.0f , 0.0f},
	{ -0.5f, 0.0f, -0.5f , 0.0f},
	{ -0.5f, -0.3536f, -0.6464f , 0.0f},
	{ 0.0f, -0.3536f, -0.6464f , 0.0f},
	{ 0.0f, 0.3536f, -1.354f , 0.0f},
	{ 0.5f, 0.3536f, -1.354f , 0.0f},
	{ 1.0f, 0.5f, -0.5f , 0.0f},
	{ 1.0f, 0.5f, 0.0f , 0.0f},
	{ 0.0f, 0.1179f, -1.118f , 0.0f},
	{ 0.5f, 0.1179f, -1.118f , 0.0f},
	{ 1.0f, 0.1667f, -0.5f , 0.0f},
	{ 1.0f, 0.1667f, 0.0f , 0.0f},
	{ 0.0f, -0.1179f, -0.8821f , 0.0f},
	{ 0.5f, -0.1179f, -0.8821f , 0.0f},
	{ 1.0f, -0.1667f, -0.5f , 0.0f},
	{ 1.0f, -0.1667f, 0.0f , 0.0f},
	{ 0.0f, -0.3536f, -0.6464f , 0.0f},
	{ 0.5f, -0.3536f, -0.6464f , 0.0f},
	{ 1.0f, -0.5f, -0.5f , 0.0f},
	{ 1.0f, -0.5f, 0.0f , 0.0f},
});

  m_actualScene->getRoot()->attach(m_morbActor);
}

void 
TestApp::onDestroy()
{
  auto& api = GraphicAPI::instance();
  if (api.m_actualGraphicAPI == "DIRECTX11") {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
  }

  if (api.m_actualGraphicAPI == "OPENGL") {
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
  }

  ImGui::DestroyContext();
}

void
TestApp::onInit()
{
  auto& graphicsApi = GraphicAPI::instance();

  m_window = graphicsApi.createWindow(WindowProc,this,m_windowSize,m_windowName);
}

void 
TestApp::postInit()
{
  //SamplerDesc sampDesc;
  //ZeroMemory( &sampDesc, sizeof(sampDesc) );
  //sampDesc.filter = FILTER::kMinMagMipLinear;
  //sampDesc.addressU = TEXTURE_ADDRESS_MODE::kWrap;
  //sampDesc.addressV = TEXTURE_ADDRESS_MODE::kWrap;
  //sampDesc.addressW = TEXTURE_ADDRESS_MODE::kWrap;
  //sampDesc.comparison = COMPARISON_FUNC::kNever;
  //sampDesc.minLOD = 0.0f;
  //sampDesc.maxLOD = Math::MAX_FLOAT;

  auto& graphicAPI = GraphicAPI::instance();
  


  IMGUI_CHECKVERSION();

  initImGui();

  graphicAPI.setBackgroundColor(Color::OCEAN);

  //ResoureManager::instancePtr()->loadTexture(Path("textures/wall.jpg"));

  m_actualScene = makeSPtr<Scene>();

  m_actualScene->init();

  m_selectedActor = m_actualScene->getRoot();

  graphicAPI.initTest();

  graphicAPI.setPrimitiveTopology(oaEngineSDK::PRIMITIVE_TOPOLOGY::kTrianlgeList);
  m_ssaoConfig.x=.01f;
  m_ssaoConfig.y=0;
  m_ssaoConfig.z=1;

  auto& input = InputAPI::instance();
  m_keyboard = input.createDeviceKeyboard();
  m_mouse = input.createDeviceMouse();

  //auto& eventSystem = EventSystem::instance();
  handler.suscribe<Camera,&Camera::moveCamera>(m_camera.get());
  //m_lights.push_back(DirectionalLight());
  //m_lights[0].direction = {0,0,0,0};
  //m_lights[0].color = Color::WHITE;

  genMorbiusTrip();

}


void 
TestApp::onUpdate(float delta)
{ 
  auto& inputManager = InputAPI::instance();
  inputManager.update();

  if(m_mouse->isButtonDown(BUTTON::kRight)){
    auto axisX = m_mouse->getAxis(AXIS::kX);
    auto axisY = m_mouse->getAxis(AXIS::kY);
    auto mouseDelta = Vector2f(axisX,axisY).normalized()*6.f;
    m_camera->rotateWithMouse(mouseDelta);
  }

  //if(m_controlledActor){
  //  if (inputManager.(VK_RBUTTON))
  //  {
  //    m_controlledActor->getComponent<CameraComponent>()->
  //      getCamera()->rotateWithMouse(inputManager.getMouseDelta());
  //  }
  //}
  //else{
  //  if (inputManager.getInput(VK_RBUTTON))
  //  {
  //    m_camera->rotateWithMouse(inputManager.getMouseDelta());
  //  }
  //
  //  m_camera->update();
  //}
  if(m_keyboard->isKeyDown(KEY::kA)){
    m_camera->moveCamera(Vector3f(-m_secondPerFrame,0,0));
  }
  if(m_keyboard->isKeyDown(KEY::kD)){
    m_camera->moveCamera(Vector3f(m_secondPerFrame,0,0));
  }
  if(m_keyboard->isKeyDown(KEY::kW)){
    //m_camera->moveCamera(Vector3f(0,0,m_secondPerFrame));
    handler.publish(Vector3f(0,0,m_secondPerFrame));
  }
  if(m_keyboard->isKeyDown(KEY::kS)){
    m_camera->moveCamera(Vector3f(0,0,-m_secondPerFrame));
  }
  if(m_keyboard->isKeyDown(KEY::kQ)){
    m_camera->moveCamera(Vector3f(0,m_secondPerFrame,0));
  }
  if(m_keyboard->isKeyDown(KEY::kE)){
    m_camera->moveCamera(Vector3f(0,-m_secondPerFrame,0));
  }
  //if(!m_controlledActor){
  //  switch (input)
  //  {
  //  case 'A':
  //    m_camera->moveCamera(Vector3f(-m_secondPerFrame,0,0));
  //    break;
  //
  //  case 'D':
  //    m_camera->moveCamera(Vector3f(m_secondPerFrame,0,0));
  //    break;
  //
  //  case 'W':
  //    m_camera->moveCamera(Vector3f(0,0,m_secondPerFrame));
  //    break;
  //
  //  case 'S':
  //    m_camera->moveCamera(Vector3f(0,0,-m_secondPerFrame));
  //    break;
  //
  //  case 'Q':
  //    m_camera->moveCamera(Vector3f(0,m_secondPerFrame,0));
  //    break;
  //
  //  case 'E':
  //    m_camera->moveCamera(Vector3f(0,-m_secondPerFrame,0));
  //    break;
  //
  //  default:
  //    break;
  //  }
  //}
  //else{
  //  switch (input)
  //  {
  //  case 'A':
  //    m_controlledActor->GetActorTransform().move(Vector3f(-m_secondPerFrame,0,0));
  //    break;
  //
  //  case 'D':
  //    m_controlledActor->GetActorTransform().move(Vector3f(m_secondPerFrame,0,0));
  //    break;
  //
  //  case 'W':
  //    m_controlledActor->GetActorTransform().move(Vector3f(0,0,m_secondPerFrame));
  //    break;
  //
  //  case 'S':
  //    m_controlledActor->GetActorTransform().move(Vector3f(0,0,-m_secondPerFrame));
  //    break;
  //
  //  case 'Q':
  //    m_controlledActor->GetActorTransform().move(Vector3f(0,m_secondPerFrame,0));
  //    break;
  //
  //  case 'E':
  //    m_controlledActor->GetActorTransform().move(Vector3f(0,-m_secondPerFrame,0));
  //    break;
  //
  //  default:
  //    break;
  //  }
  //}
  m_camera->update();
}

void 
TestApp::draw()
{
  auto& graphicsAPI = GraphicAPI::instance();

  auto& resourseManager = ResoureManager::instance();
   
  //
  ////m_camera->setCamera();
  //
  //lights->write(&dir.x);
  //graphicsAPI.setVSBuffer(lights,3);
  //graphicsAPI.setPSBuffer(lights,0);

  auto& renderer = Renderer::instance();

  //graphicsAPI.renderTest();

  //if(m_controlledActor){
  //  renderer.render(m_actualScene,m_controlledActor->getComponent<CameraComponent>()->getCamera(),m_controlledActor->getComponent<CameraComponent>()->getCamera());
  //}
  //else if(m_debugCamera){
  //  renderer.render(m_actualScene,m_camera,m_debugCamera);
  //}
  //else{
    renderer.render(m_actualScene,m_camera,m_camera,m_directionalLights,m_pointLights,m_spotLights,m_ssaoConfig);
  //}
  
  newImGuiFrame();
  drawImGui();
  renderImGui();

}

void 
TestApp::initImGui()
{
  auto& api = GraphicAPI::instance();
  if (!api.m_actualGraphicAPI.empty()) {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
  }
  
  if (api.m_actualGraphicAPI == "DIRECTX11") {
    ImGui_ImplWin32_Init(m_window);
    ImGui_ImplDX11_Init(
      (ID3D11Device*)api.getDevice(), 
      (ID3D11DeviceContext*)api.getContext());
  }
  if (api.m_actualGraphicAPI == "OPENGL") {
    //ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)api.getWindow(), true);
    //ImGui_ImplOpenGL3_Init("#version 130");
  }
  

}

void 
TestApp::newImGuiFrame()
{
  auto& api = GraphicAPI::instance();
  if (api.m_actualGraphicAPI =="DIRECTX11") {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
  }

  if (api.m_actualGraphicAPI == "OPENGL") {
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
  }
  
  if (!api.m_actualGraphicAPI.empty()) {
    ImGui::NewFrame();
  }
  
}

void TestApp::renderImGui()
{
  auto& api = GraphicAPI::instance();
  //ImGuiIO& io = ImGui::GetIO();
  //io.DisplaySize.x = static_cast<float>(api.m_windowWidth);
  //io.DisplaySize.y = static_cast<float>(api.m_windowHeight);
  
  if (!api.m_actualGraphicAPI.empty()) {
    ImGui::Render();
  }

  if (api.m_actualGraphicAPI =="DIRECTX11") {
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

  if (api.m_actualGraphicAPI == "OPENGL") {
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

}

void oaEngineSDK::TestApp::drawImGui()
{
  auto& resourceManager = ResoureManager::instance();
  auto& audioApi = AudioAPI::instance();
  auto& renderer = Renderer::instance();

  auto shadowMap = renderer.getShadowMap();
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
  ImGui::Begin("shaders");
  if(ImGui::Button("ReloadShaders")){
    resourceManager.loadDefaultShaders();
  }
  ImGui::End();

 

  ImGui::Begin("Actor atributes");
  if(!m_selectedActor.expired()){
    auto selectedActor = m_selectedActor.lock();
    if(ImGui::Button("Add Component")){
      isAddingComponent = true;
    }

    if (ImGui::CollapsingHeader("transform")){
      
      auto& transform = selectedActor->GetActorTransform();
      Vector3f vec = transform.getLocation();
      if(ImGui::DragFloat3("location", &vec.x, .01f)){
        transform.setLocation(vec);
      }
      vec = transform.getScale();
      if(ImGui::DragFloat3("scale", &vec.x, .01f)){
        transform.setScale(vec);
      }
      vec = transform.getRotation()*Math::RAD_TO_DEG;
      
      if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
        transform.setRotation(vec*Math::DEG_TO_RAD);
      };
    }

    WPtr<Component> wComponent;
    Vector<SPtr<Component>> components;
    components = selectedActor->getComponents<GraphicsComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("models"+StringUtilities::intToString(i)).c_str())){
          auto graphicsComponent = cast<GraphicsComponent>(components[i]);

          if(ImGui::Button("select model") && !m_selectedModel.expired()){
            graphicsComponent->setModel(m_selectedModel);
          }

          auto& wModel = graphicsComponent->getModel();
          if(!wModel.expired()){
            auto model = wModel.lock();
            ImGui::Text(model->getName().c_str());
            auto& transform = graphicsComponent->getTransform();
            ImGui::DragFloat3("location Model",&transform.getLocation().x);
            ImGui::DragFloat3("scale Model",&transform.getScale().x);
            auto vec = transform.getRotation()*Math::RAD_TO_DEG;
            if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
              transform.setRotation(vec*Math::DEG_TO_RAD);
            };
          }
        }
        
      }
      

    }

    wComponent = selectedActor->getComponent<SkeletalComponent>();
    
    if (!wComponent.expired() && ImGui::CollapsingHeader("skeleton")){
      auto component = wComponent.lock();
      if(ImGui::Button("select Skeleton")){
        cast<SkeletalComponent>(component)->setSkeleton(m_selectedSkeleton);

      }

      //if(cast<SkeletalComponent>(component)->m_skeleton){
      //  if(ImGui::Button("add socket")){
      //    isAddingSocket = true;
      //  }
      //}

    }

    wComponent = selectedActor->getComponent<AnimationComponent>();

    if (!wComponent.expired() && ImGui::CollapsingHeader("animation")){
      auto component = wComponent.lock();
      auto animComponent = cast<AnimationComponent>(component);
      //if(ImGui::Button("select Animation")){
      //  animComponent->m_animation = m_selectedAnimation;
      //  animComponent->m_model = m_selectedModel;
      //  animComponent->m_skeleton = m_selectedSkeleton;
      //}
      //if(animComponent->m_animation){
      //  ImGui::DragFloat("m_selectedTime",&animComponent->m_animTimeInSecs);
      //}
      //ImGui::Checkbox("play",&animInPlay);
      //if(animInPlay){
      //  animComponent->m_animTimeInSecs += Time::instance().getDelta();
      //}
    }

    wComponent = selectedActor->getComponent<CameraComponent>();

    if (!wComponent.expired() && ImGui::CollapsingHeader("camera")){
      auto component = wComponent.lock();
      auto cameraComponent = cast<CameraComponent>(component);
      //if(ImGui::Button("view from this") ){
      //
      //  if(m_controlledActor == selectedActor){
      //    m_controlledActor = SPtr<Actor>();
      //  }
      //  else{
      //    m_controlledActor = m_selectedActor;
      //  }
      //}

      ImGui::Checkbox("debug",&cameraComponent->m_debug);
      if(cameraComponent->m_debug){
        m_debugCamera = cameraComponent->getCamera();
      }
    }
  }
  ImGui::End();

  ImGui::Begin("resources");

  if (ImGui::Button("load resurse"))
    ImGuiFileDialog::Instance()->OpenDialog("Asset", "Choose File", ".png,.jpg,.hpp,.obj,.fbx,.wav", ".");

  if (ImGuiFileDialog::Instance()->Display("Asset")) 
  {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk())
    {
      std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
      Path path(filePathName);
      loader = new Loader;
      loader->loadResource(path);
    //  //loadflags = loader->checkForLoad(path);
      delete loader;
      loader = 0;
      // action
    }
    
    // close
    ImGuiFileDialog::Instance()->Close();
  }

  //if(ImGui::Button("load resurse")){
  //  Path path;
  //  
  //  //if(path.searchForPath()){
  //  //  loader = new Loader;
  //  //  loader->loadResource(path);
  //  //  //loadflags = loader->checkForLoad(path);
  //  //  delete loader;
  //  //  loader = 0;
  //  //}
  //}
  if (ImGui::CollapsingHeader("textures")){
    if(ImGui::Button("load Texture")){
      Path path;
      //if(path.searchForPath()){
      //  loader = new Loader;
      //  loader->loadTexture(path);
      //  //loadflags = loader->checkForLoad(path);
      //  delete loader;
      //  loader = 0;
      //}
    }
    for(auto texture : resourceManager.m_textures){
      if(texture.second)
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
      //if(path.searchForPath()){
      //  loader = new Loader;
      //  loader->loadScene(path);
      //  //loadflags = loader->checkForLoad(path);
      //  delete loader;
      //  loader = 0;
      //}
    }

    for(auto model : resourceManager.m_models){
      if(ImGui::Button(model.second->getName().c_str(),ImVec2(100,100))){
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

   if (ImGui::CollapsingHeader("sounds")){
    for(auto sound : resourceManager.m_sounds){
      if(ImGui::Button(sound.second->getName().c_str(),ImVec2(100,100))){
        audioApi.playSound(sound.second);
      }
    }
  }

  ImGui::End();

  ImGui::Begin("Actors");
  if(ImGui::Button("new Actor")){
    isCreatingActor = true;
  }
  if(ImGui::Button("scene")){
    m_selectedActor = m_actualScene->getRoot();
  }
  childsInImgui(m_actualScene->getRoot());
  ImGui::End();

  ImGui::Begin("configs");
  ImGui::DragFloat4("ssao",&m_ssaoConfig.x,.001f);
  //ImGui::DragFloat("blur",1,.01f);
  ImGui::End();


  ImGui::Begin("directional lights");
  if(ImGui::Button("add light")){
    m_directionalLights.push_back(DirectionalLight());
  }
  auto lightNum = m_directionalLights.size();
  for(int32 i = 0;i<lightNum;++i){
    ImGui::DragFloat3(("direction"+StringUtilities::intToString(i)).c_str(),&m_directionalLights[i].direction.x,.01f,-1.0f,1.0f);
    ImGui::DragFloat3(("color"+StringUtilities::intToString(i)).c_str(),&m_directionalLights[i].color.r,.01f,0.0f,1.0f);
  }
  ImGui::End();

  ImGui::Begin("point lights");
  if(ImGui::Button("add light")){
    m_pointLights.push_back(PointLight());
  }
  lightNum = m_pointLights.size();
  for(int32 i = 0;i<lightNum;++i){
    ImGui::DragFloat3(("color"+StringUtilities::intToString(i)).c_str(),&m_pointLights[i].color.r,.01f,0.0f,1.0f);
    ImGui::DragFloat3(("location"+StringUtilities::intToString(i)).c_str(),&m_pointLights[i].location.x,.01f);
    ImGui::DragFloat(("intensity"+StringUtilities::intToString(i)).c_str(),&m_pointLights[i].intensity);
  }
  ImGui::End();

  ImGui::Begin("spot lights");
  if(ImGui::Button("add light")){
    m_spotLights.push_back(SpotLight());

  }
  lightNum = m_spotLights.size();
  for(int32 i = 0;i<lightNum;++i){
    ImGui::DragFloat3(("color"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].color.r,.01f,0.0f,1.0f);
    ImGui::DragFloat3(("location"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].location.x,.01f);
    ImGui::DragFloat3(("direction"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].direction.x,.01f,-1.f,1.f);
    ImGui::DragFloat(("intensity"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].intensity);
    ImGui::DragFloat(("angle"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].angle,.01f,-1.f,1.f);
    ImGui::Checkbox(("cast shadows"+StringUtilities::intToString(i)).c_str(),&m_spotLights[i].castShadows);
    //ImGui::Image(shadowMap->getId(),ImVec2(100.f,100.f));
  }
  ImGui::End();

  if(isCreatingActor){
    ImGui::Begin("new Actor");
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("create")){
      auto actor = makeSPtr<Actor>();
      actor->setName(imguiString);
      if(!m_selectedActor.expired()){
        auto selectedActor = m_selectedActor.lock();
        selectedActor->attach(actor);
      }
      
      isCreatingActor = false;
    }
    ImGui::End();
  }

  if(isAddingComponent && !m_selectedActor.expired()){
    auto selectedActor = m_selectedActor.lock();

    ImGui::Begin("add component");

    if(ImGui::Button("Graphics")){
      selectedActor->attachComponent(makeSPtr<GraphicsComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Skeletal")){
      selectedActor->attachComponent(makeSPtr<SkeletalComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Animation")){
      selectedActor->attachComponent(makeSPtr<AnimationComponent>());
      isAddingComponent = false;
    }

    //if(ImGui::Button("Camera")){
    //  m_selectedActor->attachComponent(makeSPtr<CameraComponent>());
    //  m_selectedActor->getComponent<CameraComponent>()->setCamera(makeSPtr<Camera>());
    //
    //  m_selectedActor->getComponent<CameraComponent>()->getCamera()->init(
    //    static_cast<float>(m_windowSize.y)/static_cast<float>(m_windowSize.x)
    //  );
    //
    //  isAddingComponent = false;
    //}

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

  //if(isAddingSocket){
  //  ImGui::InputText("bone name",imguiString,64);
  //  if(ImGui::Button("ok")){
  //    m_selectedActor->getComponent<SkeletalComponent>()->attachToBone(m_selectedModel,imguiString);
  //    isAddingSocket = false;
  //  }
  //}

  ImGui::Begin("file");
  if(ImGui::Button("save all")){
    Serializer serializer;
    Path path;
    //if(path.searchForPath()){
    //
    //  serializer.init(path,true);
    //
    //  serializer.encodeSize(resourceManager.m_textures.size());
    //  for(auto& image: resourceManager.m_textures){
    //    image.second->save(serializer);
    //  }
    //  
    //  serializer.encodeSize(resourceManager.m_materials.size());
    //  for(auto& material: resourceManager.m_materials){
    //    material.second->save(serializer);
    //  }
    //  
    //  serializer.encodeSize(resourceManager.m_models.size());
    //  for(auto& model: resourceManager.m_models){
    //    model.second->save(serializer);
    //  }
    //  
    //  auto actors = m_actualScene->getRoot()->getChilds();
    //  serializer.encodeSize(actors.size());
    //  for(auto& actor : actors){
    //    
    //    actor->save(serializer);
    //  }
    //
    //}
  }

  if(ImGui::Button("load")){
    Serializer serializer;
    Path path;
    //if(path.searchForPath()){
    //  if(serializer.init(path,FILE::kRead)){
    //    SIZE_T number = serializer.decodeNumber();
    //    for(SIZE_T textureNum = 0; textureNum<number; ++textureNum){
    //      auto image = makeSPtr<Image>();
    //      image->load(serializer);
    //      SPtr<Texture> texture = GraphicAPI::instance().createTexture();
    //      texture->initFromImage(image);
    //      resourceManager.m_textures.insert({ texture->getName(),texture});
    //    }
    //
    //    number = serializer.decodeNumber();
    //    for(SIZE_T materialNum = 0; materialNum<number; ++materialNum){
    //      auto material = makeSPtr<Material>();
    //      material->load(serializer);
    //      resourceManager.m_materials.insert({ material->getName(),material});
    //    }
    //    
    //    number = serializer.decodeNumber();
    //    for(SIZE_T modelNum = 0; modelNum<number; ++modelNum){
    //      auto model = makeSPtr<Model>();
    //      model->load(serializer);
    //      resourceManager.m_models.insert({ model->getName(),model});
    //    }
    //
    //    number = serializer.decodeNumber();
    //    for(SIZE_T actorNum = 0; actorNum<number; ++actorNum){
    //      auto actor = makeSPtr<Actor>();
    //      actor->load(serializer);
    //      m_actualScene->getRoot()->attach(actor);
    //    }
    //  }
    //
    //  
    //}
  }

    
  

  ImGui::End();
  //ImGui::Begin("material editor");
  //if(m_selectedMaterial){
  //  SPtr<Texture> texture;
  //
  //  static const char* shaders[]{"normal","animation","paralax","transparent"};
  //
  //  int32 shader = m_selectedMaterial->getShader();
  //
  //  ImGui::Combo("shader",&shader,shaders,4);
  //
  //  m_selectedMaterial->setShader(static_cast<SHADER_TYPE::E>(shader));
  //
  //  if(ImGui::Button("select difusse")){
  //    m_selectedMaterial->setTexture(TEXTURE_TYPE::kDiffuse,m_selectedTexture);
  //  }
  //  texture = m_selectedMaterial->getTexture(TEXTURE_TYPE::kDiffuse);
  //  if(texture){
  //    ImGui::Image(texture->getId(),ImVec2(100,100));
  //  }
  //
  //  if(ImGui::Button("select normal map")){
  //    m_selectedMaterial->setTexture(TEXTURE_TYPE::kNormalMap,m_selectedTexture);
  //  }
  //  texture = m_selectedMaterial->getTexture(TEXTURE_TYPE::kNormalMap);
  //  if(texture){
  //    ImGui::Image(texture->getId(),ImVec2(100,100));
  //  }
  //
  //  if(ImGui::Button("select specular")){
  //    m_selectedMaterial->setTexture(TEXTURE_TYPE::kSpecular,m_selectedTexture);
  //  }
  //  texture = m_selectedMaterial->getTexture(TEXTURE_TYPE::kSpecular);
  //  if(texture){
  //    ImGui::Image(texture->getId(),ImVec2(100,100));
  //  }
  //
  //  if(ImGui::Button("select depth map")){
  //    m_selectedMaterial->setTexture(TEXTURE_TYPE::kDepthMap,m_selectedTexture);
  //  }
  //  texture = m_selectedMaterial->getTexture(TEXTURE_TYPE::kDepthMap);
  //  if(texture){
  //    ImGui::Image(texture->getId(),ImVec2(100,100));
  //  }
  //}
  //ImGui::End();

  ImGui::Begin("Model Editor");
  if(!m_selectedModel.expired()){
    auto selectedModel = m_selectedModel.lock();
    SIZE_T matNum = selectedModel->getNumOfMaterials();
    for(SIZE_T i = 0; i<matNum;++i){
      auto& wMaterial = selectedModel->getMaterial(i);
      if(!wMaterial.expired()){
        auto material = wMaterial.lock();
        if(ImGui::Button((material->getName()).c_str())){
          m_selectedMaterial = material;
        }
      }
      
    }

    if(ImGui::Button("divide")){
      Vector<SPtr<Model>> models;
      auto center = selectedModel->getCenter();
      resourceManager.separate(selectedModel,center,models,selectedModel->farestPoint(center));
      auto actor = makeSPtr<Actor>();
      for(auto& model : models){
        auto component = makeSPtr<GraphicsComponent>();
        component->setModel(model);
        actor->attachComponent(component);
      }
      actor->setName("divided");
      m_actualScene->getRoot()->attach(actor);
    }
  }
  ImGui::End();

  //ImGui::Begin("Shaders");
  //if(m_selectedMaterial){
  //  if(ImGui::Button("normal")){
  //     m_selectedMaterial->setShader(resourceManager.m_shaderPrograms["GBuffer"]);
  //  }
  //  if(ImGui::Button("transparent")){
  //    m_selectedMaterial->setShader(resourceManager.m_shaderPrograms["transparent"]);
  //  }
  //}
  //ImGui::End();

  ImGui::Begin("material textures");
  if(!m_selectedMaterial.expired()){
    auto selectedMaterial = m_selectedMaterial.lock();
    if (ImGui::CollapsingHeader("add")){
      ImGui::InputText("new",imguiString,64);
      if(!m_selectedTexture.expired()){
        auto selectedTexture = m_selectedTexture.lock();
        ImGui::Image(selectedTexture->getId(),ImVec2(100,100));
      }
      if(ImGui::Button("add texture")){
        selectedMaterial->setTexture(imguiString,m_selectedTexture);
      }
    }
    
    for(auto& textureChannel : selectedMaterial->getTextureChannels()){
      if(ImGui::Button(textureChannel.c_str()) && !m_selectedTexture.expired()){

        selectedMaterial->setTexture(textureChannel,m_selectedTexture);
      }
      auto texture = selectedMaterial->getTexture(textureChannel);
      if(!texture.expired()){
        ImGui::Image(texture.lock()->getId(),ImVec2(100,100));
      }
      //if(ImGui::ImageButton(texture.second->getId(),ImVec2(100,100))){
      //  m_selectedTexture = texture.second;
      //}
    }
  }
  ImGui::End();

  ImGui::Begin("lua");
  {
    if (ImGui::Button("execute lua script"))
      ImGuiFileDialog::Instance()->OpenDialog("Lua", "Choose File", ".lua", ".");

    if (ImGuiFileDialog::Instance()->Display("Lua")) 
    {
      // action if OK
      if (ImGuiFileDialog::Instance()->IsOk())
      {
        String filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
        String filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        //luaL_loadfilex(luaState,filePathName.c_str(),NULL);
        //lua_pcall(luaState, 0, LUA_MULTRET, 0);
        auto ret = luaL_dofile(luaState,filePathName.c_str());
        print(lua_tostring(luaState,-1));
      }
      
      // close
      ImGuiFileDialog::Instance()->Close();
    }
  }
  ImGui::End();

}

void oaEngineSDK::TestApp::childsInImgui(SPtr<Actor> parentActor)
{
  auto& childs = parentActor->getChilds();
  for(SPtr<Actor> actor : childs){
    if(ImGui::Button(actor->getName().c_str())){
      m_selectedActor = actor;
    }
    if(actor->getChilds().size()>0){
      if(ImGui::CollapsingHeader("childs")){
        childsInImgui(actor);
      }
    }
  }
}

//SubMesh
//oaEngineSDK::TestApp::tetrahedron()
//{
//  SubMesh ans;
//  float sq2 = Math::sqrt(2.0f);
//  float sq3 = Math::sqrt(3.0f);
//  ans.points = {
//    {0.0f,0.0f,1.0f,0.0f},
//    {2.0f*sq2/3.0f,0.0f,-1.0f/3.0f,0.0f},
//    {-sq2/3.0f,sq2/sq3,-1.0f/3.0f,0.0f},
//    {-sq2/3.0f,-sq2/sq3,-1.0f/3.0f,0.0f},
//  };
//
//  ans.indices = {0,1,2,0,2,3,0,3,1,1,3,2};
//
//  return ans;
//}

//SubMesh
//oaEngineSDK::TestApp::octahedron()
//{
//  SubMesh ans;
//  ans.points = {
//    {0.0f,0.0f, 1.0f,0.0f},
//    {0.0f,0.0f,-1.0f,0.0f},
//    {0.0f, 1.0f,0.0f,0.0f},
//    {0.0f,-1.0f,0.0f,0.0f},
//    { 1.0f,0.0f,0.0f,0.0f},
//    {-1.0f,0.0f,0.0f,0.0f},
//  };
//  ans.indices = {0,4,2,0,3,4,0,5,3,0,2,5,1,2,4,1,4,3,1,3,5,1,5,2};
//
//  return ans;
//}

//Mesh
//TestApp::icosahedron()
//{
//  float phi = (Math::sqrt(5)+1.0f)/2.0f;
//  Vector2f v{1.0f,phi};
//  v.normalize();
//
//  Mesh ans;
//
//  Vector<Vector4f> points = {
//    Vector4f(-v.x, v.y,0.0f,0.0f), 
//    Vector4f( v.x, v.y,0.0f,0.0f), 
//    Vector4f(-v.x,-v.y,0.0f,0.0f), 
//    Vector4f( v.x,-v.y,0.0f,0.0f), 
//    Vector4f(0.0f,-v.x, v.y,0.0f), 
//    Vector4f(0.0f, v.x, v.y,0.0f), 
//    Vector4f(0.0f,-v.x,-v.y,0.0f), 
//    Vector4f(0.0f, v.x,-v.y,0.0f), 
//    Vector4f( v.y,0.0f,-v.x,0.0f), 
//    Vector4f( v.y,0.0f, v.x,0.0f), 
//    Vector4f(-v.y,0.0f,-v.x,0.0f), 
//    Vector4f(-v.y,0.0f, v.x,0.0f)
//    
//  };
//
//  Vector<uint32> index = {0,11,5,0,5,1,0,1,7,0,7,10,0,10,11,1,5,9,5,11,4,11,10,2,10,7,6,
//                          7,1,8,3,9,4,3,4,2,3,2,6,3,6,8,3,8,9,4,9,5,2,4,11,6,2,10,8,6,7,
//                          9,8,1};
//
//  return ans;
//}
//
//SubMesh 
//oaEngineSDK::TestApp::SubDivide(Vector<Vector4f>& vertices, Vector<uint32>& indices)
//{
//  //SIZE_T size = indices.size();
//  //SIZE_T actualSize = size;
//  //Map<Pair<uint32, uint32>, uint32> used;
//  //for(uint32 i = 0; i < size; i+=3){
//  //  Vector3f oldPoints[3]={
//  //    vertices[indices[i]].xyz,
//  //    vertices[indices[i+1]].xyz,
//  //    vertices[indices[i+2]].xyz,
//  //  };
//  //  ;
//  //  Pair<uint32, uint32> pair(Math::min<uint32>(indices[i],indices[i+1]),Math::max<uint32>(indices[i],indices[i+1]));
//  //  if(used.find(pair)==used.end()){
//  //    used.insert({pair,actualSize});
//  //    ++actualSize;
//  //    
//  //    vertices.push_back(Vector4f(Vector3f::interpolate(oldPoints[0],oldPoints[1],.5f).normalized(),0.0f));
//  //  }
//  //}
//  //return ans;
//  return SubMesh();
//}
//
//void TestApp::vertexForEdge(Map<Pair<uint32, uint32>, uint32>& used, 
//                            Vector<Vector4f>& vertices, 
//                            uint32 index1, 
//                            uint32 index2)
//{
//  //Pair<uint32, uint32> pair(Math::min<uint32>(index1,index2),Math::max<uint32>(index1,index2));
//  //if(used.find(pair)==used.end()){
//  //  used.insert({pair,actualSize});
//  //  ++actualSize;
//  //  
//  //  vertices.push_back(Vector4f(Vector3f::interpolate(oldPoints[0],oldPoints[1],.5f).normalized(),0.0f));
//  //}
//}



}




