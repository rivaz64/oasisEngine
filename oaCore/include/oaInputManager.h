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

 public:

  FORCEINLINE void
  addInput(char key){
    m_inputs.insert({key,false});
  }

  FORCEINLINE bool
  getInput(char key){
    return m_inputs[key];
  }

  FORCEINLINE const Vector2I&
  getMousePosition(){
    return m_mousePosition;
  }

  FORCEINLINE const Vector2I&
  getMouseDelta(){
    return m_mouseDelta;
  }

private:

  /**
    * @brief the inuts that are active
   */
   Map<char,bool> m_inputs;

   /**
   * @brief the position of the mouse in the screen
  */
  Vector2I m_mousePosition;

  /**
   * @brief how much the mouse moved since the last update
  */
  Vector2I m_mouseDelta;
  
  friend class DX11GraphicAPI;

};

}


