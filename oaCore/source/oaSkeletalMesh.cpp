#include "oaSkeletalMesh.h"
#include "oaVertexBuffer.h"
#include "oaGraphicAPI.h"
#include "oaBuffer.h"

namespace oaEngineSDK{

void 
SkeletalMesh::create()
{ 
  Mesh::create();

  m_vertexB->init(m_vertices.data(),
                  sizeof(AnimationVertex),
                  m_vertices.size());

  m_bonesB = GraphicAPI::instance().createBuffer();

  m_bonesB->init(sizeof(Matrix4f)*1024);

  //m_ofset.resize(1024);
  //for(int i = 0;i<1024;++i){
  //  m_ofset[i] = Matrix4f::IDENTITY;
  //}
}

void SkeletalMesh::set()
{
  Mesh::set();

  m_bonesB->write(m_ofset.data());

  GraphicAPI::instance().setVSBuffer(m_bonesB,3);
}

}

