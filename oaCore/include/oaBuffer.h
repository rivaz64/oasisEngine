/**
* @file oaBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK{

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
   * @return if the buffer initialized correctly
  */
  virtual bool
  init(void* /*data*/, uint32 /*size*/, BIND /*flags*/) { return true; }

  /**
   * @brief changes the data of the buffer
   * @param data 
  */
  virtual void
  update(void* /*data*/){}

};

}


