#include "oaTexture.h"

namespace oaEngineSDK{

bool 
Texture::loadFromFile(const Path& /*file*/)
{
    return false;
}

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

