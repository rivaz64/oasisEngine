#include "oaSceneGraph.h"
#include "oaGraphicAPI.h"
#include "oaObject.h"

namespace oaEngineSDK{

void SceneGraph::draw()
{

  for(SPtr<Tree<Object>> obj : objects.childs){
    
    drawObject(obj,Matrix4f::identity);
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

  object->transformB->update(&localTransform);
  GraphicAPI::instancePtr()->setBuffer(object->transformB, 0);

  for(int i = 0;i<object->model->meshes.size();++i){
    GraphicAPI::instancePtr()->setTexture(
      object->model->textures[i]
    );

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

