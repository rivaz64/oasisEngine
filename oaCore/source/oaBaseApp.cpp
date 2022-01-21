/**
* @file oaBaseApp.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include "oaVector3f.h"
#include "oaInputManager.h"
#include "oaTime.h"
#include "oaObject.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaTexture.h"
#include "oaLogger.h"
#include <Windows.h>

namespace oaEngineSDK{

using foo = const void* (*)();

void BaseApp::onShutDown()
{
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputManager::shutDown();
  Time::shutDown();
  Logger::shutDown();
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
    Logger::startUp();
    Time::startUp();
    //Logger::instance().printFloats(3,3.1,2.7,1.4);
    OA_LOG("Some variable values: x: %f, y: %f",3.f,5.f);
    setWindow(GraphicAPI::instance().getWindow());

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

    update(actualScene);

    postUpdate(Time::instancePtr()->deltaTime);

    render();
  }
}

void 
BaseApp::update(SPtr<Object> object)
{
  object->update();
  auto& childs =  object->getChilds();
  for(auto child : childs){
    update(child);
  }
}

void 
BaseApp::render()
{
  //GraphicAPI::instancePtr()->clear();
  draw();
  GraphicAPI::instancePtr()->show();
}


void BaseApp::setWindow(void* window)
{
  auto& api = GraphicAPI::instance();

  api.setWindow(window);

  auto backBuffer = api.getBackBuffer();

  if(!backBuffer.get()){
    return;
  }

  finalRender = api.createRenderTarget(backBuffer);

  TextureDesc descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.width = api.windowWidth;
  descDepth.height = api.windowHeight;
  descDepth.mipLevels = 1;
  descDepth.arraySize = 1;
  descDepth.format = FORMAT::D24_UNORM_S8_UINT;
  descDepth.sampleCount = 1;
  descDepth.sampleQuality = 0;
  descDepth.bind = BIND::DEPTH_STENCIL;

  auto depthStencil = api.createTexture();

  if(!depthStencil->init(descDepth)){
    return;
  }

  DepthStencilDesc descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.format = descDepth.format;
  descDSV.viewDimension = DS_DIMENSION::TEXTURE2D;
  descDSV.MipSlice = 0;

  finalDepthStencil = api.createDepthStencil(descDSV,depthStencil);
}

void
BaseApp::resizeWindow(void* window)
{
  auto& api = GraphicAPI::instance();

  if(!api.isStarted() ){
    return;
  }
  api.unsetRenderTargetAndDepthStencil();

  if(finalRender.get())
  finalRender->release();

  if(finalDepthStencil.get())
  finalDepthStencil->release();
  
  setWindow(window);
  
}

}
