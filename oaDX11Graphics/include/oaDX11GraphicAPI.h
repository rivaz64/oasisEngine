/**
* @file oaDX11GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include <oaGraphicAPI.h>
#include <d3d11.h>
#include <oaColor.h>
#include <oaVector2I.h>

namespace oaEngineSDK{

class DX11GraphicAPI :
  public GraphicAPI
{
 public:

  void
  onShutDown() override;

  bool
  initialize(void* window) override;

  void*
  createWindow(void* function, void* app, const Vector2U& size, const String& name) override;

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

  SPtr<Shader>
  createHullShader() override; 

  SPtr<Shader>
  createDomainShader() override; 

  SPtr<Buffer>
  createBuffer() override;

  SPtr<VertexBuffer> 
  createVertexBuffer() override;

  SPtr<IndexBuffer> 
  createIndexBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  SPtr<SamplerState>
  createSamplerState() override;
  
  SPtr<RasterizerState>
  createRasterizerState() override;

  SPtr<BlendState>
  createBlendState() override;
  
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
  setRasterizerState(const SPtr<RasterizerState> rasterizer) override;

  void
  setBlendState(const SPtr<BlendState> blender) override;

  void
  setRenderTarget(const SPtr<Texture> renderTarget) override;

  void
  setRenderTargets(const Vector<SPtr<Texture>>& renderTargets) override;

  void
  setRenderTargetAndDepthStencil(
    const SPtr<Texture> renderTarget,
    const SPtr<Texture> depthStencil
  ) override;

  void
  setRenderTargetsAndDepthStencil(
    const Vector<SPtr<Texture>>& renderTargets,
    const SPtr<Texture> depthStencil
  ) override;

  void
  unsetRenderTargetAndDepthStencil() override;

  void
  unsetTextures(uint32 n) override;

  void
  setPrimitiveTopology(PRIMITIVE_TOPOLOGY::E topology) override;

  void
  clearRenderTarget(SPtr<Texture> renderTarget) override;

  void 
  clearDepthStencil(SPtr<Texture> depthStencil) override;

  bool
  loadDDS(const Path& path) override;

  Vector2U
  getWindowSize(void* window) override;

  void
  setViewport(const Vector2U& size) override;

  void
  resizeSwapChain(const Vector2U& size) override;

  virtual void*
  getDevice() override;

  virtual void*
  getContext() override;

 protected:

  DX11GraphicAPI() = default;

 public:
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
  ID3D11Device* m_device = nullptr;
  ID3D11DeviceContext* m_context = nullptr;
  IDXGISwapChain* m_swapChain = nullptr;

  MSG m_msg = MSG();

  Color m_backgroundColor;

  ID3D11Buffer* g_pVertexBuffer = NULL;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


