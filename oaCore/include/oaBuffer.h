/**
* @file oaBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

enum class BUFFER_FLAGS{
  VERTEX,
  CONSTANT
};

class OA_CORE_EXPORT Buffer
{
 public:

  /**
   * @brief constructor default para el buffer
  */
  Buffer() = default;

  virtual ~Buffer() = default;

  /**
   * @brief sets the data of this buffer to an updated one
   * @param data the new data 
   * @param size the size of the new data
   * @param flags the type of buffer 
  */
  virtual void
  init(void* data,uint32 size,BUFFER_FLAGS flags) {};

};

}


