#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>
#include "oaVector3f.h"
#include "oaGraphicAPI.h"
#include "oaModel.h"
#include "oaSamplerState.h"
#include "oaShader.h"
#include "oaInputManager.h"
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

oaEngineSDK::TestApp* app = nullptr;

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;
  if(ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;
  
  
  //std::cout<<wParam<<std::endl;
  
  

  switch( message )
  {
  case WM_PAINT:
    hdc = BeginPaint( hWnd, &ps );
    EndPaint( hWnd, &ps );
    break;

  case WM_QUIT:
    app->isRunning = false;
    break;

  case WM_DESTROY:
    app->isRunning = false;
    PostQuitMessage( 0 );
    break;


  default:
    return DefWindowProc( hWnd, message, wParam, lParam );
  }

  return 0;
}

namespace oaEngineSDK {

void TestApp::postShutDown()
{
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
  }

  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::OPENGL) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
  }

  ImGui::DestroyContext();
}

void TestApp::preInit()
{

  app = this;

  GraphicAPI::instancePtr()->eventsFunction = WindowProc;
  
}

void TestApp::postInit()
{

  InputManager::instancePtr()->addInput('W');
  InputManager::instancePtr()->addInput('S');
  InputManager::instancePtr()->addInput('A');
  InputManager::instancePtr()->addInput('D');
  InputManager::instancePtr()->addInput('E');
  InputManager::instancePtr()->addInput('Q');
  InputManager::instancePtr()->addInput(VK_RBUTTON);

  ResoureManager::instancePtr()->generateCircle(36);

  ResoureManager::instancePtr()->generatePiramid(36);

  ResoureManager::instancePtr()->generateCilinder(36);


  SamplerDesc sampDesc;
  ZeroMemory( &sampDesc, sizeof(sampDesc) );
  sampDesc.filter = FILTER::MIN_MAG_MIP_LINEAR;
  sampDesc.addressU = TEXTURE_ADDRESS_MODE::WRAP;
  sampDesc.addressV = TEXTURE_ADDRESS_MODE::WRAP;
  sampDesc.addressW = TEXTURE_ADDRESS_MODE::WRAP;
  sampDesc.comparison = COMPARISON_FUNC::NEVER;
  sampDesc.minLOD = 0.0f;
  sampDesc.maxLOD = Math::MAX_FLOAT;
  samsta = GraphicAPI::instancePtr()->createSamplerState(sampDesc);

  render = GraphicAPI::instancePtr()->createRenderTarget(GraphicAPI::instancePtr()->getBackBuffer());



  

  TextureDesc descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.width = GraphicAPI::instancePtr()->windowWidth;
  descDepth.height = GraphicAPI::instancePtr()->windowHeight;
  descDepth.mipLevels = 1;
  descDepth.arraySize = 1;
  descDepth.format = FORMAT::D24_UNORM_S8_UINT;
  descDepth.sampleCount = 1;
  descDepth.sampleQuality = 0;
  descDepth.bind = BIND::DEPTH_STENCIL;

  auto depthStencil = GraphicAPI::instancePtr()->createTexture();

  if(!depthStencil->init(descDepth)){
    return;
  }


  TextureDesc renDesc;
  ZeroMemory( &renDesc, sizeof(renDesc) );
  renDesc.width = GraphicAPI::instancePtr()->windowWidth;
  renDesc.height = GraphicAPI::instancePtr()->windowHeight;
  renDesc.mipLevels = 1;
  renDesc.arraySize = 1;
  renDesc.format = FORMAT::R32G32B32A32_FLOAT;
  renDesc.sampleCount = 1;
  renDesc.sampleQuality = 0;
  renDesc.bind = BIND::SHADER_RESOURCE_RENDER_TARGET;

  ShaderResourseViewDesc renSDesc;
  renSDesc.dimencion = SRV_DIMENSION::TEXTURE2D;
  renSDesc.format = FORMAT::R32G32B32A32_FLOAT;
  renSDesc.mipLevels = 1;
  renSDesc.mostDetailedMip = 0;

  renTex = GraphicAPI::instancePtr()->createTexture();

  if(!renTex->init(renDesc,renSDesc)){
    return;
  }
  
  renderToTexture = GraphicAPI::instancePtr()->createRenderTarget(renTex);

  DepthStencilDesc descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.format = descDepth.format;
  descDSV.viewDimension = DS_DIMENSION::TEXTURE2D;
  descDSV.MipSlice = 0;

  depthStencilView = GraphicAPI::instancePtr()->createDepthStencil(descDSV,depthStencil);

  GraphicAPI::instancePtr()->setRenderTargetAndDepthStencil(render,depthStencilView);

  vertexShader = GraphicAPI::instancePtr()->createVertexShader();

  pixelShader = GraphicAPI::instancePtr()->createPixelShader();

  vertexShader->compileFromFile("shader");

  pixelShader->compileFromFile("shader");

  vertexShader->set();

  pixelShader->set();

  //GraphicAPI::instancePtr()->compileShaders("noTextureShader");

  IMGUI_CHECKVERSION();

  initImGui();

  GraphicAPI::instancePtr()->setBackgroundColor({ 0.0f, 0.125f, 0.3f, 1.0f });

  

  



  ResoureManager::instancePtr()->loadTexture("textures/wall.jpg");

  ResoureManager::instancePtr()->models.insert({ "triangle",newSPtr<Model>() });

  ResoureManager::instancePtr()->models["triangle"]->textures.
    push_back(ResoureManager::instancePtr()->textures["textures/wall.jpg"]);
  ResoureManager::instancePtr()->models["triangle"]->meshes.
    push_back(ResoureManager::instancePtr()->meshes["triangle"]);


  character = newSPtr<Object>();

  character->model = newSPtr<Model>();

  //character->model->loadFromFile("models/Shooting Gun.fbx");

  character->location.y = -2.f;
  character->location.z = 7.f;

  character->scale.x = .1f;
  character->scale.y = .1f;
  character->scale.z = .1f;

  character->rotation.y = 3.4f;




  testObject = newSPtr<Object>();

  testObject->model = newSPtr<Model>();

  testObject->location.z = 7.f;

  testObject->model->meshes.push_back(
    ResoureManager::instancePtr()->meshes["cilinder"]
  );
  
  testObject->model->textures.push_back(
    ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );


  cam = newSPtr<Camera>();

  cam->angle = 0.785398163f;
  cam->ratio = (float)GraphicAPI::instancePtr()->windowWidth / (float)GraphicAPI::instancePtr()->windowHeight;
  cam->nearPlane = 0.01f;
  cam->farPlane = 100.0f;

  cam->updateView();

  cam->updateProyection();

  scene = newSPtr<SceneGraph>();

  scene->addToScene(character);

  scene->cam = cam;

  character->attach(testObject);

  testObject->name = "test object";

  character->name = "character";

  actualObject = testObject;



}


void TestApp::update(float delta)
{
  character->update();
  testObject->update();
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
  


}

void TestApp::draw()
{
  //GraphicAPI::instancePtr()->setBuffer(character->transformB, 0);
  /*GraphicAPI::instancePtr()->setBuffer(character->transformB, 0);

  cam->setCamera();

  GraphicAPI::instancePtr()->setSamplerState(samsta);

  GraphicAPI::instancePtr()->setRenderTarget(renderToTexture);
  GraphicAPI::instancePtr()->clearRenderTarget(renderToTexture);
  GraphicAPI::instancePtr()->clearDepthStencil(depthStencilView);

  GraphicAPI::instancePtr()->setTexture(
  ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );

  GraphicAPI::instancePtr()->setVertexBuffer(
    ResoureManager::instancePtr()->models["triangle"]->meshes[0]->vertexB
  );

  GraphicAPI::instancePtr()->setIndexBuffer(
    ResoureManager::instancePtr()->models["triangle"]->meshes[0]->indexB
  );

  GraphicAPI::instancePtr()->draw(ResoureManager::instancePtr()->models["triangle"]->meshes[0]->index.size());

  */

  //GraphicAPI::instancePtr()->setRenderTarget(render);

  GraphicAPI::instancePtr()->clearRenderTarget(render);
  GraphicAPI::instancePtr()->clearDepthStencil(depthStencilView);

   

  GraphicAPI::instancePtr()->setSamplerState(samsta);
  
  scene->draw();

  //sceneGraph->drawObject(testObject);

  /*GraphicAPI::instancePtr()->setBuffer(character->transformB, 0);
  

  GraphicAPI::instancePtr()->setTexture(
    //renTex
    ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );

  GraphicAPI::instancePtr()->setVertexBuffer(
    ResoureManager::instancePtr()->meshes["cube"]->vertexB
  );

  GraphicAPI::instancePtr()->setIndexBuffer(
    ResoureManager::instancePtr()->meshes["cube"]->indexB
  );

  GraphicAPI::instancePtr()->draw(ResoureManager::instancePtr()->meshes["cube"]->index.size());//*/

  /*for (uint32 i = 0; i < character->model->meshes.size(); ++i) {
    GraphicAPI::instancePtr()->setVertexBuffer(
      character->model->meshes[i]->vertexB
    );

    GraphicAPI::instancePtr()->setIndexBuffer(
      character->model->meshes[i]->indexB
    );
    GraphicAPI::instancePtr()->setTexture(
      character->model->textures[i]
    );

    GraphicAPI::instancePtr()->draw(character->model->meshes[i]->index.size());
  }*/
   
  newImGuiFrame();
  drawImGui();
  renderImGui();

}

void TestApp::initImGui()
{
  if (GraphicAPI::instancePtr()->actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
  }
  
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplWin32_Init(GraphicAPI::instancePtr()->getWindow());
    ImGui_ImplDX11_Init(
      (ID3D11Device*)GraphicAPI::instancePtr()->getDevice(), 
      (ID3D11DeviceContext*)GraphicAPI::instancePtr()->getContext());
  }
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::OPENGL) {
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GraphicAPI::instancePtr()->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
  }
  

}

void TestApp::newImGuiFrame()
{
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
  }

  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::OPENGL) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
  }
  
  if (GraphicAPI::instancePtr()->actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::NewFrame();
  }
  
}

void TestApp::renderImGui()
{
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize.x = GraphicAPI::instancePtr()->windowWidth;
  io.DisplaySize.y = GraphicAPI::instancePtr()->windowHeight;
  
  if (GraphicAPI::instancePtr()->actualGraphicAPI != GRAPHIC_API::NONE) {
    ImGui::Render();
  }

  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::OPENGL) {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}

void oaEngineSDK::TestApp::drawImGui()
{
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::NONE) {
    return;
  }
  ImGui::Begin("objects");
  if(ImGui::Button("character")){
    actualObject = character;
  }
  if(ImGui::Button("test object")){
    actualObject = testObject;
  }
  ImGui::End();

  ImGui::Begin("transform");
  ImGui::DragFloat3("location", &actualObject->location.x, .01f);
  ImGui::DragFloat3("scale", &actualObject->scale.x, .01f);
  ImGui::DragFloat3("rotation", &actualObject->rotation.x, .01f);
  ImGui::End();
}

}




