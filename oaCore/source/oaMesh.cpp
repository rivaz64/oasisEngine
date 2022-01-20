#include "oaMesh.h"

namespace oaEngineSDK{

void
Mesh::create(Vector<Vertex>& vertices,Vector<uint32>& index){

  
  indexNumber = static_cast<uint64>(index.size());

  vertexB = GraphicAPI::instancePtr()->createVertexBuffer();

  indexB = GraphicAPI::instancePtr()->createIndexBuffer();

  vertexB->init(vertices.data(),sizeof(Vertex),static_cast<uint64>(vertices.size()));

  indexB->init(index);

}

void
Mesh::create(Vector<AnimationVertex>& vertices,Vector<uint32>& index){

  indexNumber = static_cast<uint64>(index.size());

  vertexB = GraphicAPI::instancePtr()->createVertexBuffer();

  indexB = GraphicAPI::instancePtr()->createIndexBuffer();

  vertexB->init(vertices.data(),sizeof(AnimationVertex),static_cast<uint64>(vertices.size()));

  indexB->init(index);

}

void Mesh::create(Vector<AnimationVertex>& vertices, Vector<uint32>& index, Vector<Matrix4f>& _bones)
{
  create(vertices,index);

  hasBones = true;

  bones = _bones;

  bonesB = GraphicAPI::instancePtr()->createBuffer();

  bonesB->init(sizeof(Matrix4f)*1024);

  ofset.resize(1024);
  for(int i = 0;i<1024;++i){
    ofset[i] = Matrix4f::IDENTITY;
  }
}

void Mesh::initFromSubMesh(const SubMesh& sm)
{
  Vector<Vertex> vertices;
  Vector<uint32> indices;
  uint32 size = sm.indices.size();
  vertices.resize(size);
  for(int32 i=0;i<size;++i){
    vertices[i].textureCord = Vector2f(0,0);
    vertices[i].location = sm.points[sm.indices[i]];
    indices.push_back(indices.size());
  }
  
  Mesh::createNormals(vertices);
  
  create(vertices,indices);
}

void Mesh::createNormals(Vector<Vertex>& vertices)
{
  uint32 size = vertices.size();
  for(uint32 i=0;i<size;i+=3){
    Vector3f v1 = vertices[i+1].location.xyz-vertices[i].location.xyz;
    Vector3f v2 = vertices[i+2].location.xyz-vertices[i].location.xyz;
    Vector3f normal = Vector3f::cross(v1,v2);
    vertices[i].normal = Vector4f(normal,0.0f);
    vertices[i+1].normal = Vector4f(normal,0.0f);
    vertices[i+2].normal = Vector4f(normal,0.0f);
  }
}

}
