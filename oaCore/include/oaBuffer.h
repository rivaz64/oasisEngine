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
   * @brief getter for the buffer from the GraphicalAPI
   * @return 
  */
  virtual void*
  get() = 0;

  /**
  * @brief gets where the data of the buffer is
  * @return 
  */
  virtual void* 
  getPointer() = 0;


  /**
  * @brief gets the size of the data in bytes
  * @return 
  */
  virtual uint32 
  getSize() = 0;
};

}


