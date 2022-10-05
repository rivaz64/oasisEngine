#include "oaSkeletalMesh.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"
namespace oaEngineSDK
{
void 
SkeletalMesh::save(Serializer& serializer)
{
}
void 
SkeletalMesh::load(Serializer& serializer)
{
}
void
SkeletalMesh::writeBuffers()
{
  m_vertexB->release();
  m_indexB->release();
  m_vertexB->init(m_vertices.data(),sizeof(SkeletalVertex),m_vertices.size());
  m_indexB->init(m_index);
}

}

