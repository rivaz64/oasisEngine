#include "oaDX11RasterizerState.h"
#include "oaDX11GraphicAPI.h"

namespace oaEngineSDK{

Map<CULLING::E,D3D11_CULL_MODE> g_cullingFlags {
  {CULLING::kNone,D3D11_CULL_NONE},
  {CULLING::kFront,D3D11_CULL_FRONT},
  {CULLING::kBack,D3D11_CULL_BACK},
};

Map<FILL_MODE::E,D3D11_FILL_MODE> g_fillFlags {
  {FILL_MODE::kSolid,D3D11_FILL_SOLID},
  {FILL_MODE::kWireFrame,D3D11_FILL_WIREFRAME},
};

DX11RasterizerState::~DX11RasterizerState()
{
  release();
}

bool
DX11RasterizerState::init(CULLING::E culling, FILL_MODE::E fillMode)
{
  D3D11_RASTERIZER_DESC descriptor;

  descriptor.FillMode = g_fillFlags[fillMode];
  descriptor.CullMode = g_cullingFlags[culling];
  descriptor.FrontCounterClockwise = true;
  descriptor.DepthBias = 0;
  descriptor.DepthBiasClamp = 0;
  descriptor.SlopeScaledDepthBias = 0;
  descriptor.DepthClipEnable = false;
  descriptor.ScissorEnable = false;
  descriptor.MultisampleEnable = false;
  descriptor.AntialiasedLineEnable = false;
  //descriptor.

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateRasterizerState(&descriptor,&m_id);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void 
DX11RasterizerState::release()
{
  if(m_id){
    m_id->Release();
  }
  m_id = 0;
}


}

