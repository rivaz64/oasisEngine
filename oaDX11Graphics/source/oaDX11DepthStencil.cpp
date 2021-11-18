#include "oaDX11DepthStencil.h"
#include "oaDX11Texture.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"

oaEngineSDK::DX11DepthStencil::~DX11DepthStencil()
{
  if( depthStencil ) depthStencil->Release();
}

bool oaEngineSDK::DX11DepthStencil::init(DepthStencilDesc descritor, SPtr<Texture> texture)
{
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.Format = Flags::FORMATS[descritor.format];
  descDSV.ViewDimension = Flags::DS_DIMENCIONS[descritor.viewDimension];
  descDSV.Texture2D.MipSlice = 0;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   device->CreateDepthStencilView(cast<DX11Texture>(texture)->texture, &descDSV, &depthStencil);

  return true;
}