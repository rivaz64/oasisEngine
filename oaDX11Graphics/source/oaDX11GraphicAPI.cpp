#include "oaDX11GraphicAPI.h"
#include <d3d11.h>
#include <oaVector2U.h>
#include <oaInputManager.h>
#include "oaDX11VertexShader.h"
#include "oaDX11PixelShader.h"
#include "oaDX11Buffer.h"
#include "oaDX11Texture.h"
#include "oaDX11SamplerState.h"
#include "oaDX11RenderTarget.h"
#include "oaDX11DepthStencil.h"
#include "oaDX11VertexBuffer.h"
#include "oaDX11IndexBuffer.h"
#include "oaDX11ShaderProgram.h"
#include "oaDX11Rasterizer.h"
#include "oaDX11Blender.h"



namespace oaEngineSDK{

void 
DX11GraphicAPI::onShutDown()
{
  if( m_context ) m_context->ClearState();

  if( m_swapChain ) m_swapChain->Release();
  if( m_context ) m_context->Release();
  if( m_device ) m_device->Release();
}

bool
DX11GraphicAPI::initialize(void* window)
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

  HRESULT hr = S_OK;

  auto size = getWindowSize(window);

  DXGI_SWAP_CHAIN_DESC sd;
  memset( &sd, 0, sizeof( sd ) );
  sd.BufferCount = 1;
  sd.BufferDesc.Width = size.x;
  sd.BufferDesc.Height = size.y;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = reinterpret_cast<HWND>(window);
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;

  for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
  {
    m_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                       D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, &m_featureLevel, &m_context );
    if( SUCCEEDED( hr ) )
      break;
  }
  if( FAILED( hr ) ){
    std::cout<<"failed to start up"<<std::endl;
    return false;
  }

  return true;
}

void*
DX11GraphicAPI::createWindow(void* app, const Vector2U& size, const String& name)
{
  WNDCLASSEX wc;

  memset(&wc,0, sizeof(WNDCLASSEX));

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = static_cast<WNDPROC>(eventsFunction);
  wc.hInstance = GetModuleHandleA(nullptr);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = ( HBRUSH )COLOR_ACTIVECAPTION;
  wc.lpszClassName = "oasisEngine";
  wc.cbWndExtra = sizeof(void*);

  RegisterClassEx(&wc);
  
  HWND hWnd;

  hWnd = CreateWindowEx(NULL,
                        "oasisEngine", 
                        name.c_str(),   
                        WS_OVERLAPPEDWINDOW,    
                        300,    
                        200,   
                        size.x,  
                        size.y,    
                        nullptr,    
                        nullptr,    
                        GetModuleHandleA(nullptr),   
                        nullptr); 

  SetWindowLongPtr(hWnd,0,reinterpret_cast<LONG_PTR>(app));

  ShowWindow(hWnd, SW_SHOWDEFAULT); 

  return hWnd;
}

bool 
DX11GraphicAPI::isRunning()
{
  return m_msg.message != WM_QUIT;
}

void 
DX11GraphicAPI::events()
{

  Map<char,bool>& inputs = InputManager::instancePtr()->m_inputs;
  
  for(auto key : inputs){
    if(GetKeyState(key.first) & 0x8000){
      inputs[key.first] = true;
    }
    else{
      inputs[key.first] = false;
    }
  }

  POINT p;

  GetCursorPos(&p);

  Vector2I temp(p.x,p.y);

  InputManager::instancePtr()->m_mouseDelta = temp-InputManager::instancePtr()->m_mousePosition;

  InputManager::instancePtr()->m_mousePosition = temp;

  if (GetQueueStatus(QS_ALLINPUT))
  while( PeekMessage( &m_msg, NULL, 0, 0, PM_REMOVE ) )
  {
    TranslateMessage( &m_msg );
    DispatchMessage( &m_msg );
  }
}

SPtr<ShaderProgram> 
DX11GraphicAPI::createShaderProgram()
{
  return makeSPtr<DX11ShaderProgram>();
}

SPtr<Shader> 
DX11GraphicAPI::createVertexShader()
{
  return makeSPtr<DX11VertexShader>();
}

SPtr<Shader> 
DX11GraphicAPI::createPixelShader()
{
  return makeSPtr<DX11PixelShader>();
}

SPtr<Buffer> 
DX11GraphicAPI::createBuffer()
{
  return makeSPtr<DX11Buffer>();
}

SPtr<VertexBuffer> 
DX11GraphicAPI::createVertexBuffer()
{
  return makeSPtr<DX11VertexBuffer>();
}

SPtr<IndexBuffer> 
DX11GraphicAPI::createIndexBuffer()
{
  return makeSPtr<DX11IndexBuffer>();
}

SPtr<Texture> 
DX11GraphicAPI::createTexture()
{
  return makeSPtr<DX11Texture>();
}

SPtr<SamplerState> 
DX11GraphicAPI::createSamplerState(const SamplerDesc& descriptor)
{
  auto sampler = makeSPtr<DX11SamplerState>();
  sampler->init(descriptor);
  return sampler;
}

SPtr<RenderTarget> 
DX11GraphicAPI::createRenderTarget()
{
  return makeSPtr<DX11RenderTarget>();
}

SPtr<DepthStencil> 
DX11GraphicAPI::createDepthStencil()
{
  return makeSPtr<DX11DepthStencil>();
}

SPtr<Rasterizer> DX11GraphicAPI::createRasterizer()
{
  return makeSPtr<DX11Rasterizer>();
}

SPtr<Blender> DX11GraphicAPI::createBlender()
{
  return makeSPtr<DX11Blender>();
}

void 
DX11GraphicAPI::setBackgroundColor(const Color& color)
{
  m_backgroundColor = color;
}

SPtr<Texture> 
DX11GraphicAPI::getBackBuffer()
{
  if(!m_swapChain) return SPtr<Texture>();
  auto backBuffer = createTexture();

  HRESULT hr = m_swapChain->GetBuffer( 
    0, 
    __uuidof( ID3D11Texture2D ), 
    ( LPVOID* )&cast<DX11Texture>(backBuffer)->m_texture );

  if( FAILED( hr ) ){
    std::cout<<"failed to get backBuffer"<<std::endl;
  }

  return backBuffer;
}

void 
DX11GraphicAPI::draw(uint32 indexes)
{
  m_context->DrawIndexed(indexes, 0, 0);
}

void 
DX11GraphicAPI::show()
{
  m_swapChain->Present( 0, 0 );
}

void 
DX11GraphicAPI::setTexture(const SPtr<Texture> texture, uint8 location)
{
  m_context->PSSetShaderResources(location, 1, &cast<DX11Texture>(texture)->m_shaderResourceView );
}

void 
DX11GraphicAPI::setVSBuffer(const SPtr<Buffer> buffer, uint32 location)
{
  m_context->VSSetConstantBuffers( location, 1, &cast<DX11Buffer>(buffer)->m_buffer );
}

void 
DX11GraphicAPI::setPSBuffer(const SPtr<Buffer> buffer, uint32 location)
{
  m_context->PSSetConstantBuffers( location, 1, &cast<DX11Buffer>(buffer)->m_buffer );
}

void 
DX11GraphicAPI::setSamplerState(const SPtr<SamplerState> sampler)
{
  m_context->PSSetSamplers( 0, 1, &cast<DX11SamplerState>(sampler)->m_samplerState);
}

void 
DX11GraphicAPI::setRasterizer(const SPtr<Rasterizer> rasterizer)
{
  m_context->RSSetState(cast<DX11Rasterizer>(rasterizer)->m_id);
}

void 
DX11GraphicAPI::setBlender(const SPtr<Blender> blender)
{
  //m_context->OMSetBlendState(cast<DX11Blender>(blender)->m_id);
}

void 
DX11GraphicAPI::setRenderTarget(const SPtr<RenderTarget> renderTarget)
{
  m_context->OMSetRenderTargets( 
    1,
    &cast<DX11RenderTarget>(renderTarget)->m_renderTargetView, 
    nullptr
  );
}

void
DX11GraphicAPI::setRenderTargets(const Vector<SPtr<RenderTarget>>& renderTargets)
{
  SIZE_T numOfRenders = renderTargets.size();
  ID3D11RenderTargetView** renders = new ID3D11RenderTargetView*[numOfRenders];

  for(SIZE_T renderNum = 0; renderNum<numOfRenders; ++renderNum){
    renders[renderNum] = cast<DX11RenderTarget>(renderTargets[renderNum])->m_renderTargetView;
  }

  m_context->OMSetRenderTargets( 
    numOfRenders,
    renders, 
    nullptr
  );
}

void 
DX11GraphicAPI::setRenderTargetAndDepthStencil(
  const SPtr<RenderTarget> renderTarget, 
  const SPtr<DepthStencil> depthStencil
)
{
  m_context->OMSetRenderTargets( 
    1,
    &cast<DX11RenderTarget>(renderTarget)->m_renderTargetView, 
    cast<DX11DepthStencil>(depthStencil)->m_depthStencil
  );
  m_context->OMSetDepthStencilState(cast<DX11DepthStencil>(depthStencil)->m_depthState, 1);
}

void
DX11GraphicAPI::setRenderTargetsAndDepthStencil(
  const Vector<SPtr<RenderTarget>>& renderTargets, 
  const SPtr<DepthStencil> depthStencil)
{
  SIZE_T numOfRenders = renderTargets.size();
  ID3D11RenderTargetView** renders = new ID3D11RenderTargetView*[numOfRenders];

  for(SIZE_T renderNum = 0; renderNum<numOfRenders; ++renderNum){
    renders[renderNum] = cast<DX11RenderTarget>(renderTargets[renderNum])->m_renderTargetView;
  }

  m_context->OMSetRenderTargets( 
    numOfRenders,
    renders, 
    cast<DX11DepthStencil>(depthStencil)->m_depthStencil
  );
}

void 
DX11GraphicAPI::unsetRenderTargetAndDepthStencil()
{
  if(!m_context) return;
  m_context->OMSetRenderTargets(0,0,0);
}

void 
DX11GraphicAPI::clearRenderTarget(SPtr<RenderTarget> renderTarget)
{
  m_context->ClearRenderTargetView(
    cast<DX11RenderTarget>(renderTarget)->m_renderTargetView, 
    &m_backgroundColor.r );
}

void 
DX11GraphicAPI::clearDepthStencil(SPtr<DepthStencil> depthStencil)
{
  m_context->ClearDepthStencilView(
    cast<DX11DepthStencil>(depthStencil)->m_depthStencil,
    D3D11_CLEAR_DEPTH, 
    1.0f, 
    0
  );
}

Vector2U 
DX11GraphicAPI::getWindowSize(void* window)
{
  RECT rc;
  GetClientRect( reinterpret_cast<HWND>(window), &rc );
  return Vector2U( rc.right - rc.left, rc.bottom - rc.top);
}

void
DX11GraphicAPI::setViewport(const Vector2U& size)
{
  D3D11_VIEWPORT vp;
  vp.Width = static_cast<float>(size.x);
  vp.Height = static_cast<float>(size.y);
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  m_context->RSSetViewports( 1, &vp );
}

void 
DX11GraphicAPI::resizeSwapChain(const Vector2U& size)
{
  m_swapChain->ResizeBuffers(0, size.x, size.y, DXGI_FORMAT_UNKNOWN, 0);
}

void* 
DX11GraphicAPI::getDevice()
{
  return m_device;
}

void* 
DX11GraphicAPI::getContext()
{
  return m_context;
}


}