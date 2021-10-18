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

class DX11Buffer :
  public Buffer
{
 public:
  void
  init(void* data,uint32 size) override;

 private:
  ID3D11Buffer* buffer = nullptr;
};

}


