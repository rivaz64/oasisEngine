/**
* @file oaBaseApp.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#include "oaBaseApp.h"
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
#include <oaVector3f.h>
#include "oaInputManager.h"
#include "oaTime.h"
#include "oaActor.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaTexture.h"
#include "oaLogger.h"
#include "oaPath.h"
#include "oaCamera.h"
#include "oaScene.h"
#include <exception>
#include <Windows.h>

namespace oaEngineSDK{



using function = const void* (*)();

BaseApp::BaseApp()
  : m_windowName("Oasis Engine"), m_windowSize(800,600)
{

}

void 
BaseApp::onShutDown()
{
  onDestroy();
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputManager::shutDown();
  Time::shutDown();
  Logger::shutDown();
}

void
BaseApp::run()
{
  Logger::startUp();

  #ifdef _DEBUG
  loadPlugIn("oaDX11Graphicsd.dll");
  #else
  loadPlugIn("oaDX11Graphics.dll");
  #endif
  //loadPlugIn("oaDX11Graphics.dll");
  //loadPlugIn("oaOGL_Grafics.dll");

  if (!GraphicAPI::isStarted()) {
    GraphicAPI::startUp();
  }

  onInit();

   GraphicAPI::instance().createWindow(this,m_windowSize,m_windowName);

  if(GraphicAPI::instance().initialize()){

    ResoureManager::startUp();
    InputManager::startUp();
    Time::startUp();
    
    setWindow();

    m_camera = newSPtr<Camera>();
    m_camera->init();
    m_camera->update();

    postInit();

    try {
      mainLoop();
    }
    catch (...) {
      Logger::instance().flush();
      return;
    }
    Logger::instance().flush();

  }
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

  function foundFunction = reinterpret_cast<function>(GetProcAddress(hGetProcIDDLL, "initPlugIn"));
  if(!foundFunction())
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
  
  while(m_isRunning){

    Time::instancePtr()->update();

    GraphicAPI::instancePtr()->events();

    update(m_actualScene->getRoot());

    onUpdate(Time::instancePtr()->m_deltaTime);

    render();
  }
}

void 
BaseApp::update(SPtr<Actor> Actor)
{
  Actor->update();
  auto& childs =  Actor->getChilds();
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


void
BaseApp::setWindow()
{
  auto& api = GraphicAPI::instance();

  api.setWindow();

  auto backBuffer = api.getBackBuffer();

  if(!backBuffer.get()){
    return;
  }

  m_finalRender = api.createRenderTarget(backBuffer);

  TextureDesc descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.width = api.m_windowWidth;
  descDepth.height = api.m_windowHeight;
  descDepth.mipLevels = 1;
  descDepth.arraySize = 1;
  descDepth.format = FORMAT::kD24UNormS8UInt;
  descDepth.sampleCount = 1;
  descDepth.sampleQuality = 0;
  descDepth.bind = BIND::kDepthStencil;

  auto depthStencil = api.createTexture();

  if(!depthStencil->init(descDepth)){
    return;
  }

  DepthStencilDesc descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.format = descDepth.format;
  descDSV.viewDimension = DS_DIMENSION::kTexture2D;
  descDSV.MipSlice = 0;

  m_finalDepthStencil = api.createDepthStencil(descDSV,depthStencil);
}

void
BaseApp::resizeWindow()
{
  auto& api = GraphicAPI::instance();

  if(!api.isStarted() ){
    return;
  }
  api.unsetRenderTargetAndDepthStencil();

  if(m_finalRender.get()){
    m_finalRender->release();
  }

  if(m_finalDepthStencil.get()){
    m_finalDepthStencil->release();
  }
  
  setWindow();
  
}

void 
BaseApp::processInputs(char input)
{
  onKeyBoardInput(input);
  
}

}
