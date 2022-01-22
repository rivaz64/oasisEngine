/**
* @file oaBaseApp.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

/**
 * @brief the base app for the engine
*/
class OA_CORE_EXPORT BaseApp :
  public Module<BaseApp>
{
 protected:

  BaseApp() = default;

  ~BaseApp() = default;

 public:

   void
   onShutDown() override;

   /**
    * @brief after everything is shut down
   */
   virtual void
   postShutDown() {}

  /**
   * @brief runs the engine
  */
  void
  run();

  /**
  * @brief the things to do after the graphics api is started
  */
  virtual void
  preInit() {}

  /**
   * @brief the things to do after the graphics api is started
  */
  virtual void
  postInit();

  /**
   * @brief loads a plugin 
   * @param DLL the dll of the plugin
  */
  virtual void
  loadPlugIn(String DLL);

  /**
   * @brief the game loop
  */
  virtual void
  mainLoop();

  /**
   * @brief executed once each loop 
   * @param updates the object and his childs
  */
  void
  update(SPtr<Object> object);

  /**
   * @brief update for the subclasss
  */
  virtual void
  postUpdate(float /*delta*/) {}

  /**
  * @brief render the things to the screen
  */
  virtual void
  draw(){}

  /**
   * @brief shows the screen
  */
  void
  render();

  /**
   * @brief initializes everything needed for the window
   * @param window 
  */
  void
  setWindow(void* window);

  /**
   * @brief this function is called when the window is resized
  */
  void
  resizeWindow(void* window);

  /**
   * @brief if the app is running
  */
  bool isRunning = true; 

 protected:

  /**
   * @brief the frame rate
  */
  float framesPerSecond = 60;

  /**
   * @brief the time a frame is going to be on screen
  */
  float secondPerFrame = 1.f/framesPerSecond;

  /**
   * @brief the time that has pass since the last update
  */
  float deltaTime = 0;

  /**
   * @brief the actual scene selected
  */
  SPtr<Object> actualScene;

  /**
   * @brief the render target that is going to be shown in the screen
  */
  SPtr<RenderTarget> finalRender;

  /**
   * @brief the depth stencil to be used at the end
  */
  SPtr<DepthStencil> finalDepthStencil;

  Vector<int> mistake;

  int i=0;

  friend class Module<BaseApp>;
};

}

