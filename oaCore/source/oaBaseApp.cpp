/**
* @file oaBaseApp.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#include "oaBaseApp.h"
#include <oaVector3f.h>
#include <oaEventSystem.h>
#include "oaGraphicAPI.h"
#include "oaResoureManager.h"
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
#include "oaInputAPI.h"
#include "oaAudioAPI.h"
//extern "C" {
//#include <lua\lua.h>
//#include <lua\lualib.h>
//#include <lua/lauxlib.h>
//}
#define SOL_ALL_SAFETIES_ON 1
#include <sol\sol.hpp>

#include <exception>
#include <Windows.h>

namespace oaEngineSDK{

using Function = const void* (*)();

//lua_State *luaState;
sol::state lua;

void
initLua(){
  lua.open_libraries(sol::lib::base, sol::lib::package);
  //luaState = luaL_newstate();
  //luaL_openlibs(luaState);
}

void
closeLua(){
  //lua_close(luaState);
}
//
int luaSetWindowName(lua_State* L){
  BaseApp* ba = reinterpret_cast<BaseApp*>(luaL_checkudata(L,1,"baseApp"));
  String windowName = lua_tostring(L,2);
  ba->setWindowName(windowName);
  return 1;
}
int createObject(lua_State* /*L*/){
  return 1;
}

void
registerBaseClass(){
  sol::usertype<BaseApp> baseApp_type = lua.new_usertype<BaseApp>("baseApp",sol::constructors<BaseApp()>());
  baseApp_type.set_function("setWindowName",&BaseApp::setWindowName);
  //baseApp_type["name"] = &BaseApp::m_windowName;
  //lua_register(luaState,"baseApp",createObject);
  //luaL_newmetatable(luaState,"baseApp");
  //lua_pushvalue(luaState, -1); lua_setfield(luaState, -2, "__index");
  //lua_pushcfunction(luaState,luaSetWindowName); lua_setfield(luaState,-2,"setName");
  //lua_pop(luaState,1);
}

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
  //closeLua();
  //EventSystem::shutDown();
  GraphicAPI::shutDown();
  ResoureManager::shutDown();
  InputAPI::shutDown();
  AudioAPI::shutDown();
  Time::shutDown();
  Renderer::shutDown();
  Logger::shutDown();
}

void
BaseApp::run()
{
  Logger::startUp();

  initLua();
  registerBaseClass();
  
  lua.script_file("scripts/start.lua");
  //if(luaL_dofile(luaState, "scripts/start.lua")){
  //  print(lua_tostring(luaState,-1));
  //}
  sol::function configs = lua["configs"];
  std::function<void(BaseApp*)> stdconfigs = configs;
  stdconfigs(this);
  //lua_getglobal(luaState,"setApp");
  //lua_pushlightuserdata(luaState,this);
  //if(lua_pcall(luaState,1,0,0)){
  //  print(lua_tostring(luaState,-1));
  //}

  

  //lua_getglobal(luaState,"configs");
  //
  //lua_pushlightuserdata(luaState,this);
  //luaL_getmetatable(luaState,"baseApp");
  //lua_setmetatable(luaState,-2);
  //
  //if(lua_pcall(luaState,1,0,0)){
  //  print(lua_tostring(luaState,-1));
  //}

  #ifdef _DEBUG
  loadPlugIn("oaDX11Graphicsd.dll");
  #else
  loadPlugIn("oaDX11Graphics.dll");
  #endif

  
  loadPlugIn("oaGa_Inputd.dll");
  loadPlugIn("oaFmodAudiod.dll");
  //loadPlugIn("oaDX11Graphics.dll");
  //loadPlugIn("oaOGL_Grafics.dll");
  auto& input = InputAPI::instance();

 

  //if(luaL_dofile(luaState, "scripts/configs.lua")){
  //  print(lua_tostring(luaState,-1));
  //}
  input.init(m_windowSize);

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
    //EventSystem::startUp();
    graphicsApi.setViewport(m_windowSize);

    m_camera = makeSPtr<Camera>();
    m_camera->init(static_cast<float>(m_windowSize.x)/static_cast<float>(m_windowSize.y));
    m_camera->update();

    postInit();

    //try {
      mainLoop();
    //}
    //catch (...) {
    //  Logger::instance().flush();
    //  return;
    //}
    //Logger::instance().flush();

  }
}

void 
BaseApp::loadPlugIn(String DLL)
{
#if OA_PLATFORM == OA_PLATFORM_WIN32
  HINSTANCE hGetProcIDDLL = LoadLibrary(DLL.c_str());
  if(!hGetProcIDDLL)
  {
    print("Could not load " + DLL + " Dll");
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
BaseApp::processInputs(const MSG& msg)
{
  auto& inputManager = InputAPI::instance();
  inputManager.HandleMessage(msg);
}

}
