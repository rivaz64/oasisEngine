#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>
#include "oaVector3f.h"
#include "oaGraphicAPI.h"
#include "oaModel.h"
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;
  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;

  switch( message )
  {
  case WM_PAINT:
    hdc = BeginPaint( hWnd, &ps );
    EndPaint( hWnd, &ps );
    break;

  case WM_DESTROY:
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
  GraphicAPI::instancePtr()->eventsFunction = WindowProc;
}

void TestApp::postInit()
{
  //std::cout<<"no graphic API"<<std::endl;
  GraphicAPI::instancePtr()->compileShaders("shader");

  IMGUI_CHECKVERSION();

  initImGui();

  GraphicAPI::instancePtr()->setBackgroundColor({ 0.0f, 0.125f, 0.3f, 1.0f });

  ResoureManager::startUp();

  ResoureManager::instancePtr()->meshes.insert({ "triangle",newSPtr<Mesh>() });

  ResoureManager::instancePtr()->meshes["triangle"]->vertices =
  {
    Vertex{ Vector3f(-1.0f, 1.0f, -1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, -1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, -1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, 1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, 1.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, 1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(-1.0f, 1.0f, -1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, 1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, -1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, -1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, -1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, -1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, 1.0f, -1.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, -1.0f, 1.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, -1.0f, 1.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f) },
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

  ResoureManager::instancePtr()->models.insert({ "triangle",newSPtr<Model>() });

  ResoureManager::instancePtr()->models["triangle"]->textures.
    push_back(ResoureManager::instancePtr()->textures["textures/wall.jpg"]);
  ResoureManager::instancePtr()->models["triangle"]->meshes.
    push_back(ResoureManager::instancePtr()->meshes["triangle"]);


  character = newSPtr<Object>();

  character->model = newSPtr<Model>();

  //character->model->loadFromFile("models/youarenotmandalorian.fbx");

  character->location.y = -2.f;
  character->location.z = 7.f;

  character->scale.x = .1f;
  character->scale.y = .1f;
  character->scale.z = .1f;

  character->rotation.y = 3.4f;

  cam = newSPtr<Camera>();

  cam->angle = 0.785398163f;
  cam->ratio = (float)GraphicAPI::instancePtr()->windowWidth / (float)GraphicAPI::instancePtr()->windowHeight;
  cam->nearPlane = 0.01f;
  cam->farPlane = 100.0f;


}


void TestApp::update()
{
  character->update();
}

void TestApp::draw()
{
  newImGuiFrame();

  drawImGui();
  

  GraphicAPI::instancePtr()->setBuffer(character->transformB, 0);

  cam->setCamera();

  /*GraphicAPI::instancePtr()->setTexture(
  ResoureManager::instancePtr()->textures["textures/wall.jpg"]
  );

  GraphicAPI::instancePtr()->setVertexBuffer(
    ResoureManager::instancePtr()->models["triangle"]->meshes[0]->vertexB
  );

  GraphicAPI::instancePtr()->setIndexBuffer(
    ResoureManager::instancePtr()->models["triangle"]->meshes[0]->indexB
  );

  GraphicAPI::instancePtr()->draw(ResoureManager::instancePtr()->models["triangle"]->meshes[0]->index.size());*/

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
  /*ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize.x = GraphicAPI::instancePtr()->windowWidth;
  io.DisplaySize.y = GraphicAPI::instancePtr()->windowHeight;*/
  
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
  ImGui::Begin("test");
  ImGui::DragFloat3("location", &character->location.x, .01f);
  ImGui::DragFloat3("scale", &character->scale.x, .01f);
  ImGui::DragFloat3("rotation", &character->rotation.x, .01f);
  ImGui::End();
}

}




