#include "oaDX11Texture.h"
#include "oaPath.h"
#include "oaImage.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"



namespace oaEngineSDK{

DX11Texture::~DX11Texture()
{
  if(m_shaderResourceView) m_shaderResourceView->Release();
  if(m_texture) m_texture->Release();
}

bool 
DX11Texture::init(TextureDesc description)
{
  D3D11_TEXTURE2D_DESC descDepth;
  memset( &descDepth, 0, sizeof(descDepth) );
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
    m_device->CreateTexture2D( &descDepth, NULL, &m_texture );

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
  memset( &srvDesc, 0, sizeof(srvDesc) );
  srvDesc.Format = Flags::FORMATS[descriptionSRV.format];
  srvDesc.ViewDimension = Flags::SRV_DIMENCIONS[descriptionSRV.dimencion];
  srvDesc.Texture2D.MostDetailedMip = descriptionSRV.mostDetailedMip;
  srvDesc.Texture2D.MipLevels = descriptionSRV.mipLevels;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);

  if(FAILED(hr)){
    return false;
  }

  return true;
}

void* 
DX11Texture::getId()
{
  return m_shaderResourceView;
}

void 
DX11Texture::initFromImage(SPtr<Image> image)
{
  D3D11_TEXTURE2D_DESC descDepth;
  memset( &descDepth,0, sizeof(descDepth) );
  descDepth.Width = image->m_width;
  descDepth.Height = image->m_height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format =DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; //DXGI_FORMAT_B8G8R8X8_UNORM;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA image_subresource_data = {};
    
  image_subresource_data.pSysMem = image->m_pixels;
  image_subresource_data.SysMemPitch = image->m_pitch;
   

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateTexture2D( &descDepth, &image_subresource_data, &m_texture );

  

  m_image = image;

  //reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  //  m_context->UpdateSubresource(m_texture,0,nullptr,image->m_pixels,,0);

  

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  srvDesc.Texture2D.MostDetailedMip = 0;

  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);

}
/*
void 
DX11Texture::init(uint32 width, uint32 height)
{
  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.Width = width;
  descDepth.Height = height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateTexture2D( &descDepth, NULL, &m_texture );


}
*/

}

