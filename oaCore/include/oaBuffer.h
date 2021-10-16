/**
* @file oaBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Buffer
{
 public:

  /**
   * @brief constructor default para el buffer
  */
  Buffer() = default;

  ~Buffer() = default;

  /**
  * @brief gets where the data of the buffer is
  * @return 
  */
  virtual void* 
    getPointer() {return nullptr;};


  /**
  * @brief gets the size of the data in bytes
  * @return 
  */
  virtual uint32 
    getSize() {return 0;};

  /**
   * @brief prepares the internal things to be send to the gpu
  */
  virtual void
  init() {};

  /**
   * @brief sets the data of this buffer to an updated one
   * @param data the new data 
   * @param size the size of the new data
  */
  virtual void
  updateResourse(void* data,uint32 size) {};
 
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


