/**
* @file oaDeferred.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include <oaRenderer.h>
#include <oaScene.h>

namespace oaEngineSDK{

class Deferred :
  public Renderer
{
 public:
  
  void
  onStartUp() override;

  void
  render(SPtr<Scene> scene,
         SPtr<Camera> camForView,
         SPtr<Camera> camForFrustrum, 
         const Vector<DirectionalLight>& directionalLights,
         const Vector<PointLight>& pointLights,
         const Vector4f& config) override;
  /**
   * @brief the gBuffer pass
   * @param torender 
  */
  void 
  gBuffer(Vector<RenderData>& torender);

  /**
   * @brief gBuffer for things with transparnecy
   * @param torender 
  */
  void 
  gTransparents(Vector<RenderData>& torender);

  /**
   * @brief draw debug meshes
  */
  void 
  debug(Vector<RenderData>& toRender);

  /**
   * @brief screen space ambient oclution
  */
  void
  ssao(const Vector4f& config);

  /**
   * @brief blurrs a texture
  */
  void
  blur(SPtr<Texture> textureIn,SPtr<Texture> textureOut);

  /**
   * @brief copys the texture from in to out
   * @param textureIn 
   * @param textureOut 
  */
  void
  copy(SPtr<Texture> textureIn,SPtr<Texture> textureOut);

  

  /**
   * @brief lights as screen space
  */
  void 
  aplylights();

  void 
  directionalLight(const Matrix4f& viewMatrix, const Vector<DirectionalLight>& lights);

  void 
  pointLight(const Matrix4f& viewMatrix, const Vector<PointLight>& lights);

  void 
  diffusePoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights);

  void 
  specularPoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights);

  void 
  downSapmle(SPtr<Texture> texture);

  void
  setSize(const Vector2U& size) override;



 private:
  
  SPtr<Texture> m_colorTexture;

  SPtr<Texture> m_normalTexture;

  SPtr<Texture> m_positionTexture;

  SPtr<Texture> m_specularTexture;

  SPtr<Texture> m_emisiveTexture;

  SPtr<Texture> m_downSapmle;

  SPtr<Texture> m_ssao;

  SPtr<Texture> m_blur;

  SPtr<Texture> m_diffuseLight;

  SPtr<Texture> m_specularLight;

  Vector<SPtr<Texture>> m_gBuffer;

  Vector<SPtr<Texture>> m_lightBuffer;

  SPtr<Texture> m_renderTarget;

  SPtr<Texture> m_depthStencil;

  SPtr<Mesh> screen;

  SPtr<Buffer> m_globalTransformBuffer;

  SPtr<Buffer> m_viewBuffer;

  SPtr<Buffer> m_projectionBuffer;

  SPtr<Buffer> m_viewLocationBuffer;

  SPtr<Buffer> m_Light;

  SPtr<Buffer> m_configs;

  SPtr<Buffer> m_size;

  //SPtr<Buffer> m_smallSize;

  //SPtr<Buffer> m_matrix;
  SPtr<Buffer> m_kernel;

  SPtr<RasterizerState> m_normalRasterizer;

  SPtr<RasterizerState> m_hairRasterizer1;
  SPtr<RasterizerState> m_hairRasterizer2;

  SPtr<RasterizerState> m_debugRasterizer;

  SPtr<BlendState> m_blendState0;
  SPtr<BlendState> m_blendState1;

  SPtr<SamplerState> m_samplerState; 

  Vector<float> m_blurKernel;
};

}


