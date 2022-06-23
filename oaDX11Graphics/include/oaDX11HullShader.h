/**
* @file oaDX11HullShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 6/23/2021
*/

#pragma once
#include "oaDX11Shader.h"

namespace oaEngineSDK{

class DX11HullShader :
  public DX11Shader
{
 public:

  ~DX11HullShader();

  bool 
  compileFromFile(const String& file,const Vector<String>& defines) override;

  void
  set() override;

 private:

  ID3D11HullShader* m_shader = nullptr;

  friend class DX11GraphicAPI;
};

}


