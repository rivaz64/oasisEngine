/**
* @file oaDX11GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaGraphicAPI.h"
#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>

namespace oaEngineSDK{

class OA_DX11_EXPORT DX11GraphicAPI :
  public GraphicAPI
{
 public:

  bool
  initialize() override;

  bool
  isRunning() override;

  void
  events() override;

 protected:

  DX11GraphicAPI() = default;

  D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_NULL;
  D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;
  ID3D11Device*           device = nullptr;
  ID3D11DeviceContext*    context = nullptr;
  IDXGISwapChain*         swapChain = nullptr;
  ID3D11RenderTargetView* renderTargetView = nullptr;
  MSG msg = MSG();

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


