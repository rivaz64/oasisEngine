#include "oaDX11BlendState.h"
#include "oaDX11GraphicAPI.h"

namespace oaEngineSDK{

DX11BlendState::~DX11BlendState()
{
  release();
}

bool
DX11BlendState::init(bool adds)
{
  D3D11_BLEND_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.AlphaToCoverageEnable = true;
  desc.IndependentBlendEnable = false;
  desc.RenderTarget[0].BlendEnable = true;
  desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE ;
  if(adds)
  desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  else
  desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
  desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateBlendState(&desc,&m_id);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void 
DX11BlendState::release()
{
  if(m_id){
   m_id->Release();
  }
}

}

