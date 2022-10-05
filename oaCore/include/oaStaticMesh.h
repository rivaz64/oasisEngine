#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include "oaGraphicAPI.h"
#include "oaTriangle.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT StaticMesh :
  public Resourse
{
 public:
 
  /**
   * @brief default consturctor for the mesh
  */
  StaticMesh()
  {
    auto& graphicApi = GraphicAPI::instance();
    m_vertexB = graphicApi.createVertexBuffer();
    m_indexB = graphicApi.createIndexBuffer();
  }

  ~StaticMesh() = default;

  void
  save(Serializer& serializer) override;
  
  void
  load(Serializer& serializer) override;

  FORCEINLINE RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kStaticMesh;
  }

  void
  writeBuffers();

  FORCEINLINE void
  setVertexNum(SIZE_T n)
  {
    m_vertices.resize(n);
  }

  FORCEINLINE void
  setIndexNum(SIZE_T n)
  {
    m_index.resize(n);
  }


  FORCEINLINE SIZE_T
  getVertexNum()
  {
    return m_vertices.size();
  }

  FORCEINLINE SIZE_T
  getIndexNum()
  {
    return m_index.size();
  }

  FORCEINLINE void
  setVertexAt(SIZE_T place,Vertex vertex)
  {
    m_vertices[place] = vertex;
  }

  FORCEINLINE void
  setIndexAt(SIZE_T place,uint32 index)
  {
    m_index[place] = index;
  }

  FORCEINLINE Vector<uint32>&
  getIndex()
  {
    return m_index;
  }

  FORCEINLINE void
  setIndex(const Vector<uint32>& index)
  {
    m_index = index;
  }

  FORCEINLINE void
  setVertex(const Vector<Vertex>& vertices)
  {
    m_vertices = vertices;
  }

  FORCEINLINE Vector<Vertex>&
  getVertex()
  {
    return m_vertices;
  }

  FORCEINLINE const SPtr<VertexBuffer>&
  getVertexBuffer()
  {
    return m_vertexB;
  }

  FORCEINLINE const SPtr<IndexBuffer>&
  getIndexBuffer()
  {
    return m_indexB;
  }

 private:
  /**
   * @brief the vertices of this mesh
  */
  Vector<Vertex> m_vertices;

  /**
   * @brief the indices of this mesh
  */
  Vector<uint32> m_index;

  /**
  * @brief the buffer for the vertex
  */
  SPtr<VertexBuffer> m_vertexB;

  /**
   * @brief the buffer for the indices
  */
  SPtr<IndexBuffer> m_indexB;
};

}


