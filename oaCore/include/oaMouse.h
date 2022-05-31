#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief class for mosue inputs
*/
class OA_CORE_EXPORT Mouse
{
 public:
  
  /**
   * @brief if a button of the mouse is being pressed
   * @param button the button of the mouse to check 
   * @return 
  */
  virtual bool
	isButtonDown(const BUTTON::E button);

  /**
   * @brief if this key has been pressed in this frame
   * @param key 
   * @return 
  */
  virtual bool
	wasButtonPressed(const BUTTON::E button);

  /**
   * @brief if this key has been released in this frame
   * @param key 
   * @return 
  */
  virtual bool
	wasButtonReleased(const BUTTON::E button);

  /**
   * @brief gets the direction the mouse moved in a certain axis
   * @param axis 
   * @return 
  */
  virtual float
	getAxis(const AXIS::E axis);
};

}


