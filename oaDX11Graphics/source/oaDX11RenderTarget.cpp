#include "oaDX11RenderTarget.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Texture.h"

oaEngineSDK::DX11RenderTarget::~DX11RenderTarget()
{
  release();
}

bool oaEngineSDK::DX11RenderTarget::init(SPtr<Texture> texture)
{
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateRenderTargetView( cast<DX11Texture>(texture)->texture, NULL, &renderTargetView );

  //if(cast<DX11Texture>(texture)->texture) cast<DX11Texture>(texture)->texture->Release();

  if( FAILED( hr ) ){
    print("failed to init render target");
    return false;
  }

  return true;
}

void oaEngineSDK::DX11RenderTarget::release()
{
  if( renderTargetView ) renderTargetView->Release();
  renderTargetView = nullptr;
}
