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
  
  virtual
  ~VertexBuffer(){}

  /**
   * @brief initialize the buffer
   * @param data the data of the vertices
   * @param vertexSize the size of each vertex
   * @param numberOfVertices the number of vertices
   * @return if the buffer initialized correctly
  */
  virtual bool
  init(const void* /*data*/, uint32 /*vertexSize*/, SIZE_T /*numberOfVertices*/) { return true; }

  /**
   * @brief set this buffer to be used
  */
  virtual void
  set() {}

  /**
   * @brief release the data
  */
  virtual void
  release(){}
};

}

