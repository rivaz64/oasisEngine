#include "oaDeferred.h"
#include <oaFrustum.h>
#include <oaScene.h>
#include <oaMatrix4f.h>
#include <oaActor.h>
#include <oaGraphicsComponent.h>
#include <oaModel.h>
#include <oaMesh.h>
#include <oaMaterial.h>
#include <oaResoureManager.h>
#include <oaShaderProgram.h>
#include <oaBuffer.h>
#include <oaGraphicAPI.h>
#include <oaCamera.h>
#include <oaRasterizerState.h>
#include <oaCameraComponent.h>
#include <oaDebugMesh.h>
#include <oaTexture.h>
#include <oaDepthStencil.h>
#include <oaRenderTarget.h>
#include <oaBlendState.h>
#include <oaMatrix3f.h>
#include <oaLights.h>

namespace oaEngineSDK{

void 
Deferred::onStartUp()
{
  auto& graphicsAPI = GraphicAPI::instance();
  m_globalTransformBuffer = graphicsAPI.createBuffer();
  m_globalTransformBuffer->init(sizeof(Matrix4f));

  m_normalRasterizer = graphicsAPI.createRasterizerState();
  m_normalRasterizer->init(CULLING::kFront,FILL_MODE::kSolid);

  m_hairRasterizer1 = graphicsAPI.createRasterizerState();
  m_hairRasterizer1->init(CULLING::kNone,FILL_MODE::kSolid);
  m_hairRasterizer2 = graphicsAPI.createRasterizerState();
  m_hairRasterizer2->init(CULLING::kBack,FILL_MODE::kSolid);

  m_debugRasterizer = graphicsAPI.createRasterizerState();
  m_debugRasterizer->init(CULLING::kNone,FILL_MODE::kWireFrame);

  m_viewLocationBuffer = graphicsAPI.createBuffer();
  m_viewLocationBuffer->init(sizeof(Vector4f));

  m_Light = graphicsAPI.createBuffer();
  m_Light->init(sizeof(DirectionalLight));


  m_configs = graphicsAPI.createBuffer();
  m_configs->init(sizeof(Vector4f));

  m_size = graphicsAPI.createBuffer();
  m_size->init(sizeof(Vector4f));

  m_matrix = graphicsAPI.createBuffer();
  m_matrix->init(sizeof(Matrix4f));

  m_viewBuffer = graphicsAPI.createBuffer();
  m_viewBuffer->init(sizeof(Matrix4f));

  m_projectionBuffer = graphicsAPI.createBuffer();
  m_projectionBuffer->init(sizeof(Matrix4f));

  m_depthStencil = graphicsAPI.createTexture();

  m_colorTexture = graphicsAPI.createTexture();
  m_normalTexture = graphicsAPI.createTexture();
  m_positionTexture = graphicsAPI.createTexture();
  m_specularTexture = graphicsAPI.createTexture();
  m_ssao = graphicsAPI.createTexture();
  m_blur = graphicsAPI.createTexture();

  m_blendState0 = graphicsAPI.createBlendState();
  m_blendState0->init(false);

  m_blendState1 = graphicsAPI.createBlendState();
  m_blendState1->init(true);

  m_gBuffer = {m_colorTexture,m_normalTexture,m_positionTexture,m_specularTexture};
  Vector<SimpleVertex> points{
    SimpleVertex(Vector4f( -1.0f, 1.0f, 0.5f, 1.0f ),Vector2f(0,0)),
    SimpleVertex(Vector4f( 1.0f, -1.0f, 0.5f, 1.0f ),Vector2f(1,1)),
    SimpleVertex(Vector4f( -1.0f, -1.0f, 0.5f, 1.0f),Vector2f(0,1)),
    SimpleVertex(Vector4f( 1.0f, 1.0f, 0.5f, 1.0f),  Vector2f(1,0)),
  };
  
  screen = makeSPtr<Mesh>();

  screen->setIndex({0,1,2,1,0,3});

  screen->create(points.data(),sizeof(SimpleVertex),points.size());

  m_renderTarget = graphicsAPI.getBackBuffer();
  //m_renderTarget->createShaderResource(FORMAT::kR32G32B32A32Float);
  m_renderTarget->createRenderTarget(FORMAT::kR32G32B32A32Float);
  graphicsAPI.setRenderTarget(m_renderTarget);

}

void 
Deferred::render(SPtr<Scene> scene, 
                 SPtr<Camera> camForView, 
                 SPtr<Camera> camForFrustrum, 
                 const Vector<DirectionalLight>& lights,
                 const Vector4f& config)
{
  // auto& resourseManager = ResoureManager::instance();
  //
  //auto& graphicsAPI = GraphicAPI::instance();
  //
  //graphicsAPI.clearRenderTarget(m_finalRender);
  //graphicsAPI.clearDepthStencil(m_finalDepthStencil);
  //graphicsAPI.setRenderTargetAndDepthStencil(m_finalRender,m_finalDepthStencil);
  //
  //graphicsAPI.setBlendState(m_blendState);
  //
  ////resourseManager.m_shaderPrograms["GBuffer"]->set();
  //graphicsAPI.setRasterizerState(m_debugRasterizer);
  //
  //Vector<RenderData> toRender;
  //Vector<RenderData> transparents;
  //
  //Frustum frustrum(camForFrustrum->getLocation(),
  //                 camForFrustrum->getAxisMatrix(),
  //                 camForFrustrum->getNearPlaneDistance(),
  //                 camForFrustrum->getFarPlaneDistance(),
  //                 camForFrustrum->getViewAngle(),
  //                 camForFrustrum->getRatio());
  //
  //
  //scene->meshesToRender(scene->getRoot(),frustrum,toRender,transparents);
  //resourseManager.m_shaderPrograms["color"]->set();
  //
  //
  //
  //m_viewBuffer->write(camForView->getViewMatrix().getData());
  //graphicsAPI.setVSBuffer(m_viewBuffer,1);
  //
  //m_projectionBuffer->write(camForView->getProjectionMatrix().getData());
  //graphicsAPI.setVSBuffer(m_projectionBuffer,2);
  //
  //for(auto& renderData : toRender){
  //  m_globalTransformBuffer->write(&renderData.m_transform);
  //  graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  //
  //  renderData.m_mesh->set();
  //  //renderData.m_material->set();
  //  graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  //}

  auto& resourseManager = ResoureManager::instance();
  
  auto& graphicsAPI = GraphicAPI::instance();

  //graphicsAPI.unsetRenderTtextures();
  
  graphicsAPI.clearRenderTarget(m_colorTexture);
  graphicsAPI.clearRenderTarget(m_normalTexture);
  graphicsAPI.clearRenderTarget(m_positionTexture);
  graphicsAPI.clearRenderTarget(m_specularTexture);
  graphicsAPI.clearRenderTarget(m_renderTarget);
  graphicsAPI.clearRenderTarget(m_ssao);
  graphicsAPI.clearDepthStencil(m_depthStencil);
  
  graphicsAPI.setBlendState(m_blendState0);
  
  //resourseManager.m_shaderPrograms["GBuffer"]->set();
  
  
  graphicsAPI.setRasterizerState(m_normalRasterizer);
  Vector<RenderData> toRender;
  Vector<RenderData> transparents;
  
  Frustum frustrum(camForFrustrum->getLocation(),
                   camForFrustrum->getAxisMatrix(),
                   camForFrustrum->getNearPlaneDistance(),
                   camForFrustrum->getFarPlaneDistance(),
                   camForFrustrum->getViewAngle(),
                   camForFrustrum->getRatio());
  
  
  scene->meshesToRender(scene->getRoot(),frustrum,toRender,transparents);
  
  m_viewBuffer->write(camForView->getViewMatrix().getData());
  graphicsAPI.setVSBuffer(m_viewBuffer,1);
  
  m_projectionBuffer->write(camForView->getProjectionMatrix().getData());
  graphicsAPI.setVSBuffer(m_projectionBuffer,2);
  //debug(toRender);
  gBuffer(toRender);
  //copy(m_specularTexture,m_renderTarget);
  //gTransparents(transparents);
  
  diffuse(camForView->getViewMatrix(),lights);

  
  //ssao(config);
  //float n = 1.f/9.f;
  //blur(m_ssao,Matrix3f(Vector3f(n,n,n),Vector3f(n,n,n),Vector3f(n,n,n)));
  //lights(camForView->getViewMatrix()*light);
  
}

void 
Deferred::gBuffer(Vector<RenderData>& toRender)
{
  auto& resourseManager = ResoureManager::instance();
  
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setRenderTargetsAndDepthStencil(m_gBuffer,m_depthStencil);
  graphicsAPI.setRasterizerState(m_normalRasterizer);
  for(auto& renderData : toRender){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    renderData.m_material->set();
    resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
    graphicsAPI.unsetTextures(m_gBuffer.size());
  }
  
}

void Deferred::gTransparents(Vector<RenderData>& transparents)
{
  auto& resourseManager = ResoureManager::instance();

  auto& graphicsAPI = GraphicAPI::instance();

  graphicsAPI.setRasterizerState(m_hairRasterizer1);
  for(auto& renderData : transparents){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    renderData.m_material->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }

  graphicsAPI.setRasterizerState(m_hairRasterizer2);
  
  for(auto& renderData : transparents){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  
    renderData.m_mesh->set();
    renderData.m_material->set();
    resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }

  graphicsAPI.setRasterizerState(m_normalRasterizer);
  for(auto& renderData : transparents){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  
    renderData.m_mesh->set();
    renderData.m_material->set();
    resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }
}

void 
Deferred::debug(Vector<RenderData>& toRender)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  resourseManager.m_shaderPrograms["debug"]->set();
  graphicsAPI.setRenderTargetAndDepthStencil(m_renderTarget,m_depthStencil);
  graphicsAPI.setRasterizerState(m_debugRasterizer);
  for(auto& renderData : toRender){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    //renderData.m_material->set();
    //resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }
  
  graphicsAPI.setRasterizerState(m_normalRasterizer);
}

void 
Deferred::ssao( const Vector4f& config)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();

  resourseManager.m_shaderPrograms["ssao"]->set();

  m_configs->write(&config);
  graphicsAPI.setPSBuffer(m_configs,0);
  graphicsAPI.setPSBuffer(m_size,1);

  graphicsAPI.setRenderTarget(m_ssao);

  graphicsAPI.setTexture(m_normalTexture,0);
  graphicsAPI.setTexture(m_positionTexture,1);
  graphicsAPI.setTexture(m_depthStencil,2);
  screen->set();
  
  graphicsAPI.draw(6);
  graphicsAPI.unsetTextures(5);
}

void
Deferred::blur(SPtr<Texture> texture, const Matrix3f& kernel)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  resourseManager.m_shaderPrograms["convolution"]->set();
  graphicsAPI.setRenderTarget(m_blur);
  graphicsAPI.setTexture(m_ssao,0);
  Matrix4f newKernel(kernel);
  m_matrix->write(newKernel.getData());
  graphicsAPI.setPSBuffer(m_matrix,0);
  graphicsAPI.setPSBuffer(m_size,1);
  
  screen->set();
  
  graphicsAPI.draw(6);
  copy(m_blur,texture);
  //auto& resourseManager = ResoureManager::instance();
  //auto& graphicsAPI = GraphicAPI::instance();
  //graphicsAPI.unsetRenderTargetAndDepthStencil();
  //resourseManager.m_shaderPrograms["convolution"]->set();
  //
  //
  //m_matrix->write(kernel.getData());
  //graphicsAPI.setPSBuffer(m_matrix,0);
  //graphicsAPI.setPSBuffer(m_size,1);
  //screen->set();
  //
  //graphicsAPI.draw(6);
  //graphicsAPI.unsetTextures(5);
}

void 
Deferred::copy(SPtr<Texture> textureIn, SPtr<Texture> textureOut)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  resourseManager.m_shaderPrograms["copy"]->set();
  graphicsAPI.setRenderTarget(textureOut);
  graphicsAPI.setTexture(textureIn,0);
  
  screen->set();

  graphicsAPI.draw(6);

  graphicsAPI.unsetTextures(5);
}



void
Deferred::lights(const Vector4f& light)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();

  resourseManager.m_shaderPrograms["lights"]->set();
  
  //m_LightLocation->write(&light);
  //graphicsAPI.setPSBuffer(m_LightLocation,0);
  
  
  graphicsAPI.setPSBuffer(m_size,3);
  graphicsAPI.setRenderTarget(m_renderTarget);
  graphicsAPI.setTexture(m_colorTexture,0);
  graphicsAPI.setTexture(m_normalTexture,1);
  graphicsAPI.setTexture(m_positionTexture,2);
  graphicsAPI.setTexture(m_specularTexture,3);
  graphicsAPI.setTexture(m_ssao,4);
  graphicsAPI.setTexture(m_depthStencil,5);
  screen->set();
  
  graphicsAPI.draw(6);
  graphicsAPI.unsetTextures(5);
}

void 
Deferred::diffuse(const Matrix4f& viewMatrix, const Vector<DirectionalLight>& lights)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  resourseManager.m_shaderPrograms["diffuse"]->set();
  graphicsAPI.setBlendState(m_blendState1);
  graphicsAPI.setRenderTarget(m_renderTarget);
  

  graphicsAPI.setTexture(m_normalTexture,0);
  graphicsAPI.setTexture(m_depthStencil,1);
  
  for(auto& light : lights){
    auto viewLight = light;
    viewLight.direction = viewMatrix*viewLight.direction;
    m_Light->write(&light);
    graphicsAPI.setPSBuffer(m_Light,0);
    screen->set();
    graphicsAPI.draw(6);
    
  }
  graphicsAPI.unsetTextures(2);
  //graphicsAPI.draw(6);
  //graphicsAPI.unsetTextures(2);
}

void 
Deferred::setSize(const Vector2U& size)
{
  auto& graphicsApi = GraphicAPI::instance();
  graphicsApi.unsetRenderTargetAndDepthStencil();

  m_depthStencil->release();
  m_renderTarget->release();
  m_colorTexture->release();
  m_normalTexture->release();
  m_positionTexture->release();
  m_specularTexture->release();
  m_ssao->release();
  auto iSize = Vector2I(size.x,size.y);

  m_depthStencil->init(iSize,BIND::kDepthStencil,FORMAT::kR24G8);

  m_renderTarget = graphicsApi.getBackBuffer();
  //m_renderTarget->createShaderResource(FORMAT::kR32G32B32A32Float);
  m_renderTarget->createRenderTarget(FORMAT::kR32G32B32A32Float);

  m_colorTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_normalTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_positionTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_specularTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_ssao->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_blur->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  auto sizef = Vector2f(size.x,size.y);
  m_size->write(&sizef);
}

}

