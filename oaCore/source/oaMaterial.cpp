/**
* @file oaMaterial.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

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
