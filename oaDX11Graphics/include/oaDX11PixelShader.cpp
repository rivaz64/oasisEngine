#include "oaDX11PixelShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

DX11PixelShader::~DX11PixelShader()
{
  if( shader ) shader->Release();
}

bool DX11PixelShader::compileFromFile(String file)
{
  version = "ps_4_0";

  if(!DX11Shader::compileFromFile(file + "/pixelShader.hlsl")){
    return false;
  }

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreatePixelShader(blob->GetBufferPointer(), 
                              blob->GetBufferSize(), 
                              nullptr, 
                              &shader);

  return true;
}

void 
DX11PixelShader::set()
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->PSSetShader( shader, NULL, 0 );
}

}
