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
  m_vertexShader->set();
  m_pixelShader->set();
  for(auto texture : m_textures){
    GraphicAPI::instancePtr()->setTexture(
        texture
      );
  }
}
