#include "oaDX11GraphicAPI.h"
#include "oaDX11VertexShader.h"
#include "oaDX11PixelShader.h"
#include <windows.h>
#include <d3d11.h>
#include <iostream>

namespace oaEngineSDK{

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;

  switch( message )
  {
  case WM_PAINT:
    hdc = BeginPaint( hWnd, &ps );
    EndPaint( hWnd, &ps );
    break;

  case WM_DESTROY:
    PostQuitMessage( 0 );
    break;

  default:
    return DefWindowProc( hWnd, message, wParam, lParam );
  }

  return 0;
}

bool 
DX11GraphicAPI::initialize()
{
  std::cout<<"directX graphic API"<<std::endl;

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

  HWND hWnd;
  // this struct holds information for the window class
  WNDCLASSEX wc;

  // clear out the window class for use
  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  // fill in the struct with the needed information
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
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

  

  ID3D11Texture2D* pBackBuffer = NULL;
  hr = swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
  if( FAILED( hr ) ){
    std::cout<<"failed to get backBuffer"<<std::endl;
    return false;
  }
    

  hr = device->CreateRenderTargetView( pBackBuffer, NULL, &renderTargetView );
  pBackBuffer->Release();
  if( FAILED( hr ) ){
    std::cout<<"failed to set backBuffer"<<std::endl;
    return false;
  }

  context->OMSetRenderTargets( 1, &renderTargetView, NULL );

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)windowWidth;
  vp.Height = (FLOAT)windowHeight;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  context->RSSetViewports( 1, &vp );

  ShowWindow(hWnd, SW_SHOWDEFAULT);

  vertexShader = newSPtr<DX11VertexShader>();

  pixelShader = newSPtr<DX11PixelShader>();

  return GraphicAPI::initialize();
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

}