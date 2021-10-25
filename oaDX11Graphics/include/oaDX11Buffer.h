/**
* @file oaDX11Buffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaBuffer.h"
#include <d3d11.h>
#include <Windows.h>
namespace oaEngineSDK{

enum class DX11BUFFER_FLAGS{
  VERTEX = D3D11_BIND_VERTEX_BUFFER,
  CONSTANT = D3D11_BIND_CONSTANT_BUFFER
};

class DX11Buffer :
  public Buffer
{
 public:

   ~DX11Buffer();

  void
  init(void* data,uint32 size,BUFFER_FLAGS flags) override;

  void
  update(void* data,uint32 size) override;

 public:
  ID3D11Buffer* buffer = nullptr;
};

}


