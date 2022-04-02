//#include "oaDX11DepthStencil.h"
//#include "oaDX11Texture.h"
//#include "oaDX11GraphicAPI.h"
//#include "oaDX11Flags.h"
//
//namespace oaEngineSDK{
//
//DX11DepthStencil::~DX11DepthStencil()
//{
//  release();
//}
//
//bool 
//DX11DepthStencil::init(SPtr<Texture> texture)
//{
//  //D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
//  //memset( &descDSV,0, sizeof(descDSV) );
//  //descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//  //descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//  //descDSV.Texture2D.MipSlice = 0;
//  ////D3D11_DEPTH_STENCIL_DESC
//  //
//  //HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//  // m_device->CreateDepthStencilView(cast<DX11Texture>(texture)->m_texture,
//  //                                  &descDSV, 
//  //                                  &m_depthStencilView);
//  //
//  //D3D11_DEPTH_STENCIL_DESC desc;
//  //memset( &desc,0, sizeof(desc) );
//  //desc.DepthEnable = true;
//	//desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	//desc.DepthFunc = D3D11_COMPARISON_LESS;
//	//desc.StencilEnable = true;
//	//desc.StencilReadMask = 0xFF;
//	//desc.StencilWriteMask = 0xFF;
//	//desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	//desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
//	//desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	//desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	//desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	//desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
//	//desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	//desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//  //
//  //hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
//  // m_device->CreateDepthStencilState(&desc,&m_depthStencilState);
//  //
//  //if(FAILED(hr)){
//  //  return false;
//  //}
//  //
//  //return true;
//}
//
//void
//DX11DepthStencil::release()
//{
//  //if( m_depthStencilView ) m_depthStencilView->Release();
//  //m_depthStencilView = nullptr;
//  //if( m_depthStencilState ) m_depthStencilState->Release();
//  //m_depthStencilState = nullptr;
//}
//
//}


