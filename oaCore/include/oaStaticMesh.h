/**
* @file oaStaticMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/9/2022
*/

#pragma once

#include "oaMesh.h"

namespace oaEngineSDK{

class StaticMesh :
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

  /**
   * @brief gets a certain vertex
   * @param n the number of the vertex
   * @return the vertex 
  */
  FORCEINLINE Vertex&
  getVertexAt(SIZE_T n){
    return m_vertices[n];
  }

 protected:
  
  /**
   * @brief the vertices of this mesh
  */
  Vector<Vertex> m_vertices;
};

}


