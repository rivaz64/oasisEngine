#include "oaSkeletalMesh.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"
namespace oaEngineSDK
{

void 
SkeletalMesh::onSave(Serializer& serializer)
{
  serializer.encodeVector(m_vertices);
  serializer.encodeVector(m_index);
  serializer.encodeVector(m_bones);
}

void 
SkeletalMesh::load(Serializer& serializer)
{
  serializer.decodeVector(m_vertices);
  serializer.decodeVector(m_index);
  serializer.decodeVector(m_bones);
  writeBuffers();
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

