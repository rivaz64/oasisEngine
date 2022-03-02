#include "oaDebugMesh.h"
#include "oaVertexBuffer.h"

namespace oaEngineSDK{

void 
DebugMesh::create()
{
  Mesh::create();

  m_vertexB->init(m_vertices.data(),sizeof(Vector4f),m_vertices.size());
}

}
