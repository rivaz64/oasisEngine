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

  bool
  init(void* data,uint32 size,BUFFER_FLAGS flags) override;

  void
  update(void* data) override;

 public:

   unsigned int VBO, VAO, EBO;

   float pointer[16];
  //unsigned int id;
};

}


