/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#include "oaGraphicAPI.h"
#include <iostream>
#include <oaVector2U.h>
#include "oaShader.h"
#include "oaTexture.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaShader.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"
#include "oaShaderProgram.h"
#include "oaRasterizerState.h"
#include "oaBlendState.h"

namespace oaEngineSDK{

bool 
GraphicAPI::initialize(void*)
{
  return true;
}

void*
GraphicAPI::createWindow(void*,void*, const Vector2U&, const String&)
{
  return nullptr;
}

bool 
GraphicAPI::isRunning()
{
  return true;
}

SPtr<ShaderProgram> GraphicAPI::createShaderProgram()
{
    return makeSPtr<ShaderProgram>();
}

SPtr<Shader> GraphicAPI::createVertexShader()
{
  return makeSPtr<Shader>();
}

SPtr<Shader> GraphicAPI::createPixelShader()
{
  return makeSPtr<Shader>();
}

SPtr<Buffer>
GraphicAPI::createBuffer()
{
  return makeSPtr<Buffer>();
}

SPtr<VertexBuffer> GraphicAPI::createVertexBuffer()
{
  return makeSPtr<VertexBuffer>();
}

SPtr<IndexBuffer> GraphicAPI::createIndexBuffer()
{
  return makeSPtr<IndexBuffer>();
}

SPtr<Texture> 
GraphicAPI::createTexture()
{
  return makeSPtr<Texture>();
}

SPtr<SamplerState> 
GraphicAPI::createSamplerState(const SamplerDesc&)
{
  return makeSPtr<SamplerState>();
}

SPtr<RasterizerState> 
GraphicAPI::createRasterizerState()
{
  return makeSPtr<RasterizerState>();
}

SPtr<BlendState> 
GraphicAPI::createBlendState()
{
  return makeSPtr<BlendState>();
}

SPtr<Texture> 
GraphicAPI::getBackBuffer()
{
  return makeSPtr<Texture>();
}

Vector2U
GraphicAPI::getWindowSize(void* /*window*/)
{
  return Vector2U(0,0);
}

}


