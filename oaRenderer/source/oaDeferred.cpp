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

  m_viewBuffer = graphicsAPI.createBuffer();
  m_viewBuffer->init(sizeof(Matrix4f));

  m_projectionBuffer = graphicsAPI.createBuffer();
  m_projectionBuffer->init(sizeof(Matrix4f));

  m_depthTexture = graphicsAPI.createTexture();

  m_finalDepthStencil = graphicsAPI.createDepthStencil();

  m_finalRender = graphicsAPI.createRenderTarget(graphicsAPI.getBackBuffer());

  m_color = graphicsAPI.createTexture();
  m_normal = graphicsAPI.createTexture();
  m_position = graphicsAPI.createTexture();
  m_specular = graphicsAPI.createTexture();
}

void 
Deferred::render(SPtr<Scene> scene, SPtr<Camera> camForView, SPtr<Camera> camForFrustrum)
{
  auto& resourseManager = ResoureManager::instance();
  
  auto& graphicsAPI = GraphicAPI::instance();

  graphicsAPI.setRenderTargetAndDepthStencil(m_finalRender,m_finalDepthStencil);

  graphicsAPI.clearRenderTarget(m_finalRender);
  graphicsAPI.clearDepthStencil(m_finalDepthStencil);
  
  m_viewBuffer->write(&camForView->getViewMatrix().m11);
  graphicsAPI.setVSBuffer(m_viewBuffer,1);
  
  m_projectionBuffer->write(&camForView->getProjectionMatrix().m11);
  graphicsAPI.setVSBuffer(m_projectionBuffer,2);
  
  m_viewLocationBuffer->write(&camForView->getLocation().x);
  graphicsAPI.setVSBuffer(m_viewLocationBuffer,4);
  
  Vector<RenderData> toRender;

  Frustum frustrum(camForFrustrum->getLocation(),
                   camForFrustrum->getAxisMatrix(),
                   camForFrustrum->getNearPlaneDistance(),
                   camForFrustrum->getFarPlaneDistance(),
                   camForFrustrum->getViewAngle(),
                   camForFrustrum->getRatio());


  scene->meshesToRender(scene->getRoot(),frustrum,toRender);

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
  }
}

void 
Deferred::setSize(const Vector2U& size)
{
  auto& graphicsApi = GraphicAPI::instance();
  graphicsApi.unsetRenderTargetAndDepthStencil();

  m_depthTexture->release();
  m_finalDepthStencil->release();

  m_depthTexture->initForDepthStencil(size);
  m_finalDepthStencil->init(m_depthTexture);

   m_finalRender = graphicsApi.createRenderTarget(graphicsApi.getBackBuffer());
}

}

