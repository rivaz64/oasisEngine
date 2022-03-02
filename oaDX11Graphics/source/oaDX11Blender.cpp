#include "oaDX11Blender.h"
#include "oaDX11GraphicAPI.h"

namespace oaEngineSDK{

bool 
DX11Blender::init()
{
  D3D11_BLEND_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.AlphaToCoverageEnable = true;


  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateBlendState(&desc,&m_id);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

}

