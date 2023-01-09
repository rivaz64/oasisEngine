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
Material::onSave(Serializer& serializer)
{
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

  serializer.encodeSize(m_colors.size());
  for(auto color : m_colors){
    serializer.encodeString(color.first);
    serializer.encodeColor(color.second);
  }
}

void
Material::load(Serializer& serializer)
{
  auto& resourseManager = ResoureManager::instance();

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

  SIZE_T numOfColors = serializer.decodeSize();
  for(SIZE_T i = 0; i<numOfColors; ++i){
    String name = serializer.decodeString();
    Color color = serializer.decodeColor();
    m_colors.insert({name,color});
  }
}

void 
Material::set()
{
  auto& graphicsAPI = GraphicAPI::instance();
  auto& resourseManager = ResoureManager::instance();

  //auto& shader = resourseManager.m_multiShaderPrograms[StringUtilities::getStringId("gBuffer")][m_shader];
  //shader->set();
  auto gBuffer = resourseManager.getResourse("gBuffer");
  cast<AdaptativeShader>(gBuffer).lock()->set(m_shader);

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
    //else if(channel == "roughtness"){
    //  m_shader |= GBUFFER_FLAGS::kRoughtness;
    //}
  }
  else{
    m_textures[channel] = texture;
  }

  m_onChanged.publish(shared_from_this());
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

void 
Material::setColor(const String& channel, const Color& color)
{
  if(m_colors.find(channel) == m_colors.end()){
    m_colors.insert({channel,color});
  }
  else{
    m_colors[channel] = color;
  }
}

bool 
Material::getColor(const String& channel, Color& color)
{
  if(m_colors.find(channel) == m_colors.end()){
    return false;
  }
  color = m_colors[channel];
  return true;
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

