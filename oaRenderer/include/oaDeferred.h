/**
* @file oaDeferred.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include <oaRenderer.h>

namespace oaEngineSDK{

class Deferred :
  public Renderer
{
 public:
  
  void
  onStartUp() override;

  void
  render(SPtr<Scene> scene,SPtr<Camera> camForView,SPtr<Camera> camForFrustrum, const Vector4f& light) override;

  void
  setSize(const Vector2U& size) override;

 private:
  
  SPtr<Texture> m_colorTexture;

  SPtr<Texture> m_normalTexture;

  SPtr<Texture> m_positionTexture;

  SPtr<Texture> m_specularTexture;

  SPtr<RenderTarget> m_colorRender;

  SPtr<RenderTarget> m_normalRender;

  SPtr<RenderTarget> m_positionRender;

  SPtr<RenderTarget> m_specularRender;

  Vector<SPtr<RenderTarget>> m_gBuffer;

  SPtr<Mesh> screen;

  SPtr<Buffer> m_globalTransformBuffer;

  SPtr<Buffer> m_viewBuffer;

  SPtr<Buffer> m_projectionBuffer;

  SPtr<Buffer> m_viewLocationBuffer;

  SPtr<Buffer> m_LightLocation;

  SPtr<Texture> m_depthTexture;

  SPtr<Texture> m_renderTexture;

  SPtr<Rasterizer> m_normalRasterizer;

  SPtr<Rasterizer> m_hairRasterizer;

  SPtr<Rasterizer> m_debugRasterizer;
  
  SPtr<RenderTarget> m_finalRender;

  SPtr<DepthStencil> m_finalDepthStencil;
};

}


