/**
* @file oaMaterial.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#include "oaMaterial.h"
#include "oaGraphicAPI.h"
#include "oaTexture.h"
#include "oaShaderProgram.h"
#include "oaResoureManager.h"
#include "oaAdaptativeShader.h"

namespace oaEngineSDK{

void 
Material::save(Serializer& serializer)
{
  serializer.encodeString(getName());

  serializer.encodeNumber(getShader());

  auto types = getTextureChannels();

  SIZE_T numOfTypes = types.size();

  serializer.file.write(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  for(auto& type : types){
    serializer.encodeString(type);
    auto wTexture = getTexture(type);
    if(wTexture.expired()){
      serializer.encodeString("");
    }
    else{
      auto texture = wTexture.lock();
      serializer.encodeString(texture->getName());
    }

  }
}

void
Material::load(Serializer& serializer)
{
  auto& resourseManager = ResoureManager::instance();

  setName(serializer.decodeString());

  setShader(serializer.decodeNumber());

  SIZE_T numOfTypes;

  serializer.file.read(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  String channel, name;

  for(SIZE_T typeNum = 0; typeNum<numOfTypes; ++typeNum){
    channel = serializer.decodeString();
    name =  serializer.decodeString();
    if(name != ""){
       setTexture(channel, cast<Texture>(resourseManager.getResourse(name)));
    }
  }
}

void 
Material::set()
{
  auto& graphicsAPI = GraphicAPI::instance();
  auto& resourseManager = ResoureManager::instance();

  //auto& shader = resourseManager.m_multiShaderPrograms[StringUtilities::getStringId("gBuffer")][m_shader];
  //shader->set();
  cast<AdaptativeShader>(resourseManager.getResourse("gBuffer")).lock()->set(m_shader);

  auto channels = {"diffuse","specular","normalMap","emisive"};

  uint32 channelNum = 0;
  for(auto& channel : channels){
    if(m_textures.find(channel)!=m_textures.end()){
      if(!m_textures[channel].expired()){
        auto texture = m_textures[channel].lock();
        graphicsAPI.setTexture(texture,channelNum);

      }

    }
    ++channelNum;
  }

  //auto& graphicsAPI = GraphicAPI::instance();
  //
  //m_shader->set();
  
  //switch (m_shader)
  //{
  //case SHADER_TYPE::kNormal:
  //case SHADER_TYPE::kAnimation:
  //case SHADER_TYPE::kTransparent:
  //  if(m_textures.find(TEXTURE_TYPE::kDiffuse) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDiffuse],0);
  //  }
  //  if(m_textures.find(TEXTURE_TYPE::kSpecular) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kSpecular],1);
  //  }
  //  if(m_textures.find(TEXTURE_TYPE::kNormalMap) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kNormalMap],2);
  //  }
  //
  //  break;
  //
  //case SHADER_TYPE::kParalax:
  //  if(m_textures.find(TEXTURE_TYPE::kDiffuse) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDiffuse],0);
  //  }
  //  if(m_textures.find(TEXTURE_TYPE::kSpecular) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kSpecular],1);
  //  }
  //  if(m_textures.find(TEXTURE_TYPE::kNormalMap) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kNormalMap],2);
  //  }
  //  if(m_textures.find(TEXTURE_TYPE::kDepthMap) != m_textures.end()){
  //    graphicsAPI.setTexture(m_textures[TEXTURE_TYPE::kDepthMap],3);
  //  }
  //
  //  break;
  //
  //default:
  //  break;
  //}
}

void 
Material::setTexture(const String& channel, WPtr<Texture> texture)
{
  if(m_textures.find(channel) == m_textures.end()){
    m_textures.insert({channel,texture});
    if(channel == "diffuse"){
      m_shader |= GBUFFER_FLAGS::kDiffuse;
    }
    else if(channel == "normalMap"){
      m_shader |= GBUFFER_FLAGS::kNormals;
    }
    else if(channel == "specular"){
      m_shader |= GBUFFER_FLAGS::kSpecular;
    }
    else if(channel == "emisive"){
      m_shader |= GBUFFER_FLAGS::kEmisive;
    }
  }
  else{
    m_textures[channel] = texture;
  }
}

WPtr<Texture> 
Material::getTexture(const String& channel)
{
  if(m_textures.find(channel) == m_textures.end()){
    return SPtr<Texture>();
  }
  else{
    return m_textures[channel];
  }
}

Vector<String> 
Material::getTextureChannels()
{
  Vector<String> types;
  for(Map<String,WPtr<Texture>>::iterator it = m_textures.begin(); it != m_textures.end(); ++it){
    types.push_back(it->first);
  }
  return types;
}

}

