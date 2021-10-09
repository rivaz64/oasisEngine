/**
* @file oaBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class Buffer
{
 public:
  /**
  * @brief gets where the data of the buffer is
  */
  virtual void* 
  getPointer() = 0;

  /**
   * @brief gets the size of the data in bytes
  */
  virtual uint32 
  getSize() = 0;
};

}


