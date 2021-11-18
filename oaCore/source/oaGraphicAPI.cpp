#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"

namespace oaEngineSDK{

bool 
GraphicAPI::initialize()
{
  return true;
}

bool 
GraphicAPI::isRunning()
{
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

SPtr<SamplerState> 
GraphicAPI::createSamplerState(SamplerDesc&)
{
  return newSPtr<SamplerState>();
}

SPtr<RenderTarget> 
GraphicAPI::createRenderTarget(SPtr<Texture>)
{
  return newSPtr<RenderTarget>();
}

SPtr<DepthStencil> 
GraphicAPI::createDepthStencil(DepthStencilDesc&, SPtr<Texture>)
{
  return SPtr<DepthStencil>();
}

SPtr<Texture> 
GraphicAPI::getBackBuffer()
{
  return newSPtr<Texture>();
}

}


