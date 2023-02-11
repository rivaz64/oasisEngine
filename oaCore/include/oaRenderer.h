/**
* @file oaRenderer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/26/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>
#include <oaMatrix4f.h>

namespace oaEngineSDK{

class OA_CORE_EXPORT Renderer :
  public Module<Renderer>
{
 public:

  /**
   * @brief clears everything for rendering a new frame
  */
  virtual void
  newFrame(){}

  /**
   * @brief renders a scene
   * @param  
   * @param  
   * @param  
   * @param  
  */
  virtual void
  render(WPtr<Actor> /*scene*/,
         WPtr<Camera> /*camForView*/,
         WPtr<Camera> /*camForFrustrum*/, 
         const Vector4f& /*config*/){}

  /**
   * @brief sets the size of what is going to render
   * @param  
  */
  virtual void
  setSize(const Vector2U& /*size*/) {}

  virtual WPtr<Texture>
  getShadowMap(){return WPtr<Texture>();}


 public:
  

};

}


