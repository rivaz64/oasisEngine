#include "oaDX11Texture.h"
#include "oaPath.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"


namespace oaEngineSDK{

DX11Texture::~DX11Texture()
{
  if(shaderResourceView) shaderResourceView->Release();
  if(texture) texture->Release();
}

bool 
DX11Texture::loadFromFile(const Path& file)
{
  HRESULT hr;

  Path p;
  String f=file.getCompletePath();

  hr = D3DX11CreateShaderResourceViewFromFile(
    reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->device,
    f.c_str(),
    nullptr,
    nullptr,
    &shaderResourceView,
    nullptr
  );

  if(FAILED(hr))
    return false;

  return true;
}

bool 
DX11Texture::init(TextureDesc description)
{
  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.Width = description.width;
  descDepth.Height = description.height;
  descDepth.MipLevels = description.mipLevels;
  descDepth.ArraySize = description.arraySize;
  descDepth.Format = Flags::FORMATS[description.format];
  descDepth.SampleDesc.Count = description.sampleCount;
  descDepth.SampleDesc.Quality = description.sampleQuality;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = Flags::FLAGS[description.bind];
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateTexture2D( &descDepth, NULL, &texture );

  if(FAILED( hr ))
    return false;

  return true;
}

bool 
DX11Texture::init(TextureDesc description, ShaderResourseViewDesc descriptionSRV)
{
  if(!init(description)){
    return false;
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  ZeroMemory( &srvDesc, sizeof(srvDesc) );
  srvDesc.Format = Flags::FORMATS[descriptionSRV.format];
  srvDesc.ViewDimension = Flags::SRV_DIMENCIONS[descriptionSRV.dimencion];
  srvDesc.Texture2D.MostDetailedMip = descriptionSRV.mostDetailedMip;
  srvDesc.Texture2D.MipLevels = descriptionSRV.mipLevels;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateShaderResourceView(texture,&srvDesc,&shaderResourceView);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void* 
DX11Texture::getId()
{
  return shaderResourceView;
}


}

