#include "oaStaticMesh.h"
#include "oaVertexBuffer.h"

namespace oaEngineSDK{

void 
StaticMesh::create()
{
  Mesh::create();

  m_vertexB->init(m_vertices.data(),sizeof(Vertex),m_vertices.size());
}

}

