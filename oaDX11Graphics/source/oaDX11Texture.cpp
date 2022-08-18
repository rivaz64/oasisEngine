#include "oaDX11Texture.h"
#include <oaVector2U.h>
#include "oaImage.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"
#include "oaLogger.h"


namespace oaEngineSDK{

DX11Texture::~DX11Texture()
{
  release();
}

void
DX11Texture::release()
{
  if(m_shaderResourceView){
    m_shaderResourceView->Release();
    m_shaderResourceView = nullptr;
  }
  if(m_depthStencilView){
    m_depthStencilView->Release();
    m_depthStencilView = nullptr;
  }
  if(m_shaderResourceView){
    m_shaderResourceView->Release();
    m_shaderResourceView = nullptr;
  }
  if(m_texture){
    m_texture->Release();
    m_texture = nullptr;
  }
}

void* 
DX11Texture::getId()
{
  return m_shaderResourceView;
}

bool
DX11Texture::init(const Vector2I& size,BIND::E bind, FORMAT::E format, const void* data, uint32 pitch)
{
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  HRESULT hr;

  D3D11_TEXTURE2D_DESC desc;
  memset( &desc,0, sizeof(desc) );
  desc.Width = size.x;
  desc.Height =  size.y;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = Flags::TEXTURE_FORMATS[format];
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = Flags::BINDS[bind];
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  if(data){
    D3D11_SUBRESOURCE_DATA imageSubresourceData;
    memset( &imageSubresourceData,0, sizeof(D3D11_SUBRESOURCE_DATA) );
    imageSubresourceData.pSysMem = data;
    imageSubresourceData.SysMemPitch = pitch;
    hr = device->CreateTexture2D( &desc, &imageSubresourceData, &m_texture );
  }
  else{
    hr = device->CreateTexture2D( &desc, nullptr, &m_texture );
  }
  
  if(FAILED(hr)){
    OA_DEBUG_LOG("error on CreateTexture2D");
    return false;
  }

  if(!createShaderResource(format)){
    return false;
  }
  
  if(bind == BIND::kRenderTarget){
    if(!createRenderTarget(format)){
      return false;
    }
  }

  if(bind == BIND::kDepthStencil){
    if(!createDepthStencil(format)){
      return false;
    }
  }

  m_format = format;

  return true;
}

bool 
DX11Texture::createShaderResource(FORMAT::E format)
{
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  memset( &srvDesc,0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC) );
  srvDesc.Format =  Flags::SHADER_RESOURCE_FORMATS[format];
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MipLevels = 1;
  srvDesc.Texture2D.MostDetailedMip = 0;

  HRESULT hr = device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);

  if(FAILED(hr)){
    OA_DEBUG_LOG("error on CreateShaderResourceView");
    return false;
  }
  return true;
}

bool
DX11Texture::createRenderTarget(FORMAT::E format)
{
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
  memset( &renderTargetDesc,0, sizeof(renderTargetDesc) );
  renderTargetDesc.Format = Flags::TEXTURE_FORMATS[format];
  renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

  HRESULT hr = device->CreateRenderTargetView(m_texture, NULL, &m_renderTargetView );

  if(FAILED(hr)){
    OA_DEBUG_LOG("error on CreateRenderTargetView");
    return false;
  }
  return true;
}

bool 
DX11Texture::createDepthStencil(FORMAT::E format)
{
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  memset( &descDSV,0, sizeof(descDSV) );
  descDSV.Format = Flags::DEPTH_STENCIL_FORMATS[format];
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  
  HRESULT hr = device->CreateDepthStencilView(m_texture,&descDSV,&m_depthStencilView);

  if(FAILED(hr)){
    OA_DEBUG_LOG("error on CreateDepthStencilView");
    return false;
  }
  return true;
}



//void
//DX11Texture::initForDepthStencil(const Vector2U& size)
//{
//  auto& graphicApi = GraphicAPI::instance();
//  D3D11_TEXTURE2D_DESC desc;
//  memset( &desc,0, sizeof(desc) );
//  desc.Width = size.x;
//  desc.Height =  size.y;
//  desc.MipLevels = 1;
//  desc.ArraySize = 1;
//  desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
//  desc.SampleDesc.Count = 1;
//  desc.SampleDesc.Quality = 0;
//  desc.Usage = D3D11_USAGE_DEFAULT;
//  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_DEPTH_STENCIL;//D3D11_BIND_SHADER_RESOURCE;
//  desc.CPUAccessFlags = 0;
//  desc.MiscFlags = 0;
//
//  m_image = makeSPtr<Image>();
//
//  m_image->setFormat(FORMAT::kD24UNormS8UInt);
//   
//  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//    m_device->CreateTexture2D( &desc, nullptr, &m_texture );
//
//  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//  srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
//  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//  srvDesc.Texture2D.MipLevels = 1;
//  srvDesc.Texture2D.MostDetailedMip = 0;
//
//  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//   m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);
//}
//
//void 
//DX11Texture::initForRenderTarget(const Vector2U& size)
//{
//  auto& graphicApi = GraphicAPI::instance();
//  D3D11_TEXTURE2D_DESC desc;
//  memset( &desc,0, sizeof(desc) );
//  desc.Width = size.x;
//  desc.Height =  size.y;
//  desc.MipLevels = 1;
//  desc.ArraySize = 1;
//  desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//  desc.SampleDesc.Count = 1;
//  desc.SampleDesc.Quality = 0;
//  desc.Usage = D3D11_USAGE_DEFAULT;
//  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
//  desc.CPUAccessFlags = 0;
//  desc.MiscFlags = 0;
//
//  m_image = makeSPtr<Image>();
//
//  m_image->setFormat(FORMAT::kR32G32B32A32Float);
//   
//  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//    m_device->CreateTexture2D( &desc, nullptr, &m_texture );
//
//  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//  srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//  srvDesc.Texture2D.MipLevels = 1;
//  srvDesc.Texture2D.MostDetailedMip = 0;
//
//  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//   m_device->CreateShaderResourceView(m_texture,&srvDesc,&m_shaderResourceView);
//}

}

