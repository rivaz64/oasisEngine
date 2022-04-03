/**
* @file oaMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaVector2f.h>
#include <oaVector3f.h>
#include <oaVector4U.h>
#include <oaVector4f.h>
#include <oaMatrix4f.h>
#include <oaSphere.h>
#include <oaAABB.h>
#include <oaTriangle.h>

namespace oaEngineSDK{
/**
 * @brief previus data for creating a mesh
*/
struct SubMesh{
  /**
   * @brief the location of the vertex
  */
  Vector<Vector4f> points;

  /**
   * @brief a temporal list of index
  */
  Vector<uint32> indices;
};

/**
 * @brief a structure for all the information at a certain point of a Mesh
*/
struct SimpleVertex{

  SimpleVertex(const Vector4f& _location, const Vector2f& _textureCord) :
    location(_location), textureCord(_textureCord){}
  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector4f location;

  /**
   * @brief the part of the texture that is going to be drawn at a certain point
  */
  Vector2f textureCord;
};

/**
 * @brief a structure for all the information at a certain point of a Mesh whit animations
*/
struct AnimationVertex{

  /**
   * @brief the ids of the bones that are afecting this vertex
  */
  Vector4U ids;

  /**
   * @brief how much each bone afects this vertex
  */
  Vector4f weights;

  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector4f location;

  /**
   * @brief the normal at this vertex
  */
  Vector4f normal;

  /**
   * @brief the tangent at this vertex
  */
  Vector4f tangent;

  /**
   * @brief the bitangent at this vertex
  */
  Vector4f bitangent;

  /**
   * @brief the part of the texture that is going to be drawn at a certain point
  */
  Vector2f textureCord;

};


/**
 * @brief a class for a mesh
*/
class OA_CORE_EXPORT Mesh
{
 public:

  /**
   * @brief default consturctor for the mesh
  */
  Mesh() = default;

  ~Mesh() = default;

  /**
   * @brief creates and fils the buffers
  */
  virtual void
  create();

  void
  create(void* data, SIZE_T vertexSize, SIZE_T dataSize);

  void
  create(SPtr<VertexBuffer> m_vertexB);

  /**
   * @brief sets the buffers to the GPU
  */
  virtual void
  set();

  /**
   * @brief calculates the boundings for this mesh
  */
  virtual void
  calculateBounding(){}

  void
  initFromSubMesh(const SubMesh& sm);

  /**
   * @brief creates the normals based on the the triangles
   * @param vertices 
   * @param index 
  */
  static void
  createNormals(Vector<Vertex>& vertices);

  /**
   * @brief sets how much indexes this mesh has
   * @param n the new number of indexes
  */
  FORCEINLINE void
  setIndexNum(SIZE_T n){
    m_index.resize(n);
  }

  FORCEINLINE SIZE_T
  getIndexNum(){
    return m_index.size();
  }

  /**
   * @brief sets an index
   * @param place where the index is in the list
   * @param index the value of the index
  */
  FORCEINLINE void
  setIndexAt(SIZE_T place,SIZE_T index){
    m_index[place] = index;
  }

  FORCEINLINE Vector<uint32>&
  getIndex(){
    return m_index;
  }

  FORCEINLINE void
  setIndex(const Vector<uint32>& index){
    m_index = index;
  }

  //template <class T>
  FORCEINLINE Vector<Vector4f>&
  getVertex(){
    return *reinterpret_cast<Vector<Vector4f>*>(&m_vertices);
  }

  FORCEINLINE const Sphere&
  getBoundingSphere(){
    return m_boundingSphere;
  }

  FORCEINLINE const AABB&
  getBoundingBox(){
    return m_boundingBox;
  }

 public:

  /**
   * @brief the number of indices this mesh has
  */
  Vector<uint32> m_index;

  /**
   * @brief the buffer for the indices
  */
  SPtr<IndexBuffer> m_indexB;

  /**
  * @brief the buffer for the vertex
  */
  SPtr<VertexBuffer> m_vertexB;

  /**
   * @brief the bounding sphere of this mesh
  */
  Sphere m_boundingSphere;

  /**
   * @brief the vertices of this mesh
  */
  Vector<char> m_vertices;

  /**
   * @brief the bounding box of this mesh
  */
  AABB m_boundingBox;

  friend class ResourceManager;
};

}


