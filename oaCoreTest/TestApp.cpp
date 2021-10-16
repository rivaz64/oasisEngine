#include "TestApp.h"
#include "oaResoureManager.h"
#include <iostream>

namespace oaEngineSDK{

void TestApp::run()
{
  loadPlugIn("oaDX11Graphics.dll");
  //loadPlugIn("oaOGL_Grafics.dll");
  BaseApp::run();
}

void TestApp::postInit()
{
  std::cout<<"load triangle"<<std::endl;
  ResoureManager::instancePtr()->meshes.push_back(newSPtr<Mesh>());

  ResoureManager::instancePtr()->meshes[0]->vertices = 
  {
    Vertex{Vector3f( 0.0f, 0.5f, 0.5f )},
    Vertex{Vector3f( 0.5f, -0.5f, 0.5f )},
    Vertex{Vector3f( -0.5f, -0.5f, 0.5f )},
  };

  ResoureManager::instancePtr()->meshes[0]->create();
}

}


