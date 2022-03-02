/**
* @file oaDebugMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/26/2022
*/

#pragma once
#include "oaMesh.h"
#include "oaVector4f.h"

namespace oaEngineSDK{

/**
 * @brief mesh with just positions
*/
class DebugMesh :
  public Mesh
{
 public:

  void 
  create() override;

  /**
   * @brief sets the number of vertices this mesh is going to have
   * @param n the number of vertices
  */
  FORCEINLINE void
  setVertexNum(SIZE_T n){
    m_vertices.resize(n);
  }

  FORCEINLINE SIZE_T
  getVertexNum(){
    return m_vertices.size();
  }

  /**
   * @brief gets a certain vertex
   * @param n the number of the vertex
   * @return the vertex 
  */
  FORCEINLINE Vector4f&
  getVertexAt(SIZE_T n){
    return m_vertices[n];
  }

  FORCEINLINE const Vector<Vector4f>&
  getVertex(){
    return m_vertices;
  }

  FORCEINLINE void
  setVertex(const Vector<Vector4f>& vertices){
    m_vertices = vertices;
  }

 protected:
  
  /**
   * @brief the vertices of this mesh
  */
  Vector<Vector4f> m_vertices;

};

}


