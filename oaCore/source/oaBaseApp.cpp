#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include "oaVector3f.h"
#include <Windows.h>
#include<iostream>

namespace oaEngineSDK{

using foo = const void* (*)();

void 
BaseApp::run()
{
  //loadPlugIn("oaDX11Graphics.dll");
  if(GraphicAPI::instancePtr()->initialize()){
    postInit();
    mainLoop();
  }
  
  GraphicAPI::shutDown();
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

    //deltaTime += 

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
