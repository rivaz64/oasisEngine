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
private:
  /**
  * @brief where the data of the buffer is
  */
  void* pointer;

  /**
   * @brief the size of the data in bytes
  */
  uint32 size;
};

}


