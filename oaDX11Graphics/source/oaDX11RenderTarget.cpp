#include "oaDX11RenderTarget.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Texture.h"
#include <iostream>

oaEngineSDK::DX11RenderTarget::~DX11RenderTarget()
{
  if( renderTargetView ) renderTargetView->Release();
}

bool oaEngineSDK::DX11RenderTarget::init(SPtr<Texture> texture)
{
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateRenderTargetView( cast<DX11Texture>(texture)->texture, NULL, &renderTargetView );

  //if(cast<DX11Texture>(texture)->texture) cast<DX11Texture>(texture)->texture->Release();

  if( FAILED( hr ) ){
    std::cout<<"failed to init render target"<<std::endl;
    return false;
  }

  return true;
}
