/**
* @file oaDX11GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include <oaGraphicAPI.h>
#include <windows.h>
#include <d3d11.h>
#include <oaColor.h>
#include <oaVector2I.h>



//#include <d3dx11.h>
class BaseApp;

namespace oaEngineSDK{

class DX11GraphicAPI :
  public GraphicAPI
{
 public:

  void
  onShutDown() override;

  bool
  initialize(BaseApp* baseApp) override;

  bool
  isRunning() override;

  void
  events() override;

  SPtr<ShaderProgram>
  createShaderProgram() override;

  SPtr<Shader>
  createVertexShader() override;

  SPtr<Shader>
  createPixelShader () override;

  SPtr<Buffer>
  createBuffer() override;

  SPtr<VertexBuffer> 
  createVertexBuffer() override;

  SPtr<IndexBuffer> 
  createIndexBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  SPtr<SamplerState>
  createSamplerState(const SamplerDesc& descriptor) override;

  SPtr<RenderTarget>
  createRenderTarget(SPtr<Texture> texture) override;

  SPtr<DepthStencil>
  createDepthStencil(const DepthStencilDesc& description, SPtr<Texture> texture) override;

  void
  setBackgroundColor(const Color& color) override;

  SPtr<Texture>
  getBackBuffer() override;

  void
  draw(uint32 indexes) override;

  void
  show() override;

  void
  setTexture(const SPtr<Texture> texture,uint8 location) override;

  void
  setVSBuffer(const SPtr<Buffer> buffer,uint32 location) override;

  void
  setPSBuffer(const SPtr<Buffer> buffer,uint32 location) override;

  void
  setSamplerState(const SPtr<SamplerState> sampler) override;

  void
  setRenderTarget(const SPtr<RenderTarget> renderTarget);

  void
  setRenderTargetAndDepthStencil(
    const SPtr<RenderTarget> renderTarget,
    const SPtr<DepthStencil> depthStencil
  ) override;

  void
  unsetRenderTargetAndDepthStencil() override;

  void
  clearRenderTarget(SPtr<RenderTarget> renderTarget) override;

  void 
  clearDepthStencil(SPtr<DepthStencil> depthStencil) override;

  void
  setWindow() override;

  virtual void*
  getWindow() override;

  virtual void*
  getDevice() override;

  virtual void*
  getContext() override;

 protected:

  DX11GraphicAPI() = default;

 public:
   HWND m_hWnd;
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
  ID3D11Device* m_device = nullptr;
  ID3D11DeviceContext* m_context = nullptr;
  IDXGISwapChain* m_swapChain = nullptr;

  MSG m_msg = MSG();

  Color m_backgroundColor;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


