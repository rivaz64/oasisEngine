#include "oaMesh.h"
#include "oaGraphicAPI.h"


void oaEngineSDK::Mesh::create()
{
  vertexB = GraphicAPI::instancePtr()->createBuffer();
  indexB = GraphicAPI::instancePtr()->createBuffer();
  vertexB->init(vertices.data(),sizeof(Vertex)*static_cast<uint64>(vertices.size()),BIND::VERTEX);
  indexB->init(index.data(),sizeof(uint32)*static_cast<uint64>(index.size()),BIND::INDEX);
  vertices.clear();
  //index.clear();
}

