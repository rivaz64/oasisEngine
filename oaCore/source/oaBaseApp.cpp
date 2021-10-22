#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include "oaVector3f.h"
#include <Windows.h>
#include<iostream>

namespace oaEngineSDK{

using foo = const void* (*)();

void BaseApp::onShutDown()
{
  ResoureManager::shutDown();
}

void
BaseApp::run()
{
  if(GraphicAPI::instancePtr()->initialize()){
    postInit();
    mainLoop();
  }

  GraphicAPI::instancePtr()->shutDown();
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
  while(GraphicAPI::instancePtr()->isRunning()){

    GraphicAPI::instancePtr()->events();

    render();
  }
}

void BaseApp::render()
{
  /*for(SPtr<Mesh>& m : ResoureManager::instancePtr()->meshes){
    m->render();
  }*/
  GraphicAPI::instancePtr()->show();
}

}
