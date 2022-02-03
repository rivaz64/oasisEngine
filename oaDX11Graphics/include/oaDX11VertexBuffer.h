/**
* @file DX11VertexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaVertexBuffer.h"
#include <d3d11.h>

namespace oaEngineSDK{

class DX11VertexBuffer :
  public VertexBuffer
{

 public:

  bool
  init(void* data, uint64 vertexSize, uint64 numberOfVertices) override;

  void
  set() override;

 private:

  ID3D11Buffer* m_buffer = nullptr;

  uint64 m_vertexSize;

};

}