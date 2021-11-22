#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include "oaVector3f.h"
#include "oaInputManager.h"
#include <Windows.h>
#include<iostream>

namespace oaEngineSDK{

using foo = const void* (*)();

void BaseApp::onShutDown()
{
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputManager::shutDown();
  postShutDown();
}

void
BaseApp::run()
{
  loadPlugIn("oaDX11Graphicsd.dll");
  //loadPlugIn("oaDX11Graphics.dll");
  //loadPlugIn("oaOGL_Grafics.dll");
  if (!GraphicAPI::isStarted()) {
    GraphicAPI::startUp();
  }
  preInit();
  if(GraphicAPI::instancePtr()->initialize()){

    ResoureManager::startUp();
    InputManager::startUp();

    postInit();
    mainLoop();
  }
}

void BaseApp::postInit()
{
  ResoureManager::startUp();
}

void BaseApp::loadPlugIn(String DLL)
{
#if OA_PLATFORM == OA_PLATFORM_WIN32
  HINSTANCE hGetProcIDDLL = LoadLibrary(DLL.c_str());
  if(!hGetProcIDDLL)
  {
    std::cout << "Could not load Dll" << std::endl;
    return;
  }

  foo function = (foo)GetProcAddress(hGetProcIDDLL, "initPlugIn");
  if(!function())
  {
    std::cout << "Could not find function" << std::endl;
    return;
  }
  std::cout << "everything working" << std::endl;
#endif
}

void
BaseApp::mainLoop()
{
  auto start = std::chrono::high_resolution_clock::now();
  while(isRunning){

    auto end = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(end - start).count();
    start = std::chrono::high_resolution_clock::now();

    GraphicAPI::instancePtr()->events();

    update(dt);

    render();


  }
}

void BaseApp::render()
{
  //GraphicAPI::instancePtr()->clear();
  draw();
  GraphicAPI::instancePtr()->show();
}

}
