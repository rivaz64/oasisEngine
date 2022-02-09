/**
* @file oaMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector2f.h"
#include "oaVector3f.h"
#include "oaVector4U.h"
#include "oaVector4f.h"
#include "oaMatrix4f.h"

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
struct Vertex{
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
 * @brief a structure for all the information at a certain point of a Mesh whit animations
*/
struct AnimationVertex{

  /**
   * @brief the ids of the bones that are afecting this vertex
  */
  Vector4U ids = Vector4U::ZERO;

  /**
   * @brief how much each bone afects this vertex
  */
  Vector4f weights = Vector4f::ZERO;

  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector4f location  = Vector4f::ZERO;

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
  * @brief sends all the data from the cpu tode gpu
  */
  /*template<class T>
  void
  create(Vector<T>& vertices,Vector<uint32>& index){

    indexNumber = static_cast<uint64>(index.size());

    vertexB = GraphicAPI::instancePtr()->createVertexBuffer();

    indexB = GraphicAPI::instancePtr()->createIndexBuffer();

    vertexB->init(vertices.data(),sizeof(T),static_cast<uint64>(vertices.size()));

    indexB->init(index);

  }*/

  void
  create(Vector<Vertex>& vertices,Vector<uint32>& index);

  void
  create(Vector<AnimationVertex>& vertices,Vector<uint32>& index);

  /**
  * @brief sends all the data from the cpu tode gpu, with bones
  */
  void
  create(Vector<AnimationVertex>& vertices,Vector<uint32>& index, Vector<Matrix4f>& _bones);

  /**
   * @brief sets the buffers to the GPU
  */
  void
  set();

  void
  initFromSubMesh(const SubMesh& sm);

  /**
   * @brief creates the normals based on the the triangles
   * @param vertices 
   * @param index 
  */
  static void
  createNormals(Vector<Vertex>& vertices);

  

 private:

  /**
   * @brief the number of indices this mesh has
  */
  uint32 m_indexNumber = 0;

  /**
   * @brief the buffer for the indices
  */
  SPtr<IndexBuffer> m_indexB;

  /**
  * @brief the buffer for the vertex
  */
  SPtr<VertexBuffer> m_vertexB;

  //SPtr<Buffer

  /**
   * @brief the buffer for the bones
  */
  SPtr<Buffer> m_bonesB;

  /**
   * @brief if this mesh has bones or not
  */
  bool m_hasBones = false;

  /**
   * @brief the bones of this mesh
  */
  Vector<Matrix4f> m_bones;

  Vector<Matrix4f> m_ofset;

  /**
   * @brief the names of the bones used by this mesh
  */
  Map<String,uint32> m_boneMaping;

  friend class TestApp;
  friend class Loader;
  friend class AnimationComponent;
};

}


