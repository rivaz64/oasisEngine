#include "oaMesh.h"
#include "oaGraphicAPI.h"
void oaEngineSDK::Mesh::create()
{
  vertexB = GraphicAPI::instancePtr()->createBuffer();
  indexB = GraphicAPI::instancePtr()->createBuffer();
  vertexB->init(vertices.data(),sizeof(Vertex)*vertices.size(),BUFFER_FLAGS::VERTEX);
  indexB->init(index.data(),sizeof(uint32)*index.size(),BUFFER_FLAGS::INDEX);
  vertices.clear();
  //index.clear();
}

void oaEngineSDK::Mesh::render()
{

}
