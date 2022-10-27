#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include <oaVector4U.h>
#include <oaVector4f.h>
#include "oaGraphicAPI.h"
#include <oaMatrix4f.h>

namespace oaEngineSDK
{

/**
 * @brief a structure for all the information at a certain point of a Mesh whit animations
*/
struct OA_CORE_EXPORT SkeletalVertex{

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

class OA_CORE_EXPORT SkeletalMesh :
  public Resourse
{
 public:

  SkeletalMesh()
  {
    auto& graphicApi = GraphicAPI::instance();
    m_vertexB = graphicApi.createVertexBuffer();
    m_indexB = graphicApi.createIndexBuffer();
    m_bones.resize(1024);
  }

  ~SkeletalMesh() = default;

  void
  save(Serializer& serializer) override;
  
  void
  load(Serializer& serializer) override;

  FORCEINLINE RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kSkeletalMesh;
  }

  void
  writeBuffers();

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

  FORCEINLINE SIZE_T
  getBonesNum(){
    return m_ids.size();
  }

  FORCEINLINE void
  setVertexAt(SIZE_T place,SkeletalVertex vertex){
    m_vertices[place] = vertex;
  }

  FORCEINLINE void
  setIndexAt(SIZE_T place,uint32 index){
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
  setVertex(const Vector<SkeletalVertex>& vertices){
    m_vertices = vertices;
  }

  FORCEINLINE Vector<SkeletalVertex>&
  getVertex(){
    return m_vertices;
  }

  FORCEINLINE Vector<Matrix4f>&
  getBones(){
    return m_bones;
  }

  FORCEINLINE const Matrix4f&
  getBoneAt(SIZE_T n){
    return m_bones[n];
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

  FORCEINLINE bool
  hasBone(uint32 id)
  {
    return find(m_ids.begin(), m_ids.end(), id) != m_ids.end();
  }

  FORCEINLINE void
  addBone(uint32 id, const Matrix4f& transform)
  {
    m_bones[m_ids.size()] = transform;
    m_ids.push_back(id);
  }

  FORCEINLINE SIZE_T
  getBoneId(uint32 name)
  {
    return find(m_ids.begin(), m_ids.end(), name) - m_ids.begin();
  }

  FORCEINLINE uint32
  getBoneId(SIZE_T id)
  {
    return m_ids[id];
  }

 private:
  /**
   * @brief the vertices of this mesh
  */
  Vector<SkeletalVertex> m_vertices;

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
  * @brief all the transforms of each bone
  */
  Vector<Matrix4f> m_bones;

  
  /**
   * @brief the name of each bone
  */
  Vector<uint32> m_ids;
  public:
  //Map<String,uint32> m_boneMaping;
  //
  //Vector<Matrix4f> m_ofset;

  
};

}


