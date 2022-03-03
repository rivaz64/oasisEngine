#include "oaStaticMesh.h"
#include "oaVertexBuffer.h"

namespace oaEngineSDK{

void 
StaticMesh::create()
{
  Mesh::create();

  m_vertexB->init(m_vertices.data(),sizeof(Vertex),m_vertices.size());

  calculateBounding();
}

void 
StaticMesh::calculateBounding()
{
  float maxDistance = 0;
  float distance;
  float inverse = 1.f/static_cast<float>(m_vertices.size());
  Vector3f center = Vector3f::ZERO;
  Vector3f maxPoint = Vector3f::ZERO;
  Vector3f minPoint = Vector3f::ZERO;

  for(auto& vertex : m_vertices){
    center += vertex.location.xyz * inverse;
    minPoint.x = Math::min(minPoint.x,vertex.location.x);
    maxPoint.x = Math::max(maxPoint.x,vertex.location.x);
    minPoint.y = Math::min(minPoint.y,vertex.location.y);
    maxPoint.y = Math::max(maxPoint.y,vertex.location.y);
    minPoint.z = Math::min(minPoint.z,vertex.location.z);
    maxPoint.z = Math::max(maxPoint.z,vertex.location.z);
  }

  m_boundingSphere.setCenter(center);
  m_boundingBox.setMinPoint(minPoint);
  m_boundingBox.setMaxPoint(maxPoint);

  for(auto& vertex : m_vertices){
    distance = (vertex.location.xyz-center).magnitud();
    maxDistance = Math::max(distance, maxDistance);
  }

  m_boundingSphere.setRadius(maxDistance);
}

}

