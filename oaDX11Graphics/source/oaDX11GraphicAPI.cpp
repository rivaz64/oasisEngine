#include "oaDX11GraphicAPI.h"
#include "oaDX11VertexShader.h"
#include "oaDX11PixelShader.h"
#include "oaDX11Buffer.h"
#include "oaDX11Texture.h"
#include "oaDX11SamplerState.h"
#include "oaDX11RenderTarget.h"
#include "oaMesh.h"
#include <windows.h>
#include <d3d11.h>
#include <iostream>


namespace oaEngineSDK{

void DX11GraphicAPI::onShutDown()
{
  if( context ) context->ClearState();

  if( depthStencil ) depthStencil->Release();
  if( depthStencilView ) depthStencilView->Release();
  if( swapChain ) swapChain->Release();
  if( context ) context->Release();
  if( device ) device->Release();
}

bool
DX11GraphicAPI::initialize()
{
  std::cout<<"directX graphic API"<<std::endl;


  // this struct holds information for the window class
  WNDCLASSEX wc;

  // clear out the window class for use
  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  // fill in the struct with the needed information
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = eventsFunction;
  wc.hInstance = GetModuleHandleA(nullptr);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = ( HBRUSH )COLOR_ACTIVECAPTION;
  wc.lpszClassName = "oasisWindow";

  // register the window class
  RegisterClassEx(&wc);

  //g_hInst = hInstance;
  hWnd = CreateWindowEx(NULL,
                        "oasisWindow",    // name of the window class
                        windowName.c_str(),   // title of the window
                        WS_OVERLAPPEDWINDOW,    // window style
                        300,    // x-position of the window
                        200,    // y-position of the window
                        windowWidth,    // width of the window
                        windowHeight,    // height of the window
                        NULL,    // we have no parent window, NULL
                        NULL,    // we aren't using menus, NULL
                        GetModuleHandleA(nullptr),    // application handle
                        NULL);    // used with multiple windows, NULL

                                  // display the window on the screen

  ShowWindow(hWnd, SW_SHOWDEFAULT);

  RECT rc;
  GetClientRect( hWnd, &rc );
  windowWidth = rc.right - rc.left;
  windowHeight = rc.bottom - rc.top;


  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driverTypes[] =
  {
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE( driverTypes );

  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };
  UINT numFeatureLevels = ARRAYSIZE( featureLevels );
  

  HRESULT hr = S_OK;

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory( &sd, sizeof( sd ) );
  sd.BufferCount = 1;
  sd.BufferDesc.Width = windowWidth;
  sd.BufferDesc.Height = windowHeight;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;



  for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
  {
    driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                       D3D11_SDK_VERSION, &sd, &swapChain, &device, &featureLevel, &context );
    if( SUCCEEDED( hr ) )
      break;
  }
  if( FAILED( hr ) ){
    std::cout<<"failed to start up"<<std::endl;
    return false;
  }

  

  //a
  /*auto renderTarget = createRenderTarget(getBackBuffer());  
  a;*/
  

 

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)windowWidth;
  vp.Height = (FLOAT)windowHeight;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  context->RSSetViewports( 1, &vp );

  vertexShader = newSPtr<DX11VertexShader>();

  pixelShader = newSPtr<DX11PixelShader>();

  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.Width = windowWidth;
  descDepth.Height = windowHeight;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  hr = device->CreateTexture2D( &descDepth, NULL, &depthStencil );
  if( FAILED( hr ) )
    return hr;

  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = device->CreateDepthStencilView( depthStencil, &descDSV, &depthStencilView );
  if( FAILED( hr ) )
    return hr;
  /*b;
  setRenderTarget(renderTarget);*/

  return true;
}

bool 
DX11GraphicAPI::isRunning()
{
  return GetMessage(&msg, NULL, 0, 0);
}

void 
DX11GraphicAPI::events()
{
  TranslateMessage(&msg);

  DispatchMessage(&msg);
}

SPtr<Buffer> 
DX11GraphicAPI::createBuffer()
{
  return newSPtr<DX11Buffer>();
}

SPtr<Texture> 
DX11GraphicAPI::createTexture()
{
  return newSPtr<DX11Texture>();
}

SPtr<SamplerState> 
DX11GraphicAPI::createSamplerState(SamplerDesc descriptor)
{
  auto sampler = newSPtr<DX11SamplerState>();
  sampler->init(descriptor);
  return sampler;
}

SPtr<RenderTarget> 
DX11GraphicAPI::createRenderTarget(SPtr<Texture> texture)
{
  auto renderTarget = newSPtr<DX11RenderTarget>();
  renderTarget->init(texture);
  return renderTarget;
}

void 
DX11GraphicAPI::setBackgroundColor(const Vector4f& color)
{
  backgroundColor = color;
}

SPtr<Texture> DX11GraphicAPI::getBackBuffer()
{
  auto backBuffer = createTexture();

  HRESULT hr = swapChain->GetBuffer( 
    0, 
    __uuidof( ID3D11Texture2D ), 
    ( LPVOID* )&cast<DX11Texture>(backBuffer)->texture );

  if( FAILED( hr ) ){
    std::cout<<"failed to get backBuffer"<<std::endl;
  }

  return backBuffer;
}

void 
DX11GraphicAPI::clear()
{
  context->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
  //context->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );
}

void 
DX11GraphicAPI::draw(uint32 indexes)
{
  context->DrawIndexed(indexes, 0, 0);
}

void 
DX11GraphicAPI::show()
{
  
  //context->OMSetRenderTargets( 1, &renderTargetView, NULL )
  //context->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );

  swapChain->Present( 0, 0 );
}

void 
DX11GraphicAPI::setVertexBuffer(const SPtr<Buffer>& buffer)
{
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  //SPtr<DX11Buffer> nen = 
  context->IASetVertexBuffers( 
    0, 
    1, 
    &cast<DX11Buffer>(buffer)->buffer,
    &stride, 
    &offset );
}

void 
DX11GraphicAPI::setIndexBuffer(const SPtr<Buffer>& buffer)
{
  context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );  
  context->IASetIndexBuffer(cast<DX11Buffer>(buffer)->buffer,DXGI_FORMAT_R32_UINT,0 );
}

void 
DX11GraphicAPI::setTexture(const SPtr<Texture>& texture)
{
  context->PSSetShaderResources( 0, 1, &cast<DX11Texture>(texture)->shaderResourceView );
}

void 
DX11GraphicAPI::setBuffer(const SPtr<Buffer>& buffer, uint32 location)
{

  context->VSSetConstantBuffers( location, 1, &cast<DX11Buffer>(buffer)->buffer );
}

void 
DX11GraphicAPI::setSamplerState(const SPtr<SamplerState> sampler)
{
  context->PSSetSamplers( 0, 1, &cast<DX11SamplerState>(sampler)->samplerState);
}

void 
DX11GraphicAPI::setRenderTarget(const SPtr<RenderTarget> renderTarget)
{
  context->OMSetRenderTargets( 
    1,
    &cast<DX11RenderTarget>(renderTarget)->renderTargetView, 
    depthStencilView );
}

void 
DX11GraphicAPI::clearRenderTarget(SPtr<RenderTarget> renderTarget)
{
  context->ClearRenderTargetView(
    cast<DX11RenderTarget>(renderTarget)->renderTargetView, 
    &backgroundColor.x );
}

void* 
DX11GraphicAPI::getWindow()
{
  return hWnd;
}

void* 
DX11GraphicAPI::getDevice()
{
  return device;
}

void* 
DX11GraphicAPI::getContext()
{
  return context;
}

}