/**
* @file oaOGL_RenderTarget.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/1/2021
*/

#pragma once


#include <oaRenderTarget.h>

namespace oaEngineSDK{

class OGL_RenderTarget :
  public RenderTarget
{
  bool 
  init(SPtr<Texture> texture) override;

  void
  release();

 private:
  
  uint32 m_id;
};

}

