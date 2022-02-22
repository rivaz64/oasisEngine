/**
* @file oaMaterial.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#include "oaMaterial.h"
#include "oaGraphicAPI.h"
#include "oaTexture.h"
#include "oaShaderProgram.h"

namespace oaEngineSDK{

Material::Material()
{
  auto& graphicsAPI = GraphicAPI::instance();

  m_program = graphicsAPI.createShaderProgram();
}

void 
Material::set()
{
  m_program->set();

  auto& graphicsAPI = GraphicAPI::instance();
  
  graphicsAPI.setTexture(m_diffuse,0);

  if(m_specular){
    graphicsAPI.setTexture(m_specular,1);
  }

  if(m_normalMap){
    graphicsAPI.setTexture(m_normalMap,2);
  }

  if(m_depthMap){
    graphicsAPI.setTexture(m_depthMap,3);
  }
}

}

