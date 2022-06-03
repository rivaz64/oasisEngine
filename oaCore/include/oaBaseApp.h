/**
* @file oaBaseApp.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaVector2U.h>
#include "oaInputAPI.h"

namespace oaEngineSDK{

/**
 * @brief the base app for the engine
*/
class OA_CORE_EXPORT BaseApp
{
 public:

  BaseApp();

  ~BaseApp();

 public:

  void
  onShutDown();

  virtual void
  onDestroy(){}

  /**
   * @brief runs the engine
  */
  void
  run();

  /**
  * @brief the things to do after the graphics api is started
  */
  virtual void
  onInit() {}

  /**
   * @brief the things to do after the graphics api is started
  */
  virtual void
  postInit() {}

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
   * @param updates the Actor and his childs
  */
  void
  update(SPtr<Actor> Actor);

  /**
   * @brief update for the subclasss
  */
  virtual void
  onUpdate(float /*delta*/) {}

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
  setWindow();

  /**
   * @brief this function is called when the window is resized
  */
  void
  resizeWindow();

  /**
   * @brief triggers the effect of certain input
   * @param input 
  */
  void
  processInputs(const MSG& msg);

  /**
   * @brief for the subclass to test the imputs
   * @param input 
  */
  virtual void
  onKeyBoardInput(char /*input*/){}

  /**
   * @brief if the app is running
  */
  bool m_isRunning = true; 

 protected:

  /**
   * @brief the frame rate
  */
  float m_framesPerSecond = 60;

  /**
   * @brief the time a frame is going to be on screen
  */
  float m_secondPerFrame = 1.f/m_framesPerSecond;

  /**
   * @brief the time that has pass since the last update
  */
  float m_deltaTime = 0;

  /**
   * @brief the actual scene selected
  */
  SPtr<Scene> m_actualScene;

  /**
   * @brief the camera for the editor
  */
  SPtr<Camera> m_camera;

  /**
   * @brief the name of the window of the app
  */
  String m_windowName;

  /**
   * @brief the size of the window of the app
  */
  Vector2U m_windowSize;

  void* m_window;

};

}

