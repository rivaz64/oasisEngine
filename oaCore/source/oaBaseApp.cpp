#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include <Windows.h>
#include<iostream>

using foo = const void* (*)();

void oaEngineSDK::BaseApp::run()
{
#if OA_PLATFORM == OA_PLATFORM_WIN32
  HINSTANCE hGetProcIDDLL = LoadLibrary("oaDX11Graphics.dll");
  if(!hGetProcIDDLL)
  {
    std::cout << "Could not load Dll" << std::endl;
    return;
  }
#endif
  /*GraphicAPI::startUp();
  GraphicAPI::instancePtr()->initialize();
  GraphicAPI::shutDown();*/
}
