/**
* @file oaMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector2f.h"
#include "oaVector3f.h"
#include "oaBuffer.h"

namespace oaEngineSDK{

/**
 * @brief a tructure for all the information at a certain point of a Mesh
*/
struct Vertex{
  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector3f location;

  /**
   * @brief the normal at a certain point
  */
  //Vector3f normals;

  /**
   * @brief the part of the texture that is going to be drawn at a certain point
  */
  //Vector2f textureCord;
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
  virtual void
  create();

  /**
   * @brief draws the mesh to screen
  */
  virtual void
  render();

 public:

  /**
   * @brief the indices of the vertices of each triangle
  */
  Vector<uint32> index;

  /**
   * @brief the location of the vertices of the mesh
  */
  Vector<Vertex> vertices;
 public:
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


