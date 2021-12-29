/**
 * @file oaChunk.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 12/16/2021
 */

#pragma once

#include "oaMesh.h"
#include "oaGrid3D.h"
#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class Chunk :
  public Mesh 
{
 public:

  /**
   * @brief initializes a chunk from the diven data
   * @param data 
  */
  void 
  init(const Grid3D<float>& data);

 private:

  /**
   * @brief creates the cube for the mesh at the given position
   * @param position 
   * @param data 
  */
  void
  createCubeAt(const Vector3U& position,const Grid3D<float>& data);

  /**
   * @brief if in this position should be a cube
   * @param position 
   * @param data 
   * @return 
  */
  bool 
  hasCube(const Vector3U& position,const Grid3D<float>& data);

  /**
   * @brief the indices for the chunk
  */
  Vector<uint32> indices;

  /**
   * @brief the vertices for the chunk
  */
  Vector<Vertex> vertices;


};

}


