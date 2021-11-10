/**
* @file oaDX11Buffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaBuffer.h"
#include <d3d11.h>
namespace oaEngineSDK{

class DX11Buffer :
  public Buffer
{
 public:

   ~DX11Buffer();

  bool
  init(void* data,uint32 size,BUFFER_FLAGS flags) override;

  void
  update(void* data) override;

 public:
  ID3D11Buffer* buffer = nullptr;
};

}


