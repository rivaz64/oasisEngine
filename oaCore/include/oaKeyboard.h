/**
* @file oaKeyboard.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 5/30/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief class for keyboard inputs
*/
class OA_CORE_EXPORT Keyboard
{

 public:
  
	Keyboard() = default;

	/**
	 * @brief if a key is being pressed
	 * @param key the key to check if is pressed 
	 * @return 
	*/
	virtual bool
	isKeyDown(const KEY::E key);

  /**
   * @brief if this key has been pressed in this frame
   * @param key 
   * @return 
  */
  virtual bool
	wasKeyPressed(const KEY::E key);

  /**
   * @brief if this key has been released in this frame
   * @param key 
   * @return 
  */
  virtual bool
	wasKeyReleased(const KEY::E key);

  ///**
  // * @brief map maps a key to a string
  // * @param name the name of the input
  // * @param key the key to map
  //*/
  ////virtual void
  ////map(const String& name, const KEY::E key){}

};

}


