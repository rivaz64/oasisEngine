#include "oaDX11Buffer.h"
#include "oaDX11GraphicAPI.h"
#include "oaMesh.h"
#include <Windows.h>
#include<d3d11.h>

namespace oaEngineSDK{

Map<BUFFER_FLAGS,uint32> FLAGS = {
  {BUFFER_FLAGS::VERTEX,D3D11_BIND_VERTEX_BUFFER},
  {BUFFER_FLAGS::CONSTANT,D3D11_BIND_CONSTANT_BUFFER},
  };

DX11Buffer::~DX11Buffer()
{
  if(buffer)
  buffer->Release();
}

void DX11Buffer::init(void* data, uint32 size,BUFFER_FLAGS flags)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = size;
  bd.BindFlags = FLAGS[flags];
  bd.CPUAccessFlags = 0;
  if(data){
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = data;
    HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
      device->CreateBuffer( &bd, &InitData, &buffer );
  }
  else{
    HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
      device->CreateBuffer( &bd, nullptr, &buffer );
  }
  
}

void DX11Buffer::update(void* data, uint32 size)
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->UpdateSubresource( buffer, 0, NULL, data, 0, 0);
    
}

}

