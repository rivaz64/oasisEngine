#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"

bool 
oaEngineSDK::GraphicAPI::initialize()
{
  //std::cout<<"no graphic API"<<std::endl;

  if(!vertexShader->compileFromFile("C:/Users/roriv/Documents/GitHub/oasisEngine/bin/x64/vertexShader")){
    return false;
  }

  return true;
}

bool 
oaEngineSDK::GraphicAPI::isRunning()
{
  return true;
}

void 
oaEngineSDK::GraphicAPI::events()
{

}


