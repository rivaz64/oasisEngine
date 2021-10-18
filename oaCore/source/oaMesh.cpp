#include "oaMesh.h"
#include "oaGraphicAPI.h"
void oaEngineSDK::Mesh::create()
{
  vertexB = GraphicAPI::instancePtr()->createBuffer();
  vertexB->init(vertices.data(),sizeof(Vertex)*vertices.size());
  vertices.clear();
}

void oaEngineSDK::Mesh::render()
{

}
