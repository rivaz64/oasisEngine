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
}

void 
Material::set()
{
  
  auto& graphicsAPI = GraphicAPI::instance();
  
  switch (m_shader)
  {
  case SHADER_TYPE::kNormal:
  case SHADER_TYPE::kAnimation:
  case SHADER_TYPE::kTransparent:
    if(m_textures.find(TEXTURE_TYPE::kDiffuse) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDiffuse],0);
    }
    if(m_textures.find(TEXTURE_TYPE::kSpecular) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kSpecular],1);
    }
    if(m_textures.find(TEXTURE_TYPE::kNormalMap) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kNormalMap],2);
    }

    break;

  case SHADER_TYPE::kParalax:
    if(m_textures.find(TEXTURE_TYPE::kDiffuse) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDiffuse],0);
    }
    if(m_textures.find(TEXTURE_TYPE::kSpecular) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kSpecular],1);
    }
    if(m_textures.find(TEXTURE_TYPE::kNormalMap) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kNormalMap],2);
    }
    if(m_textures.find(TEXTURE_TYPE::kDepthMap) != m_textures.end()){
      graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDepthMap],3);
    }

    break;

  default:
    break;
  }
}

void 
Material::setTexture(TEXTURE_TYPE::E type, SPtr<Texture> texture)
{
  if(m_textures.find(type) == m_textures.end()){
    m_textures.insert({type,texture});
  }
  else{
    m_textures[type] = texture;
  }
}

SPtr<Texture> 
Material::getTexture(TEXTURE_TYPE::E type)
{
  if(m_textures.find(type) == m_textures.end()){
    return SPtr<Texture>();
  }
  else{
    return m_textures[type];
  }
}

Vector<TEXTURE_TYPE::E> 
Material::getTextureTypes()
{
  Vector<TEXTURE_TYPE::E> types;
  for(Map<TEXTURE_TYPE::E,SPtr<Texture>>::iterator it = m_textures.begin(); it != m_textures.end(); ++it){
    types.push_back(it->first);
  }
  return types;
}

}

