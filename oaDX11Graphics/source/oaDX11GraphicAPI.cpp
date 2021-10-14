#include "oaDX11GraphicAPI.h"
#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>
#include <iostream>

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

void oaEngineSDK::DX11GraphicAPI::initialize()
{
  std::cout<<"directX graphic API"<<std::endl;

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
  wc.hbrBackground = ( HBRUSH )COLOR_BACKGROUND;
  wc.lpszClassName = "oasisWindow";

  // register the window class
  RegisterClassEx(&wc);



  //g_hInst = hInstance;
  hWnd = CreateWindowEx(NULL,
                        "oasisWindow",    // name of the window class
                        "Oasis Engine",   // title of the window
                        WS_OVERLAPPEDWINDOW,    // window style
                        300,    // x-position of the window
                        300,    // y-position of the window
                        500,    // width of the window
                        400,    // height of the window
                        NULL,    // we have no parent window, NULL
                        NULL,    // we aren't using menus, NULL
                        GetModuleHandleA(nullptr),    // application handle
                        NULL);    // used with multiple windows, NULL

                                  // display the window on the screen
  //ShowWindow(hWnd, nCmdShow);

  ShowWindow(hWnd, SW_SHOWDEFAULT);

  MSG msg;

  // wait for the next message in the queue, store the result in 'msg'
  while(GetMessage(&msg, NULL, 0, 0))
  {
    // translate keystroke messages into the right format
    TranslateMessage(&msg);

    // send the message to the WindowProc function
    DispatchMessage(&msg);
  }
}
