#include "oaDX11Buffer.h"
#include "oaDX11GraphicAPI.h"
#include "oaMesh.h"
#include "oaDX11Flags.h"
#include <Windows.h>
#include<d3d11.h>

namespace oaEngineSDK{

DX11Buffer::~DX11Buffer()
{
  if(buffer)
  buffer->Release();
}

bool DX11Buffer::init(void* data, uint32 size,BIND flags)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory( &bd, sizeof(bd) );
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = size;
  bd.BindFlags = Flags::FLAGS[flags];
  bd.CPUAccessFlags = 0;
  if(data){
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = data;
    HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
      device->CreateBuffer( &bd, &InitData, &buffer );

    if(FAILED(hr)){
      return false;
    }
  }
  else{
    HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
      device->CreateBuffer( &bd, nullptr, &buffer );

    if(FAILED(hr)){
      return false;
    }
  }
  return true;
}

void DX11Buffer::update(void* data)
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->UpdateSubresource( buffer, 0, NULL, data, 0, 0);   
}

}

