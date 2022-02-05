#include "oaDX11Buffer.h"
#include "oaDX11GraphicAPI.h"
#include "oaMesh.h"
#include "oaDX11Flags.h"
#include <Windows.h>
#include<d3d11.h>

namespace oaEngineSDK{

DX11Buffer::~DX11Buffer()
{
  if(m_buffer)
  m_buffer->Release();
}

bool DX11Buffer::init(uint32 size)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = size;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateBuffer( &bd, nullptr, &m_buffer );

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void DX11Buffer::write(void* data)
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_context->UpdateSubresource( m_buffer, 0, NULL, data, 0, 0);   
}

}

