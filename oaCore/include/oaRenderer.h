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

  virtual void
  render(WPtr<Scene> /*scene*/,
         WPtr<Camera> /*camForView*/,
         WPtr<Camera> /*camForFrustrum*/, 
         const Vector4f& /*config*/){}

  virtual void
  setSize(const Vector2U& /*size*/) {}

  virtual WPtr<Texture>
  getShadowMap(){return WPtr<Texture>();}


 public:
  

};

}


