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
#include <oaSamplerState.h>
#include <oaVertexBuffer.h>

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

  m_LightBuffer = graphicsAPI.createBuffer();
  m_LightBuffer->init(sizeof(DirectionalLight));
  m_spotLightBuffer = graphicsAPI.createBuffer();
  m_spotLightBuffer->init(sizeof(Vector4f)*3);


  m_configs = graphicsAPI.createBuffer();
  m_configs->init(sizeof(Vector4f));

  m_size = graphicsAPI.createBuffer();
  m_size->init(sizeof(Vector4f));

  m_tessBufer = graphicsAPI.createBuffer();
  m_tessBufer->init(sizeof(Vector4f));
  

  //m_smallSize = graphicsAPI.createBuffer();
  //m_smallSize->init(sizeof(Vector4f));

  m_kernel = graphicsAPI.createBuffer();
  m_kernel->init(sizeof(float)*16);

  m_viewBuffer = graphicsAPI.createBuffer();
  m_viewBuffer->init(sizeof(Matrix4f));

  m_projectionBuffer = graphicsAPI.createBuffer();
  m_projectionBuffer->init(sizeof(Matrix4f));

  m_depthStencil = graphicsAPI.createTexture();

  m_colorTexture = graphicsAPI.createTexture();
  m_normalTexture = graphicsAPI.createTexture();
  m_positionTexture = graphicsAPI.createTexture();
  m_specularTexture = graphicsAPI.createTexture();
  m_emisiveTexture = graphicsAPI.createTexture();
  m_downSapmle = graphicsAPI.createTexture();
  m_ssao = graphicsAPI.createTexture();
  m_blur = graphicsAPI.createTexture();
  m_diffuseLight = graphicsAPI.createTexture();
  m_specularLight = graphicsAPI.createTexture();
  m_shadowMap = graphicsAPI.createTexture();
  m_shadowMap->init({2048,2048},BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_blendState0 = graphicsAPI.createBlendState();
  m_blendState0->init(false);

  m_blendState1 = graphicsAPI.createBlendState();
  m_blendState1->init(true);

  m_gBuffer = {m_colorTexture,m_normalTexture,m_positionTexture,m_specularTexture,m_emisiveTexture};
  m_lightBuffer = {m_diffuseLight,m_specularLight};

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
  m_blurKernel.resize(16);

  m_samplerState = graphicsAPI.createSamplerState();
  m_samplerState->init(TEXTURE_ADDRESS_MODE::kBorder);
  graphicsAPI.setSamplerState(m_samplerState);

  m_shadowMaps.resize(4);
  for(int32 i = 0; i<4; ++i){
    m_shadowMaps[i] = graphicsAPI.createTexture();
    auto& shadowMap = m_shadowMaps[i];
    shadowMap->init({2048,2048},BIND::kDepthStencil,FORMAT::kR24G8);
  }
  

  m_shadowsCamera = makeSPtr<Camera>();
  m_shadowsCamera->init(1);
}

void 
Deferred::render(SPtr<Scene> scene,
         SPtr<Camera> camForView,
         SPtr<Camera> camForFrustrum, 
         const Vector<DirectionalLight>& directionalLights,
         const Vector<PointLight>& pointLights,
         const Vector<SpotLight>& spotLights,
         const Vector4f& config)
{
  auto& graphicsAPI = GraphicAPI::instance();
  
  graphicsAPI.clearRenderTarget(m_colorTexture);
  graphicsAPI.clearRenderTarget(m_normalTexture);
  graphicsAPI.clearRenderTarget(m_positionTexture);
  graphicsAPI.clearRenderTarget(m_specularTexture);
  graphicsAPI.clearRenderTarget(m_emisiveTexture);
  graphicsAPI.clearRenderTarget(m_renderTarget);
  graphicsAPI.clearRenderTarget(m_ssao);
  graphicsAPI.clearRenderTarget(m_diffuseLight);
  graphicsAPI.clearRenderTarget(m_specularLight);
  graphicsAPI.clearDepthStencil(m_depthStencil);
  graphicsAPI.clearRenderTarget(m_downSapmle);

  
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
  
  
  //scene->meshesToRender(scene->getRoot(),frustrum,toRender,transparents);
  
  setCamera(camForView);
  //debug(toRender);
  //gBuffer(toRender);
  m_tessBufer->write(&config);
  vertex(scene->getRoot(),frustrum);
  graphicsAPI.setPrimitiveTopology(PRIMITIVE_TOPOLOGY::kTrianlgeList);
  graphicsAPI.unsetShaders();
  //copy(m_colorTexture,m_renderTarget);
  //downSapmle(m_emisiveTexture);
  //blur(m_downSapmle,m_blur);
  //gTransparents(transparents);

  ssao(config);
  directionalLight(camForView->getViewMatrix(),directionalLights);
  pointLight(camForView->getViewMatrix(),pointLights);
  spotLight(camForView->getViewMatrix(),spotLights);
  shadows(spotLights,scene);
  aplylights();
  
  
}

void
Deferred::vertex(SPtr<Actor> actor,const Frustum& frustum)
{
  auto& childs = actor->getChilds();
  auto& resourseManager = ResoureManager::instance();

  Matrix4f actorTransform;
  Matrix4f finalTransform;
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setRenderTargetsAndDepthStencil(m_gBuffer,m_depthStencil);
  graphicsAPI.setRasterizerState(m_normalRasterizer);
  for(auto child : childs){
    actorTransform = child->getGlobalTransform();
    auto components = child->getComponents<GraphicsComponent>();
    for(auto& component : components){
      auto meshComponent = cast<GraphicsComponent>(component);
      auto model = meshComponent->getModel();
      if(model){
        finalTransform = actorTransform*meshComponent->getTransform().getMatrix();
        SIZE_T meshes = model->getNumOfMeshes();
        for(SIZE_T i = 0; i<meshes;++i){
          
          auto& mesh = model->getMesh(i);
          
          auto controlPoints = mesh->getControlPoints();
          if(controlPoints){
            graphicsAPI.setRasterizerState(m_debugRasterizer);
            graphicsAPI.setHSBuffer(m_tessBufer,0);
            m_globalTransformBuffer->write(finalTransform.getData());
            graphicsAPI.setDSBuffer(m_globalTransformBuffer, 0);
            resourseManager.m_shaderPrograms["Tesselator"]->set();
            controlPoints->set();
            graphicsAPI.setPrimitiveTopology(PRIMITIVE_TOPOLOGY::k16ContolPointPathlist);
            graphicsAPI.draw(mesh->getNumOfControlPoints());
          }
          else{
            graphicsAPI.setRasterizerState(m_normalRasterizer);
            auto& mat = model->getMaterial(i);
            m_globalTransformBuffer->write(&finalTransform);
            graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
            mesh->set();
            mat->set();
            graphicsAPI.setPrimitiveTopology(PRIMITIVE_TOPOLOGY::kTrianlgeList);
            graphicsAPI.drawIndex(mesh->getIndexNum());
          }
          
        }
      }
    }
    vertex(child,frustum);
  }
}

void 
Deferred::gBuffer(Vector<RenderData>& toRender)
{ 
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setRenderTargetsAndDepthStencil(m_gBuffer,m_depthStencil);
  graphicsAPI.setRasterizerState(m_normalRasterizer);

  for(auto& renderData : toRender){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    renderData.m_material->set();
    //resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.drawIndex(renderData.m_mesh->getIndexNum());
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
    graphicsAPI.drawIndex(renderData.m_mesh->getIndexNum());
  }

  graphicsAPI.setRasterizerState(m_hairRasterizer2);
  
  for(auto& renderData : transparents){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  
    renderData.m_mesh->set();
    renderData.m_material->set();
    resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.drawIndex(renderData.m_mesh->getIndexNum());
  }

  graphicsAPI.setRasterizerState(m_normalRasterizer);
  for(auto& renderData : transparents){
    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  
    renderData.m_mesh->set();
    renderData.m_material->set();
    resourseManager.m_shaderPrograms["GBuffer"]->set();
    graphicsAPI.drawIndex(renderData.m_mesh->getIndexNum());
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
    graphicsAPI.drawIndex(renderData.m_mesh->getIndexNum());
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
  
  graphicsAPI.drawIndex(6);
  graphicsAPI.unsetTextures(5);
}

void
Deferred::blur(SPtr<Texture> textureIn,SPtr<Texture> textureOut)
{
  //print(StringUtilities::floatToString(std_deviation));
  for(int32 i = -4; i<5; ++i){
    m_blurKernel[i+4] = Math::computeGaussianValue(static_cast<float>(i)/4.0f,0,std_deviation);
    //print(StringUtilities::floatToString(i+4));
    //print(StringUtilities::floatToString(m_blurKernel[i+4]));
  }
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  
  graphicsAPI.setRenderTarget(textureOut);
  graphicsAPI.setTexture(textureIn,0);
  m_kernel->write(m_blurKernel.data());
  resourseManager.m_shaderPrograms["HBlur"]->set();
  graphicsAPI.setPSBuffer(m_kernel,0);
  graphicsAPI.setPSBuffer(m_size,1);
  //graphicsAPI.setPSBuffer(m_smallSize,1);
  
  
  screen->set();
  graphicsAPI.drawIndex(6);

  graphicsAPI.setRenderTarget(textureIn);
  graphicsAPI.setTexture(textureOut,0);
  resourseManager.m_shaderPrograms["VBlur"]->set();
  screen->set();
  graphicsAPI.drawIndex(6);
  //copy(m_blur,texture);
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

  graphicsAPI.drawIndex(6);

  graphicsAPI.unsetTextures(5);
}



void
Deferred::aplylights()
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();

  resourseManager.m_shaderPrograms["lights"]->set();
  
  //m_LightLocation->write(&light);
  //graphicsAPI.setPSBuffer(m_LightLocation,0);
  
  
  graphicsAPI.setPSBuffer(m_size,3);
  graphicsAPI.setRenderTarget(m_renderTarget);
  graphicsAPI.setTexture(m_colorTexture,0);
  graphicsAPI.setTexture(m_diffuseLight,1);
  graphicsAPI.setTexture(m_specularLight,2);
  graphicsAPI.setTexture(m_ssao,3);
  graphicsAPI.setTexture(m_downSapmle,4);
  graphicsAPI.setTexture(m_depthStencil,5);
  screen->set();
  
  graphicsAPI.drawIndex(6);
  graphicsAPI.unsetTextures(5);
}

void 
Deferred::directionalLight(const Matrix4f& viewMatrix, const Vector<DirectionalLight>& lights)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setBlendState(m_blendState1);
  resourseManager.m_shaderPrograms["directionalLight"]->set();
  graphicsAPI.setRenderTargets(m_lightBuffer);

  for(auto& light : lights){
    auto viewLight = light;
    viewLight.direction = (viewMatrix*viewLight.direction.normalized()).normalized();
    m_LightBuffer->write(&viewLight);
    graphicsAPI.setPSBuffer(m_LightBuffer,0);
    graphicsAPI.setTexture(m_normalTexture,0);
    graphicsAPI.setTexture(m_positionTexture,1);
    graphicsAPI.setTexture(m_specularTexture,2);
    graphicsAPI.setTexture(m_depthStencil,3);
    screen->set();
    graphicsAPI.drawIndex(6);
  }

  graphicsAPI.unsetTextures(4);
  graphicsAPI.setBlendState(m_blendState0);
}

void
Deferred::pointLight(const Matrix4f& viewMatrix, const Vector<PointLight>& lights)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setBlendState(m_blendState1);
  resourseManager.m_shaderPrograms["pointLight"]->set();
  graphicsAPI.setRenderTargets(m_lightBuffer);


  for(auto& light : lights){
    auto viewLight = light;
    viewLight.location = (viewMatrix*Vector4f(viewLight.location,1.0f)).xyz;
    m_LightBuffer->write(&viewLight);
    graphicsAPI.setPSBuffer(m_LightBuffer,0);

    graphicsAPI.setTexture(m_normalTexture,0);
    graphicsAPI.setTexture(m_positionTexture,1);
    graphicsAPI.setTexture(m_specularTexture,2);
    graphicsAPI.setTexture(m_depthStencil,3);
    screen->set();
    graphicsAPI.drawIndex(6);
  }
  graphicsAPI.unsetTextures(4);
  graphicsAPI.setBlendState(m_blendState0);
}

void 
Deferred::spotLight(const Matrix4f& viewMatrix, const Vector<SpotLight>& lights)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  graphicsAPI.setBlendState(m_blendState1);
  resourseManager.m_shaderPrograms["spotLight"]->set();
  graphicsAPI.setRenderTargets(m_lightBuffer);
  for(auto& light : lights){
    auto viewLight = light;
    viewLight.location = (viewMatrix*Vector4f(viewLight.location,1.0f)).xyz;
    viewLight.direction = (viewMatrix*Vector4f(viewLight.direction.normalized(),0.0f)).normalized().xyz;
    viewLight.direction.normalize();
    m_spotLightBuffer->write(&viewLight);
    graphicsAPI.setPSBuffer(m_spotLightBuffer,0);

    graphicsAPI.setTexture(m_normalTexture,0);
    graphicsAPI.setTexture(m_positionTexture,1);
    graphicsAPI.setTexture(m_specularTexture,2);
    graphicsAPI.setTexture(m_depthStencil,3);
    screen->set();
    graphicsAPI.drawIndex(6);

    //if(light.castShadows){
    //  generateShadowMap(light,scene)
    //}
  }
}

void 
Deferred::shadows(const Vector<SpotLight>& lights, SPtr<Scene> scene)
{
  int8 i = 0;
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  resourseManager.m_shaderPrograms["shadowMapper"]->set();
  for(auto& light : lights){
    if(light.castShadows){
      m_shadowsCamera->setLocation(light.location);
      m_shadowsCamera->lookAt(light.location+light.direction);
      setCamera(m_shadowsCamera);
      graphicsAPI.unsetRenderTargetAndDepthStencil();
      graphicsAPI.setRenderTargetAndDepthStencil(m_shadowMap,m_shadowMaps[i]);
      generateShadowMap(light,scene->getRoot());
    }
    ++i;
    if(i==4){
      break;
    }
  }
}

//void 
//Deferred::diffusePoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights)
//{
//  auto& resourseManager = ResoureManager::instance();
//  auto& graphicsAPI = GraphicAPI::instance();
//  graphicsAPI.unsetRenderTargetAndDepthStencil();
//  resourseManager.m_shaderPrograms["diffusePoint"]->set();
//  graphicsAPI.setBlendState(m_blendState1);
//  graphicsAPI.setRenderTarget(m_diffuseLight);
//  
//  graphicsAPI.setTexture(m_positionTexture,0);
//  graphicsAPI.setTexture(m_normalTexture,1);
//  graphicsAPI.setTexture(m_depthStencil,2);
//  
//  for(auto& light : lights){
//    auto viewLight = light;
//    viewLight.location = (viewMatrix*Vector4f(viewLight.location,1.0f)).xyz;
//    m_Light->write(&viewLight);
//    graphicsAPI.setPSBuffer(m_Light,0);
//    screen->set();
//    graphicsAPI.draw(6);
//    
//  }
//  graphicsAPI.unsetTextures(3);
//  graphicsAPI.setBlendState(m_blendState0);
//}
//
//void
//Deferred::specularPoint(const Matrix4f& viewMatrix, const Vector<PointLight>& lights)
//{
//  auto& resourseManager = ResoureManager::instance();
//  auto& graphicsAPI = GraphicAPI::instance();
//  graphicsAPI.unsetRenderTargetAndDepthStencil();
//  resourseManager.m_shaderPrograms["specularDirectional"]->set();
//  graphicsAPI.setBlendState(m_blendState1);
//  graphicsAPI.setRenderTarget(m_specularLight);
//
//  graphicsAPI.setTexture(m_normalTexture,0);
//  graphicsAPI.setTexture(m_positionTexture,1);
//  graphicsAPI.setTexture(m_specularTexture,2);
//  graphicsAPI.setTexture(m_depthStencil,3);
//  
//  for(auto& light : lights){
//    auto viewLight = light;
//    viewLight.location = (viewMatrix*Vector4f(viewLight.location,1.0f)).xyz;
//    m_Light->write(&viewLight);
//    graphicsAPI.setPSBuffer(m_Light,0);
//    screen->set();
//    graphicsAPI.draw(6);
//    
//  }
//  graphicsAPI.unsetTextures(2);
//  graphicsAPI.setBlendState(m_blendState0);
//}

void 
Deferred::downSapmle(SPtr<Texture> texture)
{
  auto& resourseManager = ResoureManager::instance();
  auto& graphicsAPI = GraphicAPI::instance();
  graphicsAPI.unsetRenderTargetAndDepthStencil();
  resourseManager.m_shaderPrograms["downSample"]->set();
  graphicsAPI.setTexture(texture,0);
  graphicsAPI.setRenderTarget(m_downSapmle);
  graphicsAPI.setPSBuffer(m_size,0);
  screen->set();
  graphicsAPI.drawIndex(6);
  graphicsAPI.unsetTextures(1);
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
  m_emisiveTexture->release();
  m_ssao->release();
  m_diffuseLight->release();
  m_specularLight->release();
  m_downSapmle->release();
  m_shadowMap->release();
  auto iSize = Vector2I(size.x,size.y);

  m_depthStencil->init(iSize,BIND::kDepthStencil,FORMAT::kR24G8);

  m_renderTarget = graphicsApi.getBackBuffer();
  //m_renderTarget->createShaderResource(FORMAT::kR32G32B32A32Float);
  m_renderTarget->createRenderTarget(FORMAT::kR32G32B32A32Float);

  m_colorTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_normalTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_positionTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_specularTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_emisiveTexture->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_ssao->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_blur->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_diffuseLight->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_specularLight->init(iSize,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  m_downSapmle->init(iSize/4,BIND::kRenderTarget,FORMAT::kR32G32B32A32Float);
  
  auto sizef = Vector2f(size.x,size.y);
  m_size->write(&sizef);
  sizef /= 4.f;
  //m_smallSize->write(&sizef);
}

void
Deferred::generateShadowMap(const SpotLight& light,SPtr<Actor> actor)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& childs = actor->getChilds();
  Matrix4f actorTransform;
  Matrix4f finalTransform;
  for(auto child : childs){
    actorTransform = child->getGlobalTransform();
    auto components = child->getComponents<GraphicsComponent>();
    for(auto& component : components){
      auto meshComponent = cast<GraphicsComponent>(component);
      auto model = meshComponent->getModel();
      if(model){
        finalTransform = actorTransform*meshComponent->getTransform().getMatrix();
        SIZE_T meshes = model->getNumOfMeshes();
        for(SIZE_T i = 0; i<meshes;++i){
        
          if(model->getMaterial(i)->getCastShadows()){
            auto& mesh =  model->getMesh(i);
            m_globalTransformBuffer->write(&finalTransform);
            graphicsApi.setVSBuffer(m_globalTransformBuffer, 0);
            mesh->set();
            graphicsApi.drawIndex(mesh->getIndexNum());
          }
        }
      }
    }
    generateShadowMap(light,child);
  }
}

//SPtr<Texture>
//Deferred::getShadowMap(const PointLight& lights,Vector<RenderData>& toRender)
//{
//  auto& graphicsAPI = GraphicAPI::instance();
//  auto& resourseManager = ResoureManager::instance();
//  graphicsAPI.unsetRenderTargetAndDepthStencil();
//  graphicsAPI.setRenderTargetAndDepthStencil(m_shadowMap,m_depthStencil);
//  graphicsAPI.setRasterizerState(m_normalRasterizer);
//  resourseManager.m_shaderPrograms["shadowMapper"]->set();
//  for(auto& renderData : toRender){
//    m_globalTransformBuffer->write(&renderData.m_transform);
//    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
//    renderData.m_mesh->set();
//    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
//  }
//}

SPtr<Texture> Deferred::applyShadowMap(SPtr<Texture>& scene, SPtr<Texture>& map)
{
  return SPtr<Texture>();
}

void
Deferred::setCamera(SPtr<Camera> camera)
{
  auto& graphicsApi = GraphicAPI::instance();

  m_viewBuffer->write(camera->getViewMatrix().getData());
  graphicsApi.setVSBuffer(m_viewBuffer,1);
  graphicsApi.setDSBuffer(m_viewBuffer,1);
  
  m_projectionBuffer->write(camera->getProjectionMatrix().getData());
  graphicsApi.setVSBuffer(m_projectionBuffer,2);
  graphicsApi.setDSBuffer(m_projectionBuffer,2);
}

SPtr<Texture> 
Deferred::getShadowMap()
{
  return m_shadowMap;
}

}

