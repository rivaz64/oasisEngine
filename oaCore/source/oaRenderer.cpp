#include "oaRenderer.h"
#include <oaFrustum.h>
#include "oaScene.h"
#include "oaMatrix4f.h"
#include "oaActor.h"
#include "oaGraphicsComponent.h"
#include "oaModel.h"
#include "oaMesh.h"
#include "oaMaterial.h"
#include "oaResoureManager.h"
#include "oaShaderProgram.h"
#include "oaBuffer.h"
#include "oaGraphicAPI.h"
#include "oaCamera.h"
#include "oaRasterizer.h"
#include "oaCameraComponent.h"
#include "oaDebugMesh.h"

namespace oaEngineSDK{
void Renderer::init()
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

}

void
Renderer::render(SPtr<Scene> scene,SPtr<Camera> camera)
{
  auto& resourseManager = ResoureManager::instance();
  
  auto& graphicsAPI = GraphicAPI::instance();
  
  m_viewBuffer->write(&camera->getViewMatrix().m11);
  graphicsAPI.setVSBuffer(m_viewBuffer,1);
  
  m_projectionBuffer->write(&camera->getProjectionMatrix().m11);
  graphicsAPI.setVSBuffer(m_projectionBuffer,2);
  
  m_viewLocationBuffer->write(&camera->getLocation().x);
  graphicsAPI.setVSBuffer(m_viewLocationBuffer,4);
  
  Vector<RenderData> toRender;

  Frustum frustrum(camera->getLocation(),
                   camera->getAxisMatrix(),
                   camera->getNearPlaneDistance(),
                   camera->getFarPlaneDistance(),
                   camera->getViewAngle(),
                   camera->getRatio());



  meshesInFrustum(scene->getRoot(),frustrum,toRender);

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
    
    default:
      break;
    }

    m_globalTransformBuffer->write(&renderData.m_transform);
    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);

    renderData.m_mesh->set();
    graphicsAPI.draw(renderData.m_mesh->getIndexNum());
  }
  //
  //Matrix4f finalTransform;
  //
  //Matrix4f globalActorTransform;
  //
  //for(auto actor : seenActors){
  //  
  //  auto component =  actor->getComponent<GraphicsComponent>();
  //
  //  if(!(component && component->m_models.size()!=0)){
  //    continue;
  //  }
  //
  //  globalActorTransform = actor->getGlobalTransform();
  //
  //  for(auto& modelPair : actor->getComponent<GraphicsComponent>()->m_models){
  //
  //    auto& model = modelPair.second.model;
  //
  //    for(uint32 i = 0;i<model->getNumOfMeshes();++i){
  //    
  //      if(model->getNumOfMaterials()>i && model->getMaterial(i)){
  //        model->getMaterial(i)->set();
  //        switch (model->getMaterial(i)->getShader())
  //        {
  //        case SHADER_TYPE::kNormal:
  //          resourseManager.m_shaderPrograms["default"]->set();
  //          graphicsAPI.setRasterizer(m_normalRasterizer);
  //          break;
  //
  //        case SHADER_TYPE::kAnimation:
  //          resourseManager.m_shaderPrograms["animation"]->set();
  //          graphicsAPI.setRasterizer(m_normalRasterizer);
  //          break;
  //
  //        case SHADER_TYPE::kParalax:
  //          resourseManager.m_shaderPrograms["paralax"]->set();
  //          graphicsAPI.setRasterizer(m_normalRasterizer);
  //          break;
  //
  //        case SHADER_TYPE::kTransparent:
  //          resourseManager.m_shaderPrograms["transparent"]->set();
  //          graphicsAPI.setRasterizer(m_normalRasterizer);
  //          break;
  //
  //        default:
  //          break;
  //        }
  //      }
  //
  //      finalTransform = globalActorTransform * modelPair.second.getFinalTransform();
  //
  //      m_globalTransformBuffer->write(&finalTransform);
  //
  //      graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  //
  //      auto& actualMesh = model->getMesh(i);
  //
  //      actualMesh->set();
  //     
  //      graphicsAPI.draw(actualMesh->getIndexNum());
  //    }
  //  }
  //}
  //
  //for(auto actor : seenActors){
  //  auto cameraComponent = actor->getComponent<CameraComponent>();
  //  if(cameraComponent){
  //    auto& cam =cameraComponent->getCamera();
  //    auto points = Frustum::calculatePoints(cam->getLocation(),
  //                                           cam->getAxisMatrix(),
  //                                           cam->getNearPlaneDistance(),
  //                                           cam->getFarPlaneDistance(),
  //                                           cam->getViewAngle(),
  //                                           cam->getRatio());
  //
  //    Vector<Vector4f> vertices;
  //
  //    for(auto& point : points){
  //      vertices.push_back(Vector4f(point,1.0f));
  //    }
  //
  //    auto mesh = newSPtr<DebugMesh>();
  //    mesh->setVertex(vertices);
  //
  //    mesh->setIndex({
  //      0,1,2,
  //      1,2,3,
  //      
  //      4,5,6,
  //      5,6,7,
  //      
  //      0,1,4,
  //      1,4,5,
  //      
  //      2,3,6,
  //      3,6,7,
  //      
  //      0,2,4,
  //      2,4,6,
  //      
  //      1,3,5,
  //      3,5,7,
  //
  //    });
  //
  //    mesh->create();
  //
  //    mesh->set();
  //
  //    graphicsAPI.setRasterizer(m_debugRasterizer);
  //
  //    finalTransform = actor->getGlobalTransform();
  //
  //    m_globalTransformBuffer->write(&finalTransform);
  //
  //    graphicsAPI.setVSBuffer(m_globalTransformBuffer, 0);
  //
  //    resourseManager.m_shaderPrograms["debug"]->set();
  //
  //    graphicsAPI.draw(mesh->getIndexNum());
  //
  //  }
  //}
}

void 
Renderer::meshesInFrustum(SPtr<Actor> actor, const Frustum& frustum,Vector<RenderData>& toRender)
{
  auto& childs = actor->getChilds();

  Matrix4f actorTransform;
  
  Matrix4f finalTransform;

  for(auto actor : childs){
  
    auto component = actor->getComponent<GraphicsComponent>();
    if(!component){
      continue;
    }

    auto model = component->getModel();
    if(!model){
      continue;
    }

    actorTransform = actor->getGlobalTransform();

    finalTransform = actorTransform*component->getTransform().getMatrix();

    SIZE_T meshes = model->getNumOfMeshes();
    for(SIZE_T i = 0; i<meshes;++i){
      toRender.push_back(RenderData(model->getMesh(i),model->getMaterial(i),finalTransform));
    }
  
    meshesInFrustum(actor,frustum,toRender);
  
  }
}



}

