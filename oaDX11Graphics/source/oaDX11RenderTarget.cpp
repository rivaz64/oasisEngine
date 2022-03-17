#include "oaDX11RenderTarget.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Texture.h"
#include "oaDX11Flags.h"

oaEngineSDK::DX11RenderTarget::~DX11RenderTarget()
{
  release();
}

bool oaEngineSDK::DX11RenderTarget::init(SPtr<Texture> texture)
{
  D3D11_RENDER_TARGET_VIEW_DESC desc;
   memset( &desc,0, sizeof(desc) );
   desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
   desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateRenderTargetView( cast<DX11Texture>(texture)->m_texture, NULL, &m_renderTargetView );

  //if(cast<DX11Texture>(texture)->texture) cast<DX11Texture>(texture)->texture->Release();

  if( FAILED( hr ) ){
    print("failed to init render target");
    return false;
  }

  return true;
}

void oaEngineSDK::DX11RenderTarget::release()
{
  if( m_renderTargetView ) m_renderTargetView->Release();
  m_renderTargetView = nullptr;
}
