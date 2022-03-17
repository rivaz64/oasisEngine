#include "oaBaseApp.h"
#include "TestApp.h"
#include "oaGraphicAPI.h"
#include "../oaDX11Graphics/include/oaDX11GraphicAPI.h"
#include "../oaDX11Graphics/include/oaDX11Texture.h"
#include "../oaDX11Graphics/include/oaDX11RenderTarget.h"
#include "../oaDX11Graphics/include/oaDX11PixelShader.h"
#include "../oaDX11Graphics/include/oaDX11VertexShader.h"
#include "../oaDX11Graphics/include/oaDX11VertexBuffer.h"
using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;

int main(){
  //srand(time(NULL));
  BaseApp* app = new TestApp;
  //app.startUp<TestApp>();
  app->run();
  //app.shutDown();

  delete app;

  app = 0;

  return 0;
}
//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dcompiler.h>
//#include <xnamath.h>
//
////{{NO_DEPENDENCIES}}
//// Microsoft Visual C++ generated include file.
//// Used by Tutorial03.rc
////
//
//#define IDS_APP_TITLE           103
//
//#define IDR_MAINFRAME           128
//#define IDD_TUTORIAL1_DIALOG    102
//#define IDD_ABOUTBOX            103
//#define IDM_ABOUT               104
//#define IDM_EXIT                105
//#define IDI_TUTORIAL1           107
//#define IDI_SMALL               108
//#define IDC_TUTORIAL1           109
//#define IDC_MYICON              2
//#define IDC_STATIC              -1
//// Next default values for new objects
//// 
//#ifdef APSTUDIO_INVOKED
//#ifndef APSTUDIO_READONLY_SYMBOLS
//
//#define _APS_NO_MFC                 130
//#define _APS_NEXT_RESOURCE_VALUE    129
//#define _APS_NEXT_COMMAND_VALUE     32771
//#define _APS_NEXT_CONTROL_VALUE     1000
//#define _APS_NEXT_SYMED_VALUE       110
//#endif
//#endif
//
//
////--------------------------------------------------------------------------------------
//// Structures
////--------------------------------------------------------------------------------------
//struct SimpleVertex
//{
//    oaEngineSDK::Vector4f Pos;
//};
//
//
////--------------------------------------------------------------------------------------
//// Global Variables
////--------------------------------------------------------------------------------------
//
//HWND                    g_hWnd = NULL;
////ID3D11DeviceContext*    g_pImmediateContext = NULL;
//IDXGISwapChain*         g_pSwapChain = NULL;
//ID3D11RenderTargetView* g_pRenderTargetView = NULL;
//ID3D11VertexShader*     g_pVertexShader = NULL;
//ID3D11PixelShader*      g_pPixelShader = NULL;
//ID3D11InputLayout*      g_pVertexLayout = NULL;
//ID3D11Buffer*           g_pVertexBuffer = NULL;
//
//oaEngineSDK::SPtr<oaEngineSDK::RenderTarget> renderTarget;
//oaEngineSDK::SPtr<oaEngineSDK::Shader> pixelShader;
//oaEngineSDK::SPtr<oaEngineSDK::Shader> vertexShader;
//oaEngineSDK::SPtr<oaEngineSDK::VertexBuffer> vertexBuffer;
////--------------------------------------------------------------------------------------
//// Forward declarations
////--------------------------------------------------------------------------------------
//HRESULT InitWindow( /*HINSTANCE hInstance, int nCmdShow*/ );
//HRESULT InitDevice();
//void CleanupDevice();
//LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
//void Render();
//
//using Function = const void* (*)();
//
//void loadPlugIn(const oaEngineSDK::String& DLL){
//  HINSTANCE hGetProcIDDLL = LoadLibrary(DLL.c_str());
//  if(!hGetProcIDDLL)
//  {
//    //print("Could not load Dll");
//    return;
//  }
//
//  Function foundFunction = reinterpret_cast<Function>(GetProcAddress(hGetProcIDDLL, "initPlugIn"));
//  if(!foundFunction())
//  {
//    //print("Could not find function");
//    return;
//  }
//  //print("everything working");
//}
////--------------------------------------------------------------------------------------
//// Entry point to the program. Initializes everything and goes into a message processing 
//// loop. Idle time is used to render the scene.
////--------------------------------------------------------------------------------------
//int WINAPI main(/* HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow */)
//{
//    //UNREFERENCED_PARAMETER( hPrevInstance );
//    //UNREFERENCED_PARAMETER( lpCmdLine );
//
//    loadPlugIn("oaDX11Graphicsd.dll");
//
//    if( FAILED( InitWindow( /*hInstance, nCmdShow*/ )) )
//        return 0;
//
//    if( FAILED( InitDevice() ) )
//    {
//        CleanupDevice();
//        return 0;
//    }
//
//    // Main message loop
//    MSG msg = {0};
//    while( WM_QUIT != msg.message )
//    {
//        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
//        {
//            TranslateMessage( &msg );
//            DispatchMessage( &msg );
//        }
//        else
//        {
//            Render();
//        }
//    }
//
//    CleanupDevice();
//
//    return ( int )msg.wParam;
//}
//
//
////--------------------------------------------------------------------------------------
//// Register class and create window
////--------------------------------------------------------------------------------------
//HRESULT InitWindow( /*HINSTANCE hInstance, int nCmdShow*/ )
//{
//  auto& api = oaEngineSDK::GraphicAPI::instance();
//  g_hWnd = reinterpret_cast<HWND>(api.createWindow(WndProc,nullptr,oaEngineSDK::Vector2U(640, 480),"oaEngine"));
//   return S_OK;
//}
//
//
////--------------------------------------------------------------------------------------
//// Helper for compiling shaders with D3DX11
////--------------------------------------------------------------------------------------
//HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
//{
//    HRESULT hr = S_OK;
//
//    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//    // Setting this flag improves the shader debugging experience, but still allows 
//    // the shaders to be optimized and to run exactly the way they will run in 
//    // the release configuration of this program.
//    dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
//
//    ID3DBlob* pErrorBlob;
//    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
//        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
//    if( FAILED(hr) )
//    {
//        if( pErrorBlob != NULL )
//            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
//        if( pErrorBlob ) pErrorBlob->Release();
//        return hr;
//    }
//    if( pErrorBlob ) pErrorBlob->Release();
//
//    return S_OK;
//}
//
//
////--------------------------------------------------------------------------------------
//// Create Direct3D device and swap chain
////--------------------------------------------------------------------------------------
//HRESULT InitDevice()
//{
//    HRESULT hr = S_OK;
//
//    auto api = oaEngineSDK::GraphicAPI::instancePtr();
//    api->initialize(g_hWnd);
//
//    RECT rc;
//    GetClientRect( g_hWnd, &rc );
//    UINT width = rc.right - rc.left;
//    UINT height = rc.bottom - rc.top;
//
//    g_pSwapChain = reinterpret_cast<oaEngineSDK::DX11GraphicAPI*>(api)->m_swapChain;
//
//    renderTarget = api->createRenderTarget();
//
//    renderTarget->init(api->getBackBuffer());
//
//    api->setRenderTarget(renderTarget);
//
//    g_pRenderTargetView = oaEngineSDK::cast<oaEngineSDK::DX11RenderTarget>(renderTarget)->m_renderTargetView;
//
//    api->setViewport(oaEngineSDK::Vector2U(width,height));
//
//     ID3DBlob* pVSBlob = NULL;
//     vertexShader = api->createVertexShader();
//  oaEngineSDK::cast<oaEngineSDK::DX11VertexShader>(vertexShader)->m_version = "vs_4_0";
//  oaEngineSDK::cast<oaEngineSDK::DX11VertexShader>(vertexShader)->compileFromFile("Screen");
//  pVSBlob = oaEngineSDK::cast<oaEngineSDK::DX11VertexShader>(vertexShader)->m_blob;
//  g_pVertexShader = oaEngineSDK::cast<oaEngineSDK::DX11VertexShader>(vertexShader)->m_shader;
//  g_pVertexLayout = oaEngineSDK::cast<oaEngineSDK::DX11VertexShader>(vertexShader)->m_inputLayout;
//
//    pixelShader = api->createPixelShader();
//    pixelShader->compileFromFile("lights");
//    g_pPixelShader = oaEngineSDK::cast<oaEngineSDK::DX11PixelShader>(pixelShader)->m_shader;
//
//    // Create vertex buffer
//  oaEngineSDK::Vector<oaEngineSDK::Vector4f> vertices{
//    oaEngineSDK::Vector4f( 0.0f, 0.5f, 0.5f, 1.0f ),
//    oaEngineSDK::Vector4f( 0.5f, -0.5f, 0.5f, 1.0f ),
//    oaEngineSDK::Vector4f( -0.5f, -0.5f, 0.5f, 1.0f),
//    //SimpleVertex(Vector4f(1,1,.5f,0),Vector2f(1,1)),
//  };
//
//  vertexBuffer = api->createVertexBuffer();
//  vertexBuffer->init(vertices.data(),sizeof(oaEngineSDK::Vector4f),vertices.size());
//  vertexBuffer->set();
//  g_pVertexBuffer = oaEngineSDK::cast<oaEngineSDK::DX11VertexBuffer>(pixelShader)->m_buffer;
//
//  api->setPrimitiveTopology(oaEngineSDK::PRIMITIVE_TOPOLOGY::kTrianlgeList);
//
//    return S_OK;
//}
//
//
////--------------------------------------------------------------------------------------
//// Clean up the objects we've created
////--------------------------------------------------------------------------------------
//void CleanupDevice()
//{
//    //if( g_pImmediateContext ) g_pImmediateContext->ClearState();
//
//    if( g_pVertexBuffer ) g_pVertexBuffer->Release();
//    if( g_pVertexLayout ) g_pVertexLayout->Release();
//    if( g_pVertexShader ) g_pVertexShader->Release();
//    if( g_pPixelShader ) g_pPixelShader->Release();
//    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
//    if( g_pSwapChain ) g_pSwapChain->Release();
//}
//
//
////--------------------------------------------------------------------------------------
//// Called every time the application receives a message
////--------------------------------------------------------------------------------------
//LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
//{
//    PAINTSTRUCT ps;
//    HDC hdc;
//
//    switch( message )
//    {
//        case WM_PAINT:
//            hdc = BeginPaint( hWnd, &ps );
//            EndPaint( hWnd, &ps );
//            break;
//
//        case WM_DESTROY:
//            PostQuitMessage( 0 );
//            break;
//
//        default:
//            return DefWindowProc( hWnd, message, wParam, lParam );
//    }
//
//    return 0;
//}
//
//
////--------------------------------------------------------------------------------------
//// Render a frame
////--------------------------------------------------------------------------------------
//void Render()
//{
//    // Clear the back buffer 
//    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
//    //g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );
//    auto api = oaEngineSDK::GraphicAPI::instancePtr();
//    api->clearRenderTarget(renderTarget);
//    vertexShader->set();
//    // Render a triangle
//	//g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
//	//g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
//    pixelShader->set();
//    //g_pImmediateContext->Draw( 3, 0 );
//    api->draw(3);
//    // Present the information rendered to the back buffer to the front buffer (the screen)
//    api->show();
//}