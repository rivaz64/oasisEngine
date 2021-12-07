#include "oaMaterial.h"
#include "oaGraphicAPI.h"
#include "oaTexture.h"
#include "oaShader.h"

void oaEngineSDK::Material::set()
{
  vertexShader->set();
  pixelShader->set();
  for(auto texture : textures){
    GraphicAPI::instancePtr()->setTexture(
        texture
      );
  }
}
