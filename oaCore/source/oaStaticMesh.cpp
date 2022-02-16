#include "oaStaticMesh.h"
#include "oaVertexBuffer.h"

namespace oaEngineSDK{

void 
StaticMesh::create()
{
  Mesh::create();

  m_vertexB->init(m_vertices.data(),sizeof(Vertex),static_cast<uint32>(m_vertices.size()));
}

}

