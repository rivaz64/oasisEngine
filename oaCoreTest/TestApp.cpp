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
#include <oaStaticMesh.h>
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
#include <oaStaticMeshComponent.h>
#include <oaSkeletalMeshComponent.h>
#include <oaSkeletalModel.h>
//#include <oaCrowdComponent.h>
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <oaSerializer.h>
#include <oaOmniverseApi.h>
#include <oaDirectionalLightComponent.h>
#include <oaPointLightComponent.h>
#include <oaSpotLightComponent.h>
#include <oaAmbientLightComponent.h>
#include <chrono>
#include "WanderAgent.h"
#include <SpatialPartition.h>
#include "TestAgent.h"
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

float randomFloat()
{
  return static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}

vector<Vector2f>
scatter(size_t numOfPoints,Vector2f minPoint, Vector2f maxPoint)
{
  vector<Vector2f> ans;
  auto length = maxPoint-minPoint;
  ans.resize(numOfPoints);
  for(auto& i : ans){
    i = {randomFloat()*length.x+minPoint.x,randomFloat()*length.y+minPoint.y};
  }
  return ans;
}

vector<Vector2f>
blueNoise(vector<Vector2f> points, float radii){
  auto ans = points;
  auto numOfPoints = points.size();
  for(size_t i = 0; i<numOfPoints-1; ++i){
    for(size_t o = i+1; o<numOfPoints; ++o){
      auto d = points[i]-points[o];
      auto dis = d.magnitud();
      if(dis<radii){
        ans[i] += d.normalized();
        ans[o] = ans[o]-d.normalized();
      }
    }
  }
  return ans;
}

//void
//TestApp::genMorbiusTrip(){
//  auto& grapgicApi = GraphicAPI::instance();
//  m_morbiusTrip = makeSPtr<StaticMesh>();
//  m_morbModel = makeSPtr<Model>();
//  m_morbComponent = makeSPtr<GraphicsComponent>();
//  m_morbActor = makeSPtr<Actor>();
//  m_morbComponent->setModel(m_morbModel);
//  m_morbActor->attachComponent(m_morbComponent);
//  m_morbActor->GetActorTransform().setScale({1.f,1.f,1.f});
//  
//  //m_morbModel->addMesh(m_morbiusTrip);
//  m_morbiusTrip->setControlPoints({
//	{ 1.0f, -0.5f, 0.0f, 0.0f },
//	{ 1.0f, -0.5f, 0.5f, 0.0f },
//	{ 0.5f, -0.3536f, 1.354f, 0.0f },
//	{ 0.0f, -0.3536f, 1.354f, 0.0f },
//	{ 1.0f, -0.1667f, 0.0f, 0.0f },
//	{ 1.0f, -0.1667f, 0.5f, 0.0f },
//	{ 0.5f, -0.1179f, 1.118f, 0.0f },
//	{ 0.0f, -0.1179f, 1.118f, 0.0f },
//	{ 1.0f, 0.1667f, 0.0f, 0.0f },
//	{ 1.0f, 0.1667f, 0.5f, 0.0f },
//	{ 0.5f, 0.1179f, 0.8821f, 0.0f },
//	{ 0.0f, 0.1179f, 0.8821f, 0.0f },
//	{ 1.0f, 0.5f, 0.0f, 0.0f },
//	{ 1.0f, 0.5f, 0.5f, 0.0f },
//	{ 0.5f, 0.3536f, 0.6464f, 0.0f },
//	{ 0.0f, 0.3536f, 0.6464f, 0.0f },
//	{ 0.0f, -0.3536f, 1.354f, 0.0f },
//	{ -0.5f, -0.3536f, 1.354f, 0.0f },
//	{ -1.5f, 0.0f, 0.5f, 0.0f },
//	{ -1.5f, 0.0f, 0.0f, 0.0f },
//	{ 0.0f, -0.1179f, 1.118f, 0.0f },
//	{ -0.5f, -0.1179f, 1.118f , 0.0f},
//	{ -1.167f, 0.0f, 0.5f , 0.0f},
//	{ -1.167f, 0.0f, 0.0f , 0.0f},
//	{ 0.0f, 0.1179f, 0.8821f , 0.0f},
//	{ -0.5f, 0.1179f, 0.8821f , 0.0f},
//	{ -0.8333f, 0.0f, 0.5f , 0.0f},
//	{ -0.8333f, 0.0f, 0.0f , 0.0f},
//	{ 0.0f, 0.3536f, 0.6464f , 0.0f},
//	{ -0.5f, 0.3536f, 0.6464f , 0.0f},
//	{ -0.5f, 0.0f, 0.5f , 0.0f},
//	{ -0.5f, 0.0f, 0.0f , 0.0f},
//	{ -1.5f, 0.0f, 0.0f , 0.0f},
//	{ -1.5f, 0.0f, -0.5f , 0.0f},
//	{ -0.5f, 0.3536f, -1.354f , 0.0f},
//	{ 0.0f, 0.3536f, -1.354f , 0.0f},
//	{ -1.167f, 0.0f, 0.0f , 0.0f},
//	{ -1.167f, 0.0f, -0.5f , 0.0f},
//	{ -0.5f, 0.1179f, -1.118f , 0.0f},
//	{ 0.0f, 0.1179f, -1.118f , 0.0f},
//	{ -0.8333f, 0.0f, 0.0f , 0.0f},
//	{ -0.8333f, 0.0f, -0.5f , 0.0f},
//	{ -0.5f, -0.1179f, -0.8821f , 0.0f},
//	{ 0.0f, -0.1179f, -0.8821f , 0.0f},
//	{ -0.5f, 0.0f, 0.0f , 0.0f},
//	{ -0.5f, 0.0f, -0.5f , 0.0f},
//	{ -0.5f, -0.3536f, -0.6464f , 0.0f},
//	{ 0.0f, -0.3536f, -0.6464f , 0.0f},
//	{ 0.0f, 0.3536f, -1.354f , 0.0f},
//	{ 0.5f, 0.3536f, -1.354f , 0.0f},
//	{ 1.0f, 0.5f, -0.5f , 0.0f},
//	{ 1.0f, 0.5f, 0.0f , 0.0f},
//	{ 0.0f, 0.1179f, -1.118f , 0.0f},
//	{ 0.5f, 0.1179f, -1.118f , 0.0f},
//	{ 1.0f, 0.1667f, -0.5f , 0.0f},
//	{ 1.0f, 0.1667f, 0.0f , 0.0f},
//	{ 0.0f, -0.1179f, -0.8821f , 0.0f},
//	{ 0.5f, -0.1179f, -0.8821f , 0.0f},
//	{ 1.0f, -0.1667f, -0.5f , 0.0f},
//	{ 1.0f, -0.1667f, 0.0f , 0.0f},
//	{ 0.0f, -0.3536f, -0.6464f , 0.0f},
//	{ 0.5f, -0.3536f, -0.6464f , 0.0f},
//	{ 1.0f, -0.5f, -0.5f , 0.0f},
//	{ 1.0f, -0.5f, 0.0f , 0.0f},
//});
//
//  //m_actualScene->getRoot()->attach(m_morbActor);
//}

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

  m_worldScene = makeSPtr<Actor>();

  m_worldScene->setName("scene");

  m_actualScene = m_worldScene;

  m_selectedActor = m_worldScene;

  initMeshScene();
  generateCube();
  initMaterialScene();
  initModelScene();
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

  //genMorbiusTrip();

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
  if(m_mouse->isButtonDown(BUTTON::kRight)){
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

  

  newImGuiFrame();
  updateImGui();

  OmniverseApi::instance().update();

  m_actualScene.lock()->postUpdate();

  if(play){
    cw->update(.0625f);
    int num = agents.size();
    for(int i = 0; i<num;++i){
      auto point = cw->getPosition(i);
      agents[i].lock()->setActorLocation(Vector3f(point.x,0.0f,point.y));
    }
  }
}

void 
TestApp::draw()
{
  auto& graphicsAPI = GraphicAPI::instance();

  auto& resourseManager = ResoureManager::instance();
   
  //
  ////m_camera->setCamera();

  auto& renderer = Renderer::instance();

  //graphicsAPI.renderTest();

  //if(m_controlledActor){
  //  renderer.render(m_actualScene,m_controlledActor->getComponent<CameraComponent>()->getCamera(),m_controlledActor->getComponent<CameraComponent>()->getCamera());
  //}
  //else if(m_debugCamera){
  //  renderer.render(m_actualScene,m_camera,m_debugCamera);
  //}
  //else{
    renderer.render(m_actualScene,m_camera,m_camera,m_ssaoConfig);
  //}
  
  
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

void TestApp::childsInImgui(SPtr<Actor> parentActor)
{
  auto& childs = parentActor->getChilds();
  for(SPtr<Actor> actor : childs){
    ImGui::Indent(6);
    if(ImGui::Button(actor->getName().c_str())){
      m_selectedActor = actor;
    }
    if(actor->getChilds().size()>0){
      //if(ImGui::CollapsingHeader("childs")){
        childsInImgui(actor);
      //}
    }
    ImGui::Unindent(6);
  }
}

void
TestApp::initMeshScene()
{
  m_meshScene =  makeSPtr<Actor>();
  auto actor = makeSPtr<Actor>();
  auto component = makeSPtr<StaticMeshComponent>();
  m_meshModel = makeSPtr<Model>();
  m_meshMaterial = makeSPtr<Material>();
  m_meshMaterial->setColor("diffuse",Color::WHITE);
  m_meshModel->setMaterial(m_meshMaterial);
  component->setModel(m_meshModel);
  actor->attachComponent(component);
  actor->attachComponent(makeSPtr<AmbientLightComponent>());
  m_meshScene->attach(actor);
}

void 
TestApp::generateCube()
{

  cube = makeSPtr<StaticMesh>();

  Vector<Vertex> vertices = {
    Vertex( Vector4f(-.5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f( .5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f( .5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f), Vector4f(-1.0f,0.0f, 0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 1.0f) ),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) ),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) ),
  };

  Vector<uint32> index = {
    3,1,0,
    2,1,3,
    
    6,4,5,
    7,4,6,
    
    11,9,8,
    10,9,11,
    
    14,12,13,
    15,12,14,
    
    19,17,16,
    18,17,19,
    
    22,20,21,
    23,20,22
  };


  cube->setVertex(vertices);
  cube->setIndex(index);
  cube->writeBuffers();
  //Plane plane(Vector3f(.25,0,0),Vector3f(.25,1,0),Vector3f(.25,0,1));

  //Octree tree;
  //auto planes = tree.getPlanes();
  //Vector<uint32> indexFront;
  //Vector<uint32> indexBack;
  //Vector<Vector<uint32>> meshes;
  //meshes.push_back(index);
  //Vector<Vector<uint32>> newMeshes;
  //for(auto& plane: planes){
  //  for(Vector<uint32>& m : meshes){
  //    indexBack.clear();
  //    indexFront.clear();
  //    divide(plane, vertices,m,indexBack,indexFront);
  //    newMeshes.push_back(indexBack);
  //    newMeshes.push_back(indexFront);
  //  }
  //  meshes = newMeshes;
  //  newMeshes.clear();
  //}
  
 
  //String name = "cube";//+StringUtilities::intToString(i);
  //m_models.insert({name,makeSPtr<Model>()});
  //auto& model = m_models[name];
  //model->setName(name);
  //model->addMaterial(makeSPtr<Material>());
  //auto& material = model->getMaterial(0);
  //material->setShader(0);
  //m_materials.insert({"wall",material});
  //model->addMesh(makeSPtr<Mesh>());
  //auto& mesh = model->getMesh(0);
  //mesh->setIndex(index);
  //mesh->create(vertices.data(),sizeof(Vertex),vertices.size());
}
void 
TestApp::initMaterialScene()
{
  m_materialScene = makeSPtr<Actor>();
  auto actor = makeSPtr<Actor>();
  auto component = makeSPtr<StaticMeshComponent>();
  m_materialModel = makeSPtr<Model>();
  m_materialModel->setMesh(cube);
  component->setModel(m_materialModel);
  actor->attachComponent(component);
  actor->attachComponent(makeSPtr<AmbientLightComponent>());
  actor->attachComponent(makeSPtr<DirectionalLightComponent>());
  m_materialScene->attach(actor);
}

void 
TestApp::initModelScene()
{
  m_modelScene = makeSPtr<Actor>();
  auto actor = makeSPtr<Actor>();
  auto component = makeSPtr<StaticMeshComponent>();
  actor->attachComponent(component);
  actor->attachComponent(makeSPtr<AmbientLightComponent>());
  actor->attachComponent(makeSPtr<DirectionalLightComponent>());
  m_modelScene->attach(actor);
}

void 
TestApp::components()
{
  Vector<EventHandler<>> handler;
  for(int type = 0; type != COMPONENT_TYPE::numOfComponents; ++type){

  }
}

void 
TestApp::updateImGui()
{
  auto& resourceManager = ResoureManager::instance();
  auto& audioApi = AudioAPI::instance();
  auto& renderer = Renderer::instance();

  auto shadowMap = renderer.getShadowMap();

  ImGui::Begin("game");
  {
    ImGui::Checkbox("play",&play);
  }
  ImGui::End();

  ImGui::Begin("shaders");
  if(ImGui::Button("ReloadShaders")){
    resourceManager.loadDefaultShaders();
  }
  ImGui::End();

 

  ImGui::Begin("Actor atributes");
  if(!m_selectedActor.expired()){
    auto actor = m_selectedActor.lock();
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("changeName")){
      actor->setName(imguiString);
    }
    auto selectedActor = m_selectedActor.lock();
    if(ImGui::Button("Add Component")){
      isAddingComponent = true;
    }

    if (ImGui::CollapsingHeader("transform")){
      
      //auto& transform = selectedActor->GetActorTransform();
      Vector3f vec = selectedActor->getLocalLocation();
      if(ImGui::DragFloat3("location", &vec.x, .01f)){
        selectedActor->setActorLocation(vec);
      }
      vec = selectedActor->getLocalScale();
      if(ImGui::DragFloat3("scale", &vec.x, .01f)){
        selectedActor->setActorScale(vec);
      }
      vec = selectedActor->getLocalRotation()*Math::RAD_TO_DEG;
      
      if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
        selectedActor->setActorRotation(vec*Math::DEG_TO_RAD);
      };
    }

    WPtr<Component> wComponent;
    Vector<SPtr<Component>> components;
    components = selectedActor->getComponents<StaticMeshComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("static mesh "+StringUtilities::intToString(i)).c_str())){
          auto graphicsComponent = cast<StaticMeshComponent>(components[i]);

          if(ImGui::Button("select model")){
            if(!m_selectedModel.expired()){
              graphicsComponent->setModel(m_selectedModel);
            }
            else if(!m_selectedMesh.expired()){
              auto newModel = makeSPtr<Model>();
              newModel->setMesh(m_selectedMesh.lock());
              newModel->setMaterial(resourceManager.m_defaultMaterial);
              resourceManager.registerResourse(m_selectedMesh.lock()->getName(),newModel);
              graphicsComponent->setModel(newModel);
            }
          }

          auto& wModel = graphicsComponent->getModel();
          if(!wModel.expired()){
            auto model = wModel.lock();
            ImGui::Text(model->getName().c_str());
            auto& transform = graphicsComponent->getTransform();
            auto vec = transform.getLocation();
            if(ImGui::DragFloat3("location Model",&vec.x)){
              transform.setLocation(vec);
            }
            vec = transform.getScale();
            if(ImGui::DragFloat3("scale Model",&vec.x)){
              transform.setScale(vec);
            }
            vec = transform.getRotation()*Math::RAD_TO_DEG;
            if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
              transform.setRotation(vec*Math::DEG_TO_RAD);
            };
          }
        }
      }
    }

    components = selectedActor->getComponents<SkeletalMeshComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("skeletal mesh "+StringUtilities::intToString(i)).c_str())){
          auto graphicsComponent = cast<SkeletalMeshComponent>(components[i]);

          if(ImGui::Button("select model")){
            if(!m_selectedSkeletalModel.expired()){
              graphicsComponent->setModel(m_selectedSkeletalModel);
            }
          }

          auto& wModel = graphicsComponent->getModel();
          if(!wModel.expired()){
            auto model = wModel.lock();
            ImGui::Text(model->getName().c_str());



            if(ImGui::DragFloat("at time", &graphicsComponent->m_actualTick,1.f/6.f)){
              graphicsComponent->setAtTick(graphicsComponent->m_actualTick);
            }

            auto& transform = graphicsComponent->getTransform();
            auto vec = transform.getLocation();
            if(ImGui::DragFloat3("location Model",&vec.x)){
              transform.setLocation(vec);
            }
            vec = transform.getScale();
            if(ImGui::DragFloat3("scale Model",&vec.x)){
              transform.setScale(vec);
            }
            vec = transform.getRotation()*Math::RAD_TO_DEG;
            if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
              transform.setRotation(vec*Math::DEG_TO_RAD);
            };
          }
        }
        
      }
      

    }

    components = selectedActor->getComponents<AmbientLightComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("ambient light "+StringUtilities::intToString(i)).c_str())){
          auto lightComponent = cast<AmbientLightComponent>(components[i]);
          ImGui::DragFloat3("color",reinterpret_cast<float*>(&lightComponent->m_light.color),1.f/36.f,0,1);
        }
      }
    }

    components = selectedActor->getComponents<DirectionalLightComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("directional light "+StringUtilities::intToString(i)).c_str())){
          auto lightComponent = cast<DirectionalLightComponent>(components[i]);
          ImGui::DragFloat3("color",reinterpret_cast<float*>(&lightComponent->m_light.color),1.f/36.f,0,1);
          ImGui::DragFloat3("direction",reinterpret_cast<float*>(&lightComponent->m_light.direction),1.f/36.f,-1,1);
        }
      }
    }

    components = selectedActor->getComponents<PointLightComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("point light "+StringUtilities::intToString(i)).c_str())){
          auto lightComponent = cast<PointLightComponent>(components[i]);
          ImGui::DragFloat3("color",reinterpret_cast<float*>(&lightComponent->m_light.color),1.f/36.f,0,1);
          ImGui::DragFloat3("location",reinterpret_cast<float*>(&lightComponent->m_light.location),1);
          ImGui::DragFloat("intensity",reinterpret_cast<float*>(&lightComponent->m_light.intensity),6,0);
        }
      }
    }

    components = selectedActor->getComponents<SpotLightComponent>();
    if (components.size()>0){
      SIZE_T numComponents = components.size();
      for(SIZE_T i=0;i<numComponents;++i){
        if( ImGui::CollapsingHeader(("spot light "+StringUtilities::intToString(i)).c_str())){
          auto lightComponent = cast<SpotLightComponent>(components[i]);
          ImGui::DragFloat3("color",reinterpret_cast<float*>(&lightComponent->m_light.color),1.f/36.f,0,1);
          ImGui::DragFloat3("direction",reinterpret_cast<float*>(&lightComponent->m_light.direction),1.f/36.f,-1,1);
          ImGui::DragFloat3("location",reinterpret_cast<float*>(&lightComponent->m_light.location),1);
          ImGui::DragFloat("intensity",reinterpret_cast<float*>(&lightComponent->m_light.intensity),6,0);
          ImGui::DragFloat("angle",reinterpret_cast<float*>(&lightComponent->m_light.angle),.001,-1,1);

        }
      }
    }

    //wComponent = selectedActor->getComponent<CrowdComponent>();
    //
    //if (!wComponent.expired() && ImGui::CollapsingHeader("crowd")){
    //  //auto component
    //}
    //
    //wComponent = selectedActor->getComponent<SkeletalComponent>();
    //
    //if (!wComponent.expired() && ImGui::CollapsingHeader("skeleton")){
    //  auto component = wComponent.lock();
    //  if(ImGui::Button("select Skeleton")){
    //    cast<SkeletalComponent>(component)->setSkeleton(m_selectedSkeleton);
    //
    //  }
    //
    //  auto wSkeleton = cast<SkeletalComponent>(component)->getSkeleton();
    //
    //  if(!wSkeleton.expired()){
    //    auto skeleton = wSkeleton.lock();
    //    ImGui::Text(skeleton->getName().c_str());
    //    //if(ImGui::Button("add socket")){
    //    //  isAddingSocket = true;
    //    //}
    //  }
    //
    //}

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

    if(ImGui::Button("save")){
      Serializer serializer;
      serializer.init(m_projectPath.string()+"/"+m_selectedActor.lock()->getName()+".oa",true);
      m_selectedActor.lock()->onSave(serializer);
      m_actors.push_back(m_selectedActor.lock()->getName());
    }

    if(ImGui::Button("delete")){
      auto parent = selectedActor->getParent().lock();
      parent->unattach(m_selectedActor);
    }
  }
  ImGui::End();

  ImGui::Begin("resources");

  if (ImGui::Button("load resourse"))
    ImGuiFileDialog::Instance()->OpenDialog("Asset", "Choose File", ".png,.jpg,.hpp,.obj,.fbx,.glb,.wav", ".");

  if (ImGuiFileDialog::Instance()->Display("Asset")) 
  {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk())
    {
      std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
      Path path(filePathName);
      loader = new Loader;
      loader->loadResource(path,m_selectedActor);
      delete loader;
      loader = 0;
    }
    ImGuiFileDialog::Instance()->Close();
  }

  if (ImGui::Button("load merged image"))
    ImGuiFileDialog::Instance()->OpenDialog("merged", "Choose File", ".png,.jpg", ".");

  if (ImGuiFileDialog::Instance()->Display("merged")) 
  {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk())
    {
      std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
      Path path(filePathName);
      loader = new Loader;
      loader->loadMergedTexture(path);
      delete loader;
      loader = 0;
    }
    ImGuiFileDialog::Instance()->Close();
  }

  if (ImGui::CollapsingHeader("textures")){
    for(auto texture : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kTexture)){
      if(!texture.expired())
      if(ImGui::ImageButton(cast<Texture>(texture).lock()->getId(),ImVec2(100,100))){
        m_selectedTexture = cast<Texture>(texture);
        textureInspector = true;
      }
    }
  }
  
  if (ImGui::CollapsingHeader("materials")){
    if(ImGui::Button("create material")){
      resourceManager.registerResourse("newMat",makeSPtr<Material>());
    }
    for(auto material : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kMaterial)){
      if(ImGui::Button(material.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedMaterial = cast<Material>(material);
        m_actualScene = m_materialScene;
        m_selectedActor = m_materialScene->getChilds()[0];
        m_materialScene->getChilds()[0]->getComponent<StaticMeshComponent>().lock()->getModel().lock()->setMaterial(m_selectedMaterial);
        auto name = m_selectedMaterial.lock()->getName().c_str();
        auto nameSize =  m_selectedMaterial.lock()->getName().size();
        memcpy(imguiString,name,nameSize);
      }
    }
  }

  if (ImGui::CollapsingHeader("static meshes")){
    for(auto mesh : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kStaticMesh)){
      if(ImGui::Button(mesh.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedMesh = cast<StaticMesh>(mesh);
        m_actualScene = m_meshScene;
        m_selectedActor = m_meshScene->getChilds()[0];
        m_meshScene->getChilds()[0]->getComponent<StaticMeshComponent>().lock()->getModel().lock()->setMesh(m_selectedMesh);
        auto name = m_selectedMesh.lock()->getName().c_str();
        auto nameSize =  m_selectedMesh.lock()->getName().size();
        memcpy(imguiString,name,nameSize);
      }
    }
  }
  
  if (ImGui::CollapsingHeader("static models")){
    if(ImGui::Button("create model")){
      resourceManager.registerResourse("newModel",makeSPtr<Material>());
    }
    for(auto model : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kModel)){
      if(ImGui::Button(model.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedModel = cast<Model>(model);
        m_actualScene = m_modelScene;
        m_selectedActor = m_modelScene->getChilds()[0];
        m_modelScene->getChilds()[0]->getComponent<StaticMeshComponent>().lock()->setModel(m_selectedModel);
        auto name = m_selectedModel.lock()->getName().c_str();
        auto nameSize =  m_selectedModel.lock()->getName().size();
        memcpy(imguiString,name,nameSize);
      }
    }
  }

  if (ImGui::CollapsingHeader("actors")){
    for(auto actor : m_actors){
      if(ImGui::Button(actor.c_str(),ImVec2(100,100))){
        Serializer serializer;
        serializer.init(m_projectPath.string()+"/"+actor+".oa",false);
        m_worldScene = makeSPtr<Actor>();
        m_worldScene->load(serializer);
        m_actualScene = m_worldScene;
        m_worldScene->setName(actor);
      }
    }
  }

  if (ImGui::CollapsingHeader("skeletal meshes")){
    for(auto mesh : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kSkeletalMesh)){
      if(ImGui::Button(mesh.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedSkeletalMesh = cast<SkeletalMesh>(mesh);
      }
    }
  }
  
  if (ImGui::CollapsingHeader("skeletal models")){
    for(auto model : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kSkeletalModel)){
      if(ImGui::Button(model.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedSkeletalModel = cast<SkeletalModel>(model);
      }
    }
  }

  if (ImGui::CollapsingHeader("skeletons")){
    for(auto skeleton : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kSkeleton)){
      if(ImGui::Button(skeleton.lock()->getName().c_str(),ImVec2(100,100))){
        print("working");
        m_selectedSkeleton = cast<Skeleton>(skeleton);
      }
    }
  }

  if (ImGui::CollapsingHeader("animations")){
    for(auto animation : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kAnimation)){
      if(ImGui::Button(animation.lock()->getName().c_str(),ImVec2(100,100))){
        m_selectedAnimation = cast<Animation>(animation);
      }
    }
  }

   if (ImGui::CollapsingHeader("sounds")){
    for(auto sound : resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kSound)){
      if(ImGui::Button(sound.lock()->getName().c_str(),ImVec2(100,100))){
        audioApi.playSound(cast<Sound>(sound));
      }
    }
  }

  ImGui::End();

  ImGui::Begin("Actors");
  if(ImGui::Button("new Actor")){
    isCreatingActor = true;
  }

  if(ImGui::Button("add Actor")){
    isAddingActor = true;
  }

  if(ImGui::Button(m_worldScene->getName().c_str())){
    m_selectedActor = m_worldScene;
  }
  childsInImgui(m_actualScene.lock());
  ImGui::End();

  ImGui::Begin("configs");
  ImGui::DragFloat4("ssao",&m_ssaoConfig.x,.001f);
  //ImGui::DragFloat("blur",1,.01f);
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

    if(ImGui::Button("Static Mesh")){
      selectedActor->attachComponent(makeSPtr<StaticMeshComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Skeletal Mesh")){
      selectedActor->attachComponent(makeSPtr<SkeletalMeshComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Directioal Light")){
      selectedActor->attachComponent(makeSPtr<DirectionalLightComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Point Light")){
      selectedActor->attachComponent(makeSPtr<PointLightComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Spot Light")){
      selectedActor->attachComponent(makeSPtr<SpotLightComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("AmbientLight Light")){
      selectedActor->attachComponent(makeSPtr<AmbientLightComponent>());
      isAddingComponent = false;
    }

    //if(ImGui::Button("crowd")){
    //  selectedActor->attachComponent(makeSPtr<CrowdComponent>());
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

  ImGui::Begin("scene");
  {
    if(ImGui::Button("new scene")){
      m_worldScene = makeSPtr<Actor>();
      m_actualScene = m_worldScene;
      m_selectedActor = m_worldScene;
    }
    ImGui::End();
  }

  
  

  ImGui::Begin("Model Editor");{
    if(!m_selectedModel.expired()){
      auto selectedModel = m_selectedModel.lock();
      //SIZE_T matNum = selectedModel->getNumOfMaterials();
      //for(SIZE_T i = 0; i<matNum;++i){
        auto wMaterial = selectedModel->getMaterial();
        if(!wMaterial.expired()){
          auto material = wMaterial.lock();
          if(ImGui::Button((material->getName()).c_str())){
            m_selectedMaterial = material;
          }
        }
        
      //}

      //if(ImGui::Button("divide")){
      //  Vector<SPtr<Model>> models;
      //  auto center = selectedModel->getCenter();
      //  resourceManager.separate(selectedModel,center,models,selectedModel->farestPoint(center));
      //  auto actor = makeSPtr<Actor>();
      //  for(auto& model : models){
      //    auto component = makeSPtr<StaticMeshComponent>();
      //    component->setModel(model);
      //    actor->attachComponent(component);
      //  }
      //  actor->setName("divided");
      //  m_actualScene->getRoot()->attach(actor);
      //}
    }
    ImGui::End();
  }

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

  ImGui::Begin("omniverse");
  {
    auto& omniverse = OmniverseApi::instance();
    if(ImGui::Button("connect")){
      omniverse.connect();
    }

    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("create file")){
      omniverse.createModel(imguiString,m_worldScene);
    }
    if(ImGui::Button("open file")){
      omniverse.connectToModel(imguiString,m_worldScene);
    }
    if(ImGui::Button("close file")){
      omniverse.closeScene();
    }
    if(ImGui::Button("create session")){
      omniverse.createSession(imguiString);
    }
    if(ImGui::Button("join session")){
      omniverse.joinToSession(imguiString);
    }
    if(ImGui::Button("leave session")){
      omniverse.leaveSession();
    }
    if(ImGui::Button("test")){
      omniverse.test();
    }

  }
  ImGui::End();

  ImGui::Begin("project");
  if (ImGui::Button("choose"))
    ImGuiFileDialog::Instance()->OpenDialog("choose project", "Choose File", ".oa", ".");

  if (ImGuiFileDialog::Instance()->Display("choose project")) 
  {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk())
    {
      String filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      String filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
      m_projectPath = filePath;
      print(filePath);
    }
    
    // close
    ImGuiFileDialog::Instance()->Close();
  }
  if (ImGui::Button("save"))
  {
    Serializer serializer;
    serializer.init(m_projectPath.string()+"/"+"OasisEngineTestProject.oa",true);
    auto textures = resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kTexture);
    auto staticMeshes = resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kStaticMesh);
    auto materials = resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kMaterial);
    auto models = resourceManager.getAllResoursesOfType(RESOURSE_TYPE::kModel);
    serializer.encodeSize(textures.size()+staticMeshes.size()+materials.size()+models.size());
    for(auto& texture : textures){
      cast<Texture>(texture).lock()->getImage()->save(serializer);
    }
    for(auto& staticMesh : staticMeshes){
      cast<StaticMesh>(staticMesh).lock()->save(serializer);
    }
    for(auto& material : materials){
      cast<Material>(material).lock()->save(serializer);
    }
    for(auto& model : models){
      cast<Model>(model).lock()->save(serializer);
    }
    m_worldScene->save(serializer);
  }
  if(ImGui::Button("load"))
  {
    Serializer serializer;
    serializer.init(m_projectPath.string()+"/"+"OasisEngineTestProject.oa",false);
    auto numOfResources = serializer.decodeSize();
    for(auto i = 0; i < numOfResources; ++i)
    {
      int type = serializer.decodeNumber();
      Serializer localSerializer;
      Path resourceFile = serializer.decodeString();
      localSerializer.init(resourceFile,false);
      if(type == RESOURSE_TYPE::kImage){
        auto image = makeSPtr<Image>();
        image->setName(resourceFile.stem().string());
        image->load(localSerializer);
        SPtr<Texture> texture = GraphicAPI::instance().createTexture();
        texture->initFromImage(image);
        resourceManager.registerResourse(texture->getName(),texture);
      }
      else if(type == RESOURSE_TYPE::kStaticMesh){
        auto staticMesh = makeSPtr<StaticMesh>();
        staticMesh->setName(resourceFile.stem().string());
        staticMesh->load(localSerializer);
        resourceManager.registerResourse(staticMesh->getName(),staticMesh);
      }
      else if(type == RESOURSE_TYPE::kMaterial){
        auto material = makeSPtr<Material>();
        material->setName(resourceFile.stem().string());
        material->load(localSerializer);
        resourceManager.registerResourse(material->getName(),material);
      }
      else if(type == RESOURSE_TYPE::kModel){
        auto model = makeSPtr<Model>();
        model->setName(resourceFile.stem().string());
        model->load(localSerializer);
        resourceManager.registerResourse(model->getName(),model);
      }
    }
    Serializer localSerializer;
    localSerializer.init(m_projectPath.string()+"/"+"scene.oa",false);
    m_worldScene->load(localSerializer);
  }
  ImGui::End();

  if(textureInspector){
    ImGui::Begin("texture inspector");
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("changeName")){
      resourceManager.changeName(m_selectedTexture.lock()->getImage()->getName(),imguiString);
    }
    if(ImGui::Button("delete")){
      resourceManager.deleteResourse(m_selectedTexture.lock()->getName());
      textureInspector = false;
    }
    if(ImGui::Button("close")){
      textureInspector = false;
    }
    ImGui::End();
  }

  if(m_actualScene.lock() == m_meshScene){
    ImGui::Begin("mesh inspector");{
      ImGui::InputText("name",imguiString,64);
      if(ImGui::Button("changeName")){
        resourceManager.changeName(m_selectedMesh.lock()->getName(),imguiString);
      }
      if(ImGui::Button("delete")){
        resourceManager.deleteResourse(m_selectedMesh.lock()->getName());
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene;
      }
      if(ImGui::Button("close")){
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene;
      }
      
    }
    ImGui::End();
  }

  if(m_actualScene.lock() == m_materialScene){
    ImGui::Begin("material editor");{
     
      auto selectedMaterial = m_selectedMaterial.lock();

      ImGui::InputText("name",imguiString,64);
      if(ImGui::Button("changeName")){
        resourceManager.changeName(selectedMaterial->getName(),imguiString);
      }

      ImGui::Combo("cooling",reinterpret_cast<int*>(&selectedMaterial->m_culling),"none\0front\0back");

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
      if(ImGui::Button("delete")){
        resourceManager.deleteResourse(m_selectedMaterial.lock()->getName());
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene;
      }
      if(ImGui::Button("close")){
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene;
      }
    }
    ImGui::End();
  }

  if(m_actualScene.lock() == m_modelScene){
    ImGui::Begin("model inspector");{
      ImGui::InputText("name",imguiString,64);
      auto model = m_selectedModel.lock();
      if(ImGui::Button("changeName")){
        resourceManager.changeName(model->getName(),imguiString);
      }
      ImGui::Text("material");
      if(!model->getMaterial().expired() && ImGui::Button(model->getMaterial().lock()->getName().c_str(),ImVec2(100,100))){
        model->setMaterial(m_selectedMaterial);
      }
      ImGui::Text("mesh");
      if(!model->getMesh().expired() && ImGui::Button(model->getMesh().lock()->getName().c_str(),ImVec2(100,100))){
        model->setMesh(m_selectedMesh);
      }
      if(ImGui::Button("delete")){
        resourceManager.deleteResourse(m_selectedModel.lock()->getName());
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene.lock();
      }
      if(ImGui::Button("close")){
        m_actualScene = m_worldScene;
        m_selectedActor = m_actualScene.lock();
      }
      
    }
    ImGui::End();
  }

  if(isAddingActor)
  {
    ImGui::Begin("actor to add");
    for(auto actor : m_actors){
      if(ImGui::Button(actor.c_str(),ImVec2(100,100))){
        Serializer serializer;
        serializer.init(m_projectPath.string()+"/"+actor+".oa",false);
        auto newActor = makeSPtr<Actor>();
        newActor->setName(actor+"_");
        newActor->load(serializer);
        m_selectedActor.lock()->attach(newActor);
      }
    }
    ImGui::End();
  }
  //ImGui::Begin("crowds");
  //
  //if(ImGui::Button("crowd test")){
  //  cw = cwSDKtoolkit::CrowdSimulator::create<cwSDKtoolkit::SpatialPartition>();
  //  auto& resourses = ResoureManager::instance();
  //  agent = makeSPtr<Actor>();
  //  agent->setName("agent");
  //  //m_selectedActor.lock()->attach(agent);
  //  loader = new Loader;
  //  loader->loadResource("C:/Users/roriv/Downloads/r2d2-lowpoly/source/r2d2 lowpoly/r2d2 lowpoly.obj",agent);
  //  delete loader;
  //  loader = 0;
  //  
  //}
  //
  //ImGui::DragInt("number of agents",&numOfAgents);
  //
  //if(ImGui::Button("cirlce")){
  //  float population = numOfAgents;
  //  float angle = 3.14159265358979323846f*2.f/population;
  //  SPtr<Actor> newAgent ;
  //  for(float i = 0; i<population;++i){
  //    newAgent =makeSPtr<Actor>();
  //    newAgent->setName("agent"+StringUtilities::intToString(i));
  //    m_selectedActor.lock()->attach(newAgent);
  //    auto comp = makeSPtr<StaticMeshComponent>();
  //    comp->setModel(cast<StaticMeshComponent>(agent->getComponent<StaticMeshComponent>().lock())->getModel());
  //    newAgent->attachComponent(comp);
  //    newAgent->setActorLocation(Vector3f(std::cos(angle*i)*3.f*float(numOfAgents),0.0f,std::sin(angle*i)*3.f*float(numOfAgents)));
  //    cw->addAgent<TestAgent>(cwSDKtoolkit::Vector2f(std::cos(angle*i)*3.f*float(numOfAgents),std::sin(angle*i)*3.f*float(numOfAgents)),cwSDKtoolkit::Vector2f(-std::cos(angle*i)*3.f*float(numOfAgents),-std::sin(angle*i)*3.f*float(numOfAgents)));
  //    agents.push_back(newAgent);
  //  }
  //  newAgent->attachComponent(makeSPtr<DirectionalLightComponent>());
  //}
  //
  //if(ImGui::Button("random")){
  //  float dist = sqrtf(numOfAgents)*12.f;
  //  auto positions = scatter(numOfAgents,{-dist,-dist},{dist,dist});
  //  for(int i = 0;i<6;++i){
  //    positions = blueNoise(positions,12);
  //  }
  //  
  //  SPtr<Actor> newAgent;
  //  for(float i = 0; i<numOfAgents;++i){
  //    newAgent =makeSPtr<Actor>();
  //    newAgent->setName("agent"+StringUtilities::intToString(i));
  //    m_selectedActor.lock()->attach(newAgent);
  //    auto comp = makeSPtr<StaticMeshComponent>();
  //    comp->setModel(cast<StaticMeshComponent>(agent->getComponent<StaticMeshComponent>().lock())->getModel());
  //    newAgent->attachComponent(comp);
  //    newAgent->setActorLocation(Vector3f(positions[i].x,0.0f,positions[i].y));
  //    cw->addAgent<WanderAgent>(cwSDKtoolkit::Vector2f(positions[i].x,positions[i].y),cwSDKtoolkit::Vector2f(cwSDKtoolkit::Vector2f(positions[i].x,positions[i].y)));
  //    agents.push_back(newAgent);
  //  }
  //  newAgent->attachComponent(makeSPtr<DirectionalLightComponent>());
  //}
  //
  //if(ImGui::Button("step")){
  //  cw->update(.25f);
  //  for(int i = 0; i<numOfAgents;++i){
  //    auto point = cw->getPosition(i);
  //    agents[i].lock()->setActorLocation(Vector3f(point.x,0.0f,point.y));
  //  }
  //}
  //
  //ImGui::End();
}

}


