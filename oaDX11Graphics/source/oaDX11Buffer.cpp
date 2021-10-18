#include "oaDX11Buffer.h"
#include "oaDX11GraphicAPI.h"


void oaEngineSDK::DX11Buffer::init(void* data, uint32 size)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = size;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory( &InitData, sizeof(InitData) );
  InitData.pSysMem = data;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  device->CreateBuffer( &bd, &InitData, &buffer );
  

  // Set vertex buffer
  UINT stride = size;
  UINT offset = 0;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  context->IASetVertexBuffers( 0, 1, &buffer, &stride, &offset );
}
