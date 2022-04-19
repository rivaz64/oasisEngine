/**
* @file oaDX11VertexShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaDX11Shader.h"



namespace oaEngineSDK{

class DX11VertexShader :
public DX11Shader
{
 public:

  ~DX11VertexShader();

  bool 
  compileFromFile(const String& file,const Vector<String>& defines) override;

  void
  set() override;

 public:

  bool
  createInputLayout(ID3DBlob* blob);

  ID3D11VertexShader* m_shader = nullptr;

  ID3D11InputLayout* m_inputLayout = NULL;

  ID3DBlob*m_blob;

  friend class DX11GraphicAPI;
};

}


