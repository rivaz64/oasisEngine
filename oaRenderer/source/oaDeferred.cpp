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
#include <oaRasterizer.h>
#include <oaCameraComponent.h>
#include <oaDebugMesh.h>
#include <oaTexture.h>
#include <oaDepthStencil.h>
#include <oaRenderTarget.h>

namespace oaEngineSDK{

void 
Deferred::onStartUp()
{
  auto& graphicsAPI = GraphicAPI::instance();
  m_globalTransformBuffer = graphicsAPI.createBuffer();
  m_globalTransformBuffer->init(sizeof(Matrix4f));

  m_normalRasterizer = graphicsAPI.createRasterizer();
  m_normalRasterizer->init(CULLING::kFront,FILL_MODE::kSolid);

  m_hairRasterizer = graphicsAPI.createRasterizer();
  m_hairRasterizer->init(CULLING::kNone,FILL_MODE::kSolid);

  m_debugRasterizer = graphicsAPI.createRasterizer();
  m_debugRasterizer->init(CULLING::kNone,FILL_MODE::kWireFrame);

  m_viewLocationBuffer = graphicsAPI.createBuffer();
  m_viewLocationBuffer->init(sizeof(Vector4f));

  m_LightLocation = graphicsAPI.createBuffer();
  m_LightLocation->init(sizeof(Vector4f));

  m_viewBuffer = graphicsAPI.createBuffer();
  m_viewBuffer->init(sizeof(Matrix4f));

  m_projectionBuffer = graphicsAPI.createBuffer();
  m_projectionBuffer->init(sizeof(Matrix4f));

  m_depthTexture = graphicsAPI.createTexture();
  //m_depthTexture->initForDepthStencil();
  m_finalDepthStencil = graphicsAPI.createDepthStencil();
  //m_finalDepthStencil->init(m_depthTexture);

  m_finalRender = graphicsAPI.createRenderTarget();
  m_finalRender->init(graphicsAPI.getBackBuffer());

  m_colorTexture = graphicsAPI.createTexture();
  //ResoureManager::instance().m_textures.insert({"color",m_colorTexture});
  m_normalTexture = graphicsAPI.createTexture();
  m_positionTexture = graphicsAPI.createTexture();
  m_specularTexture = graphicsAPI.createTexture();

  m_colorRender = graphicsAPI.createRenderTarget();
  m_normalRender = graphicsAPI.createRenderTarget();
  m_positionRender = graphicsAPI.createRenderTarget();
  m_specularRender = graphicsAPI.createRenderTarget();

  m_gBuffer = {m_colorRender,m_normalRender,m_positionRender,m_specularRender};
  Vector<SimpleVertex> points{
    SimpleVertex(Vector4f( -1.0f, 1.0f, 0.5f, 1.0f ),Vector2f(0,0)),
    SimpleVertex(Vector4f( 1.0f, -1.0f, 0.5f, 1.0f ),Vector2f(1,1)),
    SimpleVertex(Vector4f( -1.0f, -1.0f, 0.5f, 1.0f),Vector2f(0,1)),
    SimpleVertex(Vector4f( 1.0f, 1.0f, 0.5f, 1.0f),  Vector2f(1,0)),
  };
  
  screen = makeSPtr<Mesh>();

  screen->setIndex({0,1,2,1,0,3});

  screen->create(points.data(),sizeof(SimpleVertex),points.size());

  graphicsAPI.setRenderTarget(m_finalRender);
}

void 
Deferred::render(SPtr<Scene> scene, SPtr<Camera> camForView, SPtr<Camera> camForFrustrum, const Vector4f& light)
{
  auto& resourseManager = ResoureManager::instance();
  
  auto& graphicsAPI = GraphicAPI::instance();

  graphicsAPI.clearRenderTarget(m_colorRender);
  graphicsAPI.clearRenderTarget(m_normalRender);
  graphicsAPI.clearRenderTarget(m_positionRender);
  graphicsAPI.clearRenderTarget(m_specularRender);
  graphicsAPI.clearRenderTarget(m_finalRender);
  graphicsAPI.clearDepthStencil(m_finalDepthStencil);

  resourseManager.m_shaderPrograms["GBuffer"]->set();

  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setRenderTargetsAndDepthStencil(m_gBuffer,m_finalDepthStencil);
  graphicsAPI.setRasterizer(m_normalRasterizer);
  Vector<RenderData> toRender;

  Frustum frustrum(camForFrustrum->getLocation(),
                   camForFrustrum->getAxisMatrix(),
                   camForFrustrum->getNearPlaneDistance(),
                   camForFrustrum->getFarPlaneDistance(),
                   camForFrustrum->getViewAngle(),
                   camForFrustrum->getRatio());
  

  scene->meshesToRender(scene->getRoot(),frustrum,toRender);

  m_viewBuffer->write(camForView->getViewMatrix().getData());
  graphicsAPI.setVSBuffer(m_viewBuffer,1);
  
  m_projectionBuffer->write(camForView->getProjectionMatrix().getData());
  graphicsAPI.setVSBuffer(m_projectionBuffer,2);

  

  for(auto& renderData : toRender){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    renderData.m_material->set();

    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setRenderTarget(m_finalRender);
  
  resourseManager.m_shaderPrograms["lights"]->set();

  m_viewLocationBuffer->write(&camForView->getLocation());
  graphicsAPI.setPSBuffer(m_viewLocationBuffer,0);

  m_LightLocation->write(&light);
  graphicsAPI.setPSBuffer(m_LightLocation,1);
  
  graphicsAPI.setTexture(m_colorTexture,0);
  graphicsAPI.setTexture(m_normalTexture,1);
  graphicsAPI.setTexture(m_positionTexture,2);
  graphicsAPI.setTexture(m_specularTexture,3);
  graphicsAPI.setTexture(m_depthTexture,4);
  screen->set();
  
  graphicsAPI.draw(6);

  //graphicsAPI.unsetRenderTargetAndDepthStencil();
  
  /*
  for(auto& renderData : toRender){
    renderData.m_material->set();
    switch (renderData.m_material->getShader())
    {
    case SHADER_TYPE::kNormal:
      resourseManager.m_shaderPrograms["default"]->set();
      graphicsAPI.setRasterizer(m_normalRasterizer);
      break;
    
    case SHADER_TYPE::kAnimation:
      resourseManager.m_shaderPrograms["animation"]->set();
      graphicsAPI.setRasterizer(m_normalRasterizer);
      break;
    
    case SHADER_TYPE::kParalax:
      resourseManager.m_shaderPrograms["paralax"]->set();
      graphicsAPI.setRasterizer(m_normalRasterizer);
      break;
    
    case SHADER_TYPE::kTransparent:
      resourseManager.m_shaderPrograms["transparent"]->set();
      graphicsAPI.setRasterizer(m_normalRasterizer);
      break;
    
    case SHADER_TYPE::kDebug:
      resourseManager.m_shaderPrograms["debug"]->set();
      graphicsAPI.setRasterizer(m_debugRasterizer);
      break;
    
    default:
      break;
    }

    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }*/
}

void 
Deferred::setSize(const Vector2U& size)
{
  auto& graphicsApi = GraphicAPI::instance();
  graphicsApi.unsetRenderTargetAndDepthStencil();

  m_depthTexture->release();
  m_finalDepthStencil->release();
  m_finalRender->release();
  m_colorTexture->release();
  m_normalTexture->release();
  m_positionTexture->release();
  m_specularTexture->release();

  m_depthTexture->initForDepthStencil(size);
  m_finalDepthStencil->init(m_depthTexture);

  m_finalRender->init(graphicsApi.getBackBuffer());

  m_colorTexture->initForRenderTarget(size);
  m_normalTexture->initForRenderTarget(size);
  m_positionTexture->initForRenderTarget(size);
  m_specularTexture->initForRenderTarget(size);

  m_colorRender->init(m_colorTexture);
  m_normalRender->init(m_normalTexture);
  m_positionRender->init(m_positionTexture);
  m_specularRender->init(m_specularTexture);
}

}

