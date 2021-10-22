#include "oaDX11Texture.h"
#include "oaDX11GraphicAPI.h"

namespace oaEngineSDK{

DX11Texture::~DX11Texture()
{
  if(texture) texture->Release();
}

bool DX11Texture::loadFromFile(const String& file)
{
  HRESULT hr;

  hr = D3DX11CreateShaderResourceViewFromFile(
    reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->device,
    file.c_str(),
    nullptr,
    nullptr,
    &texture,
    nullptr
  );

  if(FAILED(hr))
    return false;

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->PSSetShaderResources( 0, 1, &texture );

  return true;
}


}

