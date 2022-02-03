/**
* @file oaOGL_VertexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/1/2021
*/

#pragma once

#include "oaVertexBuffer.h"

namespace oaEngineSDK{

class oaOGL_VertexBuffer :
  public VertexBuffer
{
 public:

  bool 
  compileFromFile(String file);

  void
  set() override;
};

}
