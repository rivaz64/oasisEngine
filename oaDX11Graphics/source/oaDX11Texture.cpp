#include "oaDX11Texture.h"
#include <oaVector2U.h>
#include "oaPath.h"
#include "oaImage.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"



namespace oaEngineSDK{

DX11Texture::~DX11Texture()
{
  release();
}

void
DX11Texture::release()
{
  if(m_shaderResourceView) m_shaderResourceView->Release();
  if(m_texture) m_texture->Release();
}

void* 
DX11Texture::getId()
{
  return m_shaderResourceView;
}

void 
DX11Texture::initFromImage(SPtr<Image> image)
{
  D3D11_TEXTURE2D_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.Width = image->getSize().x;
  desc.Height = image->getSize().y;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = Flags::FORMATS[image->getFormat()];// DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; 
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA image_subresource_data = {};
    
  image_subresource_data.pSysMem = image->getPixels().data();
  image_subresource_data.SysMemPitch = image->getPitch();
   

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateTexture2D( &desc, &image_subresource_data, &m_texture );

  

  m_image = image;

  //reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  //  m_context->UpdateSubresource(m_texture,0,nullptr,image->m_pixels,,0);

  

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  srvDesc.Format = Flags::FORMATS[image->getFormat()];
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  srvDesc.Texture2D.MostDetailedMip = 0;

  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);

}

void
DX11Texture::initForDepthStencil(const Vector2U& size)
{
  auto& graphicApi = GraphicAPI::instance();
  D3D11_TEXTURE2D_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.Width = size.x;
  desc.Height =  size.y;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;//D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  m_image = makeSPtr<Image>();

  m_image->setFormat(FORMAT::kD24UNormS8UInt);
   
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateTexture2D( &desc, nullptr, &m_texture );
}

void 
DX11Texture::initForRenderTarget(const Vector2U& size)
{
  auto& graphicApi = GraphicAPI::instance();
  D3D11_TEXTURE2D_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.Width = size.x;
  desc.Height =  size.y;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  m_image = makeSPtr<Image>();

  m_image->setFormat(FORMAT::kR32G32B32A32Float);
   
  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateTexture2D( &desc, nullptr, &m_texture );

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  srvDesc.Texture2D.MostDetailedMip = 0;

  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
   m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);
}

}

