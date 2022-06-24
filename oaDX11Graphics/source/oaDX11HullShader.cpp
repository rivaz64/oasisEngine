#include "oaDX11HullShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>
#include<Windows.h>

namespace oaEngineSDK{

DX11HullShader::~DX11HullShader()
{
  if( m_shader ) m_shader->Release();
}

bool 
DX11HullShader::compileFromFile(const String& file, const Vector<String>& defines)
{
  m_version = "hs_5_0";

  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  ID3DBlob* blob;

  if(!readFromFile("shader/" + file + ".hlsl", defines, &blob)){
    return false;
  }

  HRESULT hr = device->CreateHullShader(blob->GetBufferPointer(), 
                                          blob->GetBufferSize(), 
                                          nullptr, 
                                          &m_shader);

  if (FAILED(hr)) {
    return false;
  }
}

void 
DX11HullShader::set()
{
  auto& context = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_context;

  context->HSSetShader( m_shader, NULL, 0 );
}

}

