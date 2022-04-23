#include "oaDX11VertexBuffer.h"
#include "oaDX11GraphicAPI.h"

namespace oaEngineSDK{

DX11VertexBuffer::~DX11VertexBuffer()
{
  release();
}

bool DX11VertexBuffer::init(
  const void* data,
  uint32 vertexSize,
  SIZE_T numberOfVertices)
{
  m_vertexSize = vertexSize;
  D3D11_BUFFER_DESC bd;
  memset( &bd, 0, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = vertexSize*numberOfVertices;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  
  D3D11_SUBRESOURCE_DATA InitData;
  memset( &InitData, 0, sizeof(InitData) );
  InitData.pSysMem = data;

  auto api = DX11GraphicAPI::instancePtr();

  auto api2 = reinterpret_cast<DX11GraphicAPI*>(api);

  HRESULT hr = api2->m_device->CreateBuffer( &bd, &InitData, &m_buffer );

  if(FAILED(hr)){
    return false;
  }
  
  return true;
}

void DX11VertexBuffer::set()
{
  UINT stride = m_vertexSize;
  UINT offset = 0;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  m_context->IASetVertexBuffers( 
    0, 
    1, 
    &m_buffer,
    &stride, 
    &offset );
}

void
DX11VertexBuffer::release()
{
  if(m_buffer){
    m_buffer->Release();
  }
  m_buffer = 0;
}

}
