/**
* @file oaOGL_Buffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once
#include <oaBuffer.h>

namespace oaEngineSDK{

class OGL_Buffer :
  public Buffer
{

 public:
   ~OGL_Buffer();

  bool
  init(uint32 size) override;

  void
  write(void* data) override;


 public:

   //unsigned int VBO, VAO, EBO;

  uint32 m_id;
  uint32 m_size;

   //float pointer[16];
  //unsigned int id;
};

}


