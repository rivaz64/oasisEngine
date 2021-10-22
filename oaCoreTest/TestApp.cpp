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

  //ResoureManager::instancePtr()->

}

void TestApp::render()
{
  BaseApp::render();
}

}




