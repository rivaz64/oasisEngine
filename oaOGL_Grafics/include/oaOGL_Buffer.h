/**
* @file oaOGL_Buffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once
#include "oaBuffer.h"

namespace oaEngineSDK{

class OGL_Buffer :
  public Buffer
{

 public:
   ~OGL_Buffer();

  void
  init(void* data,uint32 size) override;

 public:

   unsigned int VBO, VAO;
  //unsigned int id;
};

}


