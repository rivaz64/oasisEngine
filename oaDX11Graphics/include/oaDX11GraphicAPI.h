/**
* @file oaDX11GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaGraphicAPI.h"
#include "oaVector4f.h"
#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>

namespace oaEngineSDK{

class DX11GraphicAPI :
  public GraphicAPI
{
 public:

  void
  onShutDown() override;

  bool
  initialize() override;

  bool
  isRunning() override;

  void
  events() override;

  SPtr<Buffer>
  createBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  SPtr<SamplerState>
  createSamplerState(SamplerDesc descriptor) override;

  SPtr<RenderTarget>
  createRenderTarget(SPtr<Texture> texture) override;

  void
  setBackgroundColor(const Vector4f& color) override;

  SPtr<Texture>
  getBackBuffer() override;

  void
  clear() override;

  void
  draw(uint32 indexes) override;

  void
  show() override;

  void
  setVertexBuffer(const SPtr<Buffer>& buffer) override;

  void
  setIndexBuffer(const SPtr<Buffer>& buffer) override;

  void
  setTexture(const SPtr<Texture>& texture) override;

  void
  setBuffer(const SPtr<Buffer>& buffer,uint32 location) override;

  void
  setSamplerState(const SPtr<SamplerState> sampler) override;

  void
  setRenderTarget(const SPtr<RenderTarget> renderTarget);

  void
  clearRenderTarget(SPtr<RenderTarget> renderTarget);

  virtual void*
  getWindow() override;

  virtual void*
  getDevice() override;

  virtual void*
  getContext() override;

 protected:

  DX11GraphicAPI() = default;

 public:
   HWND hWnd;
  D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
  D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
  ID3D11Device* device = nullptr;
  ID3D11DeviceContext* context = nullptr;
  IDXGISwapChain* swapChain = nullptr;
  //ID3D11RenderTargetView* renderTargetView = nullptr;
  ID3D11Texture2D* depthStencil = nullptr;
  ID3D11DepthStencilView* depthStencilView = nullptr;

  MSG msg = MSG();

  Vector4f backgroundColor;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


