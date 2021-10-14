/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

/**
 * @brief everything used for graphycs
*/
class OA_CORE_EXPORT GraphicAPI :
  public Module<GraphicAPI>
{
public:

  /**
   * @brief initialize everything needed for use the graphics API
  */
  virtual void
  initialize();


 protected:

  GraphicAPI() = default;

  /**
   * @brief the width of the window at the begining
  */
  uint32 windowWidth = 800;

  /**
  * @brief the height of the window at the begining
  */
  uint32 windowHeight = 600;

  /**
   * @brief the name of the window 
  */
  const String windowName = "Oasis Engine";

  friend class Module<GraphicAPI>;


};


}


