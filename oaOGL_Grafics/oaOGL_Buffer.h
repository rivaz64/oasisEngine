/**
* @file oaOGL_Buffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once
#include "oaBuffer.h"

namespace oaEngineSDK{

class oaOGL_Buffer :
  public Buffer
{

 public:
  void
    init(void* data,uint32 size) override;

 private:

  unsigned int id;
};

}


