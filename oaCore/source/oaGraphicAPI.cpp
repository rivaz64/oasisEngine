#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"

namespace oaEngineSDK{

bool 
GraphicAPI::initialize()
{
  //std::cout<<"no graphic API"<<std::endl;

  if(!compileShaders("shader")){
    return false;
  }

  return true;
}

bool 
GraphicAPI::isRunning()
{
  return true;
}

void 
GraphicAPI::events()
{

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

  return true;
}

SPtr<Buffer> GraphicAPI::createBuffer()
{
  return newSPtr<Buffer>();
}

SPtr<Texture> GraphicAPI::createTexture()
{
  return newSPtr<Texture>();
}

void GraphicAPI::setBackgroundColor(const Vector4f& color)
{

}

void GraphicAPI::clear()
{
}

void GraphicAPI::show()
{

}

void GraphicAPI::setVertexBuffer(const SPtr<Buffer>& buffer)
{
}

}


