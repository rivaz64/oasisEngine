#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>
#include "oaVector3f.h"
#include "oaGraphicAPI.h"
#include "oaModel.h"
#include "oaSamplerState.h"
#include "oaShader.h"
#include "oaInputManager.h"
#include "oaGrid2D.h"
#include "oaPerlinNoise2D.h"
#include "oaPerlinNoise3D.h"
#include "oaMaterial.h"
#include "oaGraphicsComponent.h"
#include "oaSkeletalComponent.h"
#include "oaAnimationComponent.h"
#include "oaDepthStencil.h"
#include "oaTexture.h"
#include "oaMesh.h"
#include "oaSimplexNoise.h"
#include "oaOctavesNoise.h"
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>


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
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
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

  IMGUI_CHECKVERSION();

  initImGui();

  GraphicAPI::instancePtr()->setBackgroundColor({ 0.0f, 0.125f, 0.3f, 1.0f });

  ResoureManager::instancePtr()->loadTexture("textures/wall.jpg");

  auto model1 = newSPtr<Model>();

  auto model2 = newSPtr<Model>();

  auto modelMC = newSPtr<Model>();

  //model->meshes.push_back(ResoureManager::instancePtr()->meshes["cube"]);

  ResoureManager::instancePtr()->materials["default"]->textures.push_back(
  ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );

  model1->materials.push_back(ResoureManager::instancePtr()->materials["default"]);

  model2->materials.push_back(ResoureManager::instancePtr()->materials["default"]);

  modelMC->materials.push_back(ResoureManager::instancePtr()->materials["default"]);

  testObject1 = newSPtr<Object>();

  testObject2 = newSPtr<Object>();

  testObject1->attachComponent(newSPtr<GraphicsComponent>());

  testObject2->attachComponent(newSPtr<GraphicsComponent>());

  testObject1->getComponent<GraphicsComponent>()->model = model1;

  testObject2->getComponent<GraphicsComponent>()->model = model2;



  testObjectMC = newSPtr<Object>();

  //testObjectMC->attachComponent(newSPtr<GraphicsComponent>());

  //testObjectMC->getComponent<GraphicsComponent>()->model = modelMC;

 

  /*character = newSPtr<Object>();

  //

  auto charmod = newSPtr<Model>();

  charmod->loadFromFile("models/Shooting Gun.fbx");

  //charmod->loadFromFile("models/youarenotmandalorian.fbx");

  character->setLocation({0.0f,-2.0f,7.0f});

  character->setScale({.1f,.1f,.1f});

  character->setRotation({0.0f,3.4f,0.0f});

  character->attachComponent(newSPtr<GraphicsComponent>());

  character->getComponent<GraphicsComponent>()->model = charmod;

  character->attachComponent(newSPtr<SkeletalComponent>());

  character->getComponent<SkeletalComponent>()->skeleton = 
  ResoureManager::instancePtr()->skeletons["Shooting Gun"];

  character->attachComponent(newSPtr<AnimationComponent>());

  character->getComponent<AnimationComponent>()->animation = 
  ResoureManager::instancePtr()->animations["Shooting Gun"];

  testObject = newSPtr<Object>();

  ResoureManager::instancePtr()->models.insert({"test",newSPtr<Model>()});

  ResoureManager::instancePtr()->models["test"]->meshes.push_back(
    ResoureManager::instancePtr()->meshes["cube"]
  );

  ResoureManager::instancePtr()->models["test"]->materials.push_back(
    ResoureManager::instancePtr()->materials["default"]
  );

  auto model = newSPtr<Model>();

  testObject->setLocation({0.0f,0.0f,7.f});

  model->meshes.push_back(
    ResoureManager::instancePtr()->meshes["torus"]
  );
  
  model->materials.push_back(
    ResoureManager::instancePtr()->materials["default"]
  );


  

  scene = newSPtr<Object>();

  //scene->cam = cam;

  //scene->attach(testObject);

  scene->attach(character);

  //ResoureManager::instancePtr()->rendereableObjects.push_back(testObject);

  //testObject->attachComponent(newSPtr<GraphicsComponent>());

  //testObject->getComponent<GraphicsComponent>()->model = model;


  //character->attach(testObject);

  testObject->name = "test object";

  character->name = "character";

  actualObject = testObject;

  auto mesh = newSPtr<GraphicsComponent>();

  mesh->model =  ResoureManager::instancePtr()->models["test"];

  */
  cam = newSPtr<Camera>();

  cam->angle = 0.785398163f;
  cam->ratio = (float)GraphicAPI::instancePtr()->windowWidth / (float)GraphicAPI::instancePtr()->windowHeight;
  cam->nearPlane = 1.0f;
  cam->farPlane = 100.0f;

  cam->updateView();

  cam->updateProyection();

  scene = newSPtr<Object>();

  scene->name = "scene";

   

  lights = GraphicAPI::instancePtr()->createBuffer();

  lights->init(sizeof(Vector4f)*2);
  
  chnk = newSPtr<Chunk>();

  mc = newSPtr<MarchingCubes>();

  pt1 = newSPtr<ProceduralTerrain>();
  pt2 = newSPtr<ProceduralTerrain>();

  Grid2D<float> chunck1({32u,32u});
  Grid2D<float> chunck2({32u,32u});

  noise1 = newSPtr<OctavesNoise>();
  noise2 = newSPtr<OctavesNoise>();

  Vector<float> amplitudes{1,.5,.25};

  cast<OctavesNoise>(noise1)->init(newSPtr<PerlinNoise2D>(),amplitudes);
  cast<OctavesNoise>(noise2)->init(newSPtr<PerlinNoise2D>(),amplitudes);

  /*chunck.setAt({0,0,0},1.f);
  chunck.setAt({1,0,0},-1.f);
  chunck.setAt({0,1,0},1.f);
  chunck.setAt({0,0,1},-1.f);
  chunck.setAt({1,1,0},-1.f);
  chunck.setAt({1,0,1},-1.f);
  chunck.setAt({0,1,1},-1.f);
  chunck.setAt({1,1,1},-1.f);*/



  //PerlinNoise3D::fillGrid(chunck,3);

  //PerlinNoise2D::fillGrid(chunck,7);
  //SimplexNoise::fillGrid(chunck,15);

  /*chnk->init(chunck);

  mc->init(chunck);*/

  noise1->fillGrid(chunck1,15);
  noise2->fillGrid(chunck2,15);

  noise1->redistribute(chunck1,2,-.125);
  noise2->redistribute(chunck2,1,-.125);

  pt1->init(chunck1);
  pt2->init(chunck2);

  auto testMesh = newSPtr<Mesh>();

 /* auto datos = icosahedron();

  datos = SubDivide(datos);
  datos = SubDivide(datos);
  datos = SubDivide(datos);

  for(auto& v : datos.points){
    v += v*.125*PerlinNoise3D::valueAt(v.xyz*.5+Vector3f(7,7,7));
  }

  testMesh->initFromSubMesh(datos);*/

  testObject1->getComponent<GraphicsComponent>()->model->meshes.push_back(pt1);

  testObject2->getComponent<GraphicsComponent>()->model->meshes.push_back(pt2);

  //testObjectMC->getComponent<GraphicsComponent>()->model->meshes.push_back(mc);

  testObject1->name = "octaves";

  testObject2->name = "vanilla";

  testObjectMC->name = "marching cube";

  scene->attach(testObject1);
  
  scene->attach(testObject2); 

  //scene->attach(testObjectMC); 
}


void TestApp::update(float delta)
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

  lights->update(&color.x);
}

void TestApp::draw()
{

  GraphicAPI::instancePtr()->clearRenderTarget(render);
  GraphicAPI::instancePtr()->clearDepthStencil(depthStencilView);

   

  GraphicAPI::instancePtr()->setSamplerState(samsta);
  
  cam->setCamera();

  //auto lista = ResoureManager::instancePtr()->rendereableObjects;

  auto seenObjects = cam->seeObjects(ResoureManager::instancePtr()->rendereableObjects);

  for(auto object : seenObjects){

   
    
    auto mat = object->getGlobalTransform();

    object->transformB->update(&mat);

    auto model = object->getComponent<GraphicsComponent>()->model;

    for(int i = 0;i<model->meshes.size();++i){

      model->materials[i]->set();

      GraphicAPI::instancePtr()->setVSBuffer(object->transformB, 0);

      GraphicAPI::instancePtr()->setPSBuffer(lights,0);

      auto actualMesh = model->meshes[i];

      actualMesh->vertexB->set();

      actualMesh->indexB->set();

      if(actualMesh->hasBones){
        actualMesh->bonesB->update(actualMesh->ofset.data());

        GraphicAPI::instancePtr()->setVSBuffer( actualMesh->bonesB,3);
      }
     

      GraphicAPI::instancePtr()->draw(actualMesh->indexNumber);
    }

  }
   
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
    //ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GraphicAPI::instancePtr()->getWindow(), true);
    //ImGui_ImplOpenGL3_Init("#version 130");
  }
  

}

void TestApp::newImGuiFrame()
{
  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::DIRECTX11) {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
  }

  if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::OPENGL) {
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
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
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

}

void oaEngineSDK::TestApp::drawImGui()
{
  /*if (GraphicAPI::instancePtr()->actualGraphicAPI == GRAPHIC_API::NONE) {
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
  */
  ImGui::Begin("transform");
  if(actualObject.get()){
    Vector3f vec = actualObject->getLocation();
    if(ImGui::DragFloat3("location", &vec.x, .01f)){
      actualObject->setLocation(vec);
    }
    vec = actualObject->getScale();
    if(ImGui::DragFloat3("scale", &vec.x, .01f)){
      actualObject->setScale(vec);
    }
    vec = actualObject->getRotation();
    if(ImGui::DragFloat3("rotation", &vec.x, .01f)){
      actualObject->setRotation(vec);
    };
  }
  
  ImGui::End();
  
  ImGui::Begin("textures");
  for(auto texture : ResoureManager::instancePtr()->textures){
    if(ImGui::ImageButton(texture.second->getId(),ImVec2(100,100))){
      actualTexture = texture.second;
    }
  }
  ImGui::End();

  ImGui::Begin("materials");
  for(auto material : ResoureManager::instancePtr()->materials){
    if(ImGui::Button(material.first.c_str(),ImVec2(100,100))){
      material.second->textures[0] = actualTexture;
    }
  }
  ImGui::End();

  ImGui::Begin("meshes");
  for(auto mesh : ResoureManager::instancePtr()->meshes){
    if(ImGui::Button(mesh.first.c_str(),ImVec2(100,100))){
      actualMesh = mesh.second;
    }
  }
  ImGui::End();
  
  ImGui::Begin("models");
  for(auto model : ResoureManager::instancePtr()->models){
    if(ImGui::Button(model.first.c_str(),ImVec2(100,100))){
      actualModel = model.second;
    }
  }
  ImGui::End();

  ImGui::Begin("objects");
  /*if(ImGui::Button("new object")){

  }*/
  childsInImgui(scene);
  ImGui::End();

  ImGui::Begin("lighs");
  ImGui::ColorPicker3("ambient",&color.x);
  ImGui::DragFloat3("direction",&dir.x,.01f,-1.0f,1.0f);
  ImGui::End();
}

void oaEngineSDK::TestApp::childsInImgui(SPtr<Object> parentObject)
{
  for(SPtr<Object> object : parentObject->getChilds()){
    if(ImGui::Button(object->name.c_str(),ImVec2(100,100))){
      actualObject = object;
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
  uint32 size = data.indices.size();
  SubMesh ans;
  for(int i = 0;i<size;i+=3){
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

    int actual = ans.points.size();

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




