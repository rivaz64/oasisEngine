#include "oaDX11IndexBuffer.h"
#include "oaDX11GraphicAPI.h"

bool oaEngineSDK::DX11IndexBuffer::init(Vector<uint32>& data)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(uint32)*data.size();
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory( &InitData, sizeof(InitData) );
  InitData.pSysMem = data.data();
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateBuffer( &bd, &InitData, &buffer );

  if(FAILED(hr)){
    return false;
  }
  
  return true;
}

void oaEngineSDK::DX11IndexBuffer::set()
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ); 

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  context->IASetIndexBuffer(buffer,DXGI_FORMAT_R32_UINT,0 );
}