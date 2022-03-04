#include "oaDX11DepthStencil.h"
#include "oaDX11Texture.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"

namespace oaEngineSDK{

DX11DepthStencil::~DX11DepthStencil()
{
  release();
}

bool 
DX11DepthStencil::init(SPtr<Texture> texture)
{
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  memset( &descDSV,0, sizeof(descDSV) );
  descDSV.Format = Flags::FORMATS[texture->getFormat()];
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateDepthStencilView(cast<DX11Texture>(texture)->m_texture,
                                    &descDSV, 
                                    &m_depthStencil);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void
DX11DepthStencil::release()
{
  if( m_depthStencil ) m_depthStencil->Release();
  m_depthStencil = nullptr;
}

}


