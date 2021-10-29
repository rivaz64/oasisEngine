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
    Vertex{ Vector3f( -1.0f, 1.0f, -1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, -1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, 1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, 1.0f, 1.0f ), Vector2f( 0.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, -1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, -1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, 1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, 1.0f ), Vector2f( 0.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, 1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, -1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( -1.0f, 1.0f, -1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, 1.0f, 1.0f ), Vector2f( 0.0f, 1.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, 1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, -1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, -1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, 1.0f ), Vector2f( 0.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, -1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, -1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, -1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, 1.0f, -1.0f ), Vector2f( 0.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, -1.0f, 1.0f ), Vector2f( 0.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, -1.0f, 1.0f ), Vector2f( 1.0f, 0.0f ) },
    Vertex{ Vector3f( 1.0f, 1.0f, 1.0f ), Vector2f( 1.0f, 1.0f ) },
    Vertex{ Vector3f( -1.0f, 1.0f, 1.0f ), Vector2f( 0.0f, 1.0f ) },
  };

  ResoureManager::instancePtr()->meshes["triangle"]->index = {
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

  ResoureManager::instancePtr()->meshes["triangle"]->create();

  

  ResoureManager::instancePtr()->loadTexture("textures/wall.jpg");

  ResoureManager::instancePtr()->models.insert({"triangle",newSPtr<Model>()});

  ResoureManager::instancePtr()->models["triangle"]->textures.
    push_back(ResoureManager::instancePtr()->textures["textures/wall.jpg"]);
  ResoureManager::instancePtr()->models["triangle"]->meshes.
    push_back(ResoureManager::instancePtr()->meshes["triangle"]);


  character = newSPtr<Object>();

  character->model = newSPtr<Model>();

  character->model->loadFromFile("models/youarenotmandalorian.fbx");

  cam = newSPtr<Camera>();

  cam->angle = 0.785398163f;
  cam->ratio =(float)GraphicAPI::instancePtr()->windowWidth /  (float)GraphicAPI::instancePtr()->windowHeight;
  cam->nearPlane = 0.0f;
  cam->farPlane = 100.0f;

 
}


void TestApp::update()
{
  character->update();
}

void oaEngineSDK::TestApp::draw()
{
  ImGui::SetCurrentContext((ImGuiContext*)GraphicAPI::instancePtr()->getImGui());
  GraphicAPI::instancePtr()->newImGuiFrame();
  

  ImGui::Begin("test");
  ImGui::DragFloat3("location",&character->location.x,.01f);
  ImGui::DragFloat3("scale",&character->scale.x,.01f);
  ImGui::DragFloat3("rotation",&character->rotation.x,.01f);
  ImGui::End();

  GraphicAPI::instancePtr()->setBuffer(character->transformB,0);

  cam->setCamera();

  /*GraphicAPI::instancePtr()->setTexture(
  ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );*/
  
  for(uint32 i = 0; i<character->model->meshes.size();++i){
    GraphicAPI::instancePtr()->setVertexBuffer(
      character->model->meshes[i]->vertexB
    );

    GraphicAPI::instancePtr()->setIndexBuffer(
      character->model->meshes[i]->indexB
    );

    GraphicAPI::instancePtr()->draw(character->model->meshes[i]->index.size());

  
  }
  
}

}




