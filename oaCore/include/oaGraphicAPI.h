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

  friend class Module<GraphicAPI>;
};


}


