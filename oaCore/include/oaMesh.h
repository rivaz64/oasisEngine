/**
* @file oaMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include <oaVector2f.h>
#include <oaVector3f.h>
#include <oaVector4U.h>
#include <oaVector4f.h>
#include <oaMatrix4f.h>
#include <oaSphere.h>
#include <oaAABB.h>
#include <oaTriangle.h>
#include <oaSerializer.h>
#include "oaBuffer.h"
#include "oaIndexBuffer.h"
#include "oaVertexBuffer.h"
#include "oaGraphicAPI.h"



namespace oaEngineSDK{

/**
 * @brief a structure for all the information at a certain point of a Mesh
*/
struct OA_CORE_EXPORT SimpleVertex{

  SimpleVertex() = default;

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
struct OA_CORE_EXPORT AnimationVertex{

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

class OA_CORE_EXPORT MeshType:
  public Resourse
{

};

/**
 * @brief a class for a mesh
*/
template<class VertexType>
class OA_CORE_EXPORT Mesh :
  public MeshType
{
 public:

  /**
   * @brief default consturctor for the mesh
  */
  Mesh()
  {
    auto& graphicApi = GraphicAPI::instance();
    m_vertexB = graphicApi.createVertexBuffer();
    m_indexB = graphicApi.createIndexBuffer();
  }

  ~Mesh() = default;

  void
  save(Serializer& serializer) override
  {
    serializer.encodeNumber(m_vertices.size());
    serializer.file.write(reinterpret_cast<const char*>(m_vertices.data()),
                          sizeof(VertexType)*m_vertices.size());
    serializer.encodeNumber(m_index.size());
    serializer.file.write(reinterpret_cast<const char*>(m_index.data()),
                          sizeof(uint32)*m_index.size());
  }
  
  void
  load(Serializer& serializer) override
  {
    SIZE_T num;
    num = serializer.decodeNumber();
    m_vertices.resize(num);
    serializer.file.read(reinterpret_cast<char*>(m_vertices.data()),
                          sizeof(VertexType)*num);
    serializer.encodeNumber(num);
    m_index.resize(num);
    serializer.file.write(reinterpret_cast<char*>(m_index.data()),
                          sizeof(uint32)*num);
  }

  void
  writeBuffers()
  {
    m_vertexB->release();
    m_indexB->release();
    m_vertexB->init(m_vertices.data(),sizeof(Vertex),m_vertices.size());
    m_indexB->init(m_index);
  }

  /**
   * @brief sets the buffers to the GPU
  */
  FORCEINLINE void
  set()
  {
    m_vertexB->set();
    m_indexB->set();
  }

  /**
   * @brief calculates the boundings for this mesh
  */
  virtual void
  calculateBounding(){}

  FORCEINLINE void
  setVertexNum(SIZE_T n){
    m_vertices.resize(n);
  }

  FORCEINLINE void
  setIndexNum(SIZE_T n){
    m_index.resize(n);
  }


  FORCEINLINE SIZE_T
  getVertexNum(){
    return m_vertices.size();
  }

  FORCEINLINE SIZE_T
  getIndexNum(){
    return m_index.size();
  }

  FORCEINLINE void
  setVertexAt(SIZE_T place,Vertex vertex){
    m_vertices[place] = vertex;
  }

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

  FORCEINLINE void
  setVertex(const Vector<VertexType>& vertices){
    m_vertices = vertices;
  }

  FORCEINLINE Vector<VertexType>&
  getVertex(){
    return m_vertices;
  }

  FORCEINLINE const Sphere&
  getBoundingSphere(){
    return m_boundingSphere;
  }

  FORCEINLINE const AABB&
  getBoundingBox(){
    return m_boundingBox;
  }

  void
  setControlPoints(const Vector<Vector4f>& points)
  {
    auto& graphicsApi = GraphicAPI::instance();
    m_controlPoints = graphicsApi.createVertexBuffer();
    m_controlPoints->init(points.data(),sizeof(Vector4f),points.size());
    m_numOfControlPoints = points.size();
  }

  FORCEINLINE SPtr<VertexBuffer>
  getControlPoints(){
    return m_controlPoints;
  }

  FORCEINLINE int32
  getNumOfControlPoints(){
    return m_numOfControlPoints;
  }

 public:

  /**
   * @brief the indices of this mesh
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
   * @brief the vertices of this mesh
  */
  Vector<VertexType> m_vertices;

  /**
   * @brief the bounding sphere of this mesh
  */
  Sphere m_boundingSphere;

  /**
   * @brief the bounding box of this mesh
  */
  AABB m_boundingBox;

  /**
   * @brief the control points used for bezier curbes
  */
  SPtr<VertexBuffer> m_controlPoints;

  Map<String,uint32> m_boneMaping;

  Vector<Matrix4f> m_ofset;

  Vector<Matrix4f> m_bones;

  int32 m_numOfControlPoints;

  friend class ResourceManager;
};


//typedef OA_CORE_EXPORT Mesh<AnimationVertex>;
//typedef OA_CORE_EXPORT Mesh<SimpleVertex>;

}


