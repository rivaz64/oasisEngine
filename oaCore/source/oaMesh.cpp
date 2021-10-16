#include "oaMesh.h"

void oaEngineSDK::Mesh::create()
{
  //indexB->updateResourse(index.data(),sizeof(uint32)*index.size());
  vertexB->updateResourse(vertices.data(),sizeof(Vertex)*vertices.size());
  vertices.clear();
}
