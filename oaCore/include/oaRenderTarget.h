/**
* @file oaRenderTarget.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a texture where the renderer is going to draw
*/
class RenderTarget
{
 public:

  virtual ~RenderTarget() {}

  /**
   * @brief initializes the render target
   * @param texture where the render is going to be drawn
   * @return 
  */
  virtual bool 
  init(SPtr<Texture> texture) { return true; }

  /**
   * @brief releases the render target
  */
  virtual void
  release(){}

};

}



