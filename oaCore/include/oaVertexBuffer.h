/**
* @file oaVertexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/30/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a buffer for the vertices
*/
class OA_CORE_EXPORT VertexBuffer
{

 public:
  /**
   * @brief initialize the buffer
   * @param data the data of the vertices
   * @param vertexSize the size of each vertex
   * @param numberOfVertices the number of vertices
   * @return if the buffer initialized correctly
  */
  virtual bool
  init(void* /*data*/, uint32 /*vertexSize*/, uint32 /*numberOfVertices*/) { return true; }


  virtual void
  set() {}
};

}

