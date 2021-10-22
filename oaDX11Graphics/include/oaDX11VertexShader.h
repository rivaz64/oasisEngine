/**
* @file oaDX11VertexShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaDX11Shader.h"



namespace oaEngineSDK{

class DX11VertexShader :
public DX11Shader
{
 public:

  ~DX11VertexShader();

  bool 
  compileFromFile(String file);

 private:

  void
  createInputLayout(ID3DBlob*& blob);

  ID3D11VertexShader* shader = nullptr;

  ID3D11InputLayout* inputLayout = NULL;
};

}


