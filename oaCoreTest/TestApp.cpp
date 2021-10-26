#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>
#include "oaVector3f.h"
#include "oaGraphicAPI.h"
#include "oaModel.h"

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

namespace oaEngineSDK{

void TestApp::run()
{
  loadPlugIn("oaDX11Graphics.dll");
  //loadPlugIn("oaOGL_Grafics.dll");
  BaseApp::run();
}

void TestApp::postInit()
{
  IMGUI_CHECKVERSION();
  

  GraphicAPI::instancePtr()->initImGui();
  

  GraphicAPI::instancePtr()->setBackgroundColor({ 0.0f, 0.125f, 0.3f, 1.0f });
  
  ResoureManager::startUp();

  ResoureManager::instancePtr()->meshes.insert({"triangle",newSPtr<Mesh>()});

  ResoureManager::instancePtr()->meshes["triangle"]->vertices = 
  {
    Vertex{Vector3f( 0.0f, 0.5f, 0.5f ),Vector2f(.5f,1)},
    Vertex{Vector3f( 0.5f, -0.5f, 0.5f ),Vector2f(1,0)},
    Vertex{Vector3f( -0.5f, -0.5f, 0.5f ),Vector2f(0,0)},
  };

  ResoureManager::instancePtr()->meshes["triangle"]->create();

  

  ResoureManager::instancePtr()->loadTexture("textures/wall.jpg");

  ResoureManager::instancePtr()->models.insert({"triangle",newSPtr<Model>()});

  ResoureManager::instancePtr()->models["triangle"]->textures.
    push_back(ResoureManager::instancePtr()->textures["textures/wall.jpg"]);
  ResoureManager::instancePtr()->models["triangle"]->meshes.
    push_back(ResoureManager::instancePtr()->meshes["triangle"]);


  triangle = newSPtr<Object>();
  triangle->model = ResoureManager::instancePtr()->models["triangle"];

  cam = newSPtr<Camera>();

  cam->angle = 0.785398163f;
  cam->ratio =(float)GraphicAPI::instancePtr()->windowWidth /  (float)GraphicAPI::instancePtr()->windowHeight;
  cam->nearPlane = 0.0f;
  cam->farPlane = 100.0f;
}


void TestApp::update()
{
  triangle->update();
}

void oaEngineSDK::TestApp::draw()
{
  ImGui::SetCurrentContext((ImGuiContext*)GraphicAPI::instancePtr()->getImGui());
  GraphicAPI::instancePtr()->newImGuiFrame();
  

  ImGui::Begin("test");
  ImGui::DragFloat3("location",&triangle->location.x,.01f);
  ImGui::DragFloat3("scale",&triangle->scale.x,.01f);
  ImGui::DragFloat("rotation",&triangle->rotation.x,.01f);
  ImGui::End();


  GraphicAPI::instancePtr()->setVertexBuffer(
    ResoureManager::instancePtr()->meshes["triangle"]->vertexB
  );
  GraphicAPI::instancePtr()->setTexture(
    ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );
  GraphicAPI::instancePtr()->setBuffer(triangle->transformB,0);


  cam->setCamera();

  
}

}




