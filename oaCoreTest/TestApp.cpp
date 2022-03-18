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
#include <oaShaderProgram.h>
#include <oaResoureManager.h>
#include <oaScene.h>
#include <oaRasterizer.h>
#include <oaRenderer.h>
#include <oaCameraComponent.h>
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <oaSerializer.h>




extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace oaEngineSDK {

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;

  BaseApp* app = reinterpret_cast<BaseApp*>(GetWindowLongPtr(hWnd, 0));

  if(ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;

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
    app->processInputs(wParam);
    break;
    
  //case WM_NCCREATE:
    
    //break;

  default:
    
    return DefWindowProc( hWnd, message, wParam, lParam );
  }

  return 0;
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

  IMGUI_CHECKVERSION();

  initImGui();

  graphicAPI.setBackgroundColor(Color::OCEAN);

  //ResoureManager::instancePtr()->loadTexture(Path("textures/wall.jpg"));

  m_actualScene = makeSPtr<Scene>();

  m_actualScene->init();

  m_selectedActor = m_actualScene->getRoot();

  graphicAPI.initTest();

  graphicAPI.setPrimitiveTopology(oaEngineSDK::PRIMITIVE_TOPOLOGY::kTrianlgeList);
}


void 
TestApp::onUpdate(float delta)
{ 
  auto& inputManager = InputManager::instance();

  if(m_controlledActor){
    if (inputManager.getInput(VK_RBUTTON))
    {
      m_controlledActor->getComponent<CameraComponent>()->
        getCamera()->rotateWithMouse(inputManager.getMouseDelta());
    }
  }
  else{
    if (inputManager.getInput(VK_RBUTTON))
    {
      m_camera->rotateWithMouse(inputManager.getMouseDelta());
    }

    m_camera->update();
  }
  
}

void 
TestApp::draw()
{
  auto& graphicsAPI = GraphicAPI::instance();

  auto& resourseManager = ResoureManager::instance();
   
  graphicsAPI.setSamplerState(m_samplerState);
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
    renderer.render(m_actualScene,m_camera,m_camera,m_light);
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
      auto graphicsComponent = cast<GraphicsComponent>(component);
      if(ImGui::Button("select model") && m_selectedModel.get()){
        graphicsComponent->setModel(m_selectedModel);
      }
      auto& model = graphicsComponent->getModel();
      if(model){
        ImGui::Text(model->getName().c_str());
        auto& transform = graphicsComponent->getTransform();
        ImGui::DragFloat3("location Model",&transform.getLocation().x);
        ImGui::DragFloat3("scale Model",&transform.getScale().x);
        ImGui::DragFloat3("rotation Model",&transform.getRotation().x);
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

    component = m_selectedActor->getComponent<CameraComponent>();

    if (component && ImGui::CollapsingHeader("camera")){
      auto cameraComponent = cast<CameraComponent>(component);
      if(ImGui::Button("view from this")){
        if(m_controlledActor == m_selectedActor){
          m_controlledActor = SPtr<Actor>();
        }
        else{
          m_controlledActor = m_selectedActor;
        }
      }

      ImGui::Checkbox("debug",&cameraComponent->m_debug);
      if(cameraComponent->m_debug){
        m_debugCamera = cameraComponent->getCamera();
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

  ImGui::Begin("lights");
  ImGui::DragFloat3("direction",&m_light.x,.01f,-1.0f,1.0f);
  //ImGui::DragFloat("paralax",&dir.w,1.0f);
  ImGui::End();

  if(isCreatingActor){
    ImGui::Begin("new Actor");
    ImGui::InputText("name",imguiString,64);
    if(ImGui::Button("create")){
      auto actor = makeSPtr<Actor>();
      actor->setName(imguiString);
      m_selectedActor->attach(actor);
      isCreatingActor = false;
    }
    ImGui::End();
  }

  if(isAddingComponent){
    ImGui::Begin("add component");
    if(ImGui::Button("Graphics")){
      m_selectedActor->attachComponent(makeSPtr<GraphicsComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Skeletal")){
      m_selectedActor->attachComponent(makeSPtr<SkeletalComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Animation")){
      m_selectedActor->attachComponent(makeSPtr<AnimationComponent>());
      isAddingComponent = false;
    }

    if(ImGui::Button("Camera")){
      m_selectedActor->attachComponent(makeSPtr<CameraComponent>());
      m_selectedActor->getComponent<CameraComponent>()->setCamera(makeSPtr<Camera>());

      m_selectedActor->getComponent<CameraComponent>()->getCamera()->init(
        static_cast<float>(m_windowSize.y)/static_cast<float>(m_windowSize.x)
      );

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

      serializer.encodeNumber(resourceManager.m_textures.size());
      for(auto& image: resourceManager.m_textures){
        serializer.encodeImage(image.second->getimage());
      }

      serializer.encodeNumber(resourceManager.m_materials.size());
      for(auto& material: resourceManager.m_materials){
        serializer.encodeMaterial(material.second);
      }
      
      serializer.encodeNumber(resourceManager.m_models.size());
      for(auto& model: resourceManager.m_models){
        serializer.encodeModel(model.second);
      }

    }
  }

  if(ImGui::Button("load")){
    Serializer serializer;
    Path path;
    if(path.searchForPath()){
      serializer.init(path);

      SIZE_T number = serializer.decodeNumber();
      for(SIZE_T textureNum = 0; textureNum<number; ++textureNum){
        auto image = serializer.decodeImage();
        SPtr<Texture> texture = GraphicAPI::instance().createTexture();
        texture->initFromImage(image);
        ResoureManager::instance().m_textures.insert({ texture->getName(),texture});
      }

      number = serializer.decodeNumber();
      for(SIZE_T materialNum = 0; materialNum<number; ++materialNum){
        auto material = serializer.decodeMaterial();
        ResoureManager::instance().m_materials.insert({ material->getName(),material});
      }
      
      number = serializer.decodeNumber();
      for(SIZE_T modelNum = 0; modelNum<number; ++modelNum){
        auto model = serializer.decodeModel();
        ResoureManager::instance().m_models.insert({ model->getName(),model});
      }
    }
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

void 
TestApp::onKeyBoardInput(char input)
{
  if(!m_controlledActor){
    switch (input)
    {
    case 'A':
      m_camera->moveCamera(Vector3f(-m_secondPerFrame,0,0));
      break;

    case 'D':
      m_camera->moveCamera(Vector3f(m_secondPerFrame,0,0));
      break;

    case 'W':
      m_camera->moveCamera(Vector3f(0,0,m_secondPerFrame));
      break;

    case 'S':
      m_camera->moveCamera(Vector3f(0,0,-m_secondPerFrame));
      break;

    case 'Q':
      m_camera->moveCamera(Vector3f(0,m_secondPerFrame,0));
      break;

    case 'E':
      m_camera->moveCamera(Vector3f(0,-m_secondPerFrame,0));
      break;

    default:
      break;
    }
  }
  else{
    switch (input)
    {
    case 'A':
      m_controlledActor->GetActorTransform().move(Vector3f(-m_secondPerFrame,0,0));
      break;

    case 'D':
      m_controlledActor->GetActorTransform().move(Vector3f(m_secondPerFrame,0,0));
      break;

    case 'W':
      m_controlledActor->GetActorTransform().move(Vector3f(0,0,m_secondPerFrame));
      break;

    case 'S':
      m_controlledActor->GetActorTransform().move(Vector3f(0,0,-m_secondPerFrame));
      break;

    case 'Q':
      m_controlledActor->GetActorTransform().move(Vector3f(0,m_secondPerFrame,0));
      break;

    case 'E':
      m_controlledActor->GetActorTransform().move(Vector3f(0,-m_secondPerFrame,0));
      break;

    default:
      break;
    }
  }
  
}

}




