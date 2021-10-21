#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>
#include "oaVector3f.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

void TestApp::run()
{
  //loadPlugIn("oaDX11Graphics.dll");
  loadPlugIn("oaOGL_Grafics.dll");
  BaseApp::run();
}

void TestApp::postInit()
{
  GraphicAPI::instancePtr()->setBackgroundColor({ 0.0f, 0.125f, 0.3f, 1.0f });

  std::cout<<"load triangle"<<std::endl;
  ResoureManager::startUp();

  ResoureManager::instancePtr()->meshes.push_back(newSPtr<Mesh>());

  ResoureManager::instancePtr()->meshes[0]->vertices = 
  {
    Vertex{Vector3f( 0.0f, 0.5f, 0.5f ),Vector2f(.5f,1)},
    Vertex{Vector3f( 0.5f, -0.5f, 0.5f ),Vector2f(1,0)},
    Vertex{Vector3f( -0.5f, -0.5f, 0.5f ),Vector2f(0,0)},
  };

  ResoureManager::instancePtr()->meshes[0]->create();

  ResoureManager::instancePtr()->loadTexture("textures/wall.jpg");

}

void TestApp::render()
{
  BaseApp::render();
}

}




