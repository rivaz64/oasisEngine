#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include "oaVector3f.h"
#include "oaInputManager.h"
#include "oaTime.h"
#include <Windows.h>

namespace oaEngineSDK{

using foo = const void* (*)();

void BaseApp::onShutDown()
{
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputManager::shutDown();
  Time::shutDown();
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
    Time::startUp();

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
    print("Could not load Dll");
    return;
  }

  foo function = (foo)GetProcAddress(hGetProcIDDLL, "initPlugIn");
  if(!function())
  {
    print("Could not find function");
    return;
  }
  print("everything working");
#endif
}

void
BaseApp::mainLoop()
{
  
  while(isRunning){

    Time::instancePtr()->update();

    GraphicAPI::instancePtr()->events();

    update(Time::instancePtr()->deltaTime);

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
