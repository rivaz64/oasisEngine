/**
* @file oaDX11IndexBuffer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include <oaIndexBuffer.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11IndexBuffer :
  public IndexBuffer
{
 
 public:

  ~DX11IndexBuffer();

  bool
  init(Vector<uint32>& data) override;

  void
  set() override;

  void
  release() override;

 private:

  ID3D11Buffer* m_buffer = nullptr;

};

}


