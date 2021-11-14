#include "oaSceneGraph.h"
#include "oaGraphicAPI.h"
#include "oaObject.h"
namespace oaEngineSDK{

void SceneGraph::drawObject(SPtr<Object> object)
{
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
}

}

