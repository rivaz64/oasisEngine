/**
* @file oaTexture.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#include "oaTexture.h"

namespace oaEngineSDK{

bool Texture::init(TextureDesc /*description*/)
{
  return true;
}

bool 
Texture::init(TextureDesc /*description*/,ShaderResourseViewDesc /*descriptionSRV*/)
{
  return true;
}

void* 
Texture::getId()
{
  return nullptr;
}

}

