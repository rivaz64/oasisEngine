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
#include "oaRenderer.h"
#include <exception>
#include <Windows.h>

namespace oaEngineSDK{

using Function = const void* (*)();


BaseApp::BaseApp()
  : m_windowName("Oasis Engine"), m_windowSize(800,600)
{

}

BaseApp::~BaseApp()
{
  onShutDown();
}

void 
BaseApp::onShutDown()
{
  onDestroy();
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputManager::shutDown();
  Time::shutDown();
  Renderer::shutDown();
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

  auto& graphicsApi = GraphicAPI::instance();

  m_windowSize = graphicsApi.getWindowSize(m_window);

  if(graphicsApi.initialize(m_window)){

    loadPlugIn("oaRendererd.dll");

    Renderer::instance().setSize(m_windowSize);

    ResoureManager::startUp();
    InputManager::startUp();
    Time::startUp();
    
    graphicsApi.setViewport(m_windowSize);

    m_camera = makeSPtr<Camera>();
    m_camera->init(static_cast<float>(m_windowSize.x)/static_cast<float>(m_windowSize.y));
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

  Function foundFunction = reinterpret_cast<Function>(GetProcAddress(hGetProcIDDLL, "initPlugIn"));
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
BaseApp::update(SPtr<Actor> actor)
{
  actor->update();
  auto& childs =  actor->getChilds();
  for(auto& child : childs){
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
BaseApp::resizeWindow()
{
  auto& graphicsApi = GraphicAPI::instance();

  m_windowSize = graphicsApi.getWindowSize(m_window);
  if(!graphicsApi.getContext()){
    return;
  }
  graphicsApi.setViewport(m_windowSize);
  graphicsApi.resizeSwapChain(m_windowSize);
  Renderer::instance().setSize(m_windowSize);
  
}

void 
BaseApp::processInputs(char input)
{
  onKeyBoardInput(input);
  
}

}
