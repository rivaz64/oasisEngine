/**
* @file oaTexture.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#include "oaTexture.h"
#include "oaImage.h"
#include "oaVector2I.h"

namespace oaEngineSDK{

bool
Texture::init(const Vector2I& size, BIND::E bind, FORMAT::E format, const void* data, uint32 pitch)
{
  return false;
}

void
Texture::initFromImage(SPtr<Image> image)
{
  m_image = image;
  setName(image->getName());
  init(image->getSize(),BIND::kShaderResourse,FORMAT::kB8G8R8A8UnormSRGB,image->getPixels(),image->getPitch());
}

bool 
Texture::createShaderResource(FORMAT::E format)
{
  return false;
}

bool
Texture::createRenderTarget(FORMAT::E format)
{
  return false;
}

bool
Texture::createDepthStencil(FORMAT::E format)
{
  return false;
}

void*
Texture::getId()
{
  return nullptr;
}

}

