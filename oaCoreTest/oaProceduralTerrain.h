/**
 * @file oaProceduralTerrain.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 1/11/2021
 */

#pragma once

#include "oaMesh.h"
#include "oaGrid2D.h"

namespace oaEngineSDK{

class ProceduralTerrain :
  public Mesh
{
 public:

  /**
   * @brief initializes a terrain from the diven data
   * @param data 
  */
  void 
  init(const Grid2D<float>& data);

 private:
  /**
   * @brief the indices for the Terrain
  */
  Vector<uint32> indices;

  /**
   * @brief the vertices for the Terrain
  */
  Vector<Vertex> vertices;
};

}


