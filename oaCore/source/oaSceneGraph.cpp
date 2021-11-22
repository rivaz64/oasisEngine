#include "oaSceneGraph.h"
#include "oaGraphicAPI.h"
#include "oaObject.h"
#include <iostream>

namespace oaEngineSDK{

void SceneGraph::draw()
{
  cam->setCamera();
  for(SPtr<Tree<Object>> obj : objects.childs){
    drawObject(obj,Matrix4f::IDENTITY);
  }
}

void SceneGraph::addToScene(SPtr<Object> object)
{
  auto newNode = newSPtr<Tree<Object>>();
  newNode->data = object;
  object->subObjects = newNode;
  objects.childs.push_back(newNode);
}

void SceneGraph::drawObject(const SPtr<Tree<Object>> node,const Matrix4f& parentTransform)
{

  auto object = node->data;

  auto localTransform = parentTransform * object->getTransform();

  if(cam->isInFrustrum(localTransform*Vector4f(0,0,0,1))){
    std::cout<<"'isin"<<std::endl;
  }

  object->transformB->update(&localTransform);
  GraphicAPI::instancePtr()->setBuffer(object->transformB, 0);

  for(int i = 0;i<object->model->meshes.size();++i){

    if(object->model->textures[i]){
      //GraphicAPI::instancePtr()->setShader

      GraphicAPI::instancePtr()->setTexture(
        object->model->textures[i]
      );
    }
    

    GraphicAPI::instancePtr()->setVertexBuffer(
      object->model->meshes[i]->vertexB
    );

    GraphicAPI::instancePtr()->setIndexBuffer(
      object->model->meshes[i]->indexB
    );  

    GraphicAPI::instancePtr()->draw(object->model->meshes[i]->index.size());
  }

  for(SPtr<Tree<Object>> obj : node->childs){
    drawObject(obj,localTransform);
  }
}

}

