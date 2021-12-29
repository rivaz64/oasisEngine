/**
 * @file oaMarchingCubes.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 12/28/2021
 */

#pragma once
#include <oaMesh.h>
#include <oaPrerequisitesCore.h>
#include <oaGrid3D.h>

namespace oaEngineSDK{

class MarchingCubes :
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
   * @brief gets the number of triangulation to be use 
   * @param location the location of this triangulation in the grid
   * @param data the grid
   * @return 
  */
  uint8
  getTriangulation(const Vector3U location,const Grid3D<float>& data);

  /**
   * @brief adds the triangulation
   * @param triangulation triangulation to be added 
   * @param location the location where the triangulation is going to be added
  */
  void
  addTriangulation(int8* triangulation,const Vector3U location);

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


