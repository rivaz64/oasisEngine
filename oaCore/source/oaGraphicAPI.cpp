#include "oaGraphicAPI.h"
#include <iostream>
#include "oaShader.h"
#include "oaTexture.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaShader.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"

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

SPtr<Shader> GraphicAPI::createVertexShader()
{
  return newSPtr<Shader>();
}

SPtr<Shader> GraphicAPI::createPixelShader()
{
  return newSPtr<Shader>();
}

SPtr<Buffer>
GraphicAPI::createBuffer()
{
  return newSPtr<Buffer>();
}

SPtr<VertexBuffer> GraphicAPI::createVertexBuffer()
{
  return newSPtr<VertexBuffer>();
}

SPtr<IndexBuffer> GraphicAPI::createIndexBuffer()
{
  return newSPtr<IndexBuffer>();
}

SPtr<Texture> 
GraphicAPI::createTexture()
{
  return newSPtr<Texture>();
}

SPtr<SamplerState> 
GraphicAPI::createSamplerState(const SamplerDesc&)
{
  return newSPtr<SamplerState>();
}

SPtr<RenderTarget> 
GraphicAPI::createRenderTarget(SPtr<Texture>)
{
  return newSPtr<RenderTarget>();
}

SPtr<DepthStencil> 
GraphicAPI::createDepthStencil(const DepthStencilDesc&, SPtr<Texture>)
{
  return SPtr<DepthStencil>();
}

SPtr<Texture> 
GraphicAPI::getBackBuffer()
{
  return newSPtr<Texture>();
}

}


