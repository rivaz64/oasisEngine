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
  render(SPtr<Scene> scene,SPtr<Camera> camForView,SPtr<Camera> camForFrustrum);


 protected:
  
  SPtr<Buffer> m_globalTransformBuffer;

  SPtr<Buffer> m_viewBuffer;

  SPtr<Buffer> m_projectionBuffer;

  SPtr<Buffer> m_viewLocationBuffer;

  SPtr<Rasterizer> m_normalRasterizer;

  SPtr<Rasterizer> m_hairRasterizer;

  SPtr<Rasterizer> m_debugRasterizer;

};

}


