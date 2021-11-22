/**
* @file oaInputManager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/20/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaVector2I.h"

namespace oaEngineSDK{

/**
 * @brief handles all the inputs
*/
class OA_CORE_EXPORT InputManager :
  public Module<InputManager>
{

private:

  /**
    * @brief the inuts that are active
   */
   Map<char,bool> inputs;

   /**
   * @brief the position of the mouse in the screen
  */
  Vector2I mousePosition;

  /**
   * @brief how much the mouse moved since the last update
  */
  Vector2I mouseDelta;

 public:

  FORCEINLINE void
  addInput(char key){
    inputs.insert({key,false});
  }

  FORCEINLINE bool
  getInput(char key){
    return inputs[key];
  }

  FORCEINLINE const Vector2I&
  getMousePosition(){
    return mousePosition;
  }

  FORCEINLINE const Vector2I&
  getMouseDelta(){
    return mouseDelta;
  }
  
  friend class DX11GraphicAPI;

};

}


