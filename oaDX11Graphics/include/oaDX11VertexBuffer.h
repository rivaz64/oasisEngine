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

  bool
  init(void* data, uint32 vertexSize, uint32 numberOfVertices) override;


  void
  set() override;

 private:

  ID3D11Buffer* buffer = nullptr;

  uint32 vertexSize;

};

}