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
  render(SPtr<Scene> scene,SPtr<Camera> camForView,SPtr<Camera> camForFrustrum) override;

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
};

}


