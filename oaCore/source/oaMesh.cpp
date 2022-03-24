/**
* @file oaMesh.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaMesh.h"
#include "oaBuffer.h"
#include "oaVertexBuffer.h"
#include "oaGraphicAPI.h"
#include "oaIndexBuffer.h"

namespace oaEngineSDK{

void
Mesh::create(){

  m_vertexB = GraphicAPI::instancePtr()->createVertexBuffer();

  m_indexB = GraphicAPI::instancePtr()->createIndexBuffer();

  m_indexB->init(m_index);

}

void
Mesh::set()
{
  m_vertexB->set();
  m_indexB->set();
}

void Mesh::initFromSubMesh(const SubMesh& sm)
{
  Vector<Vertex> vertices;
  Vector<uint32> indices;
  uint32 size = static_cast<uint32>(sm.indices.size());
  vertices.resize(size);
  for(uint32 i=0; i < size; ++i){
    vertices[i].textureCord = Vector2f(0,0);
    vertices[i].location = sm.points[sm.indices[i]];
    indices.push_back(static_cast<uint32>(indices.size()));
  }
  
  Mesh::createNormals(vertices);
  
  //create(vertices,indices);
}

void Mesh::createNormals(Vector<Vertex>& vertices)
{
  uint32 size = static_cast<uint32>(vertices.size());
  for(uint32 i=0; i < size; i+=3){
    Vector3f v1 = vertices[i+1].location.xyz-vertices[i].location.xyz;
    Vector3f v2 = vertices[i+2].location.xyz-vertices[i].location.xyz;
    Vector3f normal = Vector3f::cross(v1,v2);
    vertices[i].normal = Vector4f(normal,0.0f);
    vertices[i+1].normal = Vector4f(normal,0.0f);
    vertices[i+2].normal = Vector4f(normal,0.0f);
  }
}

void
Mesh::create(void* data, SIZE_T vertexSize, SIZE_T numOfVertex)
{
  create();

  m_vertexB->init(data,vertexSize,numOfVertex);
}

}
