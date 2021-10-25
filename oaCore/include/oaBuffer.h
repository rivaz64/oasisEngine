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
   * @brief initialize the buffer
   * @param data the new data 
   * @param size the size of the new data
   * @param flags the type of buffer 
  */
  virtual void
  init(void* data,uint32 size,BUFFER_FLAGS flags) {}

  /**
   * @brief changes the data of the buffer
   * @param data 
   * @param size 
  */
  virtual void
  update(void* data,uint32 size){}

};

}


