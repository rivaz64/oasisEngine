/**
* @file oaDeferred.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include <oaPrerequisitesCore.h>
#include <oaRenderer.h>
#include <oaScene.h>
#include <oaLights.h>
namespace oaEngineSDK{

class Deferred :
  public Renderer
{
 public:
  
  void
  onStartUp() override;

  void
  render(WPtr<Actor> scene,
         WPtr<Camera> camForView,
         WPtr<Camera> camForFrustrum, 
         const Vector4f& config) override;

  void 
  setScreen();

  void
  setMaterial(SPtr<Material> material);

  void
  setStaticMesh(WPtr<Model> model);

  void
  setSkeletalMesh(WPtr<SkeletalMeshComponent> component);

  //void
  //setDirectionalLight(const DirectionalLight& component,);

  /**
   * @brief all the vertex shaders
  */
  void
  vertex(SPtr<Actor> actor,const Frustum& frustum);

  

  /**
   * @brief the gBuffer pass
   * @param torender 
  */
  //void 
  //gBuffer(Vector<RenderData>& torender);
  //
  /**
  // * @brief gBuffer for things with transparnecy
  // * @param torender 
  //*/
  //void 
  //gTransparents(Vector<RenderData>& torender);

  /**
   * @brief draw debug meshes
  */
  //void 
  //debug(Vector<RenderData>& toRender);

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
  ambientLight(const Matrix4f& viewMatrix);

  void 
  directionalLight(const Matrix4f& viewMatrix);

  void 
  pointLight(const Matrix4f& viewMatrix);

  void
  spotLight(const Matrix4f& viewMatrix);

  void
  shadows(const Vector<SpotLight>& lights, SPtr<Scene> scene);

  //void 
  //diffusePoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights);
  //
  //void 
  //specularPoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights);

  void 
  downSapmle(SPtr<Texture> texture);

  void
  setSize(const Vector2U& size) override;

  void
  generateShadowMap(const SpotLight& light,SPtr<Actor> actor);

  SPtr<Texture>
  applyShadowMap(SPtr<Texture>& scene,SPtr<Texture>& map);

  void
  setCamera(SPtr<Camera> camera);

  WPtr<Texture>
  getShadowMap() override;

 private:
  
  SPtr<Texture> m_colorTexture;

  SPtr<Texture> m_normalTexture;

  SPtr<Texture> m_positionTexture;

  SPtr<Texture> m_specularTexture;

  SPtr<Texture> m_emisiveTexture;

  SPtr<Texture> m_lightTexture;

  SPtr<Texture> m_downSapmle;

  SPtr<Texture> m_ssao;

  SPtr<Texture> m_blur;

  SPtr<Texture> m_diffuseLight;

  SPtr<Texture> m_specularLight;

  SPtr<Texture> m_shadowMap;

  Vector<SPtr<Texture>> m_gBuffer;

  Vector<SPtr<Texture>> m_lightTexturesBuffer;

  SPtr<Texture> m_renderTarget;

  SPtr<Texture> m_depthStencil;

  SPtr<StaticMesh> screen;

  SPtr<Buffer> m_globalTransformBuffer;

  SPtr<Buffer> m_viewBuffer;

  SPtr<Buffer> m_projectionBuffer;

  SPtr<Buffer> m_viewLocationBuffer;

  SPtr<Buffer> m_LightBuffer;
  SPtr<Buffer> m_spotLightBuffer;

  SPtr<Buffer> m_configs;

  SPtr<Buffer> m_size;

  SPtr<Buffer> m_color;

  SPtr<Buffer> m_bones;

  //SPtr<Buffer> m_smallSize;

  //SPtr<Buffer> m_matrix;
  SPtr<Buffer> m_kernel;

  Vector<SPtr<RasterizerState>> m_rasterizers;

  SPtr<RasterizerState> m_hairRasterizer1;
  SPtr<RasterizerState> m_hairRasterizer2;

  SPtr<RasterizerState> m_debugRasterizer;

  SPtr<BlendState> m_blendState0;
  SPtr<BlendState> m_blendState1;

  SPtr<SamplerState> m_samplerState; 

  Vector<float> m_blurKernel;

  float m_tessAmount = 8.0f;
  SPtr<Buffer> m_tessBufer;

  Vector<SPtr<Texture>> m_shadowMaps;

  SPtr<Camera> m_shadowsCamera;

  Vector<AmbientLight> m_ambientLights;
  Vector<DirectionalLight> m_directionalLights;
  Vector<PointLight> m_PointLights;
  Vector<SpotLight> m_spotLights;
};

}


