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
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

/**
 * @brief a structure for all the information at a certain point of a Mesh
*/
struct Vertex{
  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector3f location;

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
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector3f location;

  /**
   * @brief the part of the texture that is going to be drawn at a certain point
  */
  Vector2f textureCord;

  /**
   * @brief the ids of the bones that are afecting this vertex
  */
  Vector4U ids = Vector4U::ZERO;

  /**
   * @brief how much each bone afects this vertex
  */
  Vector4f weights = Vector4f::ZERO;

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
  create(Vector<T> vertices){
    vertexB = GraphicAPI::instancePtr()->createBuffer();
    indexB = GraphicAPI::instancePtr()->createBuffer();
    vertexB->init(vertices.data(),sizeof(T)*static_cast<uint64>(vertices.size()),BIND::VERTEX);
    indexB->init(index.data(),sizeof(uint32)*static_cast<uint64>(index.size()),BIND::INDEX);
  }

 public:

  /**
   * @brief the number of indices this mesh has
  */
  Vector<uint32> index;

  /**
   * @brief the buffer for the indices
  */
  SPtr<Buffer> indexB;

  /**
  * @brief the buffer for the vertex
  */
  SPtr<Buffer> vertexB;

  
};

}


