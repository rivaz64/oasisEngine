/**
* @file oaBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Buffer
{
 public:

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

  /**
   * @brief prepares the internal things to be send to the gpu
  */
  virtual void
  init() = 0;

  /**
   * @brief sets the data of this buffer to an updated one
   * @param data the new data 
   * @param size the size of the new data
  */
  virtual void
  updateResourse(void* data,uint32 size) = 0;
 
 public:

  /**
   * @brief where the data is
  */
  void* pointer;

  /**
   * @brief the size of the data in bytes
  */
  uint32 size;
};

}


