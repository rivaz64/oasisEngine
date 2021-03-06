#include "oaDX11PixelShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>

namespace oaEngineSDK{

DX11PixelShader::~DX11PixelShader()
{
  if(m_shader) m_shader->Release();
}

bool 
DX11PixelShader::compileFromFile(const String& file,const Vector<String>& defines)
{
  m_version = "ps_5_0";

  ID3DBlob* blob;

  if(!readFromFile("shader/" + file + ".hlsl", defines, &blob)){
    return false;
  }

  auto graphicsApi = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr());
  auto& device = graphicsApi->m_device;

  HRESULT hr = device->CreatePixelShader(blob->GetBufferPointer(), 
                                         blob->GetBufferSize(), 
                                         nullptr, 
                                         &m_shader);

  blob->Release();

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void 
DX11PixelShader::set()
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_context->PSSetShader( m_shader, NULL, 0 );
}

}
