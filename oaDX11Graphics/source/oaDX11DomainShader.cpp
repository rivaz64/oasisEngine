#include "oaDX11DomainShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>
#include<Windows.h>

namespace oaEngineSDK{

DX11DomainShader::~DX11DomainShader()
{
  if( m_shader ) m_shader->Release();
}

bool 
DX11DomainShader::compileFromFile(const String& file, const Vector<String>& defines)
{
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  ID3DBlob* blob;

  if(!readFromFile("shader/" + file + ".hlsl", defines, &blob)){
    return false;
  }

  HRESULT hr = device->CreateDomainShader(blob->GetBufferPointer(), 
                                          blob->GetBufferSize(), 
                                          nullptr, 
                                          &m_shader);

  if (FAILED(hr)) {
    return false;
  }
}

}

