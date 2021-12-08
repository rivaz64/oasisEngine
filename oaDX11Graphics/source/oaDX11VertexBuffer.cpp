#include "oaDX11VertexBuffer.h"
#include "oaDX11GraphicAPI.h"

bool oaEngineSDK::DX11VertexBuffer::init(
  void* data,
  uint64 _vertexSize,
  uint64 numberOfVertices)
{
  vertexSize = _vertexSize;
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = vertexSize*numberOfVertices;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory( &InitData, sizeof(InitData) );
  InitData.pSysMem = data;
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateBuffer( &bd, &InitData, &buffer );

  if(FAILED(hr)){
    return false;
  }
  
  return true;
}

void oaEngineSDK::DX11VertexBuffer::set()
{
  UINT stride = vertexSize;
  UINT offset = 0;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  context->IASetVertexBuffers( 
    0, 
    1, 
    &buffer,
    &stride, 
    &offset );
}
