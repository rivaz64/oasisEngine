#include "oaStaticMesh.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"
#include "oaResoureManager.h"
namespace oaEngineSDK
{

void
StaticMesh::save(Serializer& serializer) 
{
  serializer.encodeNumber(getType());
  serializer.encodeString(getName());
  serializer.encodeVector(m_vertices);
  serializer.encodeVector(m_index);
}

void
StaticMesh::load(Serializer& serializer)
{
  setName(serializer.decodeString());
  serializer.decodeVector(m_vertices);
  serializer.decodeVector(m_index);
  writeBuffers();
}

void
StaticMesh::writeBuffers()
{
  m_vertexB->release();
  m_indexB->release();
  m_vertexB->init(m_vertices.data(),sizeof(Vertex),m_vertices.size());
  m_indexB->init(m_index);
}

}