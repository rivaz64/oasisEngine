#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"

namespace oaEngineSDK{

bool 
GraphicAPI::initialize()
{
  vertexShader = newSPtr<Shader>();
  pixelShader = newSPtr<Shader>();
  return true;
}

bool 
GraphicAPI::isRunning()
{
  return true;
}

bool 
GraphicAPI::compileShaders(String folder)
{
  if(!vertexShader->compileFromFile(folder)){
    std::cout<<"vertex shader not compiled"<<std::endl;
    return false;
  }

  if(!pixelShader->compileFromFile(folder)){
    std::cout<<"pixel shader not compiled"<<std::endl;
    return false;
  }

  createShaderProgram();

  return true;
}

SPtr<Buffer> 
GraphicAPI::createBuffer()
{
  return newSPtr<Buffer>();
}

SPtr<Texture> 
GraphicAPI::createTexture()
{
  return newSPtr<Texture>();
}

SPtr<SamplerState> GraphicAPI::createSamplerState(SamplerDesc /*descriptor*/)
{
  return newSPtr<SamplerState>();
}

}


