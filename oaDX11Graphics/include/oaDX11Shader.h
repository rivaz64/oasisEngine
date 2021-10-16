/**
* @file oaDX11Shader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaShader.h"
#include <d3d11.h>


namespace oaEngineSDK{

class OA_DX11_EXPORT DX11Shader :
  public Shader
{
 public:

  bool 
  compileFromFile(String file);

 private:
  
  void
  createInputLayout(ID3DBlob*& blob);

  ID3D11VertexShader* g_pVertexShader = nullptr;


  ID3D11InputLayout* inputLayout = NULL;

};

}


