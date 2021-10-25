/**
* @file oaOGL_Texture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once
#include "oaTexture.h"

namespace oaEngineSDK{

class OGL_Texture :
  public Texture
{
 public:

  ~OGL_Texture();

  bool
  loadFromFile(const String& file) override;

  uint32 id;

};

}
