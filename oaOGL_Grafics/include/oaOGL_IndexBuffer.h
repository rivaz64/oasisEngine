/**
* @file oaOGL_IndexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/1/2021
*/


#pragma once

#include "oaIndexBuffer.h"

namespace oaEngineSDK{

class OGL_IndexBuffer :
  public IndexBuffer
{
 public:

  bool
  init(Vector<uint32>& data) override;

  void
  set() override;

 private:
  uint32 id;
};

}


