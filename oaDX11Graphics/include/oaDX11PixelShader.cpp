#include "oaDX11PixelShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

DX11PixelShader::~DX11PixelShader()
{
  if( m_shader ) m_shader->Release();
}

bool DX11PixelShader::compileFromFile(String file)
{
  m_version = "ps_4_0";

  if(!DX11Shader::compileFromFile(file + "/pixelShader.hlsl")){
    return false;
  }

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreatePixelShader(m_blob->GetBufferPointer(), 
                                m_blob->GetBufferSize(), 
                                nullptr, 
                                &m_shader);

  return true;
}

void 
DX11PixelShader::set()
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_context->PSSetShader( m_shader, NULL, 0 );
}

}
