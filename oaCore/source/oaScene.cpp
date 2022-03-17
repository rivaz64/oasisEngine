#include "oaScene.h"
#include <oaFrustum.h>
#include "oaActor.h"
#include "oaGraphicsComponent.h"
#include "oaModel.h"
#include "oaMesh.h"
#include "oaCameraComponent.h"
#include "oaCamera.h"
#include "oaDebugMesh.h"
#include "oaResoureManager.h"

namespace oaEngineSDK{

void
Scene::init(){
  m_root = makeSPtr<Actor>();
}

void 
Scene::meshesToRender(SPtr<Actor> actor, const Frustum& frustum, Vector<RenderData>& toRender)
{
  auto& childs = actor->getChilds();

  Matrix4f actorTransform;
  
  Matrix4f finalTransform;

  for(auto actor : childs){

    actorTransform = actor->getGlobalTransform();
  
    auto component = actor->getComponent<GraphicsComponent>();
    if(component){
      auto model = component->getModel();
      if(model){
        finalTransform = actorTransform*component->getTransform().getMatrix();

        SIZE_T meshes = model->getNumOfMeshes();
        for(SIZE_T i = 0; i<meshes;++i){
          auto& mesh = model->getMesh(i);

          if(true){//frustum.isInside(mesh->getBoundingSphere(),finalTransform) || frustum.isInside(mesh->getBoundingBox(),finalTransform)){
            toRender.push_back(RenderData(mesh,model->getMaterial(i),finalTransform));
          }
        }

        
      }
    }

    auto camComponent = actor->getComponent<CameraComponent>();
    if(camComponent && camComponent->m_debug){
      auto& cam = camComponent->getCamera();
      auto points = Frustum::calculatePoints(cam->getLocation(),
                                             cam->getAxisMatrix(),
                                             cam->getNearPlaneDistance(),
                                             cam->getFarPlaneDistance(),
                                             cam->getViewAngle(),
                                             cam->getRatio());
      
      Vector<Vector4f> vertices;
      
      for(auto& point : points){
        vertices.push_back(Vector4f(point,1.0f));
      }
      
      auto mesh = makeSPtr<DebugMesh>();
      mesh->setVertex(vertices);
      
      mesh->setIndex({
        0,1,2,
        1,2,3,
        
        4,5,6,
        5,6,7,
        
        0,1,4,
        1,4,5,
        
        2,3,6,
        3,6,7,
        
        0,2,4,
        2,4,6,
        
        1,3,5,
        3,5,7,
      });
      
      mesh->create();

      toRender.push_back(RenderData(mesh,ResoureManager::instance().m_materials["debug"],Matrix4f::IDENTITY));
    }
    
    meshesToRender(actor,frustum,toRender);
  }

}

}