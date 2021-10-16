#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"

namespace oaEngineSDK{

bool 
GraphicAPI::initialize()
{
  //std::cout<<"no graphic API"<<std::endl;

  if(!vertexShader->compileFromFile("shader")){
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

}


