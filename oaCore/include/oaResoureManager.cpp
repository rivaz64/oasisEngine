#include "oaResoureManager.h"
#include "oaGraphicAPI.h"
#include <iostream>

bool oaEngineSDK::ResoureManager::loadTexture(const String& file)
{
  SPtr<Texture> texture = GraphicAPI::instancePtr()->createTexture();

  if(!texture->loadFromFile(file)){
    std::cout<<"texture not loaded"<<std::endl;
    return false;
  }

  textures.insert({file,texture});

  return true;
}
