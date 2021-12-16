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
#include "oaBuffer.h"
#include "oaVertexBuffer.h"
#include "oaGraphicAPI.h"
#include "oaIndexBuffer.h"
#include "oaMatrix4f.h"
#include <iostream>

namespace oaEngineSDK{

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
  Vector4f Normal;

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
class Mesh
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
  template<class T>
  void
  create(Vector<T>& vertices,Vector<uint32>& index){

    indexNumber = static_cast<uint64>(index.size());

    vertexB = GraphicAPI::instancePtr()->createVertexBuffer();

    indexB = GraphicAPI::instancePtr()->createIndexBuffer();

    vertexB->init(vertices.data(),sizeof(T),static_cast<uint64>(vertices.size()));

    indexB->init(index);

  }

  /**
  * @brief sends all the data from the cpu tode gpu, with bones
  */
  template<class T>
  void
  create(Vector<T>& vertices,Vector<uint32>& index, Vector<Matrix4f>& _bones){

    create(vertices,index);

    hasBones = true;

    bones = _bones;

    bonesB = GraphicAPI::instancePtr()->createBuffer();

    bonesB->init(sizeof(Matrix4f)*bones.size());

    ofset.resize(bones.size());

  }

 public:

  /**
   * @brief the number of indices this mesh has
  */
  uint64 indexNumber;

  /**
   * @brief the buffer for the indices
  */
  SPtr<IndexBuffer> indexB;

  /**
  * @brief the buffer for the vertex
  */
  SPtr<VertexBuffer> vertexB;

  //SPtr<Buffer

  /**
   * @brief the buffer for the bones
  */
  SPtr<Buffer> bonesB;

  /**
   * @brief if this mesh has bones or not
  */
  bool hasBones = false;

  /**
   * @brief the bones of this mesh
  */
  Vector<Matrix4f> bones;

  Vector<Matrix4f> ofset;

  /**
   * @brief the names of the bones used by this mesh
  */
  Map<String,uint32> boneMaping;
};

}


