#include "oaDX11PixelShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

bool oaEngineSDK::DX11PixelShader::compileFromFile(String file)
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

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  context->PSSetShader( shader, NULL, 0 );

  return true;
}
