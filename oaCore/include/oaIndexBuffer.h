/**
* @file oaIndexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a buffer for the indices
*/
class OA_CORE_EXPORT IndexBuffer
{
  public:

  /**
   * @brief initialize the buffer
   * @param data the data of the vertices
   * @return if the buffer initialized correctly
  */
  virtual bool
  init(Vector<uint32>& /*data*/) { return true; }

  /**
   * @brief set this buffer to be used
  */
  virtual void
  set() {}
};

}


